import my
import tp

self = None


def on_owner_add(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "A protective negative glow surrounds you.")


# Called on removing a ring. Not called on death of the owner.
def on_owner_remove(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "The protective negative glow around you fades.")


def on_owner_receive_dmg_negation(me, owner, hitter, real_hitter, x, y, damage):
    if my.thing_is_player(me):
        my.thing_msg(me, "You take no damage from the negation.")
    return 0


def tp_init(name, text_long_name):
    global self
    self = tp.Tp(name, text_long_name)
    # begin sort marker

    my.gfx_ascii_shown(self, True)
    my.is_buff(self, True)
    my.is_immune_to_negation(self, True)
    my.is_loggable(self, True)
    my.on_owner_add_do(self, "me.on_owner_add()")
    # my.on_owner_receive_dmg_negation_do(self, "me.on_owner_receive_dmg_negation()")
    my.on_owner_remove_do(self, "me.on_owner_remove()")
    my.text_description_long(self, "You cannot be negated.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self,
            tile="buff_negation_resist")
    my.tp_update(self)


def init():
    tp_init(name="buff_negation_resist", text_long_name="negation proof")


init()
