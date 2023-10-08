import my
import tp


#
# This is an internal only object to poison projectiles from staffs
#
def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.gfx_targeted_projectile(self, "projectile_poison")
    my.is_able_to_be_teleported(self, True)
    my.is_loggable(self, True)
    my.is_no_tile(self, True)
    my.is_projectile(self, True)
    my.text_a_or_an(self, "a")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")

    my.tp_update(self)


def init():
    tp_init(name="staff_projectile_poison", text_long_name="poison projectile", text_short_name="poison projectile")


init()
