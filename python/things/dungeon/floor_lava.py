import my
import tp


#
# NOTE: chasm tiles are not blitted explicitly. Instead a floor tile
# will check for the presence of a chasm beneath it and blit the chasm
#
def tp_init(name, tiles=[], bot3_tiles=[]):
    self = tp.Tp(name, "dirty floor", "dirty floor")
    # begin sort marker
    my.gfx_ascii_fg_color_spread_blue(self, 20)
    my.gfx_ascii_fg_color_spread_green(self, 20)
    my.gfx_ascii_fg_color_spread_red(self, 20)
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_flat(self, True)
    my.is_floor(self, True)
    my.text_a_or_an(self, "the")
    my.text_description_short(self, "The scalding dungeon floor.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_FLOOR)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="middle_dot", ascii_bg_col_name="black", ascii_fg_col_name="white",
                tile=t)

    if bot3_tiles is not None:
        for t in bot3_tiles:
            my.bot3_tile(self, t)
    else:
        my.bot3_tile(self, bot3_tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="floor_lava1",
        tiles=[
            "floor_lava1.1",
            "floor_lava1.2",
            "floor_lava1.3",
            "floor_lava1.4",
            "floor_lava1.5",
            "floor_lava1.6",
            "floor_lava1.7",
            "floor_lava1.8",
            "floor_lava1.9",
            "floor_lava1.10",
            "floor_lava1.11",
            "floor_lava1.12",
            "floor_lava1.13",
            "floor_lava1.14",
            "floor_lava1.15",
            "floor_lava1.16",
            "floor_lava1.17",
            "floor_lava1.18",
            "floor_lava1.19",
            "floor_lava1.20",
            "floor_lava1.21",
            "floor_lava1.22",
            "floor_lava1.23",
            "floor_lava1.24",
            "floor_lava1.25",
            "floor_lava1.26",
            "floor_lava1.27",
            "floor_lava1.28",
            "floor_lava1.29",
            "floor_lava1.30",
            "floor_lava1.31",
            "floor_lava1.32",
            "floor_lava1.33",
            "floor_lava1.34",
            "floor_lava1.35",
            "floor_lava1.36",
            "floor_lava1.37",
            "floor_lava1.38",
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
