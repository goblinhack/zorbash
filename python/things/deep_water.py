import zx
import tp


def deep_tp_init(name, real_name, tiles=[]):
    x = tp.Tp(name, real_name)

    x.set_a_or_an_prefix("the");
    x.set_gfx_animated(True)
    x.set_is_deep_water(True)
    x.set_is_hazard(True)
    x.set_is_interesting(True)
    x.set_is_loggable(False)
    x.set_is_obstacle(True)
    x.set_z_depth(zx.MAP_DEPTH_WATER)

    delay = 1250
    for t in tiles:
        x.set_tile(tile=t, delay_ms=delay)

    x.update()

def init():
    deep_tp_init(name="deep_water1", real_name="deep water",
            tiles=[
                "deep_water1.1",
                "deep_water1.2",
                "deep_water1.3",
                "deep_water1.4",
                "deep_water1.5",
                "deep_water1.6",
                "deep_water1.7",
                "deep_water1.8",
                "deep_water1.9",
                "deep_water1.10",
                "deep_water1.11",
                "deep_water1.12",
                "deep_water1.13",
                "deep_water1.14",
                "deep_water1.15",
                "deep_water1.16",
                ])
init()
