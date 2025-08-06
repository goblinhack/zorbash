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
    my.text_description_long2(self, "However, if you become hungry or starved, you will lose points on attack and defense and other abilities may also be impacted.")
    my.text_description_long3(self, "Best to keep food at hand.")
    my.text_description_long(self, "Hunger does not kill in this game.")
    my.text_description_short(self, "You are satiated.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    # end sort marker

    my.tile(self,
            tile="buff_status_full")
    my.tp_update(self)


def init():
    tp_init(name="buff_status_full",
            text_long_name="full and happy",
            text_short_name="full")


init()
