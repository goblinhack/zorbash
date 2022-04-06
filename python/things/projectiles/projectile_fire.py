import my
import tp


def on_born(me, x, y):
    selection_x, selection_y = my.thing_coords_get(me)
    for thing in my.level_get_all(me, selection_x, selection_y):
        if my.thing_possible_to_attack(me, thing):
            my.thing_hit(me, thing)
    my.level_spawn_at_thing(me, "explosion_fire")


#
# This is an internal only object to fire projectiles from monsters
#
def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.collision_check(self, True)
    my.damage_fire_chance_d1000(self, 0, 1000)
    my.damage_fire_dice(self, "1d10")  # This is the damage when the monst fires
    my.is_dead_on_falling(self, True)
    my.is_fire(self, True)
    my.is_loggable(self, True)
    my.is_no_tile(self, True)
    my.is_projectile(self, True)
    my.is_usable(self, True)
    my.on_born_do(self, "me.on_born()")
    my.temperature(self, 100)
    my.text_a_or_an(self, "a")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_update(self)


def init():
    tp_init(name="projectile_fire", text_name="fireball", short_text_name="fireball")


init()
