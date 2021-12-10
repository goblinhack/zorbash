import my
import tp


def tp_init(name):
    mytp = tp.Tp(name)
    mytp.set_is_moveable(True)
    mytp.set_is_msg(True)
    mytp.set_is_no_tile(True)
    mytp.set_is_removeable_if_out_of_slots(True)
    mytp.set_is_tmp_thing(True)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A message.")
    mytp.set_z_depth(my.MAP_DEPTH_MESSAGE)
    mytp.set_z_prio(my.MAP_PRIO_NORMAL)

    mytp.update()


def init():
    tp_init(name="msg")


init()
