import sys
import random
import codecs
from collections import deque
from math import ceil

import serial
import serial.tools.list_ports

from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QGridLayout, QVBoxLayout,
    QHBoxLayout, QLabel, QComboBox, QTextEdit,
    QMessageBox, QGroupBox, QCheckBox
)
from PyQt6.QtCore import QThread, QTimer, pyqtSignal, Qt
from PyQt6.QtGui import QTextCursor


# ============================================================
# PARAMETERS OF FRAME (AS IN LABORATORY WORK 3)
# ============================================================

FRAME_FLAG = b"450502-1"
FLAG_SIZE = len(FRAME_FLAG)
MAX_FRAME_SIZE = 100
SERVICE_FIELD_SIZE = 1

FCS_BITS = 10
FCS_SIZE = 2
RESERVED_SIZE = 8

MAX_DATA_SIZE = (
    MAX_FRAME_SIZE
    - FLAG_SIZE
    - 3 * SERVICE_FIELD_SIZE
    - FCS_SIZE
    - RESERVED_SIZE
)

BODY_SIZE = MAX_FRAME_SIZE - FLAG_SIZE
BODY_BITS = BODY_SIZE * 8
MAX_STUFFED_BODY_SIZE = 2 * BODY_SIZE  # Не более одного вставленного бита на бит тела.

# Вероятности первого варианта применяются при прослушивании и попытке передачи байта.
CHANNEL_BUSY_PROBABILITY = 0.10
BYTE_COLLISION_PROBABILITY = 0.40
MAX_BYTE_ATTEMPTS = 16
BACKOFF_EXPONENT_LIMIT = 10
MIN_SLOT_MS = 10
UART_BITS_PER_BYTE = 10  # 8N1: стартовый бит, 8 бит данных, стоповый бит.

# Стаффинг исключает флаг из тела кадра. За настоящим флагом следует
# нулевой тип кадра, поэтому флаг с 0xff однозначно обозначает jam.
JAM_SIGNAL = FRAME_FLAG + b'\xff'

# Field order in the transmitted body (on the wire):
# type, number, checksum, data, FCS, reserved.
TYPE_OFFSET = 0
NUMBER_OFFSET = 1
CHECKSUM_OFFSET = 2
DATA_OFFSET = 3
DATA_END = DATA_OFFSET + MAX_DATA_SIZE
FCS_OFFSET = DATA_END
RESERVED_OFFSET = FCS_OFFSET + FCS_SIZE

GENERATOR_POLY = 0b10000001001
GENERATOR_DEGREE = 10
CODEWORD_BITS = MAX_DATA_SIZE * 8 + FCS_BITS


def bytes_to_bits(data: bytes) -> str:
    return ''.join(f'{byte:08b}' for byte in data)


FLAG_BITS = bytes_to_bits(FRAME_FLAG)
FLAG_MASK = FLAG_BITS[:-1]
MASK_SIZE = len(FLAG_MASK)


def bits_to_bytes(bits: str) -> bytes:
    if len(bits) % 8:
        bits += '0' * (8 - len(bits) % 8)
    return bytes(
        int(bits[i:i + 8], 2)
        for i in range(0, len(bits), 8)
    )


# ============================================================
# CYCLIC ERROR-CORRECTING CODE
# ============================================================

def polynomial_remainder(value: int, divisor: int) -> int:
    divisor_degree = divisor.bit_length() - 1
    while value and value.bit_length() - 1 >= divisor_degree:
        shift = value.bit_length() - 1 - divisor_degree
        value ^= divisor << shift
    return value


def calculate_fcs(data: bytes) -> int:
    if len(data) != MAX_DATA_SIZE:
        raise ValueError('FCS calculation requires exactly 79 data bytes.')
    data_value = int(bytes_to_bits(data), 2)
    return polynomial_remainder(data_value << FCS_BITS, GENERATOR_POLY)


def fcs_to_bytes(fcs_value: int) -> bytes:
    bits = f'{fcs_value:010b}' + '000000'
    return bits_to_bytes(bits)


def fcs_from_bytes(fcs_bytes: bytes) -> int:
    return int(bytes_to_bits(fcs_bytes)[:FCS_BITS], 2)


def syndrome_for_codeword(data: bytes, fcs_value: int) -> int:
    value = (int(bytes_to_bits(data), 2) << FCS_BITS) | fcs_value
    return polynomial_remainder(value, GENERATOR_POLY)


