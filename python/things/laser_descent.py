import zx
import tp

def on_death(me, x, y):
    zx.level_spawn_at_thing(me, "explosion_major")
    zx.level_spawn_using_items_radius_range(me, me, me, "explosion_destroy_floor")

#
# This is an internal only object to fire lasers from monsters
#
def tp_init(name, text_name, short_text_name):
    x = tp.Tp(name, text_name, short_text_name)
    x.set_blast_max_radius(2)
    x.set_blast_min_radius(0)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(1)
    x.set_collision_radius(0.40)
    x.set_is_interesting(True)
    x.set_is_laser(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_no_tile(True)
    x.set_is_usable(True)
    x.set_on_death_do("laser_descent.on_death()")
    x.set_text_a_or_an("a")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    x.update()

def init():
    tp_init(name="laser_descent", text_name="beam of destruction", short_text_name="laser.descent")

init()
