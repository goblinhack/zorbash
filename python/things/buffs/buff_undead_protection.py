import my
import tp

self = None


def on_owner_add(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "A protective glow surrounds you.")


# Called on removing a ring. Not called on death of the owner.
def on_owner_unset(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "The protective glow around you fades.")


def on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage):
    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    # my.con("owner   {} {:X}".format(my.thing_name_get(owner), owner))
    # my.con("hitter  {} {:X}".format(my.thing_name_get(hitter), hitter))
    # my.con("rhitter {} {:X}".format(my.thing_name_get(real_hitter), real_hitter))
    if my.thing_is_undead(hitter):
        if my.thing_is_player(owner):
            my.thing_msg(me, "You take half damage from the undead attack.")
        return int(damage / 2)
    return damage


def on_owner_receive_dmg_melee(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_poison(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_drown(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_bite(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_claw(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_cold(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_fire(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_heat(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_crush(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_lightning(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_energy(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_acid(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_digest(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_nat_att(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_necrosis(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_stat_str(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_stat_con(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def tp_init(name, text_long_name):
    global self
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_buff(self, True)
    my.is_immune_to_draining(self, True)
    my.is_immune_to_necrosis(self, True)
    my.is_loggable(self, True)
    my.on_owner_add_do(self, "me.on_owner_add()")
    my.on_owner_receive_dmg_acid_do(self, "me.on_owner_receive_dmg_acid()")
    my.on_owner_receive_dmg_bite_do(self, "me.on_owner_receive_dmg_bite()")
    my.on_owner_receive_dmg_claw_do(self, "me.on_owner_receive_dmg_claw()")
    my.on_owner_receive_dmg_cold_do(self, "me.on_owner_receive_dmg_cold()")
    my.on_owner_receive_dmg_crush_do(self, "me.on_owner_receive_dmg_crush()")
    my.on_owner_receive_dmg_digest_do(self, "me.on_owner_receive_dmg_digest()")
    my.on_owner_receive_dmg_drown_do(self, "me.on_owner_receive_dmg_drown()")
    my.on_owner_receive_dmg_energy_do(self, "me.on_owner_receive_dmg_energy()")
    my.on_owner_receive_dmg_fire_do(self, "me.on_owner_receive_dmg_fire()")
    my.on_owner_receive_dmg_lightning_do(self, "me.on_owner_receive_dmg_lightning()")
    my.on_owner_receive_dmg_melee_do(self, "me.on_owner_receive_dmg_melee()")
    my.on_owner_receive_dmg_nat_att_do(self, "me.on_owner_receive_dmg_nat_att()")
    my.on_owner_receive_dmg_necrosis_do(self, "me.on_owner_receive_dmg_necrosis()")
    my.on_owner_receive_dmg_poison_do(self, "me.on_owner_receive_dmg_poison()")
    my.on_owner_receive_dmg_stat_con_do(self, "me.on_owner_receive_dmg_stat_con()")
    my.on_owner_receive_dmg_stat_str_do(self, "me.on_owner_receive_dmg_stat_str()")
    my.on_owner_unset_do(self, "me.on_owner_unset()")
    my.text_description_long(self, "Undead cause half damage.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self,
            tile="buff_undead_protection")
    my.tp_update(self)


def init():
    tp_init(name="buff_undead_protection", text_long_name="undead protection")


init()
