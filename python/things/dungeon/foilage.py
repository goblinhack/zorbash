import my
import tp


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "foilage")
    my.collision_check(self, True)
    my.collision_hit_priority(self, 3)
    my.gfx_long_shadow_caster(self, True)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_shown_in_bg(self, True)
    my.gfx_solid_shadow(self, True)
    my.gfx_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "1d5")
    my.is_able_to_fall(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_foilage(self, True)
    my.is_hittable(self, True)
    my.is_interesting(self, True)
    my.is_light_blocker_for_monst(self, True)  # to give cover to the player
    my.long_text_description(self, "Thick and sicky looking foilage and roots. Monsters cannot see through these thick bushes. Use them for cover.")
    my.noise_blocker(self, True)
    my.text_a_or_an(self, "the")
    my.text_description(self, "Thick and sicky looking foilage and roots.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_IN_FRONT)

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
