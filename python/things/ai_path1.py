import zx
import tp


def tp_init(name):
    mytp = tp.Tp(name, name)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_show_outlined(False)
    mytp.set_is_able_to_fall(False)
    mytp.set_is_debug_path(True)
    mytp.set_is_tmp_thing(True)
    mytp.set_is_moveable(True)
    mytp.set_is_removeable_if_out_of_slots(True)
    mytp.set_text_description("AI path.")
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 50
    mytp.set_tile(tile=name + ".1", delay_ms=delay)

    mytp.update()

def init():
    tp_init(name="ai_path1")

init()
