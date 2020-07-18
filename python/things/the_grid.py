import zx
import tp


def tp_init(name):
    text_name = "the grid"
    x = tp.Tp(name, text_name)

    x.set_is_the_grid(True)
    x.set_is_floating(True)
    x.set_text_a_or_an("the");
    x.set_text_description("The grid")
    x.set_z_depth(zx.MAP_DEPTH_THE_GRID)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    x.set_tile(tile=name)
    x.update()

def init():
    tp_init(name="the_grid")

init()
