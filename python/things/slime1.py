import zx
import tp

def monst_init(name, short_name):
    x = tp.Tp(name)

    x.set_is_animated(True)
    x.set_is_animated_can_hflip(True)
    x.set_is_blit_y_offset(True)
    x.set_is_monst(True)
    x.set_is_movable(True)
    x.set_is_movement_blocking(True)
    x.set_is_outlined(True)
    x.set_is_shadow_caster(True)
    x.set_is_small_shadow_caster(True)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_MONST)

    delay = 100
    x.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_none=True, delay_ms=delay)

def init():
    monst_init(name="slime1", short_name="slime1")

init()
