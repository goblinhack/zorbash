import my
import tp

self = None


def on_owner_add(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "A protective glow surrounds you.")


# Called on removing a ring. Not called on death of the owner.
def on_owner_remove(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "The protective glow around you fades.")


def on_owner_damage(me, owner, hitter, x, y, damage):
    if my.thing_is_player(owner):
        return int(damage / 2)
    return damage


def on_owner_damage_melee(me, owner, hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, x, y, damage)


def on_owner_damage_poison(me, owner, hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, x, y, damage)


def on_owner_damage_future1(me, owner, hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, x, y, damage)


def on_owner_damage_future2(me, owner, hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, x, y, damage)


def on_owner_damage_future3(me, owner, hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, x, y, damage)


def on_owner_damage_cold(me, owner, hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, x, y, damage)


def on_owner_damage_fire(me, owner, hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, x, y, damage)


def on_owner_damage_crush(me, owner, hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, x, y, damage)


def on_owner_damage_lightning(me, owner, hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, x, y, damage)


def on_owner_damage_energy(me, owner, hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, x, y, damage)


def on_owner_damage_acid(me, owner, hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, x, y, damage)


def on_owner_damage_digest(me, owner, hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, x, y, damage)


def on_owner_damage_natural_attack(me, owner, hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, x, y, damage)


def on_owner_damage_necrosis(me, owner, hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, x, y, damage)


def on_owner_damage_stat_str(me, owner, hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, x, y, damage)


def on_owner_damage_stat_con(me, owner, hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, x, y, damage)


def tp_init(name, text_name):
    global self
    self = tp.Tp(name, text_name)

    my.is_buff(self, True)
    my.is_loggable(self, True)
    my.long_text_description(self, "Undead only cause you half damage.")
    my.on_owner_add_do(self, "me.on_owner_add()")
    my.on_owner_damage_acid_do(self, "me.on_owner_damage_acid()")
    my.on_owner_damage_cold_do(self, "me.on_owner_damage_cold()")
    my.on_owner_damage_crush_do(self, "me.on_owner_damage_crush()")
    my.on_owner_damage_digest_do(self, "me.on_owner_damage_digest()")
    my.on_owner_damage_energy_do(self, "me.on_owner_damage_energy()")
    my.on_owner_damage_fire_do(self, "me.on_owner_damage_fire()")
    my.on_owner_damage_future1_do(self, "me.on_owner_damage_future1()")
    my.on_owner_damage_future2_do(self, "me.on_owner_damage_future2()")
    my.on_owner_damage_future3_do(self, "me.on_owner_damage_future3()")
    my.on_owner_damage_lightning_do(self, "me.on_owner_damage_lightning()")
    my.on_owner_damage_melee_do(self, "me.on_owner_damage_melee()")
    my.on_owner_damage_natural_attack_do(self, "me.on_owner_damage_natural_attack()")
    my.on_owner_damage_necrosis_do(self, "me.on_owner_damage_necrosis()")
    my.on_owner_damage_poison_do(self, "me.on_owner_damage_poison()")
    my.on_owner_damage_stat_con_do(self, "me.on_owner_damage_stat_con()")
    my.on_owner_damage_stat_str_do(self, "me.on_owner_damage_stat_str()")
    my.on_owner_remove_do(self, "me.on_owner_remove()")
    my.text_description(self, "Poison resistant buff.")
    my.tile(self, tile="buff_undead_resist")
    # my.z_prio(self, my.MAP_PRIO_NORMAL) # End marker for fixup.sh
    my.tp_update(self)


def init():
    tp_init(name="buff_undead_resist", text_name="undead resist")


init()
