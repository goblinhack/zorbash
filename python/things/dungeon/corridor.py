import my
import tp


def tp_init(name, tiles=[], bot3_tiles=[]):
    self = tp.Tp(name, "a corridor", "a corridor")
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.is_corridor(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_flat(self, True)
    my.is_one_per_tile(self, True)
    my.text_a_or_an(self, "the")
    my.text_description_short(self, "The dirty dungeon corridor.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_FLOOR)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="middle_dot", ascii_bg_col_name="black", ascii_fg_col_name="darkgray",
                tile=t)

    if bot3_tiles is not None:
        for t in bot3_tiles:
            my.bot3_tile(self, t)
    else:
        my.bot3_tile(self, bot3_tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="corridor1",
        tiles=[
            "corridor1.1",
            "corridor1.2",
            "corridor1.3",
            "corridor1.4",
            "corridor1.5",
            "corridor1.6",
            "corridor1.7",
            "corridor1.8",
            "corridor1.9",
            "corridor1.10",
            "corridor1.11",
            "corridor1.12",
            "corridor1.13",
            "corridor1.14",
            "corridor1.15",
            "corridor1.16",
            "corridor1.17",
            "corridor1.18",
            "corridor1.19",
            "corridor1.20",
            "corridor1.21",
            "corridor1.22",
            "corridor1.23",
            "corridor1.24",
            "corridor1.25",
            "corridor1.26",
            "corridor1.27",
            "corridor1.28",
            "corridor1.29",
            "corridor1.30",
            "corridor1.31",
            "corridor1.32",
            "corridor1.33",
            "corridor1.34",
            "corridor1.35",
            "corridor1.36",
            "corridor1.37",
            "corridor1.38",
            "corridor1.39",
            "corridor1.40",
            "corridor1.41",
            "corridor1.42",
            "corridor1.43",
            "corridor1.44",
            "corridor1.45",
            "corridor1.46",
            "corridor1.47",
            "corridor1.48",
            "corridor1.49",
            "corridor1.50",
            "corridor1.51",
            "corridor1.52",
            "corridor1.53",
            "corridor1.54",
            "corridor1.55",
            "corridor1.56",
            "corridor1.57",
        ],
        bot3_tiles=[
            "chasm1.1",
            "chasm1.2",
            "chasm1.3",
            "chasm1.4",
            "chasm1.5",
            "chasm1.6",
            "chasm1.7",
            "chasm1.8",
            "chasm1.9",
            "chasm1.10",
            "chasm1.11",
            "chasm1.12",
            "chasm1.13",
            "chasm1.14",
            "chasm1.15",
            "chasm1.16",
            "chasm1.17",
            "chasm1.18",
            "chasm1.19",
        ],
    )
    tp_init(
        name="corridor2",
        tiles=[
            "corridor2.1",
            "corridor2.2",
            "corridor2.3",
            "corridor2.4",
            "corridor2.5",
            "corridor2.6",
            "corridor2.7",
            "corridor2.8",
            "corridor2.9",
            "corridor2.10",
            "corridor2.11",
            "corridor2.12",
            "corridor2.13",
            "corridor2.14",
            "corridor2.15",
            "corridor2.16",
            "corridor2.17",
            "corridor2.18",
            "corridor2.19",
            "corridor2.20",
            "corridor2.21",
            "corridor2.22",
            "corridor2.23",
            "corridor2.24",
            "corridor2.25",
            "corridor2.26",
            "corridor2.27",
            "corridor2.28",
            "corridor2.29",
            "corridor2.30",
            "corridor2.31",
            "corridor2.32",
            "corridor2.33",
            "corridor2.34",
            "corridor2.35",
            "corridor2.36",
            "corridor2.37",
            "corridor2.38",
            "corridor2.39",
            "corridor2.40",
            "corridor2.41",
            "corridor2.42",
            "corridor2.43",
            "corridor2.44",
            "corridor2.45",
            "corridor2.46",
            "corridor2.47",
            "corridor2.48",
            "corridor2.49",
            "corridor2.50",
            "corridor2.51",
            "corridor2.52",
            "corridor2.53",
            "corridor2.54",
            "corridor2.55",
            "corridor2.56",
            "corridor2.57",
        ],
        bot3_tiles=[
            "chasm1.1",
            "chasm1.2",
            "chasm1.3",
            "chasm1.4",
            "chasm1.5",
            "chasm1.6",
            "chasm1.7",
            "chasm1.8",
            "chasm1.9",
            "chasm1.10",
            "chasm1.11",
            "chasm1.12",
            "chasm1.13",
            "chasm1.14",
            "chasm1.15",
            "chasm1.16",
            "chasm1.17",
            "chasm1.18",
            "chasm1.19",
        ],
    )


init()
