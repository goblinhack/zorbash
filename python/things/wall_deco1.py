import zx
import tp


def grate_init(name, short_name, 
              tiles=[],
              left_tiles=[]):
    
    x = tp.Tp(name)

    x.set_is_animated(True)
    x.set_is_blitted_as_sitting_on_the_ground(True)
    x.set_is_boring(True)
    x.set_is_movement_blocking(True)
    x.set_is_outlined(True)
    x.set_is_wall_deco(True)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_WALLS_DECO)
    
    delay = 2500
    for t in tiles:
        x.set_tile(tile=t, delay_ms=delay)

def init():
    grate_init(name="grate1", short_name="grate1", tiles=[ "grate1.1", "grate1.2", ])
    grate_init(name="grate2", short_name="grate2", tiles=[ "grate2.1", "grate2.2", ])
    grate_init(name="grate3", short_name="grate3", tiles=[ "grate3.1", "grate3.2", ])
    grate_init(name="grate4", short_name="grate4", tiles=[ "grate4.1", "grate4.2", ])
    grate_init(name="grate5", short_name="grate5", tiles=[ "grate5.1", "grate5.2", ])
    grate_init(name="grate6", short_name="grate6", tiles=[ "grate6.1", "grate6.2", ])
    grate_init(name="grate7", short_name="grate7", tiles=[ "grate7.1", "grate7.2", ])
    grate_init(name="grate8", short_name="grate8", tiles=[ "grate8.1", "grate8.2", ])
init()
