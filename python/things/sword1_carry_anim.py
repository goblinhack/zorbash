import zx
import tp


def my_init(name, short_name):
    x = tp.Tp(name)

    x.set_is_animated(True)
    x.set_is_animated_can_hflip(True)
    x.set_is_blit_y_offset(True)
    x.set_is_movable(True)
    x.set_is_outlined(True)
    x.set_is_small_shadow_caster(True)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_WEAPON)

    delay = 550
    x.set_tile(tile=name + ".1", delay_ms=delay)
    x.set_tile(tile=name + ".2", delay_ms=delay)

def init():
    my_init(name="sword1_carry_anim", short_name="sword1_carry_anim")

init()
