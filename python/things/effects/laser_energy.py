import my
import tp


def on_born(me, x, y):
    target_x, target_y = my.thing_get_coords(me)
    for thing in my.level_get_all(me, target_x, target_y):
        if my.thing_possible_to_attack(me, thing):
            my.thing_hit(me, thing)
    my.level_spawn_at_thing(me, "explosion_minor")


#
# This is an internal only object to fire lasers from monsters
#
def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    my.tp_set_collision_check(mytp, True)
    my.tp_set_damage_energy_chance_d1000(mytp, 1000)
    my.tp_set_damage_energy_dice(mytp, "1d6")  # This is the damage when the monst fires
    my.tp_set_is_fire(mytp, True)
    my.tp_set_is_laser(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_no_tile(mytp, True)
    my.tp_set_is_tmp_thing(mytp, True)
    my.tp_set_is_usable(mytp, True)
    my.tp_set_on_born_do(mytp, "me.on_born()")
    my.tp_set_temperature(mytp, 100)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    my.tp_update(mytp, )


def init():
    tp_init(name="laser_energy", text_name="beam of energy", short_text_name="laser.energy")


init()
