import my
import tp


def tp_init(name, text_long_name, tiles=[]):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.dmg_acid_dice(self, "1d4+1")
    my.dmg_chance_d1000_acid(self, 0, 1000)
    my.dmg_chance_d1000_poison(self, 0, 1000)
    my.dmg_nat_att_type(self, "burn")
    my.dmg_poison_dice(self, "1d4+1")
    my.environ_dislikes_cold(self, 100)
    my.environ_dislikes_fire(self, 100)
    my.gfx_ascii_animated(self, True)
    my.gfx_ascii_bg_color_spread_blue(self, 40)
    my.gfx_ascii_bg_color_spread_red(self, 40)
    my.gfx_ascii_color_is_animated(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_ooze(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.is_able_to_fall(self, True)
    my.is_acid(self, True)
    my.is_biome_dungeon(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_flat(self, True)
    my.is_hazard(self, True)
    my.is_interesting(self, True)
    my.is_obs_ai(self, True)
    my.is_only_one_per_tile(self, True)
    my.is_ooze(self, True)
    my.is_tickable(self, True)
    my.text_a_or_an(self, "the")
    my.text_description_short(self, "Black ooze.")
    my.z_depth(self, my.MAP_DEPTH_LIQUID)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="o", ascii_bg_col_name="black", ascii_fg_col_name="purple",
                tile=t, delay_ms=3000)
        my.tile(self,
                ascii_fg_char="O", ascii_bg_col_name="black", ascii_fg_col_name="purple",
                tile=t, delay_ms=1000)

    my.tp_update(self)


def init():
    tp_init(
        name="ooze",
        text_long_name="ooze",
        tiles=[
            "ooze.1",
            "ooze.2",
            "ooze.3",
            "ooze.4",
            "ooze.5",
            "ooze.6",
            "ooze.7",
            "ooze.8",
            "ooze.9",
            "ooze.10",
            "ooze.11",
            "ooze.12",
            "ooze.13",
            "ooze.14",
            "ooze.15",
            "ooze.16",
            "ooze.17",
            "ooze.18",
            "ooze.19",
            "ooze.20",
            "ooze.21",
            "ooze.22",
            "ooze.23",
            "ooze.24",
            "ooze.25",
            "ooze.26",
            "ooze.27",
            "ooze.28",
            "ooze.29",
            "ooze.30",
            "ooze.31",
            "ooze.32",
        ],
    )


init()
