#!/usr/bin/env python

import serial
import Tkinter as tk
from itertools import cycle

root = tk.Tk()
root.title('Button On/Off')
conn = serial.Serial('/dev/ttyACM0', 9600)

states = ['Off', 'On']
istates = cycle(states)

def send():
    state = button.cget('text')
    value = states.index(state)
    conn.write(chr(value))
    state = istates.next()
    button.config(text=state)

button = tk.Button(root, text='On', command=send)
button.grid(ipadx=40, ipady=20, padx=20, pady=20)

tk.mainloop()
