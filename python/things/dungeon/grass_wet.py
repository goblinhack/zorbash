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
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_shadow_very_short(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.is_able_to_dampen_footsteps(self, True)
    my.is_able_to_fall(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_grass(self, True)
    my.is_grass_wet(self, True)
    my.is_interesting(self, True)
    my.is_only_one_per_tile(self, True)
    my.nutrition_dice(self, "1d5")
    my.temperature_max(self, 50)
    my.temperature_min(self, 0)
    my.temperature_sensitive(self, True)
    my.temperature_sensitive_to_sudden_changes(self, True)
    my.text_a_or_an(self, "the")
    my.text_description_short(self, "Tall and oddly healthy subterranean grass.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_FLOOR2)  # if you change this, change grass_tick
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    for t in tiles:
        my.tile(self, delay_ms=300,
                ascii_fg_char="three_dots", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(
        name="grass_wet1",
        tiles=[
            "grass_wet1.1",
            "grass_wet1.2",
            "grass_wet1.3",
            "grass_wet1.4",
            "grass_wet1.5",
            "grass_wet1.4",
            "grass_wet1.3",
            "grass_wet1.2",
        ],
    )
    tp_init(
        name="grass_wet2",
        tiles=[
            "grass_wet2.1",
            "grass_wet2.2",
            "grass_wet2.3",
            "grass_wet2.4",
            "grass_wet2.5",
            "grass_wet2.4",
            "grass_wet2.3",
            "grass_wet2.2",
        ],
    )
    tp_init(
        name="grass_wet3",
        tiles=[
            "grass_wet3.1",
            "grass_wet3.2",
            "grass_wet3.3",
            "grass_wet3.4",
            "grass_wet3.5",
            "grass_wet3.4",
            "grass_wet3.3",
            "grass_wet3.2",
        ],
    )
    tp_init(
        name="grass_wet4",
        tiles=[
            "grass_wet4.1",
            "grass_wet4.2",
            "grass_wet4.3",
            "grass_wet4.4",
            "grass_wet4.5",
            "grass_wet4.4",
            "grass_wet4.3",
            "grass_wet4.2",
        ],
    )
    tp_init(
        name="grass_wet5",
        tiles=[
            "grass_wet5.1",
            "grass_wet5.2",
            "grass_wet5.3",
            "grass_wet5.4",
            "grass_wet5.5",
            "grass_wet5.4",
            "grass_wet5.3",
            "grass_wet5.2",
        ],
    )
    tp_init(
        name="grass_wet6",
        tiles=[
            "grass_wet6.1",
            "grass_wet6.2",
            "grass_wet6.3",
            "grass_wet6.4",
            "grass_wet6.5",
            "grass_wet6.4",
            "grass_wet6.3",
            "grass_wet6.2",
        ],
    )


init()
