import my
import tp

mytp = None


def on_tick(owner, item, x, y):
    poison = my.thing_get_poisoned_amount(owner)
    if poison == 0:
        if my.thing_is_player(owner):
            my.topcon("You are no longer poisoned.")
        my.thing_kill(item, "end of debuff")
        return True
    # Too noisy
    # my.topcon("%%fg=yellow$You are poisoned!%%fg=reset$")
    return True


def tp_init(name, text_name):
    global mytp
    mytp = tp.Tp(name, text_name)

    mytp.set_is_debuff(True)
    mytp.set_is_loggable(True)
    mytp.set_long_text_description("Poison courses through your unlucky veins.")
    mytp.set_on_tick_do("me.on_tick()")
    mytp.set_text_debuff("You are poisoned")
    mytp.set_text_description("Poisoned debuff.")
    mytp.set_tile(tile="debuff_poisoned")
    # mytp.set_z_prio(my.MAP_PRIO_NORMAL) # End marker for fixup.sh
    mytp.update()


def init():
    tp_init(name="debuff_poisoned", text_name="poisoned")


init()
