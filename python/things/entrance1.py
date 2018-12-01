import zx
import tp


def my_init(name, short_name):
    x = tp.Tp(name)

    x.set_is_blit_off_center(True)
    x.set_is_entrance(True)
    x.set_is_small_shadow_caster(True)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_EXIT)

    x.set_tile(tile=name)

def init():
    my_init(name="entrance1", short_name="entrance1")

init()
