import zx
import tp

def key_init(name):
    x = tp.Tp(name)

    x.set_gfx_animated(True)
    x.set_gfx_bounce_on_move(True)
    x.set_gfx_show_hiddend(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_interesting(True)
    x.set_is_key(True)
    x.set_is_loggable(True)
    x.set_is_movable(True)
    x.set_is_movement_blocking(True)
    x.set_z_depth(zx.MAP_DEPTH_ITEM)

    x.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=100)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=100)
    x.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=100)
    x.set_tile(tile=name + ".4", is_dir_none=True, delay_ms=100)
    x.set_tile(tile=name + ".5", is_dir_none=True, delay_ms=100)
    x.set_tile(tile=name + ".4", is_dir_none=True, delay_ms=100)
    x.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=100)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=100)

    x.update()
    
def init():
    key_init(name="key1")

init()
