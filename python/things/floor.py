import zx
import tp


def tp_init(name, short_name, 
              tiles=[],
              left_tiles=[]):
    
    x = tp.Tp(name)

    x.set_is_boring(True)
    x.set_is_floor(True)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_FLOOR)
    
    for t in tiles:
        x.set_tile(t)

def init():
    tp_init(name="floor1", short_name="The floor", 
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
                ])
    tp_init(name="floor2", short_name="The floor", 
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
                ])
init()
