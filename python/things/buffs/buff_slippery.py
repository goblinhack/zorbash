import my
import tp

mytp = None


def on_owner_set(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "You feel slippery as a banana.")


# Called on removing a ring. Not called on death of the owner.
def on_owner_unset(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "You return to your normal level of stickiness.")


def tp_init(name, text_name):
    global mytp
    mytp = tp.Tp(name, text_name)

    my.tp_set_is_buff(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_slippery(mytp, True)
    my.tp_set_long_text_description(mytp, "No more trapped in webs for you! With this buff you can glide with ease through the cobwebs.")
    my.tp_set_on_owner_set_do(mytp, "me.on_owner_set()")
    my.tp_set_on_owner_unset_do(mytp, "me.on_owner_unset()")
    my.tp_set_text_description(mytp, "You are as slippery as a banana buff.")
    my.tp_set_tile(mytp, tile="buff_slippery")
    # my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL) # End marker for fixup.sh
    my.tp_update(mytp, )


def init():
    tp_init(name="buff_slippery", text_name="slippery as the banana")


init()
