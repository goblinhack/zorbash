import my
import tp

self = None


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)

    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_debuff(self, True)
    my.is_loggable(self, True)
    my.text_description_long(self, "You are stuck and unable to move!")
    my.text_description_short(self, "You are stuck.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    # end sort marker

    my.tile(self,
            tile="debuff_status_stuck")
    my.tp_update(self)


def init():
    tp_init(name="debuff_status_stuck",
            text_long_name="stuck",
            text_short_name="stuck")


init()
