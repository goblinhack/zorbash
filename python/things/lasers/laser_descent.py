import my
import tp


def on_born(me, x, y):
    item = my.thing_immediate_owner_id_get(me)
    my.level_spawn_using_items_radius_range(id=me, parent_id=item, victim_id=me, what="explosion_destroy_floor")


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

    my.tile(self, ascii_bg_char="1", ascii_bg_col_name="blue", ascii_alpha=200)
    my.tile(self, ascii_bg_char="2", ascii_bg_col_name="blue", ascii_alpha=200)
    my.tile(self, ascii_bg_char="3", ascii_bg_col_name="blue", ascii_alpha=200)
    my.tile(self, ascii_bg_char="4", ascii_bg_col_name="blue", ascii_alpha=200)
    my.tile(self, ascii_bg_char="5", ascii_bg_col_name="blue", ascii_alpha=200)
    my.tile(self, ascii_bg_char="6", ascii_bg_col_name="blue", ascii_alpha=200)
    my.tile(self, ascii_bg_char="7", ascii_bg_col_name="blue", ascii_alpha=200)
    my.tile(self, ascii_bg_char="8", ascii_bg_col_name="blue", ascii_alpha=200)
    my.tile(self, ascii_bg_char="1", ascii_bg_col_name="blue", ascii_alpha=200)
    my.tile(self, ascii_bg_char="2", ascii_bg_col_name="blue", ascii_alpha=200)
    my.tile(self, ascii_bg_char="3", ascii_bg_col_name="blue", ascii_alpha=200)
    my.tile(self, ascii_bg_char="4", ascii_bg_col_name="blue", ascii_alpha=200)
    my.tile(self, ascii_bg_char="5", ascii_bg_col_name="blue", ascii_alpha=200)
    my.tile(self, ascii_bg_char="6", ascii_bg_col_name="blue", ascii_alpha=200)
    my.tile(self, ascii_bg_char="7", ascii_bg_col_name="blue", ascii_alpha=200)
    my.tile(self, ascii_bg_char="8", ascii_bg_col_name="blue", ascii_alpha=200)

    my.tp_update(self)


def init():
    tp_init(
        name="laser_descent",
        text_long_name="beam of destruction",
        text_short_name="beam of descent",
    )


init()
