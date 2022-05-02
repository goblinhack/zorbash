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
    my.z_depth(self, my.MAP_DEPTH_EXPLOSION_MINOR)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    delay = 50
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col="red", ascii_fg_col="",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col="red", ascii_fg_col="",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col="red", ascii_fg_col="",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col="red", ascii_fg_col="",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col="red", ascii_fg_col="",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col="red", ascii_fg_col="",
            tile=name + ".6", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col="red", ascii_fg_col="",
            tile=name + ".7", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col="red", ascii_fg_col="",
            tile=name + ".8", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col="red", ascii_fg_col="",
            tile=name + ".9", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col="red", ascii_fg_col="",
            tile=name + ".10", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col="red", ascii_fg_col="",
            tile=name + ".11", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col="red", ascii_fg_col="",
            tile=name + ".12", delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="cursor_select_fail")


init()
