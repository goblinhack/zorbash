import my
import tp


def acid_init(name, text_name, short_text_name, tiles=[], left_tiles=[]):
    self = tp.Tp(name, text_name, short_text_name)
    # start sort marker
    my.ai_obstacle(self, True)
    my.damage_acid_chance_d1000(self, 0, 1000)
    my.damage_acid_dice(self, "1d3+1")
    my.damage_nat_attack_type(self, "burn")
    my.gfx_ascii_mode_shown(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.is_able_to_fall(self, True)
    my.is_acid(self, True)
    my.is_hazard(self, True)
    my.is_loggable(self, True)
    my.is_meat_eater(self, True)
    my.is_removeable_if_out_of_slots(self, True)
    my.is_tickable(self, True)  # for lifespan tick
    my.lifespan_dice(self, "1d20+20")
    my.light_color(self, "green")
    my.light_dist(self, 2)
    my.text_a_or_an(self, "")
    my.text_description(self, "A pool of hissing acid.")
    my.text_hits(self, "burns")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_FLOOR2)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="middle_dot", ascii_bg_col_name="", ascii_fg_col_name="green",
                tile=t)

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
