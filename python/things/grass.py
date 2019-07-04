import zx
import tp


def grass_init(name, tiles=[], left_tiles=[]):
    
    x = tp.Tp(name)

    x.set_does_nothing(True)
    x.set_is_grass(True)
    x.set_z_depth(zx.MAP_DEPTH_FLOOR)
    
    for t in tiles:
        x.set_tile(t)

    x.update()
    
def init():
    grass_init(name="grass1",
            tiles=[
                        "grass1.1",
                        "grass1.2",
                        "grass1.3",
                        "grass1.4",
                        "grass1.5",
                        "grass1.6",
                        "grass1.7",
                        "grass1.8",
                        "grass1.9",
                        "grass1.10",
                        "grass1.11",
                        "grass1.12",
                        "grass1.13",
                        "grass1.14",
                        "grass1.15",
                        "grass1.16",
                        "grass1.17",
                        "grass1.18",
                        "grass1.19",
                        "grass1.20",
                ])
    grass_init(name="grass2",
            tiles=[
                        "grass2.1",
                        "grass2.2",
                        "grass2.3",
                        "grass2.4",
                        "grass2.5",
                        "grass2.6",
                        "grass2.7",
                        "grass2.8",
                        "grass2.9",
                        "grass2.10",
                        "grass2.11",
                        "grass2.12",
                        "grass2.13",
                        "grass2.14",
                        "grass2.15",
                        "grass2.16",
                        "grass2.17",
                        "grass2.18",
                        "grass2.19",
                        "grass2.20",
                ])
    grass_init(name="grass3",
            tiles=[
                        "grass3.1",
                        "grass3.2",
                        "grass3.3",
                        "grass3.4",
                        "grass3.5",
                        "grass3.6",
                        "grass3.7",
                        "grass3.8",
                        "grass3.9",
                        "grass3.10",
                        "grass3.11",
                        "grass3.12",
                        "grass3.13",
                        "grass3.14",
                        "grass3.15",
                        "grass3.16",
                        "grass3.17",
                        "grass3.18",
                        "grass3.19",
                        "grass3.20",
                ])
init()
