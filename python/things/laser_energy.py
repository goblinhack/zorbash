import zx
import tp

def on_death(me, x, y):
    target_x, target_y = zx.thing_get_coords(me)
    for thing in zx.level_get_all(me, target_x, target_y):
        if zx.thing_possible_to_attack(me, thing):
            zx.thing_hit(me, thing)
    zx.level_spawn_at_thing(me, "explosion_minor")

#
# This is an internal only object to fire lasers from monsters
#
def tp_init(name, text_name, short_text_name):
    x = tp.Tp(name, text_name, short_text_name)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(1)
    x.set_collision_radius(0.40)
    x.set_damage_melee_dice("1d6") # This is the damage when the monst fires
    x.set_is_interesting(True)
    x.set_is_laser(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_no_tile(True)
    x.set_is_usable(True)
    x.set_on_death_do("laser_energy.on_death()")
    x.set_text_a_or_an("a")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    x.update()

def init():
    tp_init(name="laser_energy", text_name="beam of energy", short_text_name="laser.energy")

init()
