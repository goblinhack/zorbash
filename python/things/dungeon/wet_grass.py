import my
import tp


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "wet grass")
    # begin sort marker
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_shadow_very_short(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.is_able_to_fall(self, True)
    my.is_biome_dungeon(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_temperature_change_sensitive(self, True)
    my.is_temperature_sensitive(self, True)
    my.is_wet_grass(self, True)
    my.text_a_or_an(self, "the")
    my.text_short_description(self, "Tall and oddly healthy subterranean grass.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    for t in tiles:
        my.tile(self, delay_ms=300,
                ascii_fg_char="\"", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(
        name="wet_grass1",
        tiles=[
            "wet_grass1.1",
            "wet_grass1.2",
            "wet_grass1.3",
            "wet_grass1.4",
            "wet_grass1.5",
            "wet_grass1.4",
            "wet_grass1.3",
            "wet_grass1.2",
        ],
    )
    tp_init(
        name="wet_grass2",
        tiles=[
            "wet_grass2.1",
            "wet_grass2.2",
            "wet_grass2.3",
            "wet_grass2.4",
            "wet_grass2.5",
            "wet_grass2.4",
            "wet_grass2.3",
            "wet_grass2.2",
        ],
    )
    tp_init(
        name="wet_grass3",
        tiles=[
            "wet_grass3.1",
            "wet_grass3.2",
            "wet_grass3.3",
            "wet_grass3.4",
            "wet_grass3.5",
            "wet_grass3.4",
            "wet_grass3.3",
            "wet_grass3.2",
        ],
    )
    tp_init(
        name="wet_grass4",
        tiles=[
            "wet_grass4.1",
            "wet_grass4.2",
            "wet_grass4.3",
            "wet_grass4.4",
            "wet_grass4.5",
            "wet_grass4.4",
            "wet_grass4.3",
            "wet_grass4.2",
        ],
    )
    tp_init(
        name="wet_grass5",
        tiles=[
            "wet_grass5.1",
            "wet_grass5.2",
            "wet_grass5.3",
            "wet_grass5.4",
            "wet_grass5.5",
            "wet_grass5.4",
            "wet_grass5.3",
            "wet_grass5.2",
        ],
    )
    tp_init(
        name="wet_grass6",
        tiles=[
            "wet_grass6.1",
            "wet_grass6.2",
            "wet_grass6.3",
            "wet_grass6.4",
            "wet_grass6.5",
            "wet_grass6.4",
            "wet_grass6.3",
            "wet_grass6.2",
        ],
    )


init()
