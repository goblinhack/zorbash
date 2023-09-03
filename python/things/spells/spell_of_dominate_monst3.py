import my
import tp
import spell_of_dominate_monst0


def on_targeted(me, x, y):
    return spell_of_dominate_monst0.on_targeted(me, x, y, 2)


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.gfx_targeted_laser(self, "laser_magic_effect")
    my.is_loggable(self, True)
    my.is_spell(self, True)
    my.is_target_select(self, True)
    my.is_usable(self, True)
    my.spell_replaces(self, "spell_of_dominate_monst2")
    my.on_targeted_do(self, "me.on_targeted()")
    my.range_max(self, 7)
    my.spell_base_name(self, name)
    my.spell_cost(self, 6)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "Attempt to dominate a monster with your mind.")
    my.text_description_long2(self, "+4 bonus to PSI attack rolls")
    my.text_description_short(self, "Spell, dominate monst III.")
    my.text_description_very_short(self, "DomMonstA")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self, tile="spell_of_dominate_monst3")
    my.tile(self, tile="spell_of_dominate_monst3_activated")
    my.tp_update(self)


def init():
    tp_init(name="spell_of_dominate_monst3", text_long_name="dominate monst III", text_short_name="dominate monst III")


init()
