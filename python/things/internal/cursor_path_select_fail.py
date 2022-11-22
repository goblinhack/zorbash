import my
import tp


def tp_init(name):
    text_long_name = "cursor path"
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.is_cursor_path(self, True)
    my.is_floating(self, True)
    my.is_internal(self, True)
    my.is_moveable(self, True)
    my.is_removeable_if_out_of_slots(self, True)
    my.is_tmp_thing(self, True)
    my.text_a_or_an(self, "the")
    my.text_description_short(self, "Cursor path.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_CURSOR)
    # end sort marker

    delay = 50
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="red", ascii_fg_col_name="",
            ascii_bg_alpha=200,
            tile=name + ".1", delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="cursor_select_fail_path")


init()
