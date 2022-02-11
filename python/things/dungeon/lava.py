import my
import tp


def lava_init(name, text_name, tiles=[]):
    mytp = tp.Tp(name, text_name)
    my.tp_set_ai_obstacle(mytp, True)
    my.tp_set_collision_check(mytp, True)
    my.tp_set_collision_hit_priority(mytp, 100)
    my.tp_set_damage_fire_chance_d1000(mytp, 1000)
    my.tp_set_damage_fire_dice(mytp, "1d12+6")
    my.tp_set_damage_natural_attack_type(mytp, "burn")
    my.tp_set_gfx_flickers(mytp, True)
    my.tp_set_gfx_glows(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_cursor_can_hover_over_x2_click(mytp, True)
    my.tp_set_is_cursor_path_hazard_for_player(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_hazard(mytp, True)
    my.tp_set_is_lava(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_light_color(mytp, "red")
    my.tp_set_light_power(mytp, 2)
    my.tp_set_temperature(mytp, 800)
    my.tp_set_text_a_or_an(mytp, "")
    my.tp_set_text_description(mytp, "%%fg=orange$Freshly scented lava%%fg=reset$ (mytp, double click to move onto).")
    my.tp_set_text_hits(mytp, "tickles")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_LAVA)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL)

    delay = 200
    for t in tiles:
        my.tp_set_tile(mytp, tile=t, delay_ms=delay)

    my.tp_update(mytp, )


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
