import zx
import tp


def corridor_init(name, tiles=[], tile_lefts=[]):
    x = tp.Tp(name)

    x.set_is_corridor(True)
    x.set_is_interesting(False)
    x.set_is_loggable(False)
    x.set_z_depth(zx.MAP_DEPTH_FLOOR)

    for t in tiles:
        x.set_tile(t)

    x.update()
    
def init():
    corridor_init(name="corridor1",
            tiles=[
                        "corridor1.1",
                        "corridor1.2",
                        "corridor1.3",
                        "corridor1.4",
                        "corridor1.5",
                        "corridor1.6",
                        "corridor1.7",
                        "corridor1.8",
                        "corridor1.9",
                        "corridor1.10",
                        "corridor1.11",
                        "corridor1.12",
                        "corridor1.13",
                        "corridor1.14",
                        "corridor1.15",
                        "corridor1.16",
                        "corridor1.17",
                        "corridor1.18",
                        "corridor1.19",
                        "corridor1.20",
                        "corridor1.21",
                        "corridor1.22",
                        "corridor1.23",
                        "corridor1.24",
                        "corridor1.25",
                        "corridor1.26",
                        "corridor1.27",
                        "corridor1.28",
                        "corridor1.29",
                        "corridor1.30",
                        "corridor1.31",
                        "corridor1.32",
                ])
init()
