import my
import tp


def on_use(owner, item, target, x, y):
    # my.topcon("owner  {} {}".format(my.thing_name_get(owner), my.thing_health(owner)))
    # my.topcon("item   {} {}".format(my.thing_name_get(item), my.thing_health(item)))
    # my.topcon("target {} {}".format(my.thing_name_get(target), my.thing_health(target)))
    for it in my.level_get_all(item, x, y):
        # my.topcon("it {} {}".format(my.thing_name_get(it), my.thing_health(it)))
        if my.thing_is_alive_monst(it) or my.thing_is_player(it):
            my.thing_debuff_add(it, "debuff_slow")


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.is_loggable(self, True)
    my.is_spell(self, True)
    my.is_spell_slow(self, True)
    my.is_target_select(self, True)
    my.is_usable(self, True)
    my.on_use_do(self, "me.on_use()")
    my.range_max(self, 7)
    my.gfx_targeted_projectile(self, "projectile_magical_effect")
    my.spell_base_name(self, name)
    my.spell_cost(self, 2)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "The target of this spell will have their speed reduced.")
    my.text_description_short(self, "Spell, slow.")
    my.text_description_very_short(self, "Slowed")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self, tile="spell_slow")
    my.tile(self, tile="spell_slow_activated")
    my.tp_update(self)


def init():
    tp_init(name="spell_slow", text_long_name="slow", text_short_name="slow")


init()
