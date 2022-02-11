import my
import tp


def tp_init(name, tiles=[]):
    mytp = tp.Tp(name, "wet grass")
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_shown_in_bg(mytp, True)
    my.tp_set_gfx_very_short_shadow_caster(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_cursor_can_hover_over(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_wet_grass(mytp, True)
    my.tp_set_text_a_or_an(mytp, "the")
    my.tp_set_text_description(mytp, "Tall and oddly healthy subterranean grass.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    for t in tiles:
        my.tp_set_tile(mytp, t)

    my.tp_update(mytp, )


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
