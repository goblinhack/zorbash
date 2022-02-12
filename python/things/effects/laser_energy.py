import my
import tp


def on_born(me, x, y):
    selection_x, selection_y = my.thing_get_coords(me)
    for thing in my.level_get_all(me, selection_x, selection_y):
        if my.thing_possible_to_attack(me, thing):
            my.thing_hit(me, thing)
    my.level_spawn_at_thing(me, "explosion_minor")


#
# This is an internal only object to fire lasers from monsters
#
def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.collision_check(self, True)
    my.damage_energy_chance_d1000(self, 1000)
    my.damage_energy_dice(self, "1d6")  # This is the damage when the monst fires
    my.is_fire(self, True)
    my.is_laser(self, True)
    my.is_loggable(self, True)
    my.is_no_tile(self, True)
    my.is_tmp_thing(self, True)
    my.is_usable(self, True)
    my.on_born_do(self, "me.on_born()")
    my.temperature(self, 100)
    my.text_a_or_an(self, "a")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_update(self)


def init():
    tp_init(name="laser_energy", text_name="beam of energy", short_text_name="laser.energy")


init()
