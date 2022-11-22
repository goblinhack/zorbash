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


def on_owner_receive_dmg_melee(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def on_owner_receive_dmg_poison(me, owner, hitter, real_hitter, x, y, damage):
    if my.thing_is_player(owner):
        my.thing_msg(me, "You take half damage from the poison.")
    return int(damage / 2)


def on_owner_receive_dmg_drown(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def on_owner_receive_dmg_bite(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def on_owner_receive_dmg_claw(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def on_owner_receive_dmg_cold(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def on_owner_receive_dmg_fire(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def on_owner_receive_dmg_crush(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def on_owner_receive_dmg_lightning(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def on_owner_receive_dmg_energy(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def on_owner_receive_dmg_acid(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def on_owner_receive_dmg_digest(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def on_owner_receive_dmg_nat_att(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def on_owner_receive_dmg_necrosis(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def on_owner_receive_dmg_draining(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def on_owner_receive_dmg_stat_str(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def on_owner_receive_dmg_stat_con(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def on_tick(owner, item, x, y):
    poison = my.thing_poisoned_amount_get(item)
    if poison == 0:
        return True
    new_poison = int(poison / 2)
    if my.thing_is_player(owner):
        if new_poison == 0:
            my.thing_msg(owner, "%%fg=green$The poison has little effect on you!%%fg=reset$")
        else:
            my.thing_msg(owner, "%%fg=green$The poison fades from your system!%%fg=reset$")
    my.thing_poisoned_amount_set(owner, new_poison)
    return True


def tp_init(name, text_long_name):
    global self
    self = tp.Tp(name, text_long_name)
    # begin sort marker

    my.gfx_ascii_shown(self, True)
    my.is_buff(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_tickable(self, True)
    my.on_owner_add_do(self, "me.on_owner_add()")
    my.on_owner_receive_dmg_acid_do(self, "me.on_owner_receive_dmg_acid()")
    my.on_owner_receive_dmg_bite_do(self, "me.on_owner_receive_dmg_bite()")
    my.on_owner_receive_dmg_claw_do(self, "me.on_owner_receive_dmg_claw()")
    my.on_owner_receive_dmg_cold_do(self, "me.on_owner_receive_dmg_cold()")
    my.on_owner_receive_dmg_crush_do(self, "me.on_owner_receive_dmg_crush()")
    my.on_owner_receive_dmg_digest_do(self, "me.on_owner_receive_dmg_digest()")
    my.on_owner_receive_dmg_draining_do(self, "me.on_owner_receive_dmg_draining()")
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
    my.on_owner_remove_do(self, "me.on_owner_remove()")
    my.on_tick_do(self, "me.on_tick()")
    my.text_description_long(self, "Poison causes you 50 percent less damage.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    # my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND) # End marker for fixup.sh
    # end sort marker
    my.tile(self,
            tile="buff_poison_resist")
    my.tp_update(self)


def init():
    tp_init(name="buff_poison_resist", text_long_name="poison resist")


init()
