import my
import tp


def on_born(me, x, y):
    item = my.thing_immediate_owner_id_get(me)
    my.spawn_using_items_radius_range(id=me, parent_id=item, victim_id=me, what="explosion_destroy_floor")


#
# This is an internal only object to fire lasers from monsters
#
def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # start sort marker
    my.blast_max_radius(self, 2)
    my.collision_check(self, True)
    my.gfx_ascii_shown(self, True)
    my.is_laser(self, True)
    my.is_loggable(self, True)
    my.is_no_tile(self, True)
    my.is_usable(self, True)
    my.on_born_do(self, "me.on_born()")
    my.text_a_or_an(self, "a")
    my.tick_prio(self, my.MAP_TICK_PRIO_VERY_HIGH)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="cyan", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="blue", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="cyan", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="blue", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="cyan", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="blue", ascii_fg_alpha=200, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="cyan", ascii_fg_alpha=200, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="blue", ascii_fg_alpha=200, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="cyan", ascii_fg_alpha=200, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="blue", ascii_fg_alpha=100, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="cyan", ascii_fg_alpha=100, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="blue", ascii_fg_alpha=100, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="cyan", ascii_fg_alpha=100, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="blue", ascii_fg_alpha=50, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="cyan", ascii_fg_alpha=50, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="blue", ascii_fg_alpha=50, tile="nothing")

    my.tp_update(self)


def init():
    tp_init(
        name="laser_descent",
        text_long_name="beam of destruction",
        text_short_name="beam of descent",
    )


init()