def find_single_bit_position(syndrome: int):
    """Поиск одиночной ошибки вычислением остатков, без таблицы."""
    found_position = None
    for position in range(CODEWORD_BITS):
        # Позиции считаются слева, степени полинома — справа.
        exponent = CODEWORD_BITS - 1 - position
        # Ошибка в одном бите соответствует полиному x**exponent.
        # Делим его на G(x) по модулю 2, как при ручном расчёте.
        error_syndrome = polynomial_remainder(
            1 << exponent, GENERATOR_POLY
        )
        if error_syndrome == syndrome:
            if found_position is not None:
                # Несколько подходящих позиций: однозначного решения нет.
                return None
            found_position = position
    return found_position


def correct_single_bit_error(data: bytes, fcs_value: int):
    if len(data) != MAX_DATA_SIZE or not 0 <= fcs_value < (1 << FCS_BITS):
        raise ValueError('Invalid data length or FCS value.')

    # Синдром: остаток от деления принятого слова Data + FCS на G(x).
    syndrome = syndrome_for_codeword(data, fcs_value)
    if syndrome == 0:
        return data, fcs_value, None, True

    # Вычисляем остатки для возможных позиций прямо при приёме.
    position = find_single_bit_position(syndrome)
    if position is None:
        return data, fcs_value, None, False

    data_bit_count = len(data) * 8
    corrected_data = data
    corrected_fcs = fcs_value

    if position < data_bit_count:
        byte_index, bit_index = divmod(position, 8)
        data_bytes = bytearray(data)
        data_bytes[byte_index] ^= 1 << (7 - bit_index)
        corrected_data = bytes(data_bytes)
        correction = ('data', position)
    else:
        fcs_position = position - data_bit_count
        corrected_fcs ^= 1 << (FCS_BITS - 1 - fcs_position)
        correction = ('fcs', fcs_position)

    # Проверяем исправленное слово повторным делением.
    valid = syndrome_for_codeword(corrected_data, corrected_fcs) == 0
    if not valid:
        return data, fcs_value, None, False
    return corrected_data, corrected_fcs, correction, True


# ============================================================
# FRAME
# ============================================================

class Frame:
    def __init__(self, data: bytes):
        if len(data) > MAX_DATA_SIZE:
            raise ValueError('The data field exceeds the allowed size of 79 bytes.')
        self.data = data.ljust(MAX_DATA_SIZE, b'\x00')
        self.frame_type = 0
        self.frame_number = 0
        self.checksum = 0
        self.fcs_value = calculate_fcs(self.data)
        self.fcs_bytes = fcs_to_bytes(self.fcs_value)
        self.reserved = bytes(RESERVED_SIZE)

    def body_bytes(self) -> bytes:
        body = (
            bytes([self.frame_type, self.frame_number, self.checksum])
            + self.data
            + self.fcs_bytes
            + self.reserved
        )
        if len(body) != BODY_SIZE:
            raise ValueError(f'Incorrect body length: {len(body)} instead of {BODY_SIZE}.')
        return body

    def to_bytes(self) -> bytes:
        frame = FRAME_FLAG + self.body_bytes()
        if len(frame) != MAX_FRAME_SIZE:
            raise ValueError('The frame must be exactly 100 bytes before stuffing.')
        return frame


# ============================================================
# BIT STUFFING AND DESTUFFING
# ============================================================

def bit_stuff_with_map(bits: str):
    result = []
    logical_to_raw = []
    tail = ''
    for bit in bits:
        logical_to_raw.append(len(result))
        result.append(bit)
        tail = (tail + bit)[-MASK_SIZE:]
        if tail == FLAG_MASK:
            result.append('0')
            tail = (tail + '0')[-MASK_SIZE:]
    return ''.join(result), logical_to_raw


def destuff_body(raw_bits: str):
    output = []
    tail = ''
    expect_stuffed_zero = False
    consumed = 0
    for bit in raw_bits:
        consumed += 1
        if expect_stuffed_zero:
            if bit != '0':
                raise ValueError('Invalid bit stuffing: expected an inserted zero.')
            tail = (tail + bit)[-MASK_SIZE:]
            expect_stuffed_zero = False
            if len(output) == BODY_BITS:
                break
            continue
        output.append(bit)
        tail = (tail + bit)[-MASK_SIZE:]
        if tail == FLAG_MASK:
            expect_stuffed_zero = True
        if len(output) == BODY_BITS and not expect_stuffed_zero:
            break
    if len(output) != BODY_BITS or expect_stuffed_zero:
        return None, 0
    return ''.join(output), consumed


