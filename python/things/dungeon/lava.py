import my
import tp


def lava_init(name, text_long_name, tiles=[]):
    self = tp.Tp(name, text_long_name)
    # start sort marker
    my.ai_obstacle(self, True)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 100)
    my.damage_fire_chance_d1000(self, 0, 1000)
    my.damage_fire_dice(self, "1d12+6")
    my.damage_nat_attack_type(self, "burn")
    my.gfx_ascii_animated(self, True)
    my.gfx_ascii_mode_color_is_animated(self, True)
    my.gfx_ascii_mode_color_spread_hue(self, 20)
    my.gfx_ascii_mode_shown(self, True)
    my.gfx_glows(self, True)
    my.gfx_shown_in_bg(self, True)
    my.is_able_to_fall(self, True)
    my.is_biome_dungeon(self, True)
    my.is_cursor_can_hover_over_x2_click(self, True)
    my.is_cursor_path_hazard_for_player(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_hazard(self, True)
    my.is_lava(self, True)
    my.is_loggable(self, True)
    my.light_color(self, "red")
    my.light_dist(self, 1)
    my.temperature(self, 800)
    my.text_a_or_an(self, "")
    my.text_hits(self, "tickles")
    my.text_short_description(self, "%%fg=orange$Freshly scented lava%%fg=reset$ (double click to move onto).")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_LIQUID)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    delay = 200
    for t in tiles:
        my.tile(self,
                ascii_fg_char="L", ascii_bg_col_name="red", ascii_fg_col_name="white",
                tile=t, delay_ms=delay)

    my.tp_update(self)


def init():
    lava_init(
        name="lava",
        text_long_name="molten lava",
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
