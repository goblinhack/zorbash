import my
import tp


def tp_init(name):
    self = tp.Tp(name)
    my.gfx_ascii_mode_shown(self, True)
    my.is_loggable(self, False)
    my.is_moveable(self, True)
    my.is_msg(self, True)
    my.is_no_tile(self, True)
    my.is_removeable_if_out_of_slots(self, True)
    my.text_a_or_an(self, "a")
    my.text_description(self, "A message.")
    my.z_depth(self, my.MAP_DEPTH_MESSAGE)
    my.z_prio(self, my.MAP_PRIO_NORMAL)

    my.tp_update(self)


def init():
    tp_init(name="msg")


init()
