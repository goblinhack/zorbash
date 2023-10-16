import my
import tp

self = None


def on_owner_add(me, owner, x, y):
    if owner and my.thing_is_player(owner):
        my.thing_msg(me, "A protective green slimy glow surrounds you.")


# Called on removing a ring. Not called on death of the owner.
def on_owner_unset(me, owner, x, y):
    if owner and my.thing_is_player(owner):
        my.thing_msg(me, "The protective green slimy glow around you fades.")


def on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage):
    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    # my.con("owner   {} {:X}".format(my.thing_name_get(owner), owner))
    # my.con("hitter  {} {:X}".format(my.thing_name_get(hitter), hitter))
    # my.con("rhitter {} {:X}".format(my.thing_name_get(real_hitter), real_hitter))
    if my.thing_is_slime(hitter):
        if owner and my.thing_is_player(owner):
            my.thing_msg(me, "You take half damage from the slime attack.")
        return int(damage / 2)
    return damage


def on_owner_attack_dmg_melee(me, owner, victim, x, y, damage):
    # my.con("on_owner_attack_dmg_melee")
    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    # my.con("victim  {} {:X}".format(my.thing_name_get(victim), victim))
    # my.con("damage  {}".format(damage))
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, f"sword_impact{my.py_non_pcg_random_range_inclusive(1, 4)}")
    if my.thing_is_slime(victim):
        if owner and my.thing_is_player(owner):
            my.thing_msg(me, "You issue double damage slime attack.")
        return (damage + my.thing_enchant_count_get(me)) * 2
    return damage + my.thing_enchant_count_get(me)


def on_owner_rcv_dmg_melee(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_rcv_dmg_poison(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_rcv_dmg_drown(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_rcv_dmg_bite(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_rcv_dmg_claw(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_rcv_dmg_cold(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_rcv_dmg_fire(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_rcv_dmg_heat(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_rcv_dmg_crush(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_rcv_dmg_lightning(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_rcv_dmg_energy(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_rcv_dmg_acid(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_rcv_dmg_digest(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_rcv_dmg_nat_att(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_rcv_dmg_necrosis(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_rcv_dmg_stat_str(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_rcv_dmg_stat_con(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage)


def tp_init(name, text_long_name):
    global self
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_buff(self, True)
    my.is_loggable(self, True)
    my.is_runic(self, True)
    my.on_owner_add_do(self, "me.on_owner_add()")
    my.on_owner_attack_dmg_melee_do(self, "me.on_owner_attack_dmg_melee()")
    my.on_owner_rcv_dmg_acid_do(self, "me.on_owner_rcv_dmg_acid()")
    my.on_owner_rcv_dmg_bite_do(self, "me.on_owner_rcv_dmg_bite()")
    my.on_owner_rcv_dmg_claw_do(self, "me.on_owner_rcv_dmg_claw()")
    my.on_owner_rcv_dmg_cold_do(self, "me.on_owner_rcv_dmg_cold()")
    my.on_owner_rcv_dmg_crush_do(self, "me.on_owner_rcv_dmg_crush()")
    my.on_owner_rcv_dmg_digest_do(self, "me.on_owner_rcv_dmg_digest()")
    my.on_owner_rcv_dmg_drown_do(self, "me.on_owner_rcv_dmg_drown()")
    my.on_owner_rcv_dmg_energy_do(self, "me.on_owner_rcv_dmg_energy()")
    my.on_owner_rcv_dmg_fire_do(self, "me.on_owner_rcv_dmg_fire()")
    my.on_owner_rcv_dmg_lightning_do(self, "me.on_owner_rcv_dmg_lightning()")
    my.on_owner_rcv_dmg_melee_do(self, "me.on_owner_rcv_dmg_melee()")
    my.on_owner_rcv_dmg_nat_att_do(self, "me.on_owner_rcv_dmg_nat_att()")
    my.on_owner_rcv_dmg_necrosis_do(self, "me.on_owner_rcv_dmg_necrosis()")
    my.on_owner_rcv_dmg_poison_do(self, "me.on_owner_rcv_dmg_poison()")
    my.on_owner_rcv_dmg_stat_con_do(self, "me.on_owner_rcv_dmg_stat_con()")
    my.on_owner_rcv_dmg_stat_str_do(self, "me.on_owner_rcv_dmg_stat_str()")
    my.on_owner_unset_do(self, "me.on_owner_unset()")
    my.text_description_long(self, "Fear slime no more. You now issue double damage on slime composed monstrosities and receive only half damage from their vile attacks.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self,
            tile="buff_slime_protection")
    my.tp_update(self)


def init():
    tp_init(name="buff_permanent_slime_protection", text_long_name="slime protection")


init()
