import my
import tp


def on_born(me, x, y):
    target_x, target_y = my.thing_get_coords(me)
    for thing in my.level_get_all(me, target_x, target_y):
        if my.thing_possible_to_attack(me, thing):
            my.thing_hit(me, thing)
    my.level_spawn_at_thing(me, "explosion_minor")


#
# This is an internal only object to fire projectiles from monsters
#
def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_collision_check(True)
    mytp.set_damage_fire_chance_d1000(1000)
    mytp.set_damage_fire_dice("1d10")  # This is the damage when the monst fires
    mytp.set_is_fire(True)
    mytp.set_is_loggable(True)
    mytp.set_is_no_tile(True)
    mytp.set_is_projectile(True)
    mytp.set_is_tmp_thing(True)
    mytp.set_is_usable(True)
    mytp.set_on_born_do("me.on_born()")
    mytp.set_text_a_or_an("a")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.update()


def init():
    tp_init(name="projectile_fire", text_name="fire ball", short_text_name="fire ball")


init()
