import my
import tp

mytp = None


def on_owner_set(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "You feel at one with the water.")


# Called on removing a ring. Not called on death of the owner.
def on_owner_unset(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "You return to your normal level of stickiness.")


def tp_init(name, text_name):
    global mytp
    mytp = tp.Tp(name, text_name)

    my.tp_set_is_aquatic(mytp, True)
    my.tp_set_is_buff(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_long_text_description(mytp, "You feel at home in the water and will suffer no more water penalties for either attack or defence when in shallow or deep water. Always beware of puddles though.")
    my.tp_set_on_owner_set_do(mytp, "me.on_owner_set()")
    my.tp_set_on_owner_unset_do(mytp, "me.on_owner_unset()")
    my.tp_set_text_description(mytp, "You are as at home in the water as on the land. If you ever were.")
    my.tp_set_tile(mytp, tile="buff_aquatic")
    # my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL) # End marker for fixup.sh
    my.tp_update(mytp, )


def init():
    tp_init(name="buff_aquatic", text_name="aquatic lover")


init()
