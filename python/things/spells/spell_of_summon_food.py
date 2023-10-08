import my
import tp


def on_targeted(me, x, y):
    my.place_at(me, "random_food", x, y)


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.gfx_targeted_laser(self, "laser_magic_effect")
    my.is_loggable(self, True)
    my.is_spell(self, True)
    my.is_spell_always_succeeds(self, True)
    my.is_target_select(self, True)
    my.is_usable(self, True)
    my.on_targeted_do(self, "me.on_targeted()")
    my.range_max(self, 3)
    my.spell_base_name(self, name)
    my.spell_cost(self, 5)
    my.text_a_or_an(self, "a")
    my.text_description_long2(self, "This service is brought to you by Dungeon Dash.")
    my.text_description_long(self, "Summon some tasty and freshly made dungeon food. Made by what or whom is best not to ask.")
    my.text_description_short(self, "Spell, summon food")
    my.text_description_very_short(self, "SumFood")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self, tile="spell_of_summon_food")
    my.tile(self, tile="spell_of_summon_food_activated")
    my.tp_update(self)


def init():
    tp_init(name="spell_of_summon_food", text_long_name="summon food", text_short_name="summon food")


init()
