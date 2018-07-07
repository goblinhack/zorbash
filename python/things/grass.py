import tp


def thing_init(t):
    return


def grass_init(name, short_name):
    x = tp.Tp(name, is_grass = True)

    x.set_short_name(short_name)
    x.set_is_grass(True)

    x.thing_init = thing_init


def init():
    grass_init(name="grass", short_name="grass")

init()
