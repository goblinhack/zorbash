import zx
import tp


def tp_init(name):
    text_name = "cursor path"
    x = tp.Tp(name, text_name)
    x.set_gfx_animated(True)
    x.set_gfx_show_outlined(True)
    x.set_is_able_to_fall(False)
    x.set_is_cursor_path(True)
    x.set_is_floating(True)
    x.set_is_movable(True)
    x.set_is_removable_if_out_of_slots(True)
    x.set_text_a_or_an("the");
    x.set_text_description("Cursor path")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    delay = 50
    x.set_tile(tile=name + ".1", delay_ms=delay)

    x.update()

def init():
    tp_init(name="cursor_path")

init()
