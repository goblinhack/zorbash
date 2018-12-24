import zx
import tp

def monst_init(name, short_name):
    x = tp.Tp(name)

    x.set_is_animated(True)
    x.set_is_boring(True)
    x.set_short_name(short_name)
    x.set_is_blitted_as_sitting_on_the_ground(True)
    x.set_z_depth(zx.MAP_DEPTH_MONST)

    delay = 100
    x.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".7", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".8", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".9", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".10", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".11", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".12", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".13", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".14", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".15", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".16", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".17", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".18", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".19", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".20", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".21", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".22", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".23", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".24", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".25", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".26", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".27", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".28", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".29", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".30", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".31", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".32", is_dir_none=True, delay_ms=delay)

def init():
    monst_init(name="smoke1", short_name="smoke1")

init()
