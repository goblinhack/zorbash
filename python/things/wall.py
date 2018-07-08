import tp


def thing_init(t):
    return


def wall_init(name, short_name, tiles=[]):
    x = tp.Tp(name, is_wall = True)

    x.set_short_name(short_name)
    x.set_is_movement_blocking(True)
    x.set_is_wall(True)

    if tiles is not None:
        for t in tiles:
            x.set_tile(t, delay_ms=150)
    else:
        x.set_tile(tile=name, delay_ms=150)

    x.thing_init = thing_init

def init():
    #wall_init(name="wall1", short_name="A boring wall", tiles=["wall1"])
    #wall_init(name="wall2", short_name="A boring wall", tiles=["wall2"])
    #wall_init(name="wall3", short_name="A boring wall", tiles=["wall3"])
    #wall_init(name="wall4", short_name="A boring wall", tiles=["wall4"])
    #wall_init(name="wall5", short_name="A boring wall", tiles=["wall5"])
    #wall_init(name="wall6", short_name="A boring wall", tiles=["wall6"])
    #wall_init(name="wall7", short_name="A boring wall", tiles=["wall7"])
    return

init()
