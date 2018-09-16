import zx
import tp


def player_init(name, short_name):
    x = tp.Tp(name, is_player = True)

    x.set_short_name(short_name)
    x.set_is_movement_blocking(True)
    x.set_is_animated(True)
    x.set_is_movable(True)
    x.set_is_animated_walk_flip(True)
    x.set_z_depth(zx.MAP_DEPTH_PLAYER)

    delay = 5
    x.set_tile(tile=name + ".1",
               is_dir_left=True,
               is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".2",
               is_dir_left=True,
               is_moving=True,
               delay_ms=delay)

    for _ in range(20):
        x.set_tile(tile=name + ".1",
                   is_dir_none=True, delay_ms=2000)
        x.set_tile(tile=name + ".2",
                   is_dir_none=True, delay_ms=100)

def init():
    player_init(name="player1", short_name="player1")

init()
