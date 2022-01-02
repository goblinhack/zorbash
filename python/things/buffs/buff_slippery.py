import my
import tp

mytp = None


def on_owner_set(me, owner, x, y):
    if my.thing_is_player(owner):
        my.topcon("You feel slippery as a banana.")


# Called on removing a ring. Not called on death of the owner.
def on_owner_unset(me, owner, x, y):
    if my.thing_is_player(owner):
        my.topcon("You return to your normal level of stickiness.")


def tp_init(name, text_name):
    global mytp
    mytp = tp.Tp(name, text_name)

    mytp.set_is_buff(True)
    mytp.set_is_loggable(True)
    mytp.set_is_slippery(True)
    mytp.set_long_text_description("No more trapped in webs for you! With this buff you can glide with ease through the cobwebs.")
    mytp.set_on_owner_set_do("me.on_owner_set()")
    mytp.set_on_owner_unset_do("me.on_owner_unset()")
    mytp.set_text_description("You are as slippery as a banana buff.")
    mytp.set_tile(tile="buff_slippery")
    # mytp.set_z_prio(my.MAP_PRIO_NORMAL) # End marker for fixup.sh
    mytp.update()


def init():
    tp_init(name="buff_slippery", text_name="slippery as the banana")


init()
