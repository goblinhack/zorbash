import zx
import tp


def lava_init(name, text_name, tiles=[]):
    x = tp.Tp(name, text_name)
    x.set_ai_obstacle(True)
    x.set_damage_melee_dice("1d12+6")
    x.set_gfx_animated(True)
    x.set_is_able_to_fall(True)
    x.set_is_cursor_can_hover_over_but_needs_double_click(True)
    x.set_is_extreme_hazard(True)
    x.set_is_hazard(True)
    x.set_is_interesting(True)
    x.set_is_lava(True)
    x.set_is_light_strength(3)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_light_color("red")
    x.set_text_a_or_an("");
    x.set_text_description("%%fg=orange$Freshly scented lava%%fg=reset$ (double click to move)")
    x.set_text_hits("tickles");
    x.set_tick_catches_up_on_attack(True)
    x.set_tick_rate_tenths(3)
    x.set_z_depth(zx.MAP_DEPTH_LAVA)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 200
    for t in tiles:
        x.set_tile(tile=t, delay_ms=delay)

    x.update()

def init():
    lava_init(name="lava1", text_name="broiling lava",
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
