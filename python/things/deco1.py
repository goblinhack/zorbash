import zx
import tp


def pillar_init(name, short_name, 
              tiles=[],
              left_tiles=[]):
    
    x = tp.Tp(name)

    x.set_is_boring(True)
    x.set_is_deco(True)
    x.set_is_movement_blocking(True)
    x.set_is_outlined(True)
    x.set_is_small_shadow_caster(True)
    x.set_short_name(short_name)
    x.set_is_blit_off_center(True)
    x.set_z_depth(zx.MAP_DEPTH_WALLS)
    
    delay = 1250
    for t in tiles:
        x.set_tile(tile=t, delay_ms=delay)

def init():
    pillar_init(name="pillar1", short_name="pillar1", 
            tiles=[ 
                "pillar1", 
                "pillar2", 
                ])
init()
