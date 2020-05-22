import zx
import tp


def tp_init(name):
    x = tp.Tp(name)

    x.set_is_gfx_show_outlined(True)
    x.set_is_movable(True)
    x.set_is_msg(True)
    x.set_is_no_tile(True)
    x.set_a_or_an("a");
    x.set_z_depth(zx.MAP_DEPTH_WALLS)

    x.update()

def init():
    tp_init(name="msg")

init()
