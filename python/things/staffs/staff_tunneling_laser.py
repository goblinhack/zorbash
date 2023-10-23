import my
import tp


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_laser(self, True)
    my.is_loggable(self, True)
    my.is_no_tile(self, True)
    my.text_a_or_an(self, "a")
    my.tick_prio(self, my.MAP_TICK_PRIO_VERY_HIGH)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="white", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="orange", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="white", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="orange", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="white", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="orange", ascii_fg_alpha=200, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="white", ascii_fg_alpha=200, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="orange", ascii_fg_alpha=200, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="white", ascii_fg_alpha=200, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="orange", ascii_fg_alpha=100, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="white", ascii_fg_alpha=100, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="orange", ascii_fg_alpha=100, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="white", ascii_fg_alpha=100, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="orange", ascii_fg_alpha=50, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="white", ascii_fg_alpha=50, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="orange", ascii_fg_alpha=50, tile="nothing")

    my.tp_update(self)


def init():
    tp_init(name="staff_tunneling_laser", text_long_name="beam of tunneling", text_short_name="laser.tunneling")


init()
