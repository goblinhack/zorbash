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


def on_owner_receiving_damage(me, owner, hitter, real_hitter, x, y, damage):
    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    # my.con("owner   {} {:X}".format(my.thing_name_get(owner), owner))
    # my.con("hitter  {} {:X}".format(my.thing_name_get(hitter), hitter))
    # my.con("rhitter {} {:X}".format(my.thing_name_get(real_hitter), real_hitter))
    if my.thing_is_projectile(hitter):
        if my.thing_is_player(owner):
            my.thing_msg(me, "You take half damage from the missile attack.")
        return int(damage / 2)
    return damage


def on_owner_receiving_damage_melee(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receiving_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receiving_damage_poison(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receiving_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receiving_damage_future1(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receiving_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receiving_damage_future2(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receiving_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receiving_damage_future3(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receiving_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receiving_damage_cold(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receiving_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receiving_damage_fire(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receiving_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receiving_damage_crush(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receiving_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receiving_damage_lightning(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receiving_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receiving_damage_energy(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receiving_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receiving_damage_acid(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receiving_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receiving_damage_digest(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receiving_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receiving_damage_nat_attack(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receiving_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receiving_damage_necrosis(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receiving_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receiving_damage_stat_str(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receiving_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receiving_damage_stat_con(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receiving_damage(me, owner, hitter, real_hitter, x, y, damage)


def tp_init(name, text_name):
    global self
    self = tp.Tp(name, text_name)

    my.is_buff(self, True)
    my.is_loggable(self, True)
    my.long_text_description(self, "Missile attacks cause half damage.")
    my.on_owner_add_do(self, "me.on_owner_add()")
    my.on_owner_receiving_damage_acid_do(self, "me.on_owner_receiving_damage_acid()")
    my.on_owner_receiving_damage_cold_do(self, "me.on_owner_receiving_damage_cold()")
    my.on_owner_receiving_damage_crush_do(self, "me.on_owner_receiving_damage_crush()")
    my.on_owner_receiving_damage_digest_do(self, "me.on_owner_receiving_damage_digest()")
    my.on_owner_receiving_damage_energy_do(self, "me.on_owner_receiving_damage_energy()")
    my.on_owner_receiving_damage_fire_do(self, "me.on_owner_receiving_damage_fire()")
    my.on_owner_receiving_damage_future1_do(self, "me.on_owner_receiving_damage_future1()")
    my.on_owner_receiving_damage_future2_do(self, "me.on_owner_receiving_damage_future2()")
    my.on_owner_receiving_damage_future3_do(self, "me.on_owner_receiving_damage_future3()")
    my.on_owner_receiving_damage_lightning_do(self, "me.on_owner_receiving_damage_lightning()")
    my.on_owner_receiving_damage_melee_do(self, "me.on_owner_receiving_damage_melee()")
    my.on_owner_receiving_damage_nat_attack_do(self, "me.on_owner_receiving_damage_nat_attack()")
    my.on_owner_receiving_damage_necrosis_do(self, "me.on_owner_receiving_damage_necrosis()")
    my.on_owner_receiving_damage_poison_do(self, "me.on_owner_receiving_damage_poison()")
    my.on_owner_receiving_damage_stat_con_do(self, "me.on_owner_receiving_damage_stat_con()")
    my.on_owner_receiving_damage_stat_str_do(self, "me.on_owner_receiving_damage_stat_str()")
    my.on_owner_remove_do(self, "me.on_owner_remove()")
    # my.z_prio(self, my.MAP_PRIO_NORMAL) # End marker for fixup.sh
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="buff_missile_resist")
    my.tp_update(self)


def init():
    tp_init(name="buff_missile_resist", text_name="missile resist")


init()
