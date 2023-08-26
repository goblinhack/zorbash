import my
import tp


def on_use(owner, item, target, x, y):
    # my.topcon("owner  {} {}".format(my.thing_name_get(owner), my.thing_health(owner)))
    # my.topcon("item   {} {}".format(my.thing_name_get(item), my.thing_health(item)))
    # my.topcon("target {} {}".format(my.thing_name_get(target), my.thing_health(target)))
    my.place_at(target, "spell_of_holding_effect", x, y)


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.is_loggable(self, True)
    my.is_spell(self, True)
    my.is_spell_of_holding(self, True)
    my.is_target_select(self, True)
    my.is_usable(self, True)
    my.on_use_do(self, "me.on_use()")
    my.range_max(self, 7)
    my.gfx_targeted_projectile(self, "projectile_magical_effect")
    my.spell_base_name(self, name)
    my.spell_cost(self, 2)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "Use this spell to place a magical barrier around a monster to prevent either their escape, or them attacking you!")
    my.text_description_short(self, "Spell of holding.")
    my.text_description_very_short(self, "Holding")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self, tile="spell_of_holding")
    my.tile(self, tile="spell_of_holding_activated")
    my.tp_update(self)


def init():
    tp_init(name="spell_of_holding", text_long_name="holding", text_short_name="holding")


init()
