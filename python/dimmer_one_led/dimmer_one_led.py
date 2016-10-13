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

def send(val):
    conn.write(chr(int(val)))

brightness = tk.Scale(root, label="Brightness", from_=255, to=0,
                      length=400, command=send)
brightness.grid(padx=20, pady=20)

tk.mainloop()
