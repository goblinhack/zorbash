import my
import tp


def tp_init(name, text_name, tiles=[]):
    mytp = tp.Tp(name, text_name)
    my.tp_set_ai_obstacle(mytp, True)
    my.tp_set_environ_avoids_fire(mytp, 1)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_water(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_hazard(mytp, True)
    my.tp_set_is_shallow_water(mytp, True)
    my.tp_set_text_a_or_an(mytp, "the")
    my.tp_set_text_description(mytp, "Some shallow water.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_WATER)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL)

    delay = 1250
    for t in tiles:
        my.tp_set_tile(mytp, tile=t, delay_ms=delay)

    my.tp_update(mytp, )


def init():
    tp_init(
        name="water1",
        text_name="water",
        tiles=[
            "water1.1",
            "water1.2",
            "water1.3",
            "water1.4",
            "water1.5",
            "water1.6",
            "water1.7",
            "water1.8",
            "water1.9",
            "water1.10",
            "water1.11",
            "water1.12",
            "water1.13",
            "water1.14",
            "water1.15",
            "water1.16",
            "water1.17",
            "water1.18",
            "water1.19",
            "water1.20",
            "water1.21",
            "water1.22",
            "water1.23",
            "water1.24",
            "water1.25",
            "water1.26",
            "water1.27",
            "water1.28",
            "water1.29",
            "water1.30",
            "water1.31",
            "water1.32",
        ],
    )


init()
