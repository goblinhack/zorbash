import zx
import tp


def acid_init(name, text_name, tiles=[], left_tiles=[]):
    x = tp.Tp(name, text_name)

    x.set_ai_obstacle(True)
    x.set_is_acid(True)
    x.set_is_hazard(True)
    x.set_is_light_strength(1)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_is_meat_eater(True)
    x.set_lifespan_dice("1d10+10")
    x.set_stats_attack_dice("1d3+1")
    x.set_light_color("green")
    x.set_text_a_or_an("");
    x.set_text_hits("dissolves");
    x.set_tick_catches_up_on_attack(True)
    x.set_tick_rate_tenths(1)
    x.set_z_depth(zx.MAP_DEPTH_FLOOR2)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)
    x.set_text_description("A pool of hissing organic acid")

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
                ])
init()
