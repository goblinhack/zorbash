import my
import tp


def lava_init(name, text_name, tiles=[]):
    self = tp.Tp(name, text_name)
    my.tp_set_ai_obstacle(self, True)
    my.tp_set_collision_check(self, True)
    my.tp_set_collision_hit_priority(self, 100)
    my.tp_set_damage_fire_chance_d1000(self, 1000)
    my.tp_set_damage_fire_dice(self, "1d12+6")
    my.tp_set_damage_natural_attack_type(self, "burn")
    my.tp_set_gfx_flickers(self, True)
    my.tp_set_gfx_glows(self, True)
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_cursor_can_hover_over_x2_click(self, True)
    my.tp_set_is_cursor_path_hazard_for_player(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_hazard(self, True)
    my.tp_set_is_lava(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_light_color(self, "red")
    my.tp_set_light_power(self, 2)
    my.tp_set_temperature(self, 800)
    my.tp_set_text_a_or_an(self, "")
    my.tp_set_text_description(self, "%%fg=orange$Freshly scented lava%%fg=reset$ (self, double click to move onto).")
    my.tp_set_text_hits(self, "tickles")
    my.tp_set_z_depth(self, my.MAP_DEPTH_LAVA)
    my.tp_set_z_prio(self, my.MAP_PRIO_NORMAL)

    delay = 200
    for t in tiles:
        my.tp_set_tile(self, tile=t, delay_ms=delay)

    my.tp_update(self)


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
