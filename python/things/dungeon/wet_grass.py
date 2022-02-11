import my
import tp


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "wet grass")
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_shown_in_bg(self, True)
    my.tp_set_gfx_very_short_shadow_caster(self, True)
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_cursor_can_hover_over(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_wet_grass(self, True)
    my.tp_set_text_a_or_an(self, "the")
    my.tp_set_text_description(self, "Tall and oddly healthy subterranean grass.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    for t in tiles:
        my.tp_set_tile(self, t)

    my.tp_update(self)


def init():
    tp_init(
        name="wet_grass",
        tiles=[
            "wet_grass.1",
            "wet_grass.2",
            "wet_grass.3",
            "wet_grass.4",
            "wet_grass.5",
            "wet_grass.6",
            "wet_grass.7",
            "wet_grass.8",
            "wet_grass.9",
            "wet_grass.10",
            "wet_grass.11",
            "wet_grass.12",
            "wet_grass.13",
            "wet_grass.14",
            "wet_grass.15",
            "wet_grass.16",
            "wet_grass.17",
            "wet_grass.18",
        ],
    )


init()
