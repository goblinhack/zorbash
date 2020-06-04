import zx
import tp


def tp_init(name):
    x = tp.Tp(name, name)

    x.set_gfx_animated(True)
    x.set_gfx_show_outlined(True)
    x.set_is_cursor_path(True)
    x.set_is_movable(True)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)
    x.set_z_depth(zx.MAP_DEPTH_OBJ)

    delay = 50
    x.set_tile(tile=name + ".1", delay_ms=delay)

    x.update()

def init():
    tp_init(name="ai_path1")

init()
