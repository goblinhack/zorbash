import my
import tp


def tp_init(name, text_long_name, tiles=[]):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.appearing_chance_d1000(self, 100)
    my.collision_hit_priority(self, 2)
    my.damage_crush_chance_d1000(self, 0, 1000)
    my.damage_crush_dice(self, "1d6")
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_glows(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_flickers(self, True)
    my.gfx_pixelart_oversized_and_on_floor(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.gfx_pixelart_submergable(self, True)
    my.is_able_to_fall(self, True)
    my.is_biome_dungeon(self, True)
    my.is_brazier(self, True)
    my.is_corpse_on_death(self, True)
    my.is_dead_on_shove(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_fire(self, True)
    my.is_floor_deco(self, True)
    my.is_heavy(self, True)
    my.is_immune_to_fire(self, True)
    my.is_interesting(self, True)  # so it can be shoved
    my.is_obs_for_ai(self, True)
    my.is_shovable(self, True)
    my.light_color(self, "orange")
    my.light_dist(self, 2)
    my.normal_placement_rules(self, True)
    my.spawn_on_shoved(self, "fire")
    my.temperature(self, 100)
    my.text_a_or_an(self, "a")
    my.text_short_description(self, "A beacon of light in this blighted place.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    delay = 100
    for t in tiles:
        my.tile(self,
                ascii_fg_char="#", ascii_bg_col_name="", ascii_fg_col_name="yellow",
                tile=t, delay_ms=delay)
        my.tile(self,
                ascii_fg_char="#", ascii_bg_col_name="", ascii_fg_col_name="white",
                tile=t, delay_ms=delay)

    my.tile(self,
            ascii_fg_char="#", ascii_bg_col_name="", ascii_fg_col_name="darkgray",
            tile=name + ".dead", is_dead=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(
        name="brazier",
        text_long_name="brazier",
        tiles=[
            "brazier.1",
            "brazier.2",
            "brazier.3",
            "brazier.4",
            "brazier.5",
            "brazier.6",
            "brazier.7",
            "brazier.8",
            "brazier.9",
            "brazier.10",
            "brazier.11",
            "brazier.12",
            "brazier.13",
            "brazier.14",
            "brazier.15",
            "brazier.16",
            "brazier.17",
            "brazier.18",
            "brazier.19",
            "brazier.20",
            "brazier.21",
            "brazier.22",
            "brazier.23",
            "brazier.24",
            "brazier.25",
            "brazier.26",
            "brazier.27",
            "brazier.28",
            "brazier.29",
            "brazier.30",
            "brazier.31",
            "brazier.32",
            "brazier.33",
            "brazier.34",
            "brazier.35",
            "brazier.36",
            "brazier.37",
        ],
    )


init()
