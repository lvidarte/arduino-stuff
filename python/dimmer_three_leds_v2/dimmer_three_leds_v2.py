#!/usr/bin/env python

"""
Author: Leo Vidarte <http://nerdlabs.com.ar>

This is free software,
you can redistribute it and/or modify it
under the terms of the GPL version 3
as published by the Free Software Foundation.

"""

import serial
import Tkinter as tk

root = tk.Tk()
root.title('Dimmer')
conn = serial.Serial('/dev/ttyACM0', 9600)

last_dimmer = None

def send(i, val):
    global last_dimmer
    if last_dimmer != i:
        conn.write(chr(i))
        last_dimmer = i
    conn.write(chr(int(val) + 100))

f = [lambda val: send(0, val),
     lambda val: send(1, val),
     lambda val: send(2, val),
    ]

dimmers = []
for i in (0, 1, 2):
    dimmer = tk.Scale(root, label="Led %d" % i, from_=25, to=0,
                      length=400, command=f[i])
    dimmer.grid(row=0, column=i, padx=20, pady=20)
    dimmers.append(dimmer)

tk.mainloop()
