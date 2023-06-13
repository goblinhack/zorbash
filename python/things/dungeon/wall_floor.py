import my
import tp


def tp_init(name, tiles=[], left1_tiles=[], bot3_tiles=[]):
    self = tp.Tp(name, "dungeon wall", "dungeon wall")
    # begin sort marker
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, False)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_floor(self, True)
    my.is_only_one_per_tile(self, True)
    my.text_a_or_an(self, "the")
    my.text_description_short(self, "The unwashed dungeon foundation.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_FLOOR)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    for t in tiles:
        my.tile(self, t)

    if bot3_tiles is not None:
        for t in bot3_tiles:
            my.bot3_tile(self, t, ascii_fg_char="middle_dot", ascii_bg_col_name="", ascii_fg_col_name="white")
    else:
        my.bot3_tile(self, name, ascii_fg_char=".", ascii_bg_col_name="", ascii_fg_col_name="white")

    my.tp_update(self)


def init():
    tp_init(
        name="wall_floor1",
        tiles=[
            "floor1.1",
            "floor1.2",
            "floor1.3",
            "floor1.4",
            "floor1.5",
            "floor1.6",
            "floor1.7",
            "floor1.8",
            "floor1.9",
            "floor1.10",
            "floor1.11",
            "floor1.12",
            "floor1.13",
            "floor1.14",
            "floor1.15",
            "floor1.16",
            "floor1.17",
            "floor1.18",
            "floor1.19",
        ],
        bot3_tiles=[
            "chasm2.1",
            "chasm2.2",
            "chasm2.3",
            "chasm2.4",
            "chasm2.5",
            "chasm2.6",
            "chasm2.7",
            "chasm2.8",
            "chasm2.9",
            "chasm2.10",
            "chasm2.11",
            "chasm2.12",
            "chasm2.13",
            "chasm2.14",
            "chasm2.15",
            "chasm2.16",
            "chasm2.17",
            "chasm2.18",
            "chasm2.19",
        ],
    )


init()
