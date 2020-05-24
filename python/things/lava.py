import zx
import tp


def lava_init(name, text_name, tiles=[], left_tiles=[]):
    x = tp.Tp(name, text_name)

    x.set_ai_obstacle(True)
    x.set_gfx_animated(True)
    x.set_is_hazard(True)
    x.set_is_interesting(True)
    x.set_is_lava(True)
    x.set_is_light_strength(3)
    x.set_light_color("red")
    x.set_stats_attack_hd("1d6+1")
    x.set_text_a_or_an("");
    x.set_text_hits("tickles");
    x.set_z_depth(zx.MAP_DEPTH_LAVA)

    delay = 1250
    for t in tiles:
        x.set_tile(tile=t, delay_ms=delay)

    x.update()

def init():
    lava_init(name="lava1", text_name="lava",
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
