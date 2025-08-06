import my
import tp


#
# This is an internal only object to fire lasers from monsters
#
def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_laser(self, True)
    my.is_loggable(self, True)
    my.is_no_tile(self, True)
    my.is_usable(self, True)
    my.text_a_or_an(self, "a")
    my.text_pluralize(self, "burst of magic")
    my.text_apostrophize(self, "burst of magic's")
    my.tick_prio(self, my.MAP_TICK_PRIO_VERY_HIGH)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="darkgreen", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="darkgreen", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="darkgreen", ascii_fg_alpha=200, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=200, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="darkgreen", ascii_fg_alpha=200, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=200, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="darkgreen", ascii_fg_alpha=100, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=100, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="darkgreen", ascii_fg_alpha=100, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=100, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="darkgreen", ascii_fg_alpha=50, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=50, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="darkgreen", ascii_fg_alpha=50, tile="nothing")

    my.tp_update(self)


def init():
    tp_init(
        name="laser_magic_effect",
        text_long_name="burst of magic",
        text_short_name="burst of magic",
    )


init()
