import my
import tp


def on_targeted(me, x, y):
    my.place_at(me, "random_monst_class_D", x, y)


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.gfx_targeted_laser(self, "laser_magic_effect")
    my.is_able_to_be_reflected(self, True)
    my.is_loggable(self, True)
    my.is_spell_always_succeeds(self, True)
    my.is_spell(self, True)
    my.is_target_select(self, True)
    my.is_usable(self, True)
    my.range_max(self, 8)
    my.spell_base_name(self, name)
    my.spell_cost(self, 8)
    my.spell_replaces(self, "spell_of_summon_monst3")
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "Summon a dangerous monster, class D.")
    my.text_description_short(self, "Spell, summon monst IV.")
    my.text_description_very_short(self, "SumMonstD")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self, tile="spell_of_summon_monst4")
    my.tile(self, tile="spell_of_summon_monst4_activated")
    my.tp_update(self)


def init():
    tp_init(name="spell_of_summon_monst4", text_long_name="summon monst IV", text_short_name="summon monst IV")


init()
