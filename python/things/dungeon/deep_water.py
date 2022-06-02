import my
import tp


def tp_init(name, text_long_name, tiles=[]):
    self = tp.Tp(name, text_long_name)
    # start sort marker
    my.ai_obstacle(self, True)
    my.environ_avoids_fire(self, 1)
    my.gfx_ascii_mode_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_shown_in_bg(self, True)
    my.gfx_water(self, True)
    my.is_able_to_fall(self, True)
    my.is_biome_dungeon(self, True)
    my.is_deep_water(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_hazard(self, True)
    my.text_a_or_an(self, "the")
    my.text_short_description(self, "A pool of deep dank water, with things in it.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_LIQUID)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    delay = 1250
    for t in tiles:
        my.tile(self,
                ascii_fg_char="~", ascii_bg_col_name="deepblue", ascii_fg_col_name="deepblue2",
                tile=t, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(
        name="deep_water1",
        text_long_name="deep water",
        tiles=[
            "deep_water1.1",
            "deep_water1.2",
            "deep_water1.3",
            "deep_water1.4",
            "deep_water1.5",
            "deep_water1.6",
            "deep_water1.7",
            "deep_water1.8",
            "deep_water1.9",
            "deep_water1.10",
            "deep_water1.11",
            "deep_water1.12",
            "deep_water1.13",
            "deep_water1.14",
            "deep_water1.15",
            "deep_water1.16",
        ],
    )


init()
