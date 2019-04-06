import zx
import tp


def tp_init(name, short_name):
    x = tp.Tp(name)

    x.set_gfx_animated(True)
    x.set_gfx_can_hflip(True)
    x.set_gfx_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_active(True)
    x.set_is_movable(True)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_WEAPON)

    delay = 550
    x.set_tile(tile=name + ".1", delay_ms=delay)
    x.set_tile(tile=name + ".2", delay_ms=delay)

    x.update()
    
def init():
    tp_init(name="sword1_carry_anim", short_name="sword1_carry_anim")

init()
