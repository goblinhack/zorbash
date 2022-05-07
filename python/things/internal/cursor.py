import my
import tp


def tp_init(name):
    text_name = "cursor"
    self = tp.Tp(name, text_name)
    my.gfx_animated(self, True)
    my.gfx_show_outlined(self, True)
    my.is_cursor(self, True)
    my.is_floating(self, True)
    my.is_moveable(self, True)
    my.is_tmp_thing(self, True)
    my.text_a_or_an(self, "the")
    my.text_description(self, "Cursor.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_IN_FRONT)

    delay = 50
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue1", ascii_fg_col_name="",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue1", ascii_fg_col_name="",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue2", ascii_fg_col_name="",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue2", ascii_fg_col_name="",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue3", ascii_fg_col_name="",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue3", ascii_fg_col_name="",
            tile=name + ".6", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue4", ascii_fg_col_name="",
            tile=name + ".7", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue4", ascii_fg_col_name="",
            tile=name + ".8", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue3", ascii_fg_col_name="",
            tile=name + ".9", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue3", ascii_fg_col_name="",
            tile=name + ".10", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue2", ascii_fg_col_name="",
            tile=name + ".11", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue2", ascii_fg_col_name="",
            tile=name + ".12", delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="cursor")


init()
