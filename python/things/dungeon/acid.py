import my
import tp


def acid_init(name, text_name, short_text_name, tiles=[], left_tiles=[]):
    mytp = tp.Tp(name, text_name, short_text_name)
    my.tp_set_ai_obstacle(mytp, True)
    my.tp_set_damage_acid_chance_d1000(mytp, 1000)
    my.tp_set_damage_acid_dice(mytp, "1d3+1")
    my.tp_set_damage_natural_attack_type(mytp, "burn")
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_acid(mytp, True)
    my.tp_set_is_hazard(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_meat_eater(mytp, True)
    my.tp_set_is_removeable_if_out_of_slots(mytp, True)
    my.tp_set_is_tickable(mytp, True)  # for lifespan tick
    my.tp_set_lifespan_dice(mytp, "1d20+20")
    my.tp_set_light_color(mytp, "green")
    my.tp_set_light_power(mytp, 2)
    my.tp_set_text_a_or_an(mytp, "")
    my.tp_set_text_description(mytp, "A pool of hissing acid.")
    my.tp_set_text_hits(mytp, "burns")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_FLOOR2)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL)

    for t in tiles:
        my.tp_set_tile(mytp, tile=t)

    my.tp_update(mytp, )


def init():
    acid_init(
        name="acid1",
        text_name="hissing acid",
        short_text_name="acid",
        tiles=[
            "acid1.1",
            "acid1.2",
            "acid1.3",
            "acid1.4",
            "acid1.5",
            "acid1.6",
            "acid1.7",
            "acid1.8",
            "acid1.9",
            "acid1.10",
            "acid1.11",
            "acid1.12",
            "acid1.13",
            "acid1.14",
            "acid1.15",
            "acid1.16",
            "acid1.17",
            "acid1.18",
            "acid1.19",
        ],
    )


init()
