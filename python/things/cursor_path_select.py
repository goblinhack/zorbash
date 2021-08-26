import zx
import tp


def tp_init(name):
    text_name = "cursor path"
    mytp = tp.Tp(name, text_name)
    mytp.set_gfx_animated(True)
    mytp.set_is_able_to_fall(False)
    mytp.set_is_cursor_path(True)
    mytp.set_is_tmp_thing(True)
    mytp.set_is_floating(True)
    mytp.set_is_moveable(True)
    mytp.set_is_removeable_if_out_of_slots(True)
    mytp.set_text_a_or_an("the")
    mytp.set_text_description("Cursor path.")
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_BEHIND)

    delay = 50
    mytp.set_tile(tile=name + ".1", delay_ms=delay)

    mytp.update()

def init():
    tp_init(name="cursor_select_path")

init()
