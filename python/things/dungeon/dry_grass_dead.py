import my
import tp


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "dead grass")
    # begin sort marker
    my.collision_hit_priority(self, 1)
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.gfx_pixelart_submergable(self, True)
    my.is_able_to_amplify_footsteps(self, True)
    my.is_able_to_fall(self, True)
    my.is_biome_dungeon(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_dry_grass(self, True)
    my.is_grass(self, True)
    my.is_interesting(self, True)
    my.nutrition_dice(self, "1d2")
    my.temperature_max(self, 50)
    my.temperature_min(self, 0)
    my.temperature_sensitive(self, True)
    my.temperature_sensitive_to_sudden_changes(self, True)
    my.text_a_or_an(self, "the")
    my.text_description_short(self, "Dead grass.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_FLOOR2)  # if you change this, change grass_tick
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="three_dots", ascii_bg_col_name="", ascii_fg_col_name="gray20",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(
        name="dry_grass_dead",
        tiles=[
            "dry_grass_dead.1",
            "dry_grass_dead.2",
            "dry_grass_dead.3",
            "dry_grass_dead.4",
            "dry_grass_dead.5",
            "dry_grass_dead.6",
            "dry_grass_dead.7",
            "dry_grass_dead.8",
            "dry_grass_dead.9",
            "dry_grass_dead.10",
            "dry_grass_dead.11",
            "dry_grass_dead.12",
            "dry_grass_dead.13",
            "dry_grass_dead.14",
            "dry_grass_dead.15",
            "dry_grass_dead.16",
            "dry_grass_dead.17",
            "dry_grass_dead.18",
        ],
    )


init()
