import my
import tp


def on_use(owner, item, target, x, y):
    # my.topcon("owner  {} {}".format(my.thing_name_get(owner), my.thing_health(owner)))
    # my.topcon("item   {} {}".format(my.thing_name_get(item), my.thing_health(item)))
    # my.topcon("target {} {}".format(my.thing_name_get(target), my.thing_health(target)))
    for it in my.level_get_all(item, x, y):
        if my.thing_is_alive_monst(it) or my.thing_is_player(it):
            my.thing_buff_add(it, "buff_hasted")


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.is_loggable(self, True)
    my.is_spell(self, True)
    my.is_target_select(self, True)
    my.is_usable(self, True)
    my.gfx_targeted_projectile(self, "laser_magic_effect")
    my.on_use_do(self, "me.on_use()")
    my.range_max(self, 7)
    my.spell_base_name(self, name)
    my.spell_cost(self, 2)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "The target of this spell will be able to zip around the dungeon with extraordinary speed.")
    my.text_description_short(self, "Spell, hasted.")
    my.text_description_very_short(self, "Hasted")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self, tile="spell_of_hasted")
    my.tile(self, tile="spell_of_hasted_activated")
    my.tp_update(self)


def init():
    tp_init(name="spell_of_hasted", text_long_name="hasted", text_short_name="hasted")


init()
