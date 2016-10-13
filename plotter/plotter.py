"""
Author: Leo Vidarte <http://nerdlabs.com.ar>

This is free software,
you can redistribute it and/or modify it
under the terms of the GPL version 3
as published by the Free Software Foundation.

"""

from math import sqrt

WIDTH = 1024 #mm
HEIGHT = 768 #mm

def h(a, b):
    return sqrt((a ** 2) + (b ** 2))

MAX_H = h(WIDTH, HEIGHT)
MAX_H_STEPS = 65536
STEPS_PER_MM = MAX_H_STEPS / MAX_H


class Dot:
    def __init__(self, x, y, width, steps_per_mm):
        self.x = x
        self.y = y
        self.h0 = h(self.x, self.y)
        self.h1 = h(width - self.x, self.y)
        self.s0 = self.h0 * steps_per_mm
        self.s1 = self.h1 * steps_per_mm


class Board:
    width = WIDTH
    height = HEIGHT
    steps_per_mm = STEPS_PER_MM
    _dots = []
    last_dot = None
    #pen_down = True

    @staticmethod
    def add_dot(x, y):
        dot = Dot(x, y, Board.width, Board.steps_per_mm)
        Board._dots.append(dot)

    @staticmethod
    def next():
        if Board._dots == []:
            raise StopIteration
        dot = Board._dots.pop(0)
        if Board.last_dot:
            s0 = dot.s0 - Board.last_dot.s0
            s1 = dot.s1 - Board.last_dot.s1
        else:
            s0 = dot.s0
            s1 = dot.s1
        Board.last_dot = dot
        return (int(s0), int(s1))

    @staticmethod
    def __iter__():
        return Board()


if __name__ == '__main__':
    Board.add_dot(40, 50)
    Board.add_dot(100, 230)
    Board.add_dot(20, 10)

    for dot in Board():
        print dot
