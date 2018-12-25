import zx
import tp


def tp_init(name, short_name):
    x = tp.Tp(name)

    x.set_is_blitted_as_sitting_on_the_ground(True)
    x.set_is_door(True)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_EXIT)
    x.set_is_outlined(True)
    x.set_is_shadow_caster(True)
    x.set_is_small_shadow_caster(True)

    x.set_tile(tile=name + ".1-closed")

def init():
    tp_init(name="door1", short_name="door1")

init()
