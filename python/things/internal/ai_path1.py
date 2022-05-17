import my
import tp


def tp_init(name):
    self = tp.Tp(name, name)
    my.gfx_animated(self, True)
    my.is_debug_path(self, True)
    my.is_moveable(self, True)
    my.is_removeable_if_out_of_slots(self, True)
    my.is_tmp_thing(self, True)
    my.text_description(self, "AI path.")
    my.z_depth(self, my.MAP_DEPTH_CURSOR)
    my.z_prio(self, my.MAP_PRIO_NORMAL)

    delay = 50
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="darkgreen", ascii_fg_col_name="",
            tile=name + ".1", delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="ai_path1")


init()
