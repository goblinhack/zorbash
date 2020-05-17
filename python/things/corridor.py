import zx
import tp


def tp_init(name, tiles=[], left1_tiles=[]):
    x = tp.Tp(name)

    x.set_is_cursor_can_hover_over(True)
    x.set_is_corridor(True)
    x.set_is_interesting(False)
    x.set_is_loggable(False)
    x.set_a_or_an("the");
    x.set_z_depth(zx.MAP_DEPTH_FLOOR)

    for t in tiles:
        x.set_tile(t)

    x.update()

def init():
    tp_init(name="corridor1",
            tiles=[
                        "corridor1.1", "corridor1.2", "corridor1.3", "corridor1.4",
                        "corridor1.5", "corridor1.6", "corridor1.7", "corridor1.8",
                        "corridor1.9", "corridor1.10", "corridor1.11", "corridor1.12",
                        "corridor1.13", "corridor1.14", "corridor1.15", "corridor1.16",
                        "corridor1.17", "corridor1.18", "corridor1.19",
                ])
init()
