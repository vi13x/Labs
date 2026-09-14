import sys
import codecs
import serial
import serial.tools.list_ports
from PyQt6.QtWidgets import (QApplication, QMainWindow, QWidget, QVBoxLayout,
                             QHBoxLayout, QLabel, QComboBox, QPushButton,
                             QTextEdit, QLineEdit, QMessageBox)
from PyQt6.QtCore import QThread, pyqtSignal, Qt


class SerialReaderThread(QThread):
    data_received = pyqtSignal(str)
    error_occurred = pyqtSignal(str)

    def __init__(self, serial_port):
        super().__init__()
        self.serial_port = serial_port
        self.running = True
        self.decoder = codecs.getincrementaldecoder('utf-8')()

    def run(self):
        while self.running:
            if self.serial_port and self.serial_port.is_open:
                try:
                    if self.serial_port.in_waiting > 0:
                        raw_data = self.serial_port.read(
                            self.serial_port.in_waiting
                        )

                        text_data = self.decoder.decode(raw_data)

                        if text_data:
                            self.data_received.emit(text_data)
                    else:
                        self.msleep(50)

                except Exception as e:
                    self.error_occurred.emit(
                        f"Ошибка чтения: {str(e)}"
                    )
                    self.msleep(1000)

    def stop(self):
        self.running = False
        self.wait()


class CharLineEdit(QLineEdit):
    char_pressed = pyqtSignal(str)

    def keyPressEvent(self, event):
        if event.text() and event.key() != Qt.Key.Key_Return:
            self.char_pressed.emit(event.text())
        super().keyPressEvent(event)


class ComPortApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.serial = serial.Serial()
        self.reader_thread = None
        self.tx_count = 0
        self.init_ui()

    def init_ui(self):
        self.setWindowTitle("COM-порт Мессенджер (Вариант 1)")
        self.resize(550, 450)
        self.setStyleSheet("QWidget { font-size: 14px; }")

        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        layout = QVBoxLayout(central_widget)

        ctrl_layout = QHBoxLayout()
        self.port_combo = QComboBox()
        self.update_ports()

        self.baudrate_combo = QComboBox()
        self.baudrate_combo.addItems(["4800", "9600", "19200", "38400", "115200"])
        self.baudrate_combo.setCurrentText("9600")

        self.toggle_btn = QPushButton("Открыть/Закрыть порт")
        self.toggle_btn.clicked.connect(self.toggle_port)

        ctrl_layout.addWidget(QLabel("COM-порт:"))
        ctrl_layout.addWidget(self.port_combo)
        ctrl_layout.addWidget(QLabel("Скорость:"))
        ctrl_layout.addWidget(self.baudrate_combo)
        ctrl_layout.addWidget(self.toggle_btn)
        layout.addLayout(ctrl_layout)

        layout.addWidget(QLabel("Окно ввода (передача сразу после нажатия):"))
        self.input_field = CharLineEdit()
        self.input_field.char_pressed.connect(self.send_data)
        layout.addWidget(self.input_field)

        layout.addWidget(QLabel("Окно вывода (принятые сообщения):"))
        self.output_field = QTextEdit()
        self.output_field.setReadOnly(True)
        layout.addWidget(self.output_field)

        self.status_label = QLabel("Статус: Порт закрыт | Передано символов: 0")
        self.status_label.setStyleSheet("color: #0055aa; font-weight: bold;")
        layout.addWidget(self.status_label)

    def update_ports(self):
        ports = [p.device for p in serial.tools.list_ports.comports()]
        if not ports:
            ports = ["COM1", "COM2", "COM3"]
        self.port_combo.addItems(ports)

    def toggle_port(self):
        if self.serial.is_open:
            self.close_port()
        else:
            self.open_port()

    def open_port(self):
        port_name = self.port_combo.currentText()
        baudrate = int(self.baudrate_combo.currentText())

        try:
            self.serial.port = port_name
            self.serial.baudrate = baudrate
            self.serial.parity = serial.PARITY_NONE
            self.serial.stopbits = serial.STOPBITS_ONE
            self.serial.bytesize = serial.EIGHTBITS
            self.serial.timeout = 0.1

            self.serial.open()

            self.port_combo.setEnabled(False)
            self.baudrate_combo.setEnabled(False)

            self.reader_thread = SerialReaderThread(self.serial)
            self.reader_thread.data_received.connect(self.receive_data)
            self.reader_thread.error_occurred.connect(self.show_error)
            self.reader_thread.start()

            self.update_status(f"Открыт {port_name}, {baudrate} бод")
        except Exception as e:
            self.show_error(f"Не удалось открыть порт: {e}")

    def close_port(self):
        if self.reader_thread:
            self.reader_thread.stop()
            self.reader_thread = None

        if self.serial.is_open:
            self.serial.close()

        self.port_combo.setEnabled(True)
        self.baudrate_combo.setEnabled(True)
        self.update_status("Порт закрыт")

    def send_data(self, char):
        if not self.serial.is_open:
            return

        try:
            self.serial.write(char.encode('utf-8'))
            self.tx_count += 1
            self.update_status("Символ отправлен")
        except Exception as e:
            self.show_error(f"Ошибка отправки: {e}")

    def receive_data(self, text):
        self.output_field.insertPlainText(text)
        self.output_field.ensureCursorVisible()

    def update_status(self, msg):
        self.status_label.setText(f"Статус: {msg} | Отправлено символов: {self.tx_count}")

    def show_error(self, error_msg):
        QMessageBox.critical(self, "Ошибка", error_msg)

    def closeEvent(self, event):
        self.close_port()
        event.accept()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = ComPortApp()
    window.show()
    sys.exit(app.exec())