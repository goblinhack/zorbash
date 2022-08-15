import my
import tp

self = None


def on_owner_add(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "A protective shield surrounds you.")


# Called on removing a ring. Not called on death of the owner.
def on_owner_remove(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "The protective shield around you fades.")


def on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage):
    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    # my.con("owner   {} {:X}".format(my.thing_name_get(owner), owner))
    # my.con("hitter  {} {:X}".format(my.thing_name_get(hitter), hitter))
    # my.con("rhitter {} {:X}".format(my.thing_name_get(real_hitter), real_hitter))
    if my.thing_is_projectile(hitter):
        if my.thing_is_player(owner):
            my.thing_msg(me, "You take half damage from the missile attack.")
        return int(damage / 2)
    return damage


def on_owner_receive_dmg_melee(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_poison(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_future1(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_future2(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_future3(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_cold(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_fire(me, owner, hitter, real_hitter, x, y, damage):
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
    # start sort marker

    my.gfx_ascii_shown(self, True)
    my.is_buff(self, True)
    my.is_loggable(self, True)
    my.on_owner_add_do(self, "me.on_owner_add()")
    my.on_owner_receive_dmg_acid_do(self, "me.on_owner_receive_dmg_acid()")
    my.on_owner_receive_dmg_cold_do(self, "me.on_owner_receive_dmg_cold()")
    my.on_owner_receive_dmg_crush_do(self, "me.on_owner_receive_dmg_crush()")
    my.on_owner_receive_dmg_digest_do(self, "me.on_owner_receive_dmg_digest()")
    my.on_owner_receive_dmg_energy_do(self, "me.on_owner_receive_dmg_energy()")
    my.on_owner_receive_dmg_fire_do(self, "me.on_owner_receive_dmg_fire()")
    my.on_owner_receive_dmg_future1_do(self, "me.on_owner_receive_dmg_future1()")
    my.on_owner_receive_dmg_future2_do(self, "me.on_owner_receive_dmg_future2()")
    my.on_owner_receive_dmg_future3_do(self, "me.on_owner_receive_dmg_future3()")
    my.on_owner_receive_dmg_lightning_do(self, "me.on_owner_receive_dmg_lightning()")
    my.on_owner_receive_dmg_melee_do(self, "me.on_owner_receive_dmg_melee()")
    my.on_owner_receive_dmg_nat_att_do(self, "me.on_owner_receive_dmg_nat_att()")
    my.on_owner_receive_dmg_necrosis_do(self, "me.on_owner_receive_dmg_necrosis()")
    my.on_owner_receive_dmg_poison_do(self, "me.on_owner_receive_dmg_poison()")
    my.on_owner_receive_dmg_stat_con_do(self, "me.on_owner_receive_dmg_stat_con()")
    my.on_owner_receive_dmg_stat_str_do(self, "me.on_owner_receive_dmg_stat_str()")
    my.on_owner_remove_do(self, "me.on_owner_remove()")
    my.text_long_description(self, "Missile attacks cause half damage.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    # my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND) # End marker for fixup.sh
    # end sort marker
    my.tile(self,
            tile="buff_missile_resist")
    my.tp_update(self)


def init():
    tp_init(name="buff_missile_resist", text_long_name="missile resist")


init()
