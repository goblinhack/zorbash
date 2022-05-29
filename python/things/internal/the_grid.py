import my
import tp


def tp_init(name):
    text_name = "the grid"
    self = tp.Tp(name, text_name)
    # start sort marker
    my.gfx_ascii_mode_shown(self, False)
    my.is_the_grid(self, True)
    my.text_a_or_an(self, "the")
    my.text_description(self, "The grid.")
    # end sort marker
    my.tile(self, tile=name)
    my.tp_update(self)


def init():
    tp_init(name="the_grid")


init()
