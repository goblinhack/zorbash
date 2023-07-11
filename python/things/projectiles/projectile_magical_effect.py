import my
import tp


def on_born(me, x, y):
    my.spawn_at_my_position(me, "magical_effect")


#
# This is an internal only object to fire projectiles from monsters
#
def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.collision_check(self, True)
    my.gfx_ascii_shown(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_dead_on_falling(self, True)
    my.is_loggable(self, True)
    my.is_no_tile(self, True)
    my.is_projectile(self, True)
    my.is_usable(self, True)
    my.on_born_do(self, "me.on_born()")
    my.text_a_or_an(self, "a")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self, ascii_fg_char="o", ascii_fg_col_name="purple",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="white",  tile="nothing")
    my.tile(self, ascii_fg_char="o", ascii_fg_col_name="purple",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="white",  tile="nothing")
    my.tile(self, ascii_fg_char="o", ascii_fg_col_name="purple",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="white",  tile="nothing")
    my.tile(self, ascii_fg_char="o", ascii_fg_col_name="purple",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="white",  tile="nothing")
    my.tile(self, ascii_fg_char="o", ascii_fg_col_name="purple",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="white",  tile="nothing")
    my.tile(self, ascii_fg_char="o", ascii_fg_col_name="purple",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="white",  tile="nothing")
    my.tile(self, ascii_fg_char="o", ascii_fg_col_name="purple",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="white",  tile="nothing")
    my.tile(self, ascii_fg_char="o", ascii_fg_col_name="purple",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="white",  tile="nothing")

    my.tp_update(self)


def init():
    tp_init(name="projectile_magical_effect", text_long_name="magical effect", text_short_name="magical effect")


init()
