import zx
import tp


def acid_init(name, text_name, tiles=[], left_tiles=[]):
    x = tp.Tp(name, text_name)

    x.set_ai_obstacle(True)
    x.set_gfx_show_outlined(True)
    x.set_ascii_show_outlined(False)
    x.set_is_acid(True)
    x.set_is_hazard(True)
    x.set_is_light_strength(1)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_is_meat_eater(True)
    x.set_lifespan_dice("1d10+10")
    x.set_light_color("green")
    x.set_stats_attack_dice("1d3+1")
    x.set_text_a_or_an("");
    x.set_text_description("A pool of hissing acid")
    x.set_text_hits("burns");
    x.set_tick_catches_up_on_attack(True)
    x.set_tick_rate_tenths(1)
    x.set_z_depth(zx.MAP_DEPTH_FLOOR2)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    for t in tiles:
        x.set_tile(tile=t)

    x.update()

def init():
    acid_init(name="acid1", text_name="hissing acid",
            tiles=[
                "acid1.1",
                "acid1.2",
                "acid1.3",
                "acid1.4",
                "acid1.5",
                "acid1.6",
                "acid1.7",
                "acid1.8",
                "acid1.9",
                "acid1.10",
                "acid1.11",
                "acid1.12",
                "acid1.13",
                "acid1.14",
                "acid1.15",
                "acid1.16",
                "acid1.17",
                "acid1.18",
                "acid1.19",
                ])
init()
