import zx
import tp

def tp_init(name, short_name):
    x = tp.Tp(name)

    x.set_is_animated(True)
    x.set_is_boring(True)
    x.set_is_ripple(True)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_MONST)

    delay = 50
    x.set_tile(tile=name + ".1", delay_ms=delay)
    x.set_tile(tile=name + ".2", delay_ms=delay)
    x.set_tile(tile=name + ".3", delay_ms=delay)
    x.set_tile(tile=name + ".4", delay_ms=delay, is_end_of_anim=True, is_dead_on_end_of_anim=True)

def init():
    tp_init(name="ripple1", short_name="ripple1")
    tp_init(name="ripple2", short_name="ripple2")

init()
