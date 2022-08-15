import my
import tp


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # start sort marker
    my.collision_hit_priority(self, 2)
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated_can_vflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.health_initial_dice(self, "1d4")
    my.is_able_to_fall(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_flat(self, True)
    my.is_green_blood(self, True)
    my.is_interesting(self, True)
    my.is_removeable_if_out_of_slots(self, True)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "1d4")
    my.text_a_or_an(self, "a")
    my.text_short_description(self, "An artwork comprised mainly of green blood.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_FLOOR2)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="middle_dot", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".100", is_hp_100_percent=True)
    my.tile(self,
            ascii_fg_char="middle_dot", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".75", is_hp_75_percent=True)
    my.tile(self,
            ascii_fg_char="middle_dot", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".50", is_hp_50_percent=True)
    my.tile(self,
            ascii_fg_char="middle_dot", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".25", is_hp_25_percent=True)

    my.tp_update(self)


def init():
    tp_init(name="floor_green_blood1", text_long_name="pool of fluorescent blood")
    tp_init(name="floor_green_blood2", text_long_name="pool of fluorescent blood")
    tp_init(name="floor_green_blood3", text_long_name="pool of fluorescent blood with bits in it")
    tp_init(name="floor_green_blood4", text_long_name="pool of fluorescent blood")
    tp_init(name="floor_green_blood5", text_long_name="pool of yucky fluorescent blood")
    tp_init(name="floor_green_blood6", text_long_name="pool of icky fluorescent blood")
    tp_init(name="floor_green_blood7", text_long_name="pool of fluorescent blood")
    tp_init(name="floor_green_blood8", text_long_name="pool of fluorescent blood")


init()
