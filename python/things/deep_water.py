import zx
import tp


def deep_tp_init(name, short_name, 
              tiles=[],
              left_tiles=[]):
    
    x = tp.Tp(name)

    x.set_is_boring(True)
    x.set_is_deep_water(True)
    x.set_is_animated(True)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_WATER)
    
    delay = 1250
    for t in tiles:
        x.set_tile(tile=t, delay_ms=delay)

def init():
    deep_tp_init(name="deep_water1", short_name="deep_water", 
            tiles=[ 
                "deep_water1.1", 
                "deep_water1.2", 
                "deep_water1.3", 
                "deep_water1.4", 
                "deep_water1.5", 
                "deep_water1.6", 
                "deep_water1.7", 
                "deep_water1.8", 
                ])
init()
