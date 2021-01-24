import zx
import tp


def tp_init(name):
    text_name = "cursor"
    x = tp.Tp(name, text_name)
    x.set_gfx_animated(True)
    x.set_gfx_show_outlined(True)
    x.set_is_able_to_fall(False)
    x.set_is_active(True)
    x.set_is_cursor(True)
    x.set_is_floating(True)
    x.set_is_moveable(True)
    x.set_text_a_or_an("the");
    x.set_text_description("Cursor")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    delay = 50
    x.set_tile(tile=name + ".1", delay_ms=delay)
    x.set_tile(tile=name + ".2", delay_ms=delay)
    x.set_tile(tile=name + ".3", delay_ms=delay)
    x.set_tile(tile=name + ".4", delay_ms=delay)
    x.set_tile(tile=name + ".5", delay_ms=delay)
    x.set_tile(tile=name + ".6", delay_ms=delay)
    x.set_tile(tile=name + ".7", delay_ms=delay)
    x.set_tile(tile=name + ".8", delay_ms=delay)
    x.set_tile(tile=name + ".9", delay_ms=delay)
    x.set_tile(tile=name + ".10", delay_ms=delay)
    x.set_tile(tile=name + ".11", delay_ms=delay)
    x.set_tile(tile=name + ".12", delay_ms=delay)

    x.update()

def init():
    tp_init(name="cursor_select")

init()
