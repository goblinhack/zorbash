import my
import tp


def on_targeted(me, x, y):
    my.place_at(me, "random_monst_class_D", x, y)


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.gfx_targeted_projectile(self, "projectile_magical_effect")
    my.spell_replaces(self, "spell_dominate_monst_C")
    my.is_loggable(self, True)
    my.is_spell(self, True)
    my.is_target_select(self, True)
    my.is_usable(self, True)
    my.range_max(self, 7)
    my.spell_base_name(self, name)
    my.spell_cost(self, 8)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "Attempt to dominate a monster with your mind.")
    my.text_description_short(self, "Spell, dominate monst D.")
    my.text_description_very_short(self, "DomMonstD")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self, tile="spell_dominate_monst_D")
    my.tile(self, tile="spell_dominate_monst_D_activated")
    my.tp_update(self)


def init():
    tp_init(name="spell_dominate_monst_D", text_long_name="dominate monst D", text_short_name="dominate monst D")


init()
