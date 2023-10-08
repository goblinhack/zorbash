import my
import tp


def on_targeted(me, x, y):
    my.place_at(me, "random_rock", x, y)
    for it in my.level_get_all(me, x, y):
        if my.thing_possible_to_attack(me, it):
            my.thing_hit(0, me, it)


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.dmg_chance_d1000_crush(self, 0, 1000)
    my.dmg_crush_dice(self, "4d6")
    my.gfx_targeted_laser(self, "laser_magic_effect")
    my.is_loggable(self, True)
    my.is_spell_always_succeeds(self, True)
    my.is_spell(self, True)
    my.is_target_select(self, True)
    my.is_usable(self, True)
    my.on_targeted_do(self, "me.on_targeted()")
    my.range_max(self, 7)
    my.spell_base_name(self, name)
    my.spell_cost(self, 3)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "Summon a slab of solid rock that you can use as a means of defense of treat as a new pet and something to talk to.")
    my.text_description_short(self, "Spell, summon rock")
    my.text_description_very_short(self, "SumRock")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self, tile="spell_of_summon_rock")
    my.tile(self, tile="spell_of_summon_rock_activated")
    my.tp_update(self)


def init():
    tp_init(name="spell_of_summon_rock", text_long_name="summon rock", text_short_name="summon rock")


init()
