import my
import tp


def on_use(owner, item, target, x, y):
    # my.topcon("owner  {} {}".format(my.thing_name_get(owner), my.thing_health(owner)))
    # my.topcon("item   {} {}".format(my.thing_name_get(item), my.thing_health(item)))
    # my.topcon("target {} {}".format(my.thing_name_get(target), my.thing_health(target)))
    spell = my.place_at(target, "spell_of_protection_barrier", x, y)
    if spell:
        if my.thing_is_the_grid(target):
            my.thing_set_leader(spell, owner)
        else:
            my.thing_set_leader(spell, target)
    my.place_at(target, "magical_effect", x, y)


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.gfx_targeted_laser(self, "laser_magic_effect")
    my.is_able_to_be_reflected(self, True)
    my.is_loggable(self, True)
    my.is_spell_always_succeeds(self, True)
    my.is_spell_of_protection(self, True)
    my.is_spell(self, True)
    my.is_target_select(self, True)
    my.is_usable(self, True)
    my.on_use_do(self, "me.on_use()")
    my.range_max(self, 7)
    my.spell_base_name(self, name)
    my.spell_cost(self, 5)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "Use this spell to place a magical barrier around a monster to protect it, or yourself, from harm")
    my.text_description_short(self, "Spell of protection.")
    my.text_description_very_short(self, "Holding")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self, tile="spell_of_protection")
    my.tile(self, tile="spell_of_protection_activated")
    my.tp_update(self)


def init():
    tp_init(name="spell_of_protection",
            text_long_name="protection",
            text_short_name="protection")


init()
