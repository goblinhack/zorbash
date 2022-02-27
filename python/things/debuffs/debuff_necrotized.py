import my
import tp

self = None


def on_tick(owner, item, x, y):
    necrosis = my.thing_necrotized_amount_get(owner)
    if necrosis == 0:
        if my.thing_is_player(owner):
            my.thing_msg(owner, "You are no longer rotting any more than usual..")
        my.thing_dead(item, "end of debuff")
        return True
    return True


def tp_init(name, text_name):
    global self
    self = tp.Tp(name, text_name)

    my.is_debuff(self, True)
    my.is_loggable(self, True)
    my.is_tickable(self, True)
    my.long_text_description(self, "Your skin is peeling off!")
    my.on_tick_do(self, "me.on_tick()")
    my.text_debuff(self, "You are rotting!")
    my.text_description(self, "Rotting debuff.")
    my.tile(self, tile="debuff_necrotized")
    # my.z_prio(self, my.MAP_PRIO_NORMAL) # End marker for fixup.sh
    my.tp_update(self)


def init():
    tp_init(name="debuff_necrotized", text_name="rotting away")


init()
