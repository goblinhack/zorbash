import my
import tp


def tp_init(name):
    text_long_name = "cursor"
    self = tp.Tp(name, text_long_name)
    # start sort marker
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.is_cursor(self, True)
    my.is_floating(self, True)
    my.is_internal(self, True)
    my.is_moveable(self, True)
    my.is_tmp_thing(self, True)
    my.text_a_or_an(self, "the")
    my.text_short_description(self, "Cursor.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_CURSOR)
    # end sort marker

    delay = 50
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue1", ascii_fg_col_name="",
            ascii_bg_alpha=200,
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue1", ascii_fg_col_name="",
            ascii_bg_alpha=200,
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue2", ascii_fg_col_name="",
            ascii_bg_alpha=200,
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue2", ascii_fg_col_name="",
            ascii_bg_alpha=200,
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue3", ascii_fg_col_name="",
            ascii_bg_alpha=200,
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue3", ascii_fg_col_name="",
            ascii_bg_alpha=200,
            tile=name + ".6", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue4", ascii_fg_col_name="",
            ascii_bg_alpha=200,
            tile=name + ".7", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue4", ascii_fg_col_name="",
            ascii_bg_alpha=200,
            tile=name + ".8", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue3", ascii_fg_col_name="",
            ascii_bg_alpha=200,
            tile=name + ".9", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue3", ascii_fg_col_name="",
            ascii_bg_alpha=200,
            tile=name + ".10", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue2", ascii_fg_col_name="",
            ascii_bg_alpha=200,
            tile=name + ".11", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="lightblue2", ascii_fg_col_name="",
            ascii_bg_alpha=200,
            tile=name + ".12", delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="cursor")


init()
