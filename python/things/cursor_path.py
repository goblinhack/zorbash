import zx
import tp


def tp_init(name):
    real_name = "cursor path"
    x = tp.Tp(name, real_name)

    x.set_a_or_an("the");
    x.set_gfx_animated(True)
    x.set_gfx_show_outlined(True)
    x.set_is_cursor_path(True)
    x.set_is_movable(True)
    x.set_z_depth(zx.MAP_DEPTH_MONST)

    delay = 50
    x.set_tile(tile=name + ".1", delay_ms=delay)

    x.update()

def init():
    tp_init(name="cursor_path")

init()
