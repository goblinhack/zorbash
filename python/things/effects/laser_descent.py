import my
import tp


def on_born(me, x, y):
    my.level_spawn_using_items_radius_range(me, me, me, "explosion_destroy_floor")


#
# This is an internal only object to fire lasers from monsters
#
def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.tp_set_blast_max_radius(self, 2)
    my.tp_set_collision_check(self, True)
    my.tp_set_is_laser(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_no_tile(self, True)
    my.tp_set_is_tmp_thing(self, True)
    my.tp_set_is_usable(self, True)
    my.tp_set_on_born_do(self, "me.on_born()")
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_update(self)


def init():
    tp_init(
        name="laser_descent",
        text_name="beam of destruction",
        short_text_name="beam of descent",
    )


init()
