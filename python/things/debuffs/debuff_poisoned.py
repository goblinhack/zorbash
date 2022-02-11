import my
import tp

mytp = None


def on_tick(owner, item, x, y):
    poison = my.thing_get_poisoned_amount(owner)
    if poison == 0:
        if my.thing_is_player(owner):
            my.thing_msg(owner, "You are no longer poisoned.")
        my.thing_dead(item, "end of debuff")
        return True
    return True


def tp_init(name, text_name):
    global mytp
    mytp = tp.Tp(name, text_name)

    my.tp_set_is_debuff(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_long_text_description(mytp, "Poison courses through your unlucky veins.")
    my.tp_set_on_tick_do(mytp, "me.on_tick()")
    my.tp_set_text_debuff(mytp, "You are poisoned")
    my.tp_set_text_description(mytp, "Poisoned debuff.")
    my.tp_set_tile(mytp, tile="debuff_poisoned")
    # my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL) # End marker for fixup.sh
    my.tp_update(mytp, )


def init():
    tp_init(name="debuff_poisoned", text_name="poisoned")


init()
