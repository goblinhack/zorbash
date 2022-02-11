import my
import tp

self = None


def on_tick(owner, item, x, y):
    necrosis = my.thing_get_necrotized_amount(owner)
    if necrosis == 0:
        if my.thing_is_player(owner):
            my.thing_msg(owner, "You are no longer rotting any more than usual..")
        my.thing_dead(item, "end of debuff")
        return True
    return True


def tp_init(name, text_name):
    global self
    self = tp.Tp(name, text_name)

    my.tp_set_is_debuff(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_long_text_description(self, "Your skin is peeling off!")
    my.tp_set_on_tick_do(self, "me.on_tick()")
    my.tp_set_text_debuff(self, "You are rotting!")
    my.tp_set_text_description(self, "Rotting debuff.")
    my.tp_set_tile(self, tile="debuff_necrotized")
    # my.tp_set_z_prio(self, my.MAP_PRIO_NORMAL) # End marker for fixup.sh
    my.tp_update(self)


def init():
    tp_init(name="debuff_necrotized", text_name="rotting away")


init()
