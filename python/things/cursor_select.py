import zx
import tp


def tp_init(name):
    text_name = "cursor"
    mytp = tp.Tp(name, text_name)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_is_able_to_fall(False)
    mytp.set_is_cursor(True)
    mytp.set_is_floating(True)
    mytp.set_is_moveable(True)
    mytp.set_is_tmp_thing(True)
    mytp.set_text_a_or_an("the")
    mytp.set_text_description("Cursor.")
    mytp.set_z_depth(zx.MAP_DEPTH_EXPLOSION_MINOR)
    mytp.set_z_prio(zx.MAP_PRIO_BEHIND)

    delay = 50
    mytp.set_tile(tile=name + ".1", delay_ms=delay)
    mytp.set_tile(tile=name + ".2", delay_ms=delay)
    mytp.set_tile(tile=name + ".3", delay_ms=delay)
    mytp.set_tile(tile=name + ".4", delay_ms=delay)
    mytp.set_tile(tile=name + ".5", delay_ms=delay)
    mytp.set_tile(tile=name + ".6", delay_ms=delay)
    mytp.set_tile(tile=name + ".7", delay_ms=delay)
    mytp.set_tile(tile=name + ".8", delay_ms=delay)
    mytp.set_tile(tile=name + ".9", delay_ms=delay)
    mytp.set_tile(tile=name + ".10", delay_ms=delay)
    mytp.set_tile(tile=name + ".11", delay_ms=delay)
    mytp.set_tile(tile=name + ".12", delay_ms=delay)

    mytp.update()

def init():
    tp_init(name="cursor_select")

init()
