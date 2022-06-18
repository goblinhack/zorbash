import my
import tp


def on_born(me, x, y):
    selection_x, selection_y = my.thing_coords_get(me)
    for thing in my.level_get_all(me, selection_x, selection_y):
        if my.thing_possible_to_attack(me, thing):
            my.thing_hit(me, thing)
    my.level_spawn_at_thing(me, "explosion_fire")
    my.thing_sound_play_channel(me, my.CHANNEL_WEAPON, "lightning_b")


#
# This is an internal only object to fire lasers from monsters
#
def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # start sort marker
    my.damage_lightning_chance_d1000(self, 0, 1000)
    my.damage_lightning_dice(self, "1d10")  # This is the damage when the monst fires
    my.gfx_ascii_shown(self, True)
    my.is_able_to_attack_owner(self, True)
    my.is_laser(self, True)
    my.is_loggable(self, True)
    my.is_no_tile(self, True)
    my.is_usable(self, True)
    my.on_born_do(self, "me.on_born()")
    my.text_a_or_an(self, "a")
    my.tick_prio(self, my.MAP_TICK_PRIO_VERY_HIGH)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tp_update(self)


def init():
    tp_init(
        name="laser_lightning_fork",
        text_long_name="fork lightning",
        text_short_name="fork lightning",
    )


init()
