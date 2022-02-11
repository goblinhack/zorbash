import my
import tp


def tp_init(name):
    mytp = tp.Tp(name)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_msg(mytp, True)
    my.tp_set_is_no_tile(mytp, True)
    my.tp_set_is_removeable_if_out_of_slots(mytp, True)
    my.tp_set_is_tmp_thing(mytp, True)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "A message.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_MESSAGE)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL)

    my.tp_update(mytp, )


def init():
    tp_init(name="msg")


init()
