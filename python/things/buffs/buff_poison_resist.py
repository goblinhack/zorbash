import my
import tp

self = None


def on_owner_add(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "A green glow surrounds you.")


# Called on removing a ring. Not called on death of the owner.
def on_owner_remove(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "The green glow around you fades.")


def on_owner_damage_melee(me, owner, hitter, x, y, damage):
    return damage


def on_owner_damage_poison(me, owner, hitter, x, y, damage):
    return int(damage / 2)


def on_owner_damage_future1(me, owner, hitter, x, y, damage):
    return damage


def on_owner_damage_future2(me, owner, hitter, x, y, damage):
    return damage


def on_owner_damage_future3(me, owner, hitter, x, y, damage):
    return damage


def on_owner_damage_cold(me, owner, hitter, x, y, damage):
    return damage


def on_owner_damage_fire(me, owner, hitter, x, y, damage):
    return damage


def on_owner_damage_crush(me, owner, hitter, x, y, damage):
    return damage


def on_owner_damage_lightning(me, owner, hitter, x, y, damage):
    return damage


def on_owner_damage_energy(me, owner, hitter, x, y, damage):
    return damage


def on_owner_damage_acid(me, owner, hitter, x, y, damage):
    return damage


def on_owner_damage_digest(me, owner, hitter, x, y, damage):
    return damage


def on_owner_damage_natural_attack(me, owner, hitter, x, y, damage):
    return damage


def on_owner_damage_necrosis(me, owner, hitter, x, y, damage):
    return damage


def on_owner_damage_stat_str(me, owner, hitter, x, y, damage):
    return damage


def on_owner_damage_stat_con(me, owner, hitter, x, y, damage):
    return damage


def on_tick(owner, item, x, y):
    poison = my.thing_get_poisoned_amount(item)
    if poison == 0:
        return True
    new_poison = int(poison / 2)
    if my.thing_is_player(owner):
        if new_poison == 0:
            my.thing_msg(owner, "%%fg=green$The poison has little effect on you!%%fg=reset$")
        else:
            my.thing_msg(owner, "%%fg=green$The poison fades from your system!%%fg=reset$")
    my.thing_set_poisoned_amount(owner, new_poison)
    return True


def tp_init(name, text_name):
    global self
    self = tp.Tp(name, text_name)

    my.tp_set_is_buff(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_long_text_description(self, "Poison causes you 50 percent less damage.")
    my.tp_set_on_owner_damage_acid_do(self, "me.on_owner_damage_acid()")
    my.tp_set_on_owner_damage_cold_do(self, "me.on_owner_damage_cold()")
    my.tp_set_on_owner_damage_crush_do(self, "me.on_owner_damage_crush()")
    my.tp_set_on_owner_damage_digest_do(self, "me.on_owner_damage_digest()")
    my.tp_set_on_owner_damage_energy_do(self, "me.on_owner_damage_energy()")
    my.tp_set_on_owner_damage_fire_do(self, "me.on_owner_damage_fire()")
    my.tp_set_on_owner_damage_future1_do(self, "me.on_owner_damage_future1()")
    my.tp_set_on_owner_damage_future2_do(self, "me.on_owner_damage_future2()")
    my.tp_set_on_owner_damage_future3_do(self, "me.on_owner_damage_future3()")
    my.tp_set_on_owner_damage_lightning_do(self, "me.on_owner_damage_lightning()")
    my.tp_set_on_owner_damage_melee_do(self, "me.on_owner_damage_melee()")
    my.tp_set_on_owner_damage_natural_attack_do(self, "me.on_owner_damage_natural_attack()")
    my.tp_set_on_owner_damage_necrosis_do(self, "me.on_owner_damage_necrosis()")
    my.tp_set_on_owner_damage_poison_do(self, "me.on_owner_damage_poison()")
    my.tp_set_on_owner_damage_stat_con_do(self, "me.on_owner_damage_stat_con()")
    my.tp_set_on_owner_damage_stat_str_do(self, "me.on_owner_damage_stat_str()")
    my.tp_set_on_owner_add_do(self, "me.on_owner_add()")
    my.tp_set_on_owner_remove_do(self, "me.on_owner_remove()")
    my.tp_set_on_tick_do(self, "me.on_tick()")
    my.tp_set_text_description(self, "Poison resistant buff.")
    my.tp_set_tile(self, tile="buff_poison_resist")
    # my.tp_set_z_prio(self, my.MAP_PRIO_NORMAL) # End marker for fixup.sh
    my.tp_update(self)


def init():
    tp_init(name="buff_poison_resist", text_name="poison lover")


init()
