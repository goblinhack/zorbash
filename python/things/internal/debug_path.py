import my
import tp


def tp_init(name):
    text_long_name = "debug path"
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.is_debug_path(self, True)
    my.is_floating(self, True)
    my.is_internal(self, True)
    my.is_moveable(self, True)
    my.is_removeable_if_out_of_slots(self, True)
    my.is_tmp_thing(self, True)
    my.text_a_or_an(self, "the")
    my.text_description_short(self, "debug path.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_CURSOR)
    # end sort marker

    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="darkblue", ascii_fg_col_name="",
            tile="ai_path1.1")

    my.tp_update(self)


def init():
    tp_init(name="debug_path")


init()
