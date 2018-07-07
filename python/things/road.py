import tp


def thing_init(t):
    return


def road_init(name, short_name):
    x = tp.Tp(name, is_road = True)

    x.set_short_name(short_name)
    x.set_is_road(True)

    x.thing_init = thing_init


def init():
    road_init(name="road", short_name="road")

init()
