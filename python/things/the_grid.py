import my
import tp


def tp_init(name):
    text_name = "the grid"
    mytp = tp.Tp(name, text_name)
    mytp.set_is_able_to_fall(False)
    mytp.set_is_the_grid(True)
    mytp.set_text_a_or_an("the")
    mytp.set_text_description("The grid.")
    mytp.set_z_depth(my.MAP_DEPTH_THE_GRID)
    mytp.set_z_prio(my.MAP_PRIO_NORMAL)

    mytp.set_tile(tile=name)
    mytp.update()

def init():
    tp_init(name="the_grid")

init()
