import my
import tp

mytp = None


def on_owner_set(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "A green glow surrounds you.")


# Called on removing a ring. Not called on death of the owner.
def on_owner_unset(me, owner, x, y):
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


def on_owner_damage_future4(me, owner, hitter, x, y, damage):
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
    global mytp
    mytp = tp.Tp(name, text_name)

    mytp.set_is_buff(True)
    mytp.set_is_loggable(True)
    mytp.set_long_text_description("Poison causes you 50 percent less damage.")
    mytp.set_on_owner_damage_acid_do("me.on_owner_damage_acid()")
    mytp.set_on_owner_damage_crush_do("me.on_owner_damage_crush()")
    mytp.set_on_owner_damage_digest_do("me.on_owner_damage_digest()")
    mytp.set_on_owner_damage_energy_do("me.on_owner_damage_energy()")
    mytp.set_on_owner_damage_fire_do("me.on_owner_damage_fire()")
    mytp.set_on_owner_damage_future1_do("me.on_owner_damage_future1()")
    mytp.set_on_owner_damage_future2_do("me.on_owner_damage_future2()")
    mytp.set_on_owner_damage_future3_do("me.on_owner_damage_future3()")
    mytp.set_on_owner_damage_future4_do("me.on_owner_damage_future4()")
    mytp.set_on_owner_damage_lightning_do("me.on_owner_damage_lightning()")
    mytp.set_on_owner_damage_melee_do("me.on_owner_damage_melee()")
    mytp.set_on_owner_damage_natural_attack_do("me.on_owner_damage_natural_attack()")
    mytp.set_on_owner_damage_necrosis_do("me.on_owner_damage_necrosis()")
    mytp.set_on_owner_damage_poison_do("me.on_owner_damage_poison()")
    mytp.set_on_owner_damage_stat_con_do("me.on_owner_damage_stat_con()")
    mytp.set_on_owner_damage_stat_str_do("me.on_owner_damage_stat_str()")
    mytp.set_on_owner_set_do("me.on_owner_set()")
    mytp.set_on_owner_unset_do("me.on_owner_unset()")
    mytp.set_on_tick_do("me.on_tick()")
    mytp.set_text_description("Poison resistant buff.")
    mytp.set_tile(tile="buff_poison_resist")
    # mytp.set_z_prio(my.MAP_PRIO_NORMAL) # End marker for fixup.sh
    mytp.update()


def init():
    tp_init(name="buff_poison_resist", text_name="poison lover")


init()
