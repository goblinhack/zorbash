import my
import tp


def lava_init(name, text_name, tiles=[]):
    mytp = tp.Tp(name, text_name)
    mytp.set_ai_obstacle(True)
    mytp.set_collision_check(True)
    mytp.set_collision_hit_priority(100)
    mytp.set_damage_fire_chance_d1000(1000)
    mytp.set_damage_fire_dice("1d12+6")
    mytp.set_damage_natural_attack_type("burn")
    mytp.set_gfx_flickers(True)
    mytp.set_gfx_glows(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_biome_dungeon(True)
    mytp.set_is_cursor_can_hover_over_x2_click(True)
    mytp.set_is_cursor_path_hazard_for_player(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_hazard(True)
    mytp.set_is_lava(True)
    mytp.set_is_loggable(True)
    mytp.set_light_color("red")
    mytp.set_light_power(2)
    mytp.set_temperature(800)
    mytp.set_text_a_or_an("")
    mytp.set_text_description("%%fg=orange$Freshly scented lava%%fg=reset$ (double click to move onto).")
    mytp.set_text_hits("tickles")
    mytp.set_z_depth(my.MAP_DEPTH_LAVA)
    mytp.set_z_prio(my.MAP_PRIO_NORMAL)

    delay = 200
    for t in tiles:
        mytp.set_tile(tile=t, delay_ms=delay)

    mytp.update()


def init():
    lava_init(
        name="lava",
        text_name="broiling lava",
        tiles=[
            "lava.1",
            "lava.2",
            "lava.3",
            "lava.4",
            "lava.5",
            "lava.6",
            "lava.7",
            "lava.8",
            "lava.9",
            "lava.10",
            "lava.11",
            "lava.12",
            "lava.13",
            "lava.14",
            "lava.15",
            "lava.16",
        ],
    )


init()
