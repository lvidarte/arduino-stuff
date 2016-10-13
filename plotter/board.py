#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Author: Leo Vidarte <http://nerdlabs.com.ar>

This is free software,
you can redistribute it and/or modify it
under the terms of the GPL version 3
as published by the Free Software Foundation.

"""

import Tkinter as tk
import math
import serial
import time


def drange(start, stop, step=1):
    r = start
    while r < stop:
        yield r
        r += step


class Serial(object):

    def __init__(self, port=None, sleep=0.1):
        self.port = port
        self.sleep = sleep
        self.conn = self.connect()

    def connect(self):
        if self.port is not None:
            return serial.Serial(self.port, 9600)
        return None

    def send(self, msg):
        if self.conn:
            self.conn.write(msg)
        time.sleep(self.sleep)


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
        return "Point(%.2f, %.2f)" % (self.x, self.y)


class Board(object):

    def __init__(self, width, height, steps_per_mm=51.2, resolution=1,
                 no_points_generation=False):
        self.width = width
        self.height = height
        self.steps_per_mm = steps_per_mm
        self.resolution = resolution
        self.no_points_generation = no_points_generation
        self.points = []
        self.last_line = []

    def add(self, point):
        if self.points:
            self.last_line = [self.points[-1]]
            if self.no_points_generation == False:
                for p in point.get_points_from(self.points[-1], self.resolution):
                    self._add(p)
        self._add(point)

    def _add(self, point):
        self.last_line.append(point)
        self.points.append(point)

    def get_hypot(self, point):
        h0 = math.hypot(point.x, point.y)
        h1 = math.hypot(self.width - point.x, point.y)
        return (h0, h1)

    def get_absolute_steps(self, point):
        h0, h1 = self.get_hypot(point)
        s0 = h0 * self.steps_per_mm
        s1 = h1 * self.steps_per_mm
        return (s0, s1)

    def get_relative_steps(self, point_to, point_from=None):
        s0, s1 = self.get_absolute_steps(point_to)
        if point_from is not None:
            s0_from, s1_from = self.get_absolute_steps(point_from)
            s0 -= s0_from
            s1 -= s1_from
        return (s0, s1)

    def get_distance(self, point, point_from=None):
        return {'from' : point_from,
                'to'   : point,
                'hypot': self.get_hypot(point),
                'steps': self.get_relative_steps(point, point_from)}


class App(tk.Frame):

    def __init__(self, board, serial, init_point):
        tk.Frame.__init__(self)
        self.grid()
        self.board = board
        self.serial = serial
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
        self.canvas.bind_all('<Motion>', self.show_position)

    def init_board(self, init_point):
        self.board.add(init_point)
        self.update()

    def show_position(self, event):
        self.master.title("Pointer at (%s, %s)" % (event.x, event.y))

    def add_point(self, event):
        point = Point(event.x, event.y)
        self.board.add(point)
        self.update()

    def update(self):
        for i, p_to in enumerate(self.board.last_line):
            if i > 0 or len(self.board.last_line) == 1:
                self.draw_point(p_to)
                if i:
                    p_from = self.board.last_line[i-1]
                else:
                    p_from = None
                distance = self.board.get_distance(p_to, p_from)
                self.update_status(distance)
                self.console_log(distance)
                if i:
                    self.serial_send(distance)

    def draw_point(self, point, color='black'):
        self.canvas.create_rectangle(
            point.x, point.y,
            point.x + 2, point.y + 2,
            width=0, fill=color)
        self.canvas.update()

    def update_status(self, distance):
        msg = "{to} :: Hypot({hypot[0]:.1f}, {hypot[1]:.1f}) :: " +\
              "RelativeSteps({steps[0]:.0f}, {steps[1]:.0f})"
        text = msg.format(**distance)
        self.status.config(text=text)
        self.status.update()

    def console_log(self, distance):
        msg = "{to} :: RelativeSteps({steps[0]:.0f}, {steps[1]:.0f})"
        print msg.format(**distance)

    def serial_send(self, distance):
        msg = "s{0:.0f},{1:.0f}\0".format(*distance['steps'])
        self.serial.send(msg)


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
    parser.add_option('-S', '--steps-per-mm', type=float, default=51.2,
                      help="amount of steps per mm for each motor")
    parser.add_option('-r', '--resolution', type=float, default=1,
                      help="step in mm to generate intermediate points")
    parser.add_option('-n', '--no-points-generation', default=False,
                      help="no generate points between actual and last point",
                      action='store_true')
    parser.add_option('-p', '--port', type=str, default=None,
                      help="name of the serial port")
    parser.add_option('-s', '--sleep', type=float, default=0.1,
                      help="seconds to sleep between serial sends")
    args, _ = parser.parse_args()

    board = Board(args.width, args.height, args.steps_per_mm,
                  args.resolution, args.no_points_generation)
    serial_ = Serial(args.port, args.sleep)
    if args.init_point:
        init_point = Point(**[int(n) for n in args.init_point.split(',')])
    else:
        init_point = Point(args.width / 2, 100)

    app = App(board, serial_, init_point)
    app.master.title(prog_name)
    app.mainloop()
