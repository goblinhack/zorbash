import my
import tp

self = None


def on_owner_attack_dmg_melee(me, owner, victim, x, y, damage):
    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    # my.con("owner   {} {:X}".format(my.thing_name_get(owner), owner))
    # my.con("victim  {} {:X}".format(my.thing_name_get(victim), victim))
    # my.con("damage  {}".format(damage))
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, f"sword_impact{my.py_non_pcg_random_range_inclusive(1, 4)}")
    damage = (damage * 2) + my.thing_enchant_count_get(me)
    return damage


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker

    my.gfx_ascii_shown(self, True)
    my.is_buff(self, True)
    my.is_loggable(self, True)
    my.is_runic(self, True)
    my.on_owner_attack_dmg_melee_do(self, "me.on_owner_attack_dmg_melee()")
    my.text_description_long(self, "Wield twice the amount of normal melee damage with no stamina loss!")
    my.text_description_short(self, "Double damage")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self, tile="buff_double_damage")
    my.tp_update(self)


def init():
    tp_init(name="buff_permanent_double_damage", text_long_name="double damage", text_short_name="double damage")


init()