def safe_data_error_positions(stuffed_bits: str, logical_to_raw):
    mask_value = int(FLAG_MASK, 2)
    unsafe_raw = set()
    for start in range(max(0, len(stuffed_bits) - MASK_SIZE + 1)):
        window = stuffed_bits[start:start + MASK_SIZE]
        if len(window) != MASK_SIZE:
            continue
        if (int(window, 2) ^ mask_value).bit_count() <= 1:
            unsafe_raw.update(range(start, start + MASK_SIZE))
    safe_by_byte = {}
    for bit_in_field in range(MAX_DATA_SIZE * 8):
        logical_position = DATA_OFFSET * 8 + bit_in_field
        raw_position = logical_to_raw[logical_position]
        if raw_position not in unsafe_raw:
            byte_index = bit_in_field // 8
            safe_by_byte.setdefault(byte_index, []).append(
                (logical_position, raw_position)
            )
    if not safe_by_byte:
        return [
            (DATA_OFFSET * 8 + i, logical_to_raw[DATA_OFFSET * 8 + i])
            for i in range(MAX_DATA_SIZE * 8)
        ]
    chosen_byte = random.choice(list(safe_by_byte.keys()))
    return safe_by_byte[chosen_byte]


# ============================================================
# DISPLAY HELPERS
# ============================================================

def format_field_bits(data: bytes) -> str:
    return ','.join(f'{byte:08b}' for byte in data)


def bits_html(bits: str, underlined_positions=None, group_bytes=True) -> str:
    underlined_positions = set(underlined_positions or [])
    tokens = []
    for i, bit in enumerate(bits):
        if i in underlined_positions:
            tokens.append(f'<u>{bit}</u>')
        else:
            tokens.append(bit)
    if group_bytes:
        groups = [''.join(tokens[i:i + 8]) for i in range(0, len(tokens), 8)]
        return ','.join(groups)
    return ''.join(tokens)


# ============================================================
# SERIAL PORT READER THREAD
# ============================================================

class SerialReaderThread(QThread):
    data_received = pyqtSignal(bytes)
    error_occurred = pyqtSignal(str)

    def __init__(self, serial_port):
        super().__init__()
        self.serial_port = serial_port
        self.running = True

    def run(self):
        while self.running:
            try:
                if (self.serial_port and self.serial_port.is_open
                        and self.serial_port.in_waiting):
                    chunk = self.serial_port.read(self.serial_port.in_waiting)
                    if chunk:
                        self.data_received.emit(chunk)
                else:
                    self.msleep(30)
            except Exception as exc:
                if self.running:
                    self.error_occurred.emit(f'Read error: {exc}')
                self.msleep(250)

    def stop(self):
        self.running = False
        self.wait(1500)


# ============================================================
# INPUT TEXT FIELD
# ============================================================

class CharTextEdit(QTextEdit):
    char_pressed = pyqtSignal(str)

    def __init__(self, parent=None):
        super().__init__(parent)
        self.cursorPositionChanged.connect(self._lock_cursor_to_end)

    def _lock_cursor_to_end(self):
        cursor = self.textCursor()
        if not cursor.atEnd():
            cursor.movePosition(QTextCursor.MoveOperation.End)
            self.setTextCursor(cursor)

    def mousePressEvent(self, event):
        super().mousePressEvent(event)
        self.moveCursor(QTextCursor.MoveOperation.End)

    def mouseDoubleClickEvent(self, event):
        self.moveCursor(QTextCursor.MoveOperation.End)

    def keyPressEvent(self, event):
        if event.key() in (Qt.Key.Key_Backspace, Qt.Key.Key_Delete):
            event.accept()
            return
        if event.key() in (
            Qt.Key.Key_Left, Qt.Key.Key_Up,
            Qt.Key.Key_Home, Qt.Key.Key_PageUp
        ):
            self.moveCursor(QTextCursor.MoveOperation.End)
            event.accept()
            return
        if event.key() in (Qt.Key.Key_Return, Qt.Key.Key_Enter):
            self.char_pressed.emit('\n')
            super().keyPressEvent(event)
            self.moveCursor(QTextCursor.MoveOperation.End)
            return
        if event.text() and event.text().isprintable():
            self.char_pressed.emit(event.text())
        super().keyPressEvent(event)
        self.moveCursor(QTextCursor.MoveOperation.End)


