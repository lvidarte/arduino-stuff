#!/usr/bin/env python
# -*- coding: utf-8 -*-

import Tkinter as tk
import math


STEPS_PER_MM = 51.2 # asumo 512 steps por cm


class Point(object):
    def __init__(self, x, y, id=None):
        self.x = x
        self.y = y
        self.id = id


class Board(object):
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.points = []

    def add_point(self, point):
        self.points.append(point)

    def get_hypot(self, point):
        h0 = math.hypot(point.x, point.y)
        h1 = math.hypot(self.width - point.x, point.y)
        return (h0, h1)

    def get_absolute_steps(self, point):
        h0, h1 = self.get_hypot(point)
        s0 = h0 * STEPS_PER_MM
        s1 = h1 * STEPS_PER_MM 
        return (s0, s1)

    def get_relative_steps(self, point):
        s0, s1 = self.get_absolute_steps(point)
        if len(self.points) > 1:
            last_s0, last_s1 = self.get_absolute_steps(self.points[-2])
            s0 -= last_s0
            s1 -= last_s1
        else:
            s0, s1 = 0, 0
        return (s0, s1)


class App(tk.Frame):

    def __init__(self, width, height):
        tk.Frame.__init__(self)
        self.grid()
        self.board = Board(width, height)
        self.create_widgets()
        self.create_events()
        self.init_board()

    def create_widgets(self):
        self.canvas = tk.Canvas(self, width=self.board.width,
                                height=self.board.height, bg='white')
        self.canvas.grid()
        self.status = tk.Label(self, text="click on board to add points")
        self.status.grid()

    def create_events(self):
        self.canvas.bind_all('<Button-1>', self._add_point)

    def init_board(self):
        self.add_point(self.board.width / 2, 100, 'red')

    def _add_point(self, event):
        self.add_point(event.x, event.y)

    def add_point(self, x, y, color='black'):
        id = self.draw_point(x, y, color)
        point = Point(x, y, id)
        self.board.add_point(point)
        self.update_status(point)

    def draw_point(self, x, y, color):
        return self.canvas.create_rectangle(x, y, x + 2, y + 2,
                                            width=0, fill=color)

    def update_status(self, point):
        h0, h1 = self.board.get_hypot(point)
        s0, s1 = self.board.get_relative_steps(point)
        args = (point.x, point.y, h0, h1, s0, s1)
        text = "Point at (%d, %d) :: Hypots (%.2f, %.2f) :: Relative steps (%d, %d)" % args
        print text
        self.status.config(text=text)


if __name__ == '__main__':

    prog_name = u'Plotter'

    from optparse import OptionParser
    parser = OptionParser(description=prog_name)
    parser.add_option('-W', '--width', type=int, default=640,
                      help="board width")
    parser.add_option('-H', '--height', type=int, default=480,
                      help="board height")
    args, _ = parser.parse_args()

    app = App(args.width, args.height)
    app.master.title(prog_name)
    app.mainloop()

