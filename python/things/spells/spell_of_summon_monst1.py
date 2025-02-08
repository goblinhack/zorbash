import my
import tp


def on_targeted(me, x, y):
    my.place_at(me, "random_monst_class_A", x, y)


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
    my.on_targeted_do(self, "me.on_targeted()")
    my.range_max(self, 5)
    my.spell_base_name(self, name)
    my.spell_cost(self, 2)
    my.text_a_or_an(self, "a")
    my.text_description_long2(self, "The type of monster summoned should match that of the tile it is placed on. e.g. if you summon over water, you might get an eel. And who doesn't like a friendly eel?")
    my.text_description_long(self, "Summon an unfriendly monster of the least dangerous type, class A if you want to get technical.")
    my.text_description_short(self, "Spell, summon monst I.")
    my.text_description_very_short(self, "SumMonstA")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self, tile="spell_of_summon_monst1")
    my.tile(self, tile="spell_of_summon_monst1_activated")
    my.tp_update(self)


def init():
    tp_init(name="spell_of_summon_monst1", text_long_name="summon monst I", text_short_name="summon monst I")


init()
