import my
import tp


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.is_biome_dungeon(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_cursor_path_blocker(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_gas_blocker(self, True)
    my.is_interesting(self, True)
    my.is_light_blocker(self, True)
    my.is_loggable(self, True)
    my.is_obs_in_the_way_for_jumping(self, True)
    my.is_secret_door(self, True)
    my.noise_blocker(self, True)
    my.noise_on_open(self, 10)
    my.noise_on_you_are_hit_and_now_dead(self, 10)
    my.noise_on_you_are_hit_but_still_alive(self, 10)
    my.normal_placement_rules(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_short(self, "A strange looking wall.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="#", ascii_bg_col_name="gray20", ascii_fg_col_name="white",
            tile=name + ".1")
    my.tile(self,
            ascii_fg_char="#", ascii_bg_col_name="gray20", ascii_fg_col_name="white",
            tile=name + ".2")
    my.tile(self,
            ascii_fg_char="#", ascii_bg_col_name="gray20", ascii_fg_col_name="white",
            tile=name + ".3")
    my.tile(self,
            ascii_fg_char="#", ascii_bg_col_name="gray20", ascii_fg_col_name="white",
            tile=name + ".4")
    my.tile(self,
            ascii_fg_char="#", ascii_bg_col_name="gray20", ascii_fg_col_name="white",
            tile=name + ".5")
    my.tile(self,
            ascii_fg_char="#", ascii_bg_col_name="gray20", ascii_fg_col_name="white",
            tile=name + ".6")
    my.tile(self,
            ascii_fg_char="#", ascii_bg_col_name="gray20", ascii_fg_col_name="white",
            tile=name + ".7")
    my.tile(self,
            ascii_fg_char="#", ascii_bg_col_name="gray20", ascii_fg_col_name="white",
            tile=name + ".8")
    my.tile(self,
            ascii_fg_char="#", ascii_bg_col_name="gray20", ascii_fg_col_name="white",
            tile=name + ".9")
    my.tile(self,
            ascii_fg_char="#", ascii_bg_col_name="gray20", ascii_fg_col_name="white",
            tile=name + ".10")
    my.tile(self,
            ascii_fg_char="#", ascii_bg_col_name="gray20", ascii_fg_col_name="white",
            tile=name + ".11")
    my.tile(self,
            ascii_fg_char="#", ascii_bg_col_name="gray20", ascii_fg_col_name="white",
            tile=name + ".12")
    my.tile(self,
            ascii_fg_char="#", ascii_bg_col_name="gray20", ascii_fg_col_name="white",
            tile=name + ".13")
    my.tile(self,
            ascii_fg_char="#", ascii_bg_col_name="gray20", ascii_fg_col_name="white",
            tile=name + ".14")
    my.tile(self,
            ascii_fg_char="#", ascii_bg_col_name="gray20", ascii_fg_col_name="white",
            tile=name + ".15")
    my.tile(self,
            ascii_fg_char="#", ascii_bg_col_name="gray20", ascii_fg_col_name="white",
            tile=name + ".16")

    my.tp_update(self)


def init():
    tp_init(name="door_secret", text_long_name="An inconspicious dungeon wall.")


init()
