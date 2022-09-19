import my
import tp


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # start sort marker
    my.gfx_ascii_shown(self, False)
    my.is_internal(self, True)
    my.is_the_grid(self, True)
    my.text_a_or_an(self, "the")
    my.text_short_description(self, "The grid.")
    # end sort marker
    my.tile(self, tile=name)
    my.tp_update(self)


def init():
    tp_init("the_grid", "ground", "ground")


init()
