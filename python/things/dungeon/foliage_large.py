import my
import tp


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "foliage")
    # begin sort marker
    my.collision_check(self, True)
    my.collision_hit_priority(self, 1)
    my.collision_hit_priority(self, 3)
    my.gfx_ascii_fg_color_spread_hue(self, 10)
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_oversized_and_on_floor(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow_long(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_solid(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "1d20")
    my.is_able_to_amplify_footsteps(self, True)
    my.is_able_to_fall(self, True)
    my.is_always_hit(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_chasms(self, True)
    my.is_burnable(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_foliage(self, True)
    my.is_hittable(self, True)
    my.is_interesting(self, True)
    my.is_light_blocker_for_monst(self, True)  # to give cover to the player
    my.noise_blocker(self, True)
    my.nutrition_dice(self, "1d8")
    my.temperature_max(self, 50)
    my.temperature_min(self, 0)
    my.temperature(self, 20)
    my.temperature_sensitive(self, True)
    my.temperature_sensitive_to_sudden_changes(self, True)
    my.text_a_or_an(self, "the")
    my.text_description_long(self, "Dense foliage. Monsters cannot see through these thick bushes. Use them for cover.")
    my.text_description_short(self, "Dense foliage.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_FOLIAGE)
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="aries", ascii_bg_col_name="", ascii_fg_col_name="darkgreen",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(
        name="foliage_large",
        tiles=[
            "foliage_large.1",
            "foliage_large.2",
            "foliage_large.3",
            "foliage_large.4",
            "foliage_large.5",
            "foliage_large.6",
            "foliage_large.7",
            "foliage_large.8",
            "foliage_large.9",
            "foliage_large.10",
            "foliage_large.11",
            "foliage_large.12",
            "foliage_large.13",
            "foliage_large.14",
            "foliage_large.15",
            "foliage_large.16",
        ],
    )


init()
