import my
import tp

self = None


def on_owner_add(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "You feel at one with the water.")


# Called on removing a ring. Not called on death of the owner.
def on_owner_remove(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "You return to your normal level of stickiness.")


def tp_init(name, text_name):
    global self
    self = tp.Tp(name, text_name)

    my.is_aquatic(self, True)
    my.is_buff(self, True)
    my.is_loggable(self, True)
    my.long_text_description(self, "You feel at home in the water and will suffer no more water penalties for either attack or defence when in shallow or deep water. Always beware of puddles though.")
    my.on_owner_add_do(self, "me.on_owner_add()")
    my.on_owner_remove_do(self, "me.on_owner_remove()")
    my.text_description(self, "You are as at home in the water as on the land. If you ever were.")
    my.tile(self, tile="buff_aquatic")
    # my.z_prio(self, my.MAP_PRIO_NORMAL) # End marker for fixup.sh
    my.tp_update(self)


def init():
    tp_init(name="buff_aquatic", text_name="aquatic lover")


init()
