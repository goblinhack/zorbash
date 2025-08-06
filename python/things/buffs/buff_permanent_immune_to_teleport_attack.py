import my
import tp

self = None


def on_owner_add(me, owner, x, y):
    if owner and my.thing_is_player(owner):
        my.thing_msg(me, "You feel substantial.")


# Called on removing a ring. Not called on death of the owner.
def on_owner_unset(me, owner, x, y):
    if owner and my.thing_is_player(owner):
        my.thing_msg(me, "You feel less substantial.")


def tp_init(name, text_long_name):
    global self
    self = tp.Tp(name, text_long_name)
    # begin sort marker

    my.gfx_ascii_shown(self, True)
    my.is_buff(self, True)
    my.is_immune_to_teleport_attack(self, True)
    my.is_loggable(self, True)
    my.is_runic_defensive_class_A(self, True)
    my.on_owner_add_do(self, "me.on_owner_add()")
    my.on_owner_unset_do(self, "me.on_owner_unset()")
    my.text_description_long(self, "You cannot be teleported against your will.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self,
            tile="buff_immune_to_teleport_attack")
    my.tp_update(self)


def init():
    tp_init(name="buff_permanent_immune_to_teleport_attack",
            text_long_name="teleport attack protection")


init()
