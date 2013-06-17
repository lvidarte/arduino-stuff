#!/usr/bin/env python
# -*- coding: utf-8 -*-

import time
import random
import Tkinter as tk

WIDTH = 2
HEIGHT = 8
SIZE = 25
SLEEP = 0.5

class Application(tk.Frame):

    def __init__(self, width=WIDTH, height=HEIGHT, size=SIZE):
        tk.Frame.__init__(self, bg='black')
        self.grid()
        self.width = width
        self.height = height
        self.size = size
        self.led_ids = []
        self.led_colors = self.get_led_colors()
        self.create_widgets()
        self.draw_grid()
        self.simulate()

    def create_widgets(self):
        width = self.width * self.size
        height = self.height * self.size
        self.canvas = tk.Canvas(self, width=width, height=height, bg='black')
        self.canvas.grid(row=0, column=0, padx=5, pady=5)

    def draw_grid(self):
        for i in xrange(self.width - 1):
            x = (self.size * i) + self.size
            y0 = 0
            y1 = self.size * self.height
            self.canvas.create_line(x, y0, x, y1, fill='#333')
        for i in xrange(self.height - 1):
            x0 = 0
            x1 = self.size * self.width
            y = (self.size * i) + self.size
            self.canvas.create_line(x0, y, x1, y, fill='#333')

    def get_led_colors(self):
        colors = []
        for i in range(self.height):
            percent = i * 100.0 / self.height
            if percent < 50:
                color = 'green'
            elif percent < 75:
                color = 'yellow'
            else:
                color = 'red'
            colors.append(color)
        return colors

    def clear_vumeters(self):
        for id in self.led_ids:
            self.canvas.delete(id)
        self.canvas.update()

    def draw_vumeters(self, values):
        self.clear_vumeters()
        max_y1 = (self.height * self.size) - self.size
        for i, v in enumerate(values):
            x1 = i * self.size
            x2 = x1 + self.size
            for j in range(v):
                y1 = max_y1 - (j * self.size)
                y2 = y1 + self.size
                id = self.canvas.create_rectangle(x1, y1, x2, y2,
                                                  fill=self.led_colors[j],
                                                  outline='#333')
                self.led_ids.append(id)
        self.canvas.update()

    def simulate(self):
        while True:
            values = []
            for i in range(self.width):
                values.append(random.randrange(self.height + 1))
            self.draw_vumeters(values)
            time.sleep(SLEEP)

if __name__ == '__main__':
    prog = u'Vumeter'

    from optparse import OptionParser
    parser = OptionParser(description=prog)
    parser.add_option('-v', '--vumeters', type=int, dest='width',
                      default=WIDTH, help="Vumeters units")
    parser.add_option('-l', '--leds', type=int, dest='height',
                      default=HEIGHT, help="LEDs by vumeter")
    parser.add_option('-s', '--size', type=int, default=SIZE,
                      help="LEDs size")
    args, _ = parser.parse_args()

    app = Application(args.width, args.height, args.size)
    app.master.title(prog)
    app.mainloop()

