import zx
import tp


def tp_init(name, tiles=[], left_tiles=[]):
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
                        "floor0.1",
                        "floor0.2",
                        "floor0.3",
                        "floor0.4",
                        "floor0.5",
                        "floor0.6",
                        "floor0.7",
                        "floor0.8",
                        "floor0.9",
                        "floor0.10",
                        "floor0.11",
                        "floor0.12",
                        "floor0.13",
                        "floor0.14",
                        "floor0.15",
                        "floor0.16",
                        "floor0.17",
                        "floor0.18",
                        "floor0.19",
                        "floor0.20",
                        "floor0.21",
                        "floor0.22",
                        "floor0.23",
                        "floor0.24",
                        "floor0.25",
                        "floor0.26",
                        "floor0.27",
                        "floor0.28",
                        "floor0.29",
                        "floor0.30",
                        "floor0.31",
                        "floor0.32",
                ])
    tp_init(name="floor1",
            tiles=[
                        "floor1.1",
                        "floor1.2",
                        "floor1.3",
                        "floor1.4",
                        "floor1.5",
                        "floor1.6",
                        "floor1.7",
                        "floor1.8",
                        "floor1.9",
                        "floor1.10",
                        "floor1.11",
                        "floor1.12",
                        "floor1.13",
                        "floor1.14",
                        "floor1.15",
                        "floor1.16",
                        "floor1.17",
                        "floor1.18",
                        "floor1.19",
                        "floor1.20",
                        "floor1.21",
                        "floor1.22",
                        "floor1.23",
                        "floor1.24",
                        "floor1.25",
                        "floor1.26",
                        "floor1.27",
                        "floor1.28",
                        "floor1.29",
                        "floor1.30",
                        "floor1.31",
                        "floor1.32",
                ])
    tp_init(name="floor2",
            tiles=[
                        "floor2.1",
                        "floor2.2",
                        "floor2.3",
                        "floor2.4",
                        "floor2.5",
                        "floor2.6",
                        "floor2.7",
                        "floor2.8",
                        "floor2.9",
                        "floor2.10",
                        "floor2.11",
                        "floor2.12",
                        "floor2.13",
                        "floor2.14",
                        "floor2.15",
                        "floor2.16",
                        "floor2.17",
                        "floor2.18",
                        "floor2.19",
                        "floor2.20",
                        "floor2.21",
                        "floor2.22",
                        "floor2.23",
                        "floor2.24",
                        "floor2.25",
                        "floor2.26",
                        "floor2.27",
                        "floor2.28",
                        "floor2.29",
                        "floor2.30",
                        "floor2.31",
                        "floor2.32",
                ])
init()
