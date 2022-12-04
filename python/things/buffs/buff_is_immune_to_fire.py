import my
import tp

self = None


def on_owner_add(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "A protective red glow surrounds you.")


# Called on removing a ring. Not called on death of the owner.
def on_owner_remove(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "The protective red glow around you fades.")


def on_owner_receive_dmg_fire(me, owner, hitter, real_hitter, x, y, damage):
    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    # my.con("owner   {} {:X}".format(my.thing_name_get(owner), owner))
    # my.con("hitter  {} {:X}".format(my.thing_name_get(hitter), hitter))
    # my.con("rhitter {} {:X}".format(my.thing_name_get(real_hitter), real_hitter))
    if my.thing_is_player(owner):
        my.thing_msg(me, "You take no fire damage.")
    return 0


def tp_init(name, text_long_name):
    global self
    self = tp.Tp(name, text_long_name)
    # begin sort marker

    my.gfx_ascii_shown(self, True)
    my.is_buff(self, True)
    my.is_immune_to_fire(self, True)
    my.is_loggable(self, True)
    my.on_owner_add_do(self, "me.on_owner_add()")
    my.on_owner_receive_dmg_fire_do(self, "me.on_owner_receive_dmg_fire()")
    my.on_owner_remove_do(self, "me.on_owner_remove()")
    my.text_description_long(self, "You bask in the hottest of fires.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self,
            tile="buff_is_immune_to_fire")
    my.tp_update(self)


def init():
    tp_init(name="buff_is_immune_to_fire", text_long_name="fire proof")


init()
