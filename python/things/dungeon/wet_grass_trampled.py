import my
import tp


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "wet grass")
    # begin sort marker
    my.collision_hit_priority(self, 1)
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.gfx_pixelart_submergable(self, True)
    my.is_able_to_dampen_footsteps(self, True)
    my.is_able_to_fall(self, True)
    my.is_biome_dungeon(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_grass(self, True)
    my.is_interesting(self, True)
    my.is_wet_grass(self, True)
    my.is_wet_grass_trampled(self, True)
    my.nutrition_dice(self, "1d4")
    my.temperature_max(self, 50)
    my.temperature_min(self, 0)
    my.temperature_sensitive(self, True)
    my.temperature_sensitive_to_sudden_changes(self, True)
    my.text_a_or_an(self, "the")
    my.text_description_short(self, "Trampled subterranean grass.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_FLOOR2)  # if you change this, change grass_tick
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    for t in tiles:
        my.tile(self, delay_ms=600,
                ascii_fg_char="three_dots", ascii_bg_col_name="", ascii_fg_col_name="green",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(
        name="wet_grass_trampled1",
        tiles=[
            "wet_grass_trampled1.1",
            "wet_grass_trampled1.2",
            "wet_grass_trampled1.3",
            "wet_grass_trampled1.4",
            "wet_grass_trampled1.5",
            "wet_grass_trampled1.4",
            "wet_grass_trampled1.3",
            "wet_grass_trampled1.2",
        ],
    )
    tp_init(
        name="wet_grass_trampled2",
        tiles=[
            "wet_grass_trampled2.1",
            "wet_grass_trampled2.2",
            "wet_grass_trampled2.3",
            "wet_grass_trampled2.4",
            "wet_grass_trampled2.5",
            "wet_grass_trampled2.4",
            "wet_grass_trampled2.3",
            "wet_grass_trampled2.2",
        ],
    )
    tp_init(
        name="wet_grass_trampled3",
        tiles=[
            "wet_grass_trampled3.1",
            "wet_grass_trampled3.2",
            "wet_grass_trampled3.3",
            "wet_grass_trampled3.4",
            "wet_grass_trampled3.5",
            "wet_grass_trampled3.4",
            "wet_grass_trampled3.3",
            "wet_grass_trampled3.2",
        ],
    )
    tp_init(
        name="wet_grass_trampled4",
        tiles=[
            "wet_grass_trampled4.1",
            "wet_grass_trampled4.2",
            "wet_grass_trampled4.3",
            "wet_grass_trampled4.4",
            "wet_grass_trampled4.5",
            "wet_grass_trampled4.4",
            "wet_grass_trampled4.3",
            "wet_grass_trampled4.2",
        ],
    )
    tp_init(
        name="wet_grass_trampled5",
        tiles=[
            "wet_grass_trampled5.1",
            "wet_grass_trampled5.2",
            "wet_grass_trampled5.3",
            "wet_grass_trampled5.4",
            "wet_grass_trampled5.5",
            "wet_grass_trampled5.4",
            "wet_grass_trampled5.3",
            "wet_grass_trampled5.2",
        ],
    )
    tp_init(
        name="wet_grass_trampled6",
        tiles=[
            "wet_grass_trampled6.1",
            "wet_grass_trampled6.2",
            "wet_grass_trampled6.3",
            "wet_grass_trampled6.4",
            "wet_grass_trampled6.5",
            "wet_grass_trampled6.4",
            "wet_grass_trampled6.3",
            "wet_grass_trampled6.2",
        ],
    )


init()
