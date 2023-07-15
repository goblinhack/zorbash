import my
import tp


def on_targeted(me, x, y):
    my.place_at(me, "random_monst_class_A", x, y)


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.gfx_targeted_projectile(self, "projectile_magical_effect")
    my.is_loggable(self, True)
    my.is_spell(self, True)
    my.is_target_select(self, True)
    my.is_usable(self, True)
    my.on_targeted_do(self, "me.on_targeted()")
    my.range_max(self, 7)
    my.spell_base_name(self, name)
    my.spell_cost(self, 2)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "Attempt to dominate a monster with your mind.")
    my.text_description_short(self, "Spell, dominate monst A.")
    my.text_description_very_short(self, "DomMonstA")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self, tile="spell_dominate_monst_A")
    my.tile(self, tile="spell_dominate_monst_A_activated")
    my.tp_update(self)


def init():
    tp_init(name="spell_dominate_monst_A", text_long_name="dominate monst A", text_short_name="dominate monst A")


init()
