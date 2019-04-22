import zx
import tp


def tp_init(name):
    x = tp.Tp(name)

    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_is_door(True)
    x.set_z_depth(zx.MAP_DEPTH_EXIT)
    x.set_gfx_outlined(True)
    x.set_gfx_large_shadow_caster(True)
    x.set_gfx_small_shadow_caster(True)

    x.set_tile(tile=name + ".1-closed")

    x.update()
    
def init():
    tp_init(name="door1")

init()
