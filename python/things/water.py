import zx
import tp


def tp_init1(name, short_name, 
              tiles=[],
              left_tiles=[]):
    
    x = tp.Tp(name)

    x.set_is_boring(True)
    x.set_is_water(True)
    x.set_is_animated(True)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_WATER)
    
    delay = 50
    for t in tiles:
        x.set_tile(tile=t, delay_ms=delay)
        x.set_tile(tile="water1.2", delay_ms=800)

def tp_init2(name, short_name, 
              tiles=[],
              left_tiles=[]):
    
    x = tp.Tp(name)

    x.set_is_boring(True)
    x.set_is_water(True)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_WATER)
    for t in tiles:
        x.set_tile(tile=t)

def init():
    tp_init1(name="water1", short_name="water", 
            tiles=[ 
                "water1.3",
                "water1.4",
                "water1.5",
                "water1.6",
                "water1.7",
                "water1.8",
                "water1.9",
                "water1.10",
                "water1.11",
                "water1.12",
                "water1.13",
                "water1.14",
                "water1.15",
                "water1.16",
                "water1.17",
                "water1.18",
                "water1.19",
                "water1.20",
                "water1.21",
                "water1.22",
                "water1.23",
                "water1.24",
                "water1.25",
                "water1.26",
                "water1.27",
                "water1.28",
                "water1.29",
                "water1.30",
                "water1.31",
                "water1.32",
                ])
    tp_init2(name="water2", short_name="water2", 
            tiles=[ 
                "water1.1",
                ])
init()
