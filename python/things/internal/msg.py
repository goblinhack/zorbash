import my
import tp


def tp_init(name):
    self = tp.Tp(name)
    my.tp_set_is_moveable(self, True)
    my.tp_set_is_msg(self, True)
    my.tp_set_is_no_tile(self, True)
    my.tp_set_is_removeable_if_out_of_slots(self, True)
    my.tp_set_is_tmp_thing(self, True)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "A message.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_MESSAGE)
    my.tp_set_z_prio(self, my.MAP_PRIO_NORMAL)

    my.tp_update(self)


def init():
    tp_init(name="msg")


init()
