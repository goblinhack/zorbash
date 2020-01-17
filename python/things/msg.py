import zx
import tp


def tp_init(name):
    x = tp.Tp(name)

    x.set_gfx_show_outlined(True)
    x.set_is_movable(True)
    x.set_is_msg(True)
    x.set_is_no_tile(True)
    x.set_stats_move_speed_ms(3000)
    x.set_z_depth(zx.MAP_DEPTH_CURSOR)
    x.update()

def init():
    tp_init(name="msg")

init()
