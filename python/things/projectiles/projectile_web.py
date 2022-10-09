import my
import tp


def on_born(me, x, y):
    it = my.spawn_at_my_position(me, "webball")
    if it != 0:
        my.thing_set_mob(me, it)


#
# This is an internal only object to fire webs
#
def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.collision_check(self, True)
    my.gfx_ascii_shown(self, True)
    my.is_interesting(self, True)
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

    my.tile(self, ascii_fg_char="cross", ascii_fg_col_name="white",  tile="nothing")
    my.tile(self, ascii_fg_char="cross", ascii_fg_col_name="white",  tile="nothing")
    my.tile(self, ascii_fg_char="cross", ascii_fg_col_name="white",  tile="nothing")
    my.tile(self, ascii_fg_char="cross", ascii_fg_col_name="white",  tile="nothing")
    my.tile(self, ascii_fg_char="cross", ascii_fg_col_name="white",  tile="nothing")
    my.tile(self, ascii_fg_char="cross", ascii_fg_col_name="white",  tile="nothing")
    my.tile(self, ascii_fg_char="cross", ascii_fg_col_name="white",  tile="nothing")
    my.tile(self, ascii_fg_char="cross", ascii_fg_col_name="white",  tile="nothing")
    my.tile(self, ascii_fg_char="cross", ascii_fg_col_name="white",  tile="nothing")
    my.tile(self, ascii_fg_char="cross", ascii_fg_col_name="white",  tile="nothing")
    my.tile(self, ascii_fg_char="cross", ascii_fg_col_name="white",  tile="nothing")
    my.tile(self, ascii_fg_char="cross", ascii_fg_col_name="white",  tile="nothing")
    my.tile(self, ascii_fg_char="cross", ascii_fg_col_name="white",  tile="nothing")
    my.tile(self, ascii_fg_char="cross", ascii_fg_col_name="white",  tile="nothing")
    my.tile(self, ascii_fg_char="cross", ascii_fg_col_name="white",  tile="nothing")
    my.tile(self, ascii_fg_char="cross", ascii_fg_col_name="white",  tile="nothing")

    my.tp_update(self)


def init():
    tp_init(name="projectile_web", text_long_name="web ball", text_short_name="web ball")


init()
