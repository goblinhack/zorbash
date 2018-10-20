import zx
import tp


def my_init(name, short_name):
    x = tp.Tp(name)

    x.set_short_name(short_name)
    x.set_is_animated(True)
    x.set_is_movable(True)
    x.set_is_animated_walk_flip(True)
    x.set_is_outlined(True)
    x.set_z_depth(zx.MAP_DEPTH_WEAPON)

    delay = 250
    x.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_none=True, delay_ms=delay,
            is_dead_on_end_of_anim=True)

def init():
    my_init(name="sword1_swing_anim", short_name="sword1_swing_anim")

init()
