import my
import tp


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "dry trampled grass")
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_shown_in_bg(self, True)
    my.tp_set_gfx_very_short_shadow_caster(self, True)
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_cursor_can_hover_over(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_dry_grass(self, True)
    my.tp_set_is_interesting(self, True)
    my.tp_set_text_a_or_an(self, "the")
    my.tp_set_text_description(self, "Burnt not so funky grass.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_FLOOR2)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    for t in tiles:
        my.tp_set_tile(self, t)

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
