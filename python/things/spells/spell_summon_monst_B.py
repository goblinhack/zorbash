import my
import tp


def on_targeted(me, x, y):
    my.place_at(me, "random_monst_class_B", x, y)


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.gfx_targeted_projectile(self, "projectile_magical_effect")
    my.is_loggable(self, True)
    my.is_spell(self, True)
    my.is_target_select(self, True)
    my.is_usable(self, True)
    my.spell_replaces(self, "spell_summon_monst_A")
    my.on_targeted_do(self, "me.on_targeted()")
    my.range_max(self, 7)
    my.spell_base_name(self, name)
    my.spell_cost(self, 4)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "Summon a very unfriendly monster of class B.")
    my.text_description_short(self, "Spell, summon monst B.")
    my.text_description_very_short(self, "SumMonstB")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self, tile="spell_summon_monst_B")
    my.tile(self, tile="spell_summon_monst_B_activated")
    my.tp_update(self)


def init():
    tp_init(name="spell_summon_monst_B", text_long_name="summon monst B", text_short_name="summon monst B")


init()
