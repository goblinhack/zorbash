import zx
import tp


def chasm_init(name, real_name, tiles=[], left_tiles=[]):
    x = tp.Tp(name, real_name)

    x.set_a_or_an_prefix("a");
    x.set_is_chasm(True)
    x.set_is_hazard(True)
    x.set_is_interesting(True)
    x.set_is_loggable(False)
    x.set_is_obstacle(True)
    x.set_z_depth(zx.MAP_DEPTH_CHASM)

    delay = 1250
    for t in tiles:
        x.set_tile(tile="chasm" + t, 
                   delay_ms=delay, 
                   gfx_outline_index_offset=16)
        x.set_tile(tile="chasm_outline" + t, delay_ms=delay, is_outline=True)

    x.update()

def init():
    chasm_init(name="chasm1", real_name="chasm",
            tiles=[
                "1.1",
                "1.2",
                "1.3",
                "1.4",
                "1.5",
                "1.6",
                "1.7",
                "1.8",
                "1.9",
                "1.10",
                "1.11",
                "1.12",
                "1.13",
                "1.14",
                "1.15",
                "1.16",
                ])
init()
