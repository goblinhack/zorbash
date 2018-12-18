import zx
import tp


def blood_init(name, short_name, 
              tiles=[],
              left_tiles=[]):
    
    x = tp.Tp(name)

    x.set_is_boring(True)
    x.set_is_blood(True)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_BLOOD)
    
    for t in tiles:
        x.set_tile(tile=t)

def init():
    blood_init(name="blood1", short_name="blood", 
            tiles=[ 
                "blood1.1", 
                "blood1.2", 
                "blood1.3", 
                "blood1.4", 
                "blood1.5", 
                "blood1.6", 
                "blood1.7", 
                "blood1.8", 
                ])
init()
