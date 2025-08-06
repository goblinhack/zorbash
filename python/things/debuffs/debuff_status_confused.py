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
    my.text_description_long(self, "You are confused and may be unable to walk in a straight line!")
    my.text_description_short(self, "You are confused. More so.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    # end sort marker

    my.tile(self,
            tile="debuff_status_confused")
    my.tp_update(self)


def init():
    tp_init(name="debuff_status_confused",
            text_long_name="confusion",
            text_short_name="confusion")


init()
