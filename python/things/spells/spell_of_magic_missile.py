import my
import tp


def on_use(owner, item, target, x, y):
    # my.topcon("owner  {} {}".format(my.thing_name_get(owner), my.thing_health(owner)))
    # my.topcon("item   {} {}".format(my.thing_name_get(item), my.thing_health(item)))
    # my.topcon("target {} {}".format(my.thing_name_get(target), my.thing_health(target)))
    damage = my.thing_dmg_energy(item)
    enchant = my.thing_enchant_count_get(item)
    my.thing_dmg_current_set(owner, damage + enchant)


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.dmg_chance_d1000_energy(self, 0, 1000)
    my.dmg_energy_dice(self, "1d6")
    my.gfx_targeted_projectile(self, "projectile_magic_missile")
    my.is_loggable(self, True)
    my.is_spell_always_succeeds(self, True)
    my.is_spell(self, True)
    my.is_target_select(self, True)
    my.is_usable(self, True)
    my.on_use_do(self, "me.on_use()")
    my.range_max(self, 7)
    my.spell_base_name(self, name)
    my.spell_cost(self, 2)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "Send a message to your enemies with a flash of directed energy.")
    my.text_description_short(self, "Spell, magic missile.")
    my.text_description_very_short(self, "MagicMiss")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self, tile="spell_of_magic_missile")
    my.tile(self, tile="spell_of_magic_missile_activated")
    my.tp_update(self)


def init():
    tp_init(name="spell_of_magic_missile", text_long_name="magic missile", text_short_name="magic missile")


init()
