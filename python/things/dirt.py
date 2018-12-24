import zx
import tp


def dirt_init(name, short_name, 
              tiles=[],
              left_tiles=[]):
    
    x = tp.Tp(name)

    x.set_is_boring(True)
    x.set_is_dirt(True)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_FLOOR)
    
    for t in tiles:
        x.set_tile(t)

def init():
    dirt_init(name="dirt1", short_name="The dirt", 
            tiles=[
                        "dirt1.1",
                        "dirt1.2",
                        "dirt1.3",
                        "dirt1.4",
                        "dirt1.5",
                        "dirt1.6",
                        "dirt1.7",
                        "dirt1.8",
                        "dirt1.9",
                        "dirt1.10",
                        "dirt1.11",
                        "dirt1.12",
                        "dirt1.13",
                        "dirt1.14",
                        "dirt1.15",
                        "dirt1.16",
                        "dirt1.17",
                        "dirt1.18",
                        "dirt1.19",
                        "dirt1.20",
                        "dirt1.21",
                        "dirt1.22",
                        "dirt1.23",
                        "dirt1.24",
                        "dirt1.25",
                        "dirt1.26",
                        "dirt1.27",
                        "dirt1.28",
                        "dirt1.29",
                        "dirt1.30",
                        "dirt1.31",
                        "dirt1.32",
                ])
init()
