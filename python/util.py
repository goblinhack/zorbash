import datetime


def Timestamp():
    return "{:%Y-%m-%d %H:%M:%S}".format(datetime.datetime.now())


class Xyz:

    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

    def __str__(self):
        return str(self.x) + "," + str(self.y) + "," + str(self.z)
