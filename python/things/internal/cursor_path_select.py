import my
import tp


def tp_init(name):
    text_name = "cursor path"
    self = tp.Tp(name, text_name)
    my.gfx_animated(self, True)
    my.is_cursor_path(self, True)
    my.is_floating(self, True)
    my.is_moveable(self, True)
    my.is_removeable_if_out_of_slots(self, True)
    my.is_tmp_thing(self, True)
    my.text_a_or_an(self, "the")
    my.text_description(self, "Cursor path.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    delay = 50
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="green", ascii_fg_col_name="",
            tile=name + ".1", delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="cursor_select_path")


init()
