import my
import tp

self = None


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)

    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_buff(self, True)
    my.is_loggable(self, True)
    my.text_description_long(self, "You are currently raging and deal more damage with more chance of hitting")
    my.text_description_long2(self, "Your stamina will decrease faster than normal while raging.")
    my.text_description_short(self, "You are satiated.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    # end sort marker

    my.tile(self,
            tile="buff_raging")
    my.tp_update(self)


def init():
    tp_init(name="buff_permanent_raging", text_long_name="raging mad", text_short_name="raging")


init()
