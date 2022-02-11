import my
import tp


def tp_init(name):
    text_name = "the grid"
    self = tp.Tp(name, text_name)
    my.tp_set_is_the_grid(self, True)
    my.tp_set_text_a_or_an(self, "the")
    my.tp_set_text_description(self, "The grid.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_THE_GRID)
    my.tp_set_z_prio(self, my.MAP_PRIO_NORMAL)

    my.tp_set_tile(self, tile=name)
    my.tp_update(self)


def init():
    tp_init(name="the_grid")


init()
