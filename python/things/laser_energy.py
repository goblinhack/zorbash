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
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_damage_melee_dice("1d6") # This is the damage when the monst fires
    mytp.set_collision_check(True)
    mytp.set_is_interesting(True)
    mytp.set_is_laser(True)
    mytp.set_is_loggable(True)
    mytp.set_is_loggable(True)
    mytp.set_is_no_tile(True)
    mytp.set_is_usable(True)
    mytp.set_on_death_do("laser_energy.on_death()")
    mytp.set_text_a_or_an("a")
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_BEHIND)

    mytp.update()

def init():
    tp_init(name="laser_energy", text_name="beam of energy", short_text_name="laser.energy")

init()
