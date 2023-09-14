import my
import tp

self = None


def on_tick(owner, item, x, y):
    necrosis = my.thing_necrotized_amount_get(owner)
    if necrosis == 0:
        if my.thing_is_player(owner):
            my.thing_msg(owner, "You are no longer unpleasant any more than usual..")
        my.thing_dead(item, "end of debuff")
        return True
    return True


def tp_init(name, text_long_name):
    global self
    self = tp.Tp(name, text_long_name)
    # begin sort marker

    my.gfx_ascii_shown(self, True)
    my.is_debuff(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_tickable(self, True)
    my.on_tick_do(self, "me.on_tick()")
    my.text_debuff(self, "You are unpleasant!")
    my.text_description_long(self, "Your skin is peeling off!")
    my.text_description_short(self, "Rotting debuff.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self,
            tile="debuff_status_necrotized")
    my.tp_update(self)


def init():
    tp_init(name="debuff_status_necrotized", text_long_name="rotting")


init()
