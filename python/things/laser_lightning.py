import zx
import tp

def on_death(me, x, y):
    target_x, target_y = zx.thing_get_coords(me)
    for thing in zx.level_get_all(me, target_x, target_y):
        if zx.thing_possible_to_attack(me, thing):
            zx.thing_hit(me, thing)
    zx.level_spawn_at_thing(me, "explosion_minor")
    zx.thing_sound_play_channel(me, zx.CHANNEL_WEAPON, "lightning_a")

    #
    # Lightning can impact all things in the same pool
    #
    for water in zx.level_flood_fill_get_all_things(me, x, y, "is_water"):
        water_x, water_y = zx.thing_get_coords(water)
        for thing in zx.level_get_all(water, water_x, water_y):
            if thing != me:
                if zx.thing_possible_to_attack(me, thing):
                    if zx.thing_is_player(thing):
                        zx.topcon("Current surges through your body")

                    zx.thing_fire_at(me, "laser_lightning_secondary", thing)


#
# This is an internal only object to fire lasers from monsters
#
def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_collision_circle(True)
    mytp.set_collision_radius(0.40)
    mytp.set_damage_melee_dice("1d10") # This is the damage when the monst fires
    mytp.set_is_interesting(True)
    mytp.set_is_laser(True)
    mytp.set_is_loggable_for_important_stuff(True)
    mytp.set_is_loggable_for_unimportant_stuff(True)
    mytp.set_is_no_tile(True)
    mytp.set_is_usable(True)
    mytp.set_on_death_do("laser_lightning.on_death()")
    mytp.set_text_a_or_an("a")
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_BEHIND)

    mytp.update()

def init():
    tp_init(name="laser_lightning", text_name="beam of lightning", short_text_name="laser.lightning")

init()
