import tkinter as tk
from tkinter import messagebox
import serial
import serial.tools.list_ports
import threading


class ComPortApp:
    def __init__(self, root):
        self.root = root
        self.root.title("COM-порт Мессенджер")
        self.serial = serial.Serial()
        self.serial.timeout = 0.1
        self.tx_count = 0

        # Окно управления: выбор порта и скорости
        ctrl_frame = tk.Frame(root)
        ctrl_frame.pack(pady=10)

        self.port_var = tk.StringVar()
        self.speed_var = tk.StringVar(value="9600")

        ports = [p.device for p in serial.tools.list_ports.comports()]
        if not ports:
            ports = ["COM1", "COM2", "COM3"]

        tk.OptionMenu(ctrl_frame, self.port_var, *ports).pack(side=tk.LEFT, padx=5)
        tk.OptionMenu(ctrl_frame, self.speed_var, "4800", "9600", "19200", "38400", "115200").pack(side=tk.LEFT, padx=5)
        tk.Button(ctrl_frame, text="Открыть/Закрыть", command=self.toggle_port).pack(side=tk.LEFT, padx=5)

        # Окно ввода сообщений
        tk.Label(root, text="Окно ввода (передача посимвольно):").pack()
        self.input_text = tk.Text(root, height=8, width=50)
        self.input_text.pack(pady=5)
        self.input_text.bind("<Key>", self.send_char)

        # Окно вывода сообщений
        tk.Label(root, text="Окно вывода (принятые сообщения):").pack()
        self.output_text = tk.Text(root, height=8, width=50, state=tk.DISABLED)
        self.output_text.pack(pady=5)

        # Окно просмотра состояния
        self.status_var = tk.StringVar(value="Передано символов: 0")
        tk.Label(root, textvariable=self.status_var, fg="blue").pack(pady=5)

        # Запуск циклического потока чтения
        self.running = True
        threading.Thread(target=self.read_loop, daemon=True).start()

    def toggle_port(self):
        if self.serial.is_open:
            self.serial.close()
            messagebox.showinfo("Инфо", "Порт закрыт")
        else:
            try:
                self.serial.port = self.port_var.get()
                self.serial.baudrate = int(self.speed_var.get())
                self.serial.open()
                messagebox.showinfo("Инфо", f"Порт {self.serial.port} открыт")
            except Exception as e:
                messagebox.showerror("Ошибка", f"Не удалось открыть порт: {e}")

    def send_char(self, event):
        if self.serial.is_open and event.char:
            try:
                self.serial.write(event.char.encode('utf-8'))
                self.tx_count += 1
                self.status_var.set(f"Передано символов: {self.tx_count}")
            except Exception as e:
                messagebox.showerror("Ошибка передачи", str(e))

    def read_loop(self):
        while self.running:
            if self.serial.is_open:
                try:
                    data = self.serial.read(self.serial.in_waiting or 1)
                    if data:
                        char = data.decode('utf-8', errors='ignore')
                        self.output_text.config(state=tk.NORMAL)
                        self.output_text.insert(tk.END, char)
                        self.output_text.see(tk.END)
                        self.output_text.config(state=tk.DISABLED)
                except Exception:
                    pass


if __name__ == "__main__":
    root = tk.Tk()
    app = ComPortApp(root)
    root.mainloop()