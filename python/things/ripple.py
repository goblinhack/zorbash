import zx
import tp

def tp_init(name):
    mytp = tp.Tp(name)
    mytp.set_gfx_animated(True)
    mytp.set_is_able_to_fall(False)
    mytp.set_is_loggable(False)
    mytp.set_is_loggable(False)
    mytp.set_is_removeable_if_out_of_slots(True)
    mytp.set_is_ripple(True)
    mytp.set_is_tickable(True)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("An ominous ripple.")
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 25
    mytp.set_tile(tile=name + ".1", delay_ms=delay)
    mytp.set_tile(tile=name + ".2", delay_ms=delay)
    mytp.set_tile(tile=name + ".3", delay_ms=delay)
    mytp.set_tile(tile=name + ".4", delay_ms=delay)
    mytp.set_tile(tile=name + ".5", delay_ms=delay)
    mytp.set_tile(tile=name + ".6", delay_ms=delay)
    mytp.set_tile(tile=name + ".7", delay_ms=delay)
    mytp.set_tile(tile=name + ".8", delay_ms=delay, is_end_of_anim=True, is_dead_on_end_of_anim=True)

    mytp.update()

def init():
    tp_init(name="ripple1")
    tp_init(name="ripple2")

init()
