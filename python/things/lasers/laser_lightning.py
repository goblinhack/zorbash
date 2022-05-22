import my
import tp


def on_born(me, x, y):
    selection_x, selection_y = my.thing_coords_get(me)
    for thing in my.level_get_all(me, selection_x, selection_y):
        if my.thing_possible_to_attack(me, thing):
            my.thing_hit(me, thing)
    my.level_spawn_at_thing(me, "explosion_fire")
    my.thing_sound_play_channel(me, my.CHANNEL_WEAPON, "lightning_a")


def on_use(owner, me, target, x, y):
    # my.con("owner   {} {:X}".format(my.thing_name_get(owner), owner))
    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    # my.con("target  {} {:X}".format(my.thing_name_get(target), target))
    #
    # Lightning can impact all things in the same pool
    #
    for water in my.level_flood_fill_get_all_things(me, x, y, "is_water"):
        water_x, water_y = my.thing_coords_get(water)
        for thing in my.level_get_all(water, water_x, water_y):
            if thing != me:
                if my.thing_possible_to_attack(me, thing):
                    if my.thing_is_player(thing):
                        my.thing_msg(thing, "Current surges through your body!")

                    my.thing_fire_at(me, "laser_lightning_fork", thing)


#
# This is an internal only object to fire lasers from monsters
#
def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.gfx_ascii_mode_shown(self, True)
    my.damage_lightning_chance_d1000(self, 0, 1000)
    my.damage_lightning_dice(self, "1d10+10")  # This is the damage when the monst fires
    my.is_able_to_attack_owner(self, True)
    my.is_laser(self, True)
    my.is_loggable(self, True)
    my.is_no_tile(self, True)
    my.is_usable(self, True)
    my.on_born_do(self, "me.on_born()")
    my.on_use_do(self, "me.on_use()")
    my.text_a_or_an(self, "a")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_update(self)


def init():
    tp_init(
        name="laser_lightning",
        text_name="ray of lightning",
        short_text_name="ray of lightning",
    )


init()
