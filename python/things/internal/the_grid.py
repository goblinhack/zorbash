import my
import tp


def tp_init(name):
    text_name = "the grid"
    mytp = tp.Tp(name, text_name)
    my.tp_set_is_the_grid(mytp, True)
    my.tp_set_text_a_or_an(mytp, "the")
    my.tp_set_text_description(mytp, "The grid.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_THE_GRID)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL)

    my.tp_set_tile(mytp, tile=name)
    my.tp_update(mytp, )


def init():
    tp_init(name="the_grid")


init()
