import zx
import tp


def lava_init(name, tiles=[], left_tiles=[]):
    
    x = tp.Tp(name)

    x.set_is_lava(True)
    x.set_gfx_animated(True)
    x.set_z_depth(zx.MAP_DEPTH_LAVA)
    x.set_str_light_color("red")
    x.set_is_obstacle(True)
    x.set_does_nothing(True)
    x.set_is_light_strength(1)
    
    delay = 1250
    for t in tiles:
        x.set_tile(tile=t, delay_ms=delay)

    x.update()
    
def init():
    lava_init(name="lava1",
            tiles=[ 
                "lava1.1", 
                "lava1.2", 
                "lava1.3", 
                "lava1.4", 
                "lava1.5", 
                "lava1.6", 
                "lava1.7", 
                "lava1.8", 
                "lava1.9", 
                "lava1.10", 
                "lava1.11", 
                "lava1.12", 
                "lava1.13", 
                "lava1.14", 
                "lava1.15", 
                "lava1.16", 
                ])
init()
