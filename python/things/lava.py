import zx
import tp


def lava_init(name, short_name, 
              tiles=[],
              left_tiles=[]):
    
    x = tp.Tp(name)

    x.set_is_boring(True)
    x.set_is_lava(True)
    x.set_gfx_animated(True)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_LAVA)
    
    delay = 1250
    for t in tiles:
        x.set_tile(tile=t, delay_ms=delay)

def init():
    lava_init(name="lava1", short_name="Lava", 
            tiles=[ 
                "lava1.1", 
                "lava1.2", 
                "lava1.3", 
                "lava1.4", 
                "lava1.5", 
                "lava1.6", 
                "lava1.7", 
                "lava1.8", 
                ])
init()
