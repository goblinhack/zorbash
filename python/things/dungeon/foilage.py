import my
import tp


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "foilage")
    # begin sort marker
    my.collision_check(self, True)
    my.collision_hit_priority(self, 3)
    my.gfx_ascii_fg_color_spread_hue(self, 50)
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_pixelart_shadow_long(self, True)
    my.gfx_pixelart_shadow_solid(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "1d5")
    my.is_able_to_burn(self, True)
    my.is_able_to_fall(self, True)
    my.is_always_hit(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_foilage(self, True)
    my.is_hittable(self, True)
    my.is_interesting(self, True)
    my.is_light_blocker_for_monst(self, True)  # to give cover to the player
    my.is_temperature_change_sensitive(self, True)
    my.is_temperature_sensitive(self, True)
    my.noise_blocker(self, True)
    my.text_a_or_an(self, "the")
    my.text_long_description(self, "Thick and sickly looking foilage and roots. Monsters cannot see through these thick bushes. Use them for cover.")
    my.text_short_description(self, "Thick and sickly looking foilage and roots.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_FOILAGE)
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="aries", ascii_bg_col_name="", ascii_fg_col_name="darkgreen",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(
        name="foilage",
        tiles=[
            "foilage.1",
            "foilage.2",
            "foilage.3",
            "foilage.4",
            "foilage.5",
            "foilage.6",
            "foilage.7",
            "foilage.8",
            "foilage.9",
            "foilage.10",
            "foilage.11",
            "foilage.12",
            "foilage.13",
            "foilage.14",
            "foilage.15",
            "foilage.16",
            "foilage.17",
            "foilage.18",
            "foilage.19",
            "foilage.20",
            "foilage.21",
            "foilage.22",
            "foilage.23",
            "foilage.24",
            "foilage.25",
            "foilage.26",
            "foilage.27",
            "foilage.28",
            "foilage.29",
            "foilage.30",
            "foilage.31",
            "foilage.32",
        ],
    )


init()
