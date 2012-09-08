#!/usr/bin/env python

import serial
import Tkinter as tk


class Application(tk.Frame):

    def __init__(self):
        tk.Frame.__init__(self)
        self.grid(sticky=tk.W+tk.E+tk.N+tk.S)
        self.conn = serial.Serial('/dev/ttyACM0', 9600)
        self.create_widgets()
        self.read()

    def create_widgets(self):
        top = self.winfo_toplevel()
        top.rowconfigure(0, weight=1)
        top.columnconfigure(0, weight=1)
        self.rowconfigure(0, weight=1)
        self.columnconfigure(0, weight=1)

        scroll = tk.Scrollbar(self)
        self.messages = tk.Text(self, yscrollcommand=scroll.set)
        self.messages.grid(row=0, column=0, sticky=tk.W+tk.E+tk.N+tk.S)
        scroll.grid(row=0, column=1, sticky=tk.N+tk.S)
        scroll.config(command=self.messages.yview)

        send_frame = tk.Frame(self)
        send_frame.grid(row=1, column=0, columnspan=2)
        self.entry = tk.Entry(send_frame, width=20)
        self.entry.grid(row=0, column=0, padx=5, pady=5)
        send = tk.Button(send_frame, text="send", command=self.write)
        send.grid(row=0, column=1, padx=5, pady=5)

    def read(self):
        text = self.conn.readline()
        self.messages.config(state=tk.NORMAL)
        self.messages.insert(tk.END, text.strip() + '\n')
        self.messages.see(tk.END)
        self.messages.config(state=tk.DISABLED)
        self.after(500, self.read)

    def write(self):
        msg = self.entry.get()
        self.entry.delete(0, tk.END)
        self.conn.write(msg + '\n')


if __name__ == '__main__':
    app = Application()
    app.master.title('Serial monitor')
    app.mainloop()
