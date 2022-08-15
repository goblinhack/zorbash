import my
import tp


def tp_init(name, text_long_name, tiles=[]):
    self = tp.Tp(name, text_long_name)
    # start sort marker
    my.ai_obstacle(self, True)
    my.damage_water_chance_d1000(self, 0, 1000)
    my.damage_water_dice(self, "1d4+1")
    my.environ_avoids_fire(self, 1)
    my.gfx_ascii_animated(self, True)
    my.gfx_ascii_bg_color_spread_blue(self, 20)
    my.gfx_ascii_bg_color_spread_green(self, 20)
    my.gfx_ascii_bg_color_spread_red(self, 5)
    my.gfx_ascii_color_is_animated(self, True)
    my.gfx_ascii_fg_color_spread_blue(self, 20)
    my.gfx_ascii_fg_color_spread_green(self, 20)
    my.gfx_ascii_fg_color_spread_red(self, 5)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_water(self, True)
    my.is_able_to_fall(self, True)
    my.is_biome_dungeon(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_hazard(self, True)
    my.is_shallow_water(self, True)
    my.text_a_or_an(self, "the")
    my.text_short_description(self, "Some shallow water.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_LIQUID)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    delay = 3000
    for t in tiles:
        my.tile(self,
                ascii_fg_char="~", ascii_bg_col_name="water", ascii_fg_col_name="deepwater",
                tile=t, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(
        name="water1",
        text_long_name="water",
        tiles=[
            "water1.1",
            "water1.2",
            "water1.3",
            "water1.4",
            "water1.5",
            "water1.6",
            "water1.7",
            "water1.8",
            "water1.9",
            "water1.10",
            "water1.11",
            "water1.12",
            "water1.13",
            "water1.14",
            "water1.15",
            "water1.16",
            "water1.17",
            "water1.18",
            "water1.19",
            "water1.20",
            "water1.21",
            "water1.22",
            "water1.23",
            "water1.24",
            "water1.25",
            "water1.26",
            "water1.27",
            "water1.28",
            "water1.29",
            "water1.30",
            "water1.31",
            "water1.32",
        ],
    )


init()
