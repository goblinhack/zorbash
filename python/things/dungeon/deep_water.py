import my
import tp


def tp_init(name, text_name, tiles=[]):
    mytp = tp.Tp(name, text_name)
    my.tp_set_ai_obstacle(mytp, True)
    my.tp_set_environ_avoids_fire(mytp, 1)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_shown_in_bg(mytp, True)
    my.tp_set_gfx_water(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_deep_water(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_hazard(mytp, True)
    my.tp_set_text_a_or_an(mytp, "the")
    my.tp_set_text_description(mytp, "A pool of deep dank water, with things in it.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_WATER)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL)

    delay = 1250
    for t in tiles:
        my.tp_set_tile(mytp, tile=t, delay_ms=delay)

    my.tp_update(mytp, )


def init():
    tp_init(
        name="deep_water1",
        text_name="deep water",
        tiles=[
            "deep_water1.1",
            "deep_water1.2",
            "deep_water1.3",
            "deep_water1.4",
            "deep_water1.5",
            "deep_water1.6",
            "deep_water1.7",
            "deep_water1.8",
            "deep_water1.9",
            "deep_water1.10",
            "deep_water1.11",
            "deep_water1.12",
            "deep_water1.13",
            "deep_water1.14",
            "deep_water1.15",
            "deep_water1.16",
        ],
    )


init()
