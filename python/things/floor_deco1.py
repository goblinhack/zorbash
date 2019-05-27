import zx
import tp


def tp_init(name, tiles=[]):
    
    x = tp.Tp(name)

    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_is_boring(True)
    x.set_gfx_is_floor_deco(True)
    x.set_is_movement_blocking(True)
    x.set_gfx_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_z_depth(zx.MAP_DEPTH_FLOOR_DECO)
    
    for t in tiles:
        x.set_tile(tile=t)

    x.update()
    
def init():
    tp_init(name="pillar1",
            tiles=[ 
                "pillar1.1", 
                "pillar1.2", 
                "pillar1.3", 
                "pillar1.4", 
                "pillar1.5", 
                "pillar1.6", 
                "pillar1.7", 
                "pillar1.8", 
                "pillar1.9", 
                "pillar1.10", 
                "pillar1.11", 
                "pillar1.12", 
                "pillar1.13", 
                "pillar1.14", 
                "pillar1.15", 
                "pillar1.16", 
                "pillar1.17", 
                "pillar1.18", 
                "pillar1.19", 
                "pillar1.20", 
                "pillar1.21", 
                "pillar1.22", 
                "pillar1.23", 
                "pillar1.24", 
                "pillar1.25", 
                "pillar1.26", 
                "pillar1.27", 
                "pillar1.28", 
                "pillar1.29", 
                "pillar1.30", 
                "pillar1.31", 
                "pillar1.32", 
                ])
init()
