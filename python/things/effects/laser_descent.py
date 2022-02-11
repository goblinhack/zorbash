import my
import tp


def on_born(me, x, y):
    my.level_spawn_using_items_radius_range(me, me, me, "explosion_destroy_floor")


#
# This is an internal only object to fire lasers from monsters
#
def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    my.tp_set_blast_max_radius(mytp, 2)
    my.tp_set_collision_check(mytp, True)
    my.tp_set_is_laser(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_no_tile(mytp, True)
    my.tp_set_is_tmp_thing(mytp, True)
    my.tp_set_is_usable(mytp, True)
    my.tp_set_on_born_do(mytp, "me.on_born()")
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    my.tp_update(mytp, )


def init():
    tp_init(
        name="laser_descent",
        text_name="beam of destruction",
        short_text_name="beam of descent",
    )


init()
