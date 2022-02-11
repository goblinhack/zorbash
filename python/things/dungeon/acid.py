import my
import tp


def acid_init(name, text_name, short_text_name, tiles=[], left_tiles=[]):
    self = tp.Tp(name, text_name, short_text_name)
    my.tp_set_ai_obstacle(self, True)
    my.tp_set_damage_acid_chance_d1000(self, 1000)
    my.tp_set_damage_acid_dice(self, "1d3+1")
    my.tp_set_damage_natural_attack_type(self, "burn")
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_acid(self, True)
    my.tp_set_is_hazard(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_meat_eater(self, True)
    my.tp_set_is_removeable_if_out_of_slots(self, True)
    my.tp_set_is_tickable(self, True)  # for lifespan tick
    my.tp_set_lifespan_dice(self, "1d20+20")
    my.tp_set_light_color(self, "green")
    my.tp_set_light_power(self, 2)
    my.tp_set_text_a_or_an(self, "")
    my.tp_set_text_description(self, "A pool of hissing acid.")
    my.tp_set_text_hits(self, "burns")
    my.tp_set_z_depth(self, my.MAP_DEPTH_FLOOR2)
    my.tp_set_z_prio(self, my.MAP_PRIO_NORMAL)

    for t in tiles:
        my.tp_set_tile(self, tile=t)

    my.tp_update(self)


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
