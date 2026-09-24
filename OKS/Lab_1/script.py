import sys
import serial
import serial.tools.list_ports
from PyQt6.QtWidgets import (QApplication, QMainWindow, QWidget, QVBoxLayout,
                             QHBoxLayout, QLabel, QComboBox,
                             QTextEdit, QLineEdit, QMessageBox, QGroupBox)
from PyQt6.QtCore import QThread, pyqtSignal, Qt


class SerialReaderThread(QThread):
    data_received = pyqtSignal(str)
    error_occurred = pyqtSignal(str)

    def __init__(self, serial_port):
        super().__init__()
        self.serial_port = serial_port
        self.running = True

    def run(self):
        while self.running:
            if self.serial_port and self.serial_port.is_open:
                try:
                    if self.serial_port.in_waiting > 0:
                        raw_data = self.serial_port.read(self.serial_port.in_waiting)
                        text_data = raw_data.decode('utf-8', errors='replace')
                        if text_data:
                            self.data_received.emit(text_data)
                    else:
                        self.msleep(40)
                except Exception as e:
                    self.error_occurred.emit(f"Ошибка чтения данных: {e}")
                    self.msleep(1000)

    def stop(self):
        self.running = False
        self.wait()


class CharLineEdit(QLineEdit):
    char_pressed = pyqtSignal(str)

    def __init__(self, parent=None):
        super().__init__(parent)
        self.cursorPositionChanged.connect(self._lock_cursor_to_end)

    def _lock_cursor_to_end(self):
        end_pos = len(self.text())
        if self.cursorPosition() != end_pos:
            self.setCursorPosition(end_pos)

    def mousePressEvent(self, event):
        super().mousePressEvent(event)
        self.end(False)

    def mouseDoubleClickEvent(self, event):
        self.end(False)

    def keyPressEvent(self, event):
        forbidden_keys = (
            Qt.Key.Key_Left,
            Qt.Key.Key_Up,
            Qt.Key.Key_Home,
            Qt.Key.Key_PageUp
        )
        if event.key() in forbidden_keys:
            self.end(False)
            event.accept()
            return

        if event.key() in (Qt.Key.Key_Return, Qt.Key.Key_Enter):
            self.char_pressed.emit('\n')
        elif event.text():
            self.char_pressed.emit(event.text())

        super().keyPressEvent(event)
        self.end(False)


class ComPortApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.serial = serial.Serial()
        self.reader_thread = None
        self.tx_count = 0
        self.init_ui()

    def init_ui(self):
        self.setWindowTitle("COM-порт Мессенджер_2")
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
        self.port_combo.currentTextChanged.connect(self.try_lock_and_open_port)

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
        control_group.setLayout(ctrl_layout)
        layout.addWidget(control_group)

        layout.addWidget(QLabel("Строка ввода (посимвольная передача):"))
        self.input_field = CharLineEdit()
        self.input_field.char_pressed.connect(self.send_data)
        layout.addWidget(self.input_field)

        layout.addWidget(QLabel("Окно вывода (принятые сообщения):"))
        self.output_field = QTextEdit()
        self.output_field.setReadOnly(True)
        layout.addWidget(self.output_field)

        status_group = QGroupBox("Окно статуса")
        status_layout = QVBoxLayout()
        self.status_label = QLabel("Передано символов: 0")
        self.status_label.setStyleSheet("color: #0055aa; font-weight: bold;")
        status_layout.addWidget(self.status_label)
        status_group.setLayout(status_layout)
        layout.addWidget(status_group)

    def update_ports(self):
        self.port_combo.clear()
        self.port_combo.addItem("")
        ports = [p.device for p in serial.tools.list_ports.comports()]
        if ports:
            self.port_combo.addItems(sorted(ports))
        self.port_combo.setCurrentIndex(0)

    def get_current_baudrate(self) -> int:
        try:
            return int(self.baudrate_combo.currentText())
        except ValueError:
            return 9600

    def try_lock_and_open_port(self, port_name):
        port_name = port_name.strip()
        if not port_name or port_name == "":
            return

        baudrate = self.get_current_baudrate()

        try:
            if self.serial.is_open:
                if self.reader_thread:
                    self.reader_thread.stop()
                    self.reader_thread = None
                self.serial.close()

            self.serial.port = port_name
            self.serial.baudrate = baudrate
            self.serial.parity = serial.PARITY_NONE
            self.serial.stopbits = serial.STOPBITS_ONE
            self.serial.bytesize = serial.EIGHTBITS
            self.serial.timeout = 0.1

            self.serial.open()
            self.port_combo.setEnabled(False)

            self.reader_thread = SerialReaderThread(self.serial)
            self.reader_thread.data_received.connect(self.receive_data)
            self.reader_thread.error_occurred.connect(self.show_error)
            self.reader_thread.start()

            self.status_label.setText(f"Передано символов: {self.tx_count}")
        except Exception as e:
            self.show_error(f"Не удалось открыть порт {port_name}: {e}")
            self.port_combo.setCurrentIndex(0)
            if self.serial.is_open:
                self.serial.close()

    def update_baudrate(self):
        if not self.serial.is_open:
            return
        try:
            new_baudrate = self.get_current_baudrate()
            self.serial.baudrate = new_baudrate
            self.status_label.setText(f"Передано символов: {self.tx_count}")
        except Exception:
            self.show_error("Не удалось изменить скорость передачи.")

    def send_data(self, char):
        if not self.serial.is_open:
            self.show_error("Сначала выберите и откройте рабочий COM-порт!")
            return

        try:
            self.serial.write(char.encode('utf-8'))
            self.tx_count += 1
            self.status_label.setText(f"Передано символов: {self.tx_count}")
        except Exception:
            self.show_error("Ошибка при отправке. Проверьте соединение.")

    def receive_data(self, text):
        self.output_field.insertPlainText(text)
        self.output_field.ensureCursorVisible()

    def show_error(self, error_msg):
        QMessageBox.critical(self, "Внимание", error_msg)

    def closeEvent(self, event):
        if self.reader_thread:
            self.reader_thread.stop()
            self.reader_thread = None

        if self.serial.is_open:
            self.serial.close()

        event.accept()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = ComPortApp()
    window.show()
    sys.exit(app.exec())