# ============================================================
# MAIN APPLICATION
# ============================================================

class ComPortApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.serial = serial.Serial()
        self.reader_thread = None

        self.tx_buffer = bytearray()
        self.tx_count = 0
        self.tx_queue = deque()
        self.tx_wire = b''
        self.tx_byte_index = 0
        self.tx_byte_attempts = 0
        self.tx_frame_chars = 0
        self.tx_collisions = 0
        self.tx_frame_html = ''
        # Одна последовательность попыток в основном цикле Qt. Таймер
        # освобождает интерфейс на время прослушивания и backoff.
        self.tx_timer = QTimer(self)
        self.tx_timer.setSingleShot(True)
        self.tx_timer.setTimerType(Qt.TimerType.PreciseTimer)
        self.tx_timer.timeout.connect(self.transmit_next)

        self.rx_buffer = bytearray()
        self.receiving_frame = False
        self.rx_wire = bytearray()
        self.rx_byte_collisions = 0

        self.rx_decoder = codecs.getincrementaldecoder('utf-8')(errors='replace')
        self.init_ui()

    def init_ui(self):
        self.setWindowTitle("COM-порт Мессенджер_1")
        self.resize(560, 480)
        self.setStyleSheet("QWidget { font-size: 14px; }")

        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        layout = QVBoxLayout(central_widget)

        control_group = QGroupBox("Окно управления")
        ctrl_layout = QHBoxLayout()

        self.port_combo = QComboBox()
        self.port_combo.setEditable(False)
        self.update_ports()
        self.port_combo.currentTextChanged.connect(self.try_open_port)

        self.baudrate_combo = QComboBox()
        self.baudrate_combo.addItems([
            "110", "300", "600", "1200", "2400", "4800", "9600",
            "14400", "19200", "38400", "57600", "115200"
        ])
        self.baudrate_combo.setCurrentText("9600")
        self.baudrate_combo.currentTextChanged.connect(self.update_baudrate)

        ctrl_layout.addWidget(QLabel("COM-порт:"))
        ctrl_layout.addWidget(self.port_combo)
        ctrl_layout.addWidget(QLabel("Скорость:"))
        ctrl_layout.addWidget(self.baudrate_combo)

        self.error_checkbox = QCheckBox("Эмуляция ошибок (10%)")
        self.error_checkbox.setChecked(False)
        ctrl_layout.addWidget(self.error_checkbox)

        self.csma_checkbox = QCheckBox("CSMA/CD")
        self.csma_checkbox.setToolTip("Эмуляция доступа к моноканалу")
        self.csma_checkbox.setAutoFillBackground(True)
        control_group.setLayout(ctrl_layout)

        # Переключатель занимает свободное место справа в заголовке группы.
        # Основной ряд управления и размеры окон ввода и вывода сохраняются.
        control_area = QWidget()
        control_layout = QGridLayout(control_area)
        control_layout.setContentsMargins(0, 0, 0, 0)
        control_layout.addWidget(control_group, 0, 0)
        header_layout = QHBoxLayout()
        header_layout.setContentsMargins(0, 0, 10, 0)
        header_layout.addStretch()
        header_layout.addWidget(self.csma_checkbox, alignment=Qt.AlignmentFlag.AlignTop)
        control_layout.addLayout(header_layout, 0, 0)
        layout.addWidget(control_area)

        layout.addWidget(QLabel("Окно ввода:"))
        self.input_field = CharTextEdit()
        self.input_field.setMinimumHeight(100)
        self.input_field.char_pressed.connect(self.send_data)
        layout.addWidget(self.input_field)

        layout.addWidget(QLabel("Окно вывода:"))
        self.output_field = QTextEdit()
        self.output_field.setReadOnly(True)
        layout.addWidget(self.output_field)

        status_group = QGroupBox("Окно статуса")
        status_layout = QVBoxLayout()

        self.status_label = QLabel("Передано символов: 0")
        self.status_label.setStyleSheet("font-weight: bold;")
        status_layout.addWidget(self.status_label)

        self.frame_state = QTextEdit()
        self.frame_state.setReadOnly(True)
        status_layout.addWidget(self.frame_state)

        status_group.setLayout(status_layout)
        layout.addWidget(status_group)

        # Заголовок в порядке отображения: Данные — четвёртыми.
        self.frame_state.setPlainText(
            "Флаг Тип_кадра Номер_кадра Данные "
            "Контрольная_сумма FCS"
        )

    # ========================================================
    # PORT MANAGEMENT
    # ========================================================

    def update_ports(self):
        self.port_combo.clear()
        self.port_combo.addItem('')
        ports = {port.device for port in serial.tools.list_ports.comports()}
        if sys.platform == 'win32':
            # Драйверы виртуальных портов могут регистрировать имена только здесь.
            import winreg

            try:
                with winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, r'HARDWARE\DEVICEMAP\SERIALCOMM') as key:
                    for index in range(winreg.QueryInfoKey(key)[1]):
                        _, name, kind = winreg.EnumValue(key, index)
                        if kind == winreg.REG_SZ and name:
                            ports.add(name)
            except OSError:
                pass
        self.port_combo.addItems(sorted(ports))
        self.port_combo.setCurrentIndex(0)

    def get_baudrate(self):
        try:
            return int(self.baudrate_combo.currentText())
        except ValueError:
            return 9600

    def try_open_port(self, port_name):
        port_name = port_name.strip()
        if not port_name:
            return
        try:
            if self.serial.is_open:
                if self.reader_thread:
                    self.reader_thread.stop()
                    self.reader_thread = None
                self.serial.close()

            # Windows требует путь устройства для имён вроде CNCA0 у com0com.
            if sys.platform == 'win32' and not port_name.startswith('\\\\.\\'):
                port_name = '\\\\.\\' + port_name
            self.serial.port = port_name
            self.serial.baudrate = self.get_baudrate()
            self.serial.parity = serial.PARITY_NONE
            self.serial.stopbits = serial.STOPBITS_ONE
            self.serial.bytesize = serial.EIGHTBITS
            self.serial.timeout = 0.1
            self.serial.open()

            self.port_combo.setEnabled(False)
            self.tx_timer.stop()
            self.tx_wire = b''
            self.tx_queue.clear()
            self.tx_buffer.clear()
            self.rx_buffer.clear()
            self.receiving_frame = False
            self.rx_wire.clear()
            self.rx_byte_collisions = 0
            self.rx_decoder.reset()

            self.reader_thread = SerialReaderThread(self.serial)
            self.reader_thread.data_received.connect(self.receive_data)
            self.reader_thread.error_occurred.connect(self.show_error)
            self.reader_thread.start()

        except Exception as exc:
            self.show_error(f'Не удалось открыть порт: {exc}')
            self.port_combo.setCurrentIndex(0)

    def update_baudrate(self):
        new_baud = self.get_baudrate()
        if not self.serial.is_open or self.tx_wire or self.serial.baudrate == new_baud:
            return
        try:
            # Меняем скорость между кадрами, включая последние байты в драйвере.
            self.serial.flush()
            if self.reader_thread:
                self.reader_thread.stop()
                self.reader_thread = None
            self.serial.close()
            self.serial.baudrate = new_baud
            self.serial.open()

            self.reader_thread = SerialReaderThread(self.serial)
            self.reader_thread.data_received.connect(self.receive_data)
            self.reader_thread.error_occurred.connect(self.show_error)
            self.reader_thread.start()
        except Exception as exc:
            if not self.serial.is_open:
                self.port_combo.setEnabled(True)
                self.port_combo.setCurrentIndex(0)
            self.show_error(f'Не удалось изменить скорость: {exc}')

    # ========================================================
    # DATA TRANSMISSION
    # ========================================================

    def send_data(self, char: str):
        if not self.serial.is_open:
            self.show_error('Сначала выберите COM-порт.')
            return
        try:
            self.tx_buffer.extend(char.encode('utf-8'))
        except UnicodeEncodeError as exc:
            self.show_error(f'Ошибка передачи: {exc}')
            return

        while len(self.tx_buffer) >= MAX_DATA_SIZE:
            block = bytes(self.tx_buffer[:MAX_DATA_SIZE])
            del self.tx_buffer[:MAX_DATA_SIZE]
            # У каждого символа UTF-8 ровно один байт с префиксом, отличным от 10.
            chars_in_frame = sum(byte & 0xC0 != 0x80 for byte in block)
            self.tx_queue.append((block, chars_in_frame))
        if self.tx_queue and not self.tx_wire and not self.tx_timer.isActive():
            self.tx_timer.start(0)

    def transmit_next(self):
        if not self.serial.is_open:
            return
        try:
            if self.tx_wire:
                self.transmit_csma_byte()
            elif self.tx_queue:
                self.start_frame(*self.tx_queue.popleft())
        except Exception as exc:
            self.finish_frame(f'Ошибка передачи кадра: {exc}')

    def start_frame(self, data: bytes, chars_in_frame: int):
        frame = Frame(data)
        body_bits = bytes_to_bits(frame.body_bytes())
        stuffed_bits, logical_to_raw = bit_stuff_with_map(body_bits)
        errored_bits = stuffed_bits
        error_raw_position = None

        # Эмуляция ошибки ЛР3 независима от CSMA/CD.
        if self.error_checkbox.isChecked() and random.random() < 0.1:
            candidates = safe_data_error_positions(stuffed_bits, logical_to_raw)
            _, error_raw_position = random.choice(candidates)
            raw = list(stuffed_bits)
            raw[error_raw_position] = str(int(raw[error_raw_position]) ^ 1)
            errored_bits = ''.join(raw)

        self.tx_frame_chars = chars_in_frame
        self.tx_collisions = 0
        self.show_last_frame(frame, body_bits, stuffed_bits, errored_bits, error_raw_position)

        wire_bytes = FRAME_FLAG + bits_to_bytes(errored_bits)
        if self.csma_checkbox.isChecked():
            self.tx_wire = wire_bytes
            self.tx_byte_index = 0
            self.tx_byte_attempts = 0
            self.tx_timer.start(0)
        else:
            self.write_bytes(wire_bytes)
            self.finish_frame()

    def write_bytes(self, data: bytes):
        written = self.serial.write(data)
        if written != len(data):
            raise IOError(f'Передано {written} из {len(data)} байт.')

    def wire_time_ms(self, byte_count: int) -> int:
        return ceil(1000 * UART_BITS_PER_BYTE * byte_count / self.serial.baudrate)

    def transmit_csma_byte(self):
        if self.tx_byte_index == len(self.tx_wire):
            self.finish_frame()
            return
        if self.tx_byte_attempts == MAX_BYTE_ATTEMPTS:
            self.finish_frame(f'Не удалось передать кадр за {MAX_BYTE_ATTEMPTS} попыток на байт.')
            return

        # Слот длиннее jam на один байт, минимум 10 мс для таймера Qt.
        slot_ms = max(MIN_SLOT_MS, self.wire_time_ms(len(JAM_SIGNAL) + 1))
        if random.random() < CHANNEL_BUSY_PROBABILITY:
            self.tx_timer.start(slot_ms)
            return

        if random.random() < BYTE_COLLISION_PROBABILITY:
            # Jam занимает место неудавшейся попытки. Индекс байта остаётся
            # прежним, чтобы после задержки заново попытаться передать его.
            self.write_bytes(JAM_SIGNAL)
            self.tx_byte_attempts += 1
            self.tx_collisions += 1
            self.refresh_frame_state()

            delay_ms = self.wire_time_ms(len(JAM_SIGNAL))
            if self.tx_byte_attempts < MAX_BYTE_ATTEMPTS:
                # IEEE 802.3: задержка r * slot, где 0 <= r < 2**min(n, 10).
                k = min(self.tx_byte_attempts, BACKOFF_EXPONENT_LIMIT)
                delay_ms += random.randrange(2 ** k) * slot_ms
            self.tx_timer.start(delay_ms)
            return

        self.write_bytes(self.tx_wire[self.tx_byte_index:self.tx_byte_index + 1])
        self.tx_byte_index += 1
        self.tx_byte_attempts = 0
        self.tx_timer.start(self.wire_time_ms(1))

    def finish_frame(self, error=None):
        self.tx_wire = b''
        if error is None:
            self.tx_count += self.tx_frame_chars
            self.status_label.setText(f'Передано символов: {self.tx_count}')
        else:
            self.show_error(error)
        self.update_baudrate()
        if self.tx_queue and self.serial.is_open:
            self.tx_timer.start(0)

    # ========================================================
    # FRAME DISPLAY
    # Порядок отображения: Флаг, Тип_кадра, Номер_кадра,
    # Данные (4-е), Контрольная_сумма, FCS.
    # Подчёркивание как в lab3.py:
    #   строка 2 — только вставленные нули;
    #   строка 3 — только инвертированный бит ошибки.
    # ========================================================

    def show_last_frame(
        self,
        frame,
        before_bits,
        stuffed_bits,
        errored_bits,
        error_raw_position=None
    ):
        body = frame.body_bytes()
        flag_bits = bytes_to_bits(FRAME_FLAG)

        _, logical_to_raw = bit_stuff_with_map(before_bits)

        inserted_raw_positions = {
            logical_to_raw[i] + 1
            for i in range(len(logical_to_raw) - 1)
            if logical_to_raw[i + 1] > logical_to_raw[i] + 1
        }

        fields = [
            ('Флаг', flag_bits, None, None),
            ('Тип_кадра',
             bytes_to_bits(body[TYPE_OFFSET:TYPE_OFFSET + 1]),
             TYPE_OFFSET * 8, (TYPE_OFFSET + 1) * 8),
            ('Номер_кадра',
             bytes_to_bits(body[NUMBER_OFFSET:NUMBER_OFFSET + 1]),
             NUMBER_OFFSET * 8, (NUMBER_OFFSET + 1) * 8),
            ('Данные',
             bytes_to_bits(body[DATA_OFFSET:DATA_END]),
             DATA_OFFSET * 8, DATA_END * 8),
            ('Контрольная_сумма',
             bytes_to_bits(body[CHECKSUM_OFFSET:CHECKSUM_OFFSET + 1]),
             CHECKSUM_OFFSET * 8, (CHECKSUM_OFFSET + 1) * 8),
            ('FCS',
             bytes_to_bits(body[FCS_OFFSET:FCS_OFFSET + FCS_SIZE]),
             FCS_OFFSET * 8, (FCS_OFFSET + FCS_SIZE) * 8),
        ]

        labels = ' '.join(item[0] for item in fields)
        before_values = []
        after_values = []
        error_values = []

        for (label, bits, logical_start, logical_end) in fields:
            # Флаг передаётся без стаффинга — одинаков во всех строках.
            if logical_start is None:
                before_values.append(bits_html(bits))
                after_values.append(bits_html(bits))
                error_values.append(bits_html(bits))
                continue

            # Первая строка: исходные биты, без подчёркиваний.
            before_values.append(bits_html(bits))

            raw_start = logical_to_raw[logical_start]
            if logical_end < len(logical_to_raw):
                raw_end = logical_to_raw[logical_end]
            else:
                raw_end = len(stuffed_bits)

            stuffed_field = stuffed_bits[raw_start:raw_end]

            # Вторая строка: подчёркнуты только вставленные нули.
            inserted_in_field = [
                position - raw_start
                for position in inserted_raw_positions
                if raw_start <= position < raw_end
            ]
            after_values.append(
                bits_html(stuffed_field, inserted_in_field, group_bytes=True)
            )

            # Третья строка: подчёркнут только бит ошибки.
            # Вставленные нули здесь НЕ подчёркиваются.
            error_underlines = []
            if (error_raw_position is not None
                    and raw_start <= error_raw_position < raw_end):
                error_underlines.append(error_raw_position - raw_start)

            error_values.append(
                bits_html(
                    errored_bits[raw_start:raw_end],
                    error_underlines,
                    group_bytes=True
                )
            )

        # Неразрывные пробелы между полями — чтобы QTextEdit
        # не переносил строку после «Флага».
        labels_html = labels.replace(' ', '&nbsp;')
        before_html = ' '.join(before_values).replace(' ', '&nbsp;')
        after_html = ' '.join(after_values).replace(' ', '&nbsp;')
        error_html = ' '.join(error_values).replace(' ', '&nbsp;')

        self.tx_frame_html = (
            f'{labels_html}<br>'
            f'{before_html}<br>'
            f'{after_html}<br>'
            f'{error_html}'
        )
        self.refresh_frame_state()

    def refresh_frame_state(self):
        collision_line = ''
        if self.tx_collisions:
            stars = ' '.join(['*'] * self.tx_collisions)
            collision_line = f'Коллизии: {stars}<br>'
        self.frame_state.setHtml(
            f'<div style="white-space: pre-wrap;">{collision_line}{self.tx_frame_html}</div>'
        )

    # ========================================================
    # DATA RECEPTION
    # ========================================================

    def _append_question_marks(self, count: int):
        if count <= 0:
            return
        self.output_field.moveCursor(QTextCursor.MoveOperation.End)
        self.output_field.insertPlainText('?' * count)
        self.output_field.ensureCursorVisible()

    def receive_data(self, raw_data: bytes):
        self.rx_wire.extend(raw_data)
        while (jam_pos := self.rx_wire.find(JAM_SIGNAL)) >= 0:
            self.receive_frame_bytes(self.rx_wire[:jam_pos])
            del self.rx_wire[:jam_pos + len(JAM_SIGNAL)]
            self.rx_byte_collisions += 1
            if self.rx_byte_collisions == MAX_BYTE_ATTEMPTS:
                # Отправитель прекратил передачу кадра. Следующие данные
                # принимаем с нового флага, сбросив неполный символ UTF-8.
                self.rx_buffer.clear()
                self.receiving_frame = False
                self.rx_decoder.reset()

        # Сохраняем только возможное начало jam между чтениями из COM-порта.
        end = len(self.rx_wire)
        for size in range(len(JAM_SIGNAL) - 1, 0, -1):
            if self.rx_wire.endswith(JAM_SIGNAL[:size]):
                end -= size
                break
        self.receive_frame_bytes(self.rx_wire[:end])
        del self.rx_wire[:end]

    def receive_frame_bytes(self, data: bytes):
        if not data:
            return
        self.rx_byte_collisions = 0
        self.rx_buffer.extend(data)

        while True:
            if not self.receiving_frame:
                flag_pos = self.rx_buffer.find(FRAME_FLAG)
                if flag_pos < 0:
                    keep = max(0, FLAG_SIZE - 1)
                    if len(self.rx_buffer) > keep:
                        discarded = len(self.rx_buffer) - keep
                        del self.rx_buffer[:-keep]
                        self._append_question_marks(discarded)
                    return
                del self.rx_buffer[:flag_pos + FLAG_SIZE]
                self.receiving_frame = True

            # При backoff пауза между байтами не означает обрыв кадра.
            # Если кадр действительно оборвался, следующий флаг отделит его.
            next_flag = self.rx_buffer.find(FRAME_FLAG, 0, MAX_STUFFED_BODY_SIZE + FLAG_SIZE)
            end = next_flag if next_flag >= 0 else MAX_STUFFED_BODY_SIZE
            try:
                logical_bits, raw_consumed_bits = destuff_body(bytes_to_bits(self.rx_buffer[:end]))
                if logical_bits is None:
                    if next_flag < 0:
                        return
                    raise ValueError('Неполный кадр перед следующим флагом.')
            except ValueError:
                self._append_question_marks(8)
                self.receiving_frame = False
                self.rx_decoder.reset()
                del self.rx_buffer[:next_flag if next_flag >= 0 else 1]
                continue

            consumed_bytes = (raw_consumed_bits + 7) // 8
            del self.rx_buffer[:consumed_bytes]
            self.receiving_frame = False

            try:
                body = bits_to_bytes(logical_bits)
                if len(body) != BODY_SIZE:
                    raise ValueError('Received body has an incorrect length.')

                data = body[DATA_OFFSET:DATA_END]
                fcs_value = fcs_from_bytes(body[FCS_OFFSET:FCS_OFFSET + FCS_SIZE])

                (corrected_data, corrected_fcs,
                 correction, valid) = correct_single_bit_error(data, fcs_value)

                if not valid:
                    self._append_question_marks(8)
                    self.rx_decoder.reset()
                    continue

                payload = corrected_data.rstrip(b'\x00')
                text = self.rx_decoder.decode(payload, final=False)
                if text:
                    self.output_field.moveCursor(QTextCursor.MoveOperation.End)
                    self.output_field.insertPlainText(text)
                    self.output_field.ensureCursorVisible()

            except Exception as exc:
                self.output_field.append(f'[Ошибка приёма кадра] {exc}')

    # ========================================================
    # ERRORS AND APPLICATION CLOSING
    # ========================================================

    def show_error(self, message: str):
        QMessageBox.warning(self, 'Ошибка', message)

    def closeEvent(self, event):
        self.tx_timer.stop()
        try:
            if self.reader_thread:
                self.reader_thread.stop()
                self.reader_thread = None
            if self.serial.is_open:
                self.serial.close()
        except Exception:
            pass
        event.accept()


# ============================================================
# MAIN
# ============================================================

def main():
    app = QApplication(sys.argv)
    window = ComPortApp()
    window.show()
    sys.exit(app.exec())


if __name__ == '__main__':
    main()
