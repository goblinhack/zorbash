import my
import tp


def tp_init(name):
    text_name = "debug path"
    mytp = tp.Tp(name, text_name)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_is_debug_path(mytp, True)
    my.tp_set_is_floating(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_removeable_if_out_of_slots(mytp, True)
    my.tp_set_is_tmp_thing(mytp, True)
    my.tp_set_text_a_or_an(mytp, "the")
    my.tp_set_text_description(mytp, "debug path.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(mytp, "ai_path1.1")

    my.tp_update(mytp, )


def init():
    tp_init(name="debug_path")


init()
