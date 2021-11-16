import my
import tp

def on_death(me, x, y):
    my.level_spawn_at_thing(me, "explosion_major")
    my.level_spawn_using_items_radius_range(me, me, me, "explosion_destroy_floor")

#
# This is an internal only object to fire lasers from monsters
#
def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_blast_max_radius(2)
    mytp.set_blast_min_radius(0)
    mytp.set_collision_check(True)
    mytp.set_is_interesting(True)
    mytp.set_is_laser(True)
    mytp.set_is_loggable(True)
    mytp.set_is_loggable(True)
    mytp.set_is_no_tile(True)
    mytp.set_is_usable(True)
    mytp.set_on_death_do("laser_descent.on_death()")
    mytp.set_text_a_or_an("a")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.update()

def init():
    tp_init(name="laser_descent", text_name="beam of destruction", short_text_name="laser.descent")

init()
