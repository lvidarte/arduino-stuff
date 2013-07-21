#!/usr/bin/env python
# -*- coding: utf-8 -*-

import Tkinter as tk
import math


def drange(start, stop, step=1):
    r = start
    while r < stop:
        yield r
        r += step


class Point(object):

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def get_points_from(self, last_point, resolution=1):
        opposite = self.y - last_point.y
        adjacent = self.x - last_point.x
        hypot = math.hypot(opposite, adjacent)
        sin = opposite / hypot
        cos = adjacent / hypot
        points = []
        for h in drange(1, int(hypot), resolution):
            x = last_point.x + (h * cos)
            y = last_point.y + (h * sin)
            points.append(Point(x, y))
        return points

    def __repr__(self):
        return "(%.2f, %.2f)" % (self.x, self.y)


class Board(object):

    def __init__(self, width, height,
                 steps_per_mm=51.2, resolution=1,
                 no_points_generation=False):

        self.width = width
        self.height = height
        self.steps_per_mm = steps_per_mm
        self.resolution = resolution
        self.no_points_generation = no_points_generation
        self.points = []
        self.canvas = None

    def add_point(self, point):
        if self.no_points_generation == False:
            last_point = self.get_last_point()
            if last_point:
                for p in point.get_points_from(last_point, self.resolution):
                    self._add_point(p)
        self._add_point(point)

    def _add_point(self, point):
        point_from = self.get_last_point()
        if self.canvas:
            self.draw_point(point)
        self.points.append(point)
        print(self.get_log(point, point_from))

    def draw_point(self, point):
        if self.points:
            color = 'black'
        else:
            color = 'red'
        size = 2
        self.canvas.create_rectangle(
            point.x, point.y,
            point.x + size, point.y + size,
            width=0, fill=color)

    def get_hypot(self, point):
        h0 = math.hypot(point.x, point.y)
        h1 = math.hypot(self.width - point.x, point.y)
        return (h0, h1)

    def get_absolute_steps(self, point):
        h0, h1 = self.get_hypot(point)
        s0 = h0 * self.steps_per_mm
        s1 = h1 * self.steps_per_mm
        return (s0, s1)

    def get_relative_steps(self, point, point_from):
        s0, s1 = self.get_absolute_steps(point)
        if point_from:
            s0_from, s1_from = self.get_absolute_steps(point_from)
            s0 -= s0_from
            s1 -= s1_from
        return (s0, s1)

    def get_last_point(self):
        if len(self.points):
            return self.points[-1]
        return None

    def get_log(self, point, point_from=None):
        h0, h1 = self.get_hypot(point)
        s0, s1 = self.get_relative_steps(point, point_from)
        args = (point, h0, h1, s0, s1)
        str = "Point %s :: Hypots (%.2f, %.2f) :: Relative steps (%d, %d)"
        return str % args


class App(tk.Frame):

    def __init__(self, board, init_point):
        tk.Frame.__init__(self)
        self.grid()
        self.board = board
        self.create_widgets()
        self.create_events()
        self.init_board(init_point)

    def create_widgets(self):
        self.canvas = tk.Canvas(self, width=self.board.width,
                                height=self.board.height, bg='white')
        self.canvas.grid()
        self.status = tk.Label(self, text="click on board to add points")
        self.status.grid()

    def create_events(self):
        self.canvas.bind_all('<Button-1>', self.add_point)

    def init_board(self, init_point):
        self.board.canvas = self.canvas
        if init_point is None:
            point = Point(self.board.width / 2, 100)
        else:
            point = Point(*[int(n) for n in init_point.split(',')])
        self.board.add_point(point)
        self.update_status(point)

    def add_point(self, event):
        point = Point(event.x, event.y)
        point_from = self.board.get_last_point()
        self.board.add_point(point)
        self.update_status(point, point_from)

    def update_status(self, point, point_from=None):
        text = self.board.get_log(point, point_from)
        self.status.config(text=text)


if __name__ == '__main__':
    from optparse import OptionParser
    prog_name = u'Plotter'
    parser = OptionParser(description=prog_name)
    parser.add_option('-w', '--width', type=int, default=640,
                      help="board width")
    parser.add_option('-H', '--height', type=int, default=480,
                      help="board height")
    parser.add_option('-i', '--init-point', type=str,
                      help="init board point")
    parser.add_option('-s', '--steps-per-mm', type=float, default=51.2,
                      help="amount of steps per mm for each motor")
    parser.add_option('-r', '--resolution', type=float, default=1,
                      help="step in mm to generate intermediate points")
    parser.add_option('-g', '--no-points-generation', action='store_true',
                      help="no generate points between actual and last point",
                      default=False)
    args, _ = parser.parse_args()
    board = Board(args.width, args.height, args.steps_per_mm,
                  args.resolution, args.no_points_generation)
    app = App(board, args.init_point)
    app.master.title(prog_name)
    app.mainloop()
