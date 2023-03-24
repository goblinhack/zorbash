import my
import tp


def tp_init(name, text_long_name, tiles=[]):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_oversized_and_on_floor(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.is_able_to_fall(self, True)
    my.text_a_or_an(self, "an")
    my.text_description_short(self, "An empty podium. With claw marks.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="_", ascii_bg_col_name="", ascii_fg_col_name="gray",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(
        name="gargoyle_podium",
        text_long_name="empty podium",
        tiles=[
            "gargoyle.podium",
        ],
    )


init()
