import zx
import tp

def tp_init(name):
    x = tp.Tp(name)

    x.set_gfx_animated(True)
    x.set_is_interesting(False)
    x.set_is_loggable(False)
    x.set_is_ripple(True)
    x.set_text_a_or_an("a");
    x.set_z_depth(zx.MAP_DEPTH_OBJ)

    delay = 100
    x.set_tile(tile=name + ".1", delay_ms=delay)
    x.set_tile(tile=name + ".2", delay_ms=delay)
    x.set_tile(tile=name + ".3", delay_ms=delay)
    x.set_tile(tile=name + ".4", delay_ms=delay)
    x.set_tile(tile=name + ".5", delay_ms=delay)
    x.set_tile(tile=name + ".6", delay_ms=delay)
    x.set_tile(tile=name + ".7", delay_ms=delay)
    x.set_tile(tile=name + ".8", delay_ms=delay, is_end_of_anim=True, is_dead_on_end_of_anim=True)

    x.update()

def init():
    tp_init(name="ripple1")
    tp_init(name="ripple2")

init()
