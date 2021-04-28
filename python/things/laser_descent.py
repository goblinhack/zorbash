import zx
import tp

def on_death(me, x, y):
    target_x, target_y = zx.thing_get_coords(me)
    for thing in zx.level_get_all(me, target_x, target_y):
        if zx.thing_is_monst(thing) or \
                zx.thing_is_item(thing) or \
                zx.thing_is_door(thing) or \
                zx.thing_is_wall(thing) or \
                zx.thing_is_player(thing) or \
                zx.thing_is_minion_generator(thing) or \
                zx.thing_is_brazier(thing):
            zx.thing_hit(me, thing)

    zx.tp_spawn_at(me, "explosion_major")
    zx.tp_spawn_radius_range(me, me, me, "explosion_destroy_floor")

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
