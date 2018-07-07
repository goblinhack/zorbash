import math
import mm


class Point(object):
    def __init__(self, x, y, z):
        self.x, self.y, self.z = x, y, z

    def __str__(self):
        return "({},{},{})".format(self.x, self.y, self.z)

    def sub(self, p):
        return Point(self.x - p.x, self.y - p.y, self.z - p.z)

    def add(self, p):
        return Point(self.x + p.x, self.y + p.y, self.z + p.z)

    def oob(self):
        if 0 <= self.x < mm.MAP_WIDTH and \
           0 <= self.y < mm.MAP_HEIGHT and \
           0 <= self.z < mm.MAP_DEPTH:
            return False
        return True

    def distFrom(self, p):
        return math.sqrt((self.x - p.x)**2 +
                         (self.y - p.y)**2 +
                         (self.z - p.z)**2)
