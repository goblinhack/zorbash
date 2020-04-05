import zx
import tp


def tp_init(name, tiles=[], left1_tiles=[]):
    x = tp.Tp(name)

    x.set_is_cursor_can_hover_over(True)
    x.set_is_floor(True)
    x.set_is_interesting(False)
    x.set_is_loggable(False)
    x.set_a_or_an("the");
    x.set_is_combustible(False)
    x.set_z_depth(zx.MAP_DEPTH_FLOOR)

    for t in tiles:
        x.set_tile(t)

    x.update()

def init():
    tp_init(name="floor0",
            tiles=[
                        "floor0.1", "floor0.2", "floor0.3", "floor0.4",
                        "floor0.5", "floor0.6", "floor0.7", "floor0.8",
                        "floor0.9", "floor0.10", "floor0.11", "floor0.12",
                        "floor0.13", "floor0.14", "floor0.15", "floor0.16",
                        "floor0.17", "floor0.18", "floor0.19",
                ])
    tp_init(name="floor1",
            tiles=[
                        "floor1.1", "floor1.2", "floor1.3", "floor1.4",
                        "floor1.5", "floor1.6", "floor1.7", "floor1.8",
                        "floor1.9", "floor1.10", "floor1.11", "floor1.12",
                        "floor1.13", "floor1.14", "floor1.15", "floor1.16",
                        "floor1.17", "floor1.18", "floor1.19",
                ])
init()
