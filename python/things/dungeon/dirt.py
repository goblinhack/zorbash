import my
import tp


#
# NOTE: chasm tiles are not blitted explicitly. Instead a floor tile
# will check for the presence of a chasm beneath it and blit the chasm
#
def tp_init(name, tiles=[], left1_tiles=[], bot3_tiles=[]):
    self = tp.Tp(name, "some dirt", "some dirt")
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
    my.is_able_to_dampen_footsteps(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_dirt(self, True)
    my.is_flat(self, True)
    my.is_only_one_per_tile(self, True)
    my.text_a_or_an(self, "the")
    my.text_description_short(self, "Some exciting dirt")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_FLOOR)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="middle_dot", ascii_fg_col_name="brown",
                tile=t)

    if bot3_tiles is not None:
        for t in bot3_tiles:
            my.bot3_tile(self, t)
    else:
        my.bot3_tile(self, bot3_tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="dirt1",
        tiles=[
            "dirt1.1",
            "dirt1.2",
            "dirt1.3",
            "dirt1.4",
            "dirt1.5",
            "dirt1.6",
            "dirt1.7",
            "dirt1.8",
            "dirt1.9",
            "dirt1.10",
            "dirt1.11",
            "dirt1.12",
            "dirt1.13",
            "dirt1.14",
            "dirt1.15",
            "dirt1.16",
            "dirt1.17",
            "dirt1.18",
            "dirt1.19",
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
        name="dirt2",
        tiles=[
            "dirt2.1",
            "dirt2.2",
            "dirt2.3",
            "dirt2.4",
            "dirt2.5",
            "dirt2.6",
            "dirt2.7",
            "dirt2.8",
            "dirt2.9",
            "dirt2.10",
            "dirt2.11",
            "dirt2.12",
            "dirt2.13",
            "dirt2.14",
            "dirt2.15",
            "dirt2.16",
            "dirt2.17",
            "dirt2.18",
            "dirt2.19",
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
        name="dirt3",
        tiles=[
            "dirt3.1",
            "dirt3.2",
            "dirt3.3",
            "dirt3.4",
            "dirt3.5",
            "dirt3.6",
            "dirt3.7",
            "dirt3.8",
            "dirt3.9",
            "dirt3.10",
            "dirt3.11",
            "dirt3.12",
            "dirt3.13",
            "dirt3.14",
            "dirt3.15",
            "dirt3.16",
            "dirt3.17",
            "dirt3.18",
            "dirt3.19",
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
