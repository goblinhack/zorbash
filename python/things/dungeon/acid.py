import my
import tp


def acid_init(name, text_long_name, text_short_name, tiles=[], left_tiles=[]):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.dmg_acid_dice(self, "1d3+1")
    my.dmg_chance_d1000_acid(self, 0, 1000)
    my.dmg_nat_att_type(self, "burn")
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.is_able_to_fall(self, True)
    my.is_acid(self, True)
    my.is_eater_of_meat(self, True)
    my.is_hazard(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_obs_ai(self, True)
    my.is_only_one_per_tile(self, True)
    my.is_removable_if_out_of_slots(self, True)
    my.is_tickable(self, True)  # for lifespan
    my.lifespan_dice(self, "1d20+20")
    my.light_color(self, "green")
    my.light_dist(self, 2)
    my.text_a_or_an(self, "")
    my.text_description_short(self, "A pool of hissing acid.")
    my.text_hits(self, "burns")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_ACID)
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
        text_long_name="hissing acid",
        text_short_name="acid",
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
