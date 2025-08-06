import my
import tp


#
# This is an internal only object to fire lasers from staffs
#
def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.gfx_targeted_laser(self, "laser_discord")
    my.is_able_to_be_reflected(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_laser(self, True)
    my.is_loggable(self, True)
    my.is_no_tile(self, True)
    my.text_a_or_an(self, "a")
    my.text_pluralize(self, "beam of healing")
    my.text_apostrophize(self, "beam of healing's")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=200, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=200, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=200, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=200, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=100, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=100, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=100, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=100, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=50, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=50, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="green", ascii_fg_alpha=50, tile="nothing")

    my.tp_update(self)


def init():
    tp_init(name="laser_healing",
            text_long_name="beam of healing",
            text_short_name="laser.healing")


init()
