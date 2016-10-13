"""
Author: Leo Vidarte <http://nerdlabs.com.ar>

This is free software,
you can redistribute it and/or modify it
under the terms of the GPL version 3
as published by the Free Software Foundation.

"""

import math

def drange(start, stop, step=1):
    r = start
    while r < stop:
        yield r
        r += step


class Triangle:
    def __init__(self, opposite, adjacent):
        self.opposite = opposite
        self.adjacent = adjacent
        self.hypotenuse = math.hypot(opposite, adjacent)
        self.sin = opposite / self.hypotenuse
        self.cos = adjacent / self.hypotenuse
        self.angle = math.degrees(math.asin(self.sin))


class Point(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def get_points_from(self, point):
        opposite = self.y - point.y
        adjacent = self.x - point.x
        triangle = Triangle(opposite, adjacent)
        points = []
        for hypotenuse in drange(1, int(triangle.hypotenuse), 0.5):
            x = point.x + (hypotenuse * triangle.cos)
            y = point.y + (hypotenuse * triangle.sin)
            points.append(Point(x, y))
        return points

    def __repr__(self):
        return "(%.2f, %.2f)" % (self.x, self.y)


if __name__ == '__main__':
    test = [
        (Point(10, 3), Point(15, 20)),
        (Point(12, 8), Point(15, 2)),
        (Point(18, 12), Point(4, 6)),
        (Point(15, 18), Point(4, 30)),
        (Point(10, 15), Point(15, 15)),
        (Point(10, 15), Point(10, 5)),
        (Point(10, 15), Point(5, 15)),
        (Point(10, 15), Point(10, 20)),
        ]
    for p1, p2 in test:
        print '-' * 20
        print 'p1', p1
        print 'p2', p2
        print p2.get_points_from(p1)
