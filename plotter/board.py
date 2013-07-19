#!/usr/bin/env python
# -*- coding: utf-8 -*-

import Tkinter as tk
import math


STEPS_PER_MM = 51.2 # asumo 512 steps por cm


def drange(start, stop, step=1):
    r = start
    while r < stop:
        yield r
        r += step


class Point(object):

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def get_points_from(self, point):
        opposite = self.y - point.y
        adjacent = self.x - point.x
        hypot = math.hypot(opposite, adjacent)
        sin = opposite / hypot
        cos = adjacent / hypot
        points = []
        for h in drange(1, int(hypot), 0.5):
            x = point.x + (h * cos)
            y = point.y + (h * sin)
            points.append(Point(x, y))
        return points

    def __repr__(self):
        return "(%.2f, %.2f)" % (self.x, self.y)


class Board(object):

    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.points = []
        self.canvas = None

    def add_point(self, point):
        if self.points:
            last_point = self.points[-1]
            for p in point.get_points_from(last_point):
                self._add_point(p)
        self._add_point(point)

    def _add_point(self, point):
        self.points.append(point)
        if self.canvas:
            self.draw_point(point)
        print(self.get_log(point))

    def draw_point(self, point):
        if self.points:
            color = 'black'
        else:
            color = 'red'
        self.canvas.create_rectangle(
            point.x, point.y,
            point.x + 1, point.y + 1,
            width=0, fill=color)

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

    def get_log(self, point):
        h0, h1 = self.get_hypot(point)
        s0, s1 = self.get_relative_steps(point)
        args = (point, h0, h1, s0, s1)
        str = "Point %s :: Hypots (%.2f, %.2f) :: Relative steps (%d, %d)"
        return str % args


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
        self.canvas.bind_all('<Button-1>', self.add_point)

    def init_board(self):
        self.board.canvas = self.canvas
        point = Point(self.board.width / 2, 100)
        self.board.add_point(point)
        self.update_status(point)

    def add_point(self, event):
        point = Point(event.x, event.y)
        self.board.add_point(point)
        self.update_status(point)

    def update_status(self, point):
        text = self.board.get_log(point)
        self.status.config(text=text)


if __name__ == '__main__':
    from optparse import OptionParser
    prog_name = u'Plotter'
    parser = OptionParser(description=prog_name)
    parser.add_option('-W', '--width', type=int, default=640,
                      help="board width")
    parser.add_option('-H', '--height', type=int, default=480,
                      help="board height")
    args, _ = parser.parse_args()
    app = App(args.width, args.height)
    app.master.title(prog_name)
    app.mainloop()

