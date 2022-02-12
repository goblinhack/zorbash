import my
import tp


def on_born(me, x, y):
    selection_x, selection_y = my.thing_get_coords(me)
    for thing in my.level_get_all(me, selection_x, selection_y):
        if my.thing_possible_to_attack(me, thing):
            my.thing_hit(me, thing)
    my.level_spawn_at_thing(me, "explosion_minor")


#
# This is an internal only object to cold projectiles from monsters
#
def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.tp_set_collision_check(self, True)
    my.tp_set_damage_cold_chance_d1000(self, 1000)
    my.tp_set_damage_cold_dice(self, "1d10")  # This is the damage when the monst colds
    my.tp_set_is_cold(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_no_tile(self, True)
    my.tp_set_is_projectile(self, True)
    my.tp_set_is_tmp_thing(self, True)
    my.tp_set_is_usable(self, True)
    my.tp_set_on_born_do(self, "me.on_born()")
    my.tp_set_temperature(self, -100)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_update(self)


def init():
    tp_init(name="projectile_cold", text_name="cold ball", short_text_name="cold ball")


init()
