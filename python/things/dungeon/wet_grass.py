import my
import tp


def tp_init(name, tiles=[]):
    mytp = tp.Tp(name, "wet grass")
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_shown_in_bg(True)
    mytp.set_gfx_very_short_shadow_caster(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_cursor_can_hover_over(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_interesting(True)  # for submerging
    mytp.set_is_wet_grass(True)
    mytp.set_text_a_or_an("the")
    mytp.set_text_description("Tall and oddly healthy subterranean grass.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    for t in tiles:
        mytp.set_tile(t)

    mytp.update()


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
