import my
import tp


def tp_init(name, text_long_name, tiles=[]):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.dmg_chance_d1000_water(self, 0, 1000)
    my.dmg_water_dice(self, "1d4+1")
    my.environ_dislikes_fire(self, 1)
    my.gfx_ascii_animated(self, True)
    my.gfx_ascii_bg_color_spread_blue(self, 40)
    my.gfx_ascii_bg_color_spread_green(self, 40)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.gfx_water(self, True)
    my.is_able_to_amplify_footsteps(self, True)
    my.is_able_to_fall(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_flooded(self, True)
    my.is_biome_swamp(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_flat(self, True)
    my.is_interesting(self, True)
    my.is_obs_ai(self, True)
    my.is_one_per_tile(self, True)
    my.is_shallow_water(self, True)
    my.text_a_or_an(self, "the")
    my.text_description_short(self, "Some shallow water.")
    my.z_depth(self, my.MAP_DEPTH_LIQUID)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    delay = 3000
    for t in tiles:
        my.tile(self,
                ascii_fg_char="middle_dot", ascii_bg_col_name="water", ascii_fg_col_name="deepwater",
                tile=t, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(
        name="water",
        text_long_name="water",
        tiles=[
            "water.1",
            "water.2",
            "water.3",
            "water.4",
            "water.5",
            "water.6",
            "water.7",
            "water.8",
            "water.9",
            "water.10",
            "water.11",
            "water.12",
            "water.13",
            "water.14",
            "water.15",
            "water.16",
            "water.17",
            "water.18",
            "water.19",
            "water.20",
            "water.21",
            "water.22",
            "water.23",
            "water.24",
            "water.25",
            "water.26",
            "water.27",
            "water.28",
            "water.29",
            "water.30",
            "water.31",
            "water.32",
        ],
    )


init()
