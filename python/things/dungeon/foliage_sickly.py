import my
import tp


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "sickly foliage")
    # begin sort marker
    my.collision_check(self, True)
    my.collision_hit_priority(self, 1)
    my.collision_hit_priority(self, 3)
    my.gfx_ascii_fg_color_spread_hue(self, 10)
    my.gfx_ascii_shown(self, True)
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_pixelart_oversized_and_on_floor(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_long(self, True)
    my.gfx_pixelart_shadow_solid(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "1d3")
    my.is_able_to_amplify_footsteps(self, True)
    my.is_able_to_fall(self, True)
    my.is_always_hit(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_burnable(self, True)
    my.is_combustible(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_foliage(self, True)
    my.is_hittable(self, True)
    my.is_interesting(self, True)
    my.is_light_blocker_for_monst(self, True)  # to give cover to the player
    my.is_one_per_tile(self, True)
    my.is_shootable(self, True)
    my.noise_blocker(self, True)
    my.nutrition_dice(self, "1d3")
    my.temperature(self, 20)
    my.temperature_max(self, 50)
    my.temperature_min(self, 0)
    my.temperature_sensitive(self, True)
    my.temperature_sensitive_to_sudden_changes(self, True)
    my.text_a_or_an(self, "the")
    my.text_description_long(self, "Thick and sickly looking foliage and roots. Monsters cannot see through these thick bushes. Use them for cover.")
    my.text_description_short(self, "Thick and sickly looking foliage and roots.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_FOLIAGE)
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="aries", ascii_bg_col_name="", ascii_fg_col_name="darkolivegreen",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(
        name="foliage_sickly",
        tiles=[
            "foliage_sickly.1",
            "foliage_sickly.2",
            "foliage_sickly.3",
            "foliage_sickly.4",
            "foliage_sickly.5",
            "foliage_sickly.6",
            "foliage_sickly.7",
            "foliage_sickly.8",
            "foliage_sickly.9",
            "foliage_sickly.10",
            "foliage_sickly.11",
            "foliage_sickly.12",
            "foliage_sickly.13",
            "foliage_sickly.14",
            "foliage_sickly.15",
            "foliage_sickly.16",
            "foliage_sickly.17",
            "foliage_sickly.18",
            "foliage_sickly.19",
            "foliage_sickly.20",
            "foliage_sickly.21",
            "foliage_sickly.22",
            "foliage_sickly.23",
            "foliage_sickly.24",
            "foliage_sickly.25",
            "foliage_sickly.26",
            "foliage_sickly.27",
            "foliage_sickly.28",
            "foliage_sickly.29",
            "foliage_sickly.30",
            "foliage_sickly.31",
            "foliage_sickly.32",
        ],
    )


init()
