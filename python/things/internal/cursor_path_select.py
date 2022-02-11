import my
import tp


def tp_init(name):
    text_name = "cursor path"
    mytp = tp.Tp(name, text_name)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_is_cursor_path(mytp, True)
    my.tp_set_is_floating(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_removeable_if_out_of_slots(mytp, True)
    my.tp_set_is_tmp_thing(mytp, True)
    my.tp_set_text_a_or_an(mytp, "the")
    my.tp_set_text_description(mytp, "Cursor path.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    delay = 50
    my.tp_set_tile(mytp, tile=name + ".1", delay_ms=delay)

    my.tp_update(mytp, )


def init():
    tp_init(name="cursor_select_path")


init()
