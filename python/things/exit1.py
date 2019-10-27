import zx
import tp


def tp_init(name):
    x = tp.Tp(name)

    x.set_gfx_animated(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_exit(True)
    x.set_is_interesting(True)
    x.set_is_light_strength(2)
    x.set_is_loggable(True)
    x.set_str_light_color("white")
    x.set_z_depth(zx.MAP_DEPTH_EXIT)

    delay = 50
    x.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".7", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".8", is_dir_none=True, delay_ms=delay)

    x.update()
    
def init():
    tp_init(name="exit1")

init()
