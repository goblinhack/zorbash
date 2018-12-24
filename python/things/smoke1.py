import zx
import tp

def monst_init(name, short_name):
    x = tp.Tp(name)

    x.set_is_animated(True)
    x.set_short_name(short_name)
    x.set_is_small_shadow_caster(True)
    x.set_is_blitted_as_sitting_on_the_ground(True)
    x.set_z_depth(zx.MAP_DEPTH_MONST)

    delay = 50
    x.set_tile(tile=name + ".1", delay_ms=delay)
    x.set_tile(tile=name + ".2", delay_ms=delay)
    x.set_tile(tile=name + ".3", delay_ms=delay)
    x.set_tile(tile=name + ".4", delay_ms=delay)
    x.set_tile(tile=name + ".5", delay_ms=delay)
    x.set_tile(tile=name + ".6", delay_ms=delay)
    x.set_tile(tile=name + ".7", delay_ms=delay)
    x.set_tile(tile=name + ".8", delay_ms=delay)
    x.set_tile(tile=name + ".9", delay_ms=delay)
    x.set_tile(tile=name + ".10", delay_ms=delay)
    x.set_tile(tile=name + ".11", delay_ms=delay)
    x.set_tile(tile=name + ".12", delay_ms=delay)
    x.set_tile(tile=name + ".13", delay_ms=delay)
    x.set_tile(tile=name + ".14", delay_ms=delay)
    x.set_tile(tile=name + ".15", delay_ms=delay)
    x.set_tile(tile=name + ".16", delay_ms=delay)
    x.set_tile(tile=name + ".17", delay_ms=delay)
    x.set_tile(tile=name + ".18", delay_ms=delay)
    x.set_tile(tile=name + ".19", delay_ms=delay)
    x.set_tile(tile=name + ".20", delay_ms=delay)
    x.set_tile(tile=name + ".21", delay_ms=delay)
    x.set_tile(tile=name + ".22", delay_ms=delay)
    x.set_tile(tile=name + ".23", delay_ms=delay)
    x.set_tile(tile=name + ".24", delay_ms=delay)
    x.set_tile(tile=name + ".25", delay_ms=delay)
    x.set_tile(tile=name + ".26", delay_ms=delay)
    x.set_tile(tile=name + ".27", delay_ms=delay)
    x.set_tile(tile=name + ".28", delay_ms=delay)
    x.set_tile(tile=name + ".29", delay_ms=delay)
    x.set_tile(tile=name + ".30", delay_ms=delay)
    x.set_tile(tile=name + ".31", delay_ms=delay)
    x.set_tile(tile=name + ".32", delay_ms=delay)

def init():
    monst_init(name="smoke1", short_name="smoke1")

init()
