import tp


def thing_init(t):
    return


def player_init(name, short_name):
    x = tp.Tp(name, is_player = True)

    x.set_short_name(short_name)
    x.set_is_movement_blocking(True)
    x.set_is_animated(True)
    x.set_is_movable(True)
    x.set_is_animated_walk_flip(True)

    delay = 10

    x.thing_init = thing_init


def init():
    player_init(name="player1", short_name="player")

init()
