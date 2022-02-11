import my
import tp


def tp_init(name):
    text_name = "cursor"
    mytp = tp.Tp(name, text_name)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_is_cursor(mytp, True)
    my.tp_set_is_floating(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_tmp_thing(mytp, True)
    my.tp_set_text_a_or_an(mytp, "the")
    my.tp_set_text_description(mytp, "Cursor.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_EXPLOSION_MINOR)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    delay = 50
    my.tp_set_tile(mytp, tile=name + ".1", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".4", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".5", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".6", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".7", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".8", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".9", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".10", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".11", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".12", delay_ms=delay)

    my.tp_update(mytp, )


def init():
    tp_init(name="cursor_select_fail")


init()
