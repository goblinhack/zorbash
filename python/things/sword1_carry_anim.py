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

    x.set_tile(tile=name + ".1")

def init():
    my_init(name="sword1_carry_anim", short_name="sword1_carry_anim")

init()
