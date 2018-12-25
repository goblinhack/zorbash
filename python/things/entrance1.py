import zx
import tp


def tp_init(name, short_name):
    x = tp.Tp(name)

    x.set_is_animated(True)
    x.set_is_blitted_as_sitting_on_the_ground(True)
    x.set_is_entrance(True)
    x.set_is_small_shadow_caster(True)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_EXIT)

    delay = 5100
    x.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=delay)

def init():
    tp_init(name="entrance1", short_name="entrance1")

init()
