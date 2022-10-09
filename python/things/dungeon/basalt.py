import my
import tp


def basalt_init(name, text_long_name, tiles=[]):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.ai_obstacle(self, True)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 100)
    my.gfx_ascii_bg_color_spread_hue(self, 30)
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.is_able_to_fall(self, True)
    my.is_basalt(self, True)
    my.is_biome_dungeon(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_tickable(self, True)
    my.text_a_or_an(self, "")
    my.text_short_description(self, "Warm to the touch basalt.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_LIQUID)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    delay = 200
    for t in tiles:
        my.tile(self,
                ascii_fg_char="L", ascii_bg_col_name="black", ascii_fg_col_name="white",
                tile=t, delay_ms=delay)

    my.tp_update(self)


def init():
    basalt_init(
        name="basalt",
        text_long_name="basalt",
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
