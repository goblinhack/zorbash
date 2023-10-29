import my
import tp

self = None


def on_owner_attack_dmg_melee(me, owner, victim, x, y, damage):
    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    # my.con("owner   {} {:X}".format(my.thing_name_get(owner), owner))
    # my.con("victim  {} {:X}".format(my.thing_name_get(victim), victim))
    # my.con("damage  {}".format(damage))
    if not my.thing_is_immune_to_vorpal_weapon(victim):
        roll = my.py_d100()
        if roll < 10 + my.thing_enchant_count_get(me) * 5:
            if owner:
                if my.thing_is_player(owner):
                    my.thing_msg(owner, f"Your vorpal weapon bites deep on the {my.thing_name_get(victim)}.")
                else:
                    my.thing_msg(owner, f"The {my.thing_name_get(owner)}'s vorpal weapon bites deep on the {my.thing_name_get(victim)}.")
            my.thing_dead(victim, "by a vorpal weapon")

    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, f"sword_impact{my.py_non_pcg_random_range_inclusive(1, 4)}")
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
    my.text_description_long2(self, "Not all monsters are vulnerable to this kind of attack. It is a matter of scholarly debate as to whether goldfish are immune to vorpal weapons.")
    my.text_description_long3(self, "Every enchant of the weapon will add 5 percent chance")
    my.text_description_long(self, "This weapon has a 10 percent chance of splitting or beheading its victim.")
    my.text_description_short(self, "Vorpal weapon")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self, tile="buff_vorpal")
    my.tp_update(self)


def init():
    tp_init(name="buff_permanent_vorpal", text_long_name="vorpal weapon", text_short_name="vorpal weapon")


init()
