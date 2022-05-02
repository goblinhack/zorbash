import my
import tp


def tp_init(name):
    text_name = "the grid"
    self = tp.Tp(name, text_name)
    my.is_the_grid(self, True)
    my.text_a_or_an(self, "the")
    my.text_description(self, "The grid.")
    my.z_depth(self, my.MAP_DEPTH_THE_GRID)
    my.z_prio(self, my.MAP_PRIO_NORMAL)

    my.tile(self,
            ascii_fg_char="X", ascii_bg_col="", ascii_fg_col="white",
            tile=name)
    my.tp_update(self)


def init():
    tp_init(name="the_grid")


init()
