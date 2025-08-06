import my
import tp

self = None


def on_owner_add(me, owner, x, y):
    if owner and my.thing_is_player(owner):
        my.thing_msg(me, "A green glow surrounds you.")


# Called on removing a ring. Not called on death of the owner.
def on_owner_unset(me, owner, x, y):
    if owner and my.thing_is_player(owner):
        my.thing_msg(me, "The green glow around you fades.")


def on_owner_rcv_dmg_poison(me, owner, hitter, real_hitter, x, y, damage):
    if owner and my.thing_is_player(owner):
        my.thing_msg(me, "You take half damage from the poison.")
    return int(damage / 2)


def on_tick(owner, item, x, y):
    poison = my.thing_poisoned_amount_get(item)
    if poison == 0:
        return False
    new_poison = int(poison / 2)
    if owner and my.thing_is_player(owner):
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
    my.is_immune_to_poison(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_runic_defensive_class_A(self, True)
    my.is_tickable(self, True)
    my.on_owner_add_do(self, "me.on_owner_add()")
    my.on_owner_rcv_dmg_poison_do(self, "me.on_owner_rcv_dmg_poison()")
    my.on_owner_unset_do(self, "me.on_owner_unset()")
    my.on_tick_do(self, "me.on_tick()")
    my.text_description_long(self, "Poison causes you 50 percent less damage.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self,
            tile="buff_immune_to_poison")
    my.tp_update(self)


def init():
    tp_init(name="buff_permanent_immune_to_poison",
            text_long_name="poison immunity")


init()
