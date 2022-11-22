import my
import tp


#
# NOTE: chasm tiles are not blitted explicitly. Instead a floor tile
# will check for the presence of a chasm beneath it and blit the chasm
#
def chasm_init(name, text_long_name, tiles=[]):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.gfx_ascii_fg_color_spread_hue(self, 20)
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.is_biome_dungeon(self, True)
    my.is_chasm(self, True)
    my.is_cursor_can_hover_over_x2_click(self, True)
    my.is_cursor_path_hazard(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_hazard(self, True)
    my.is_obs_for_ai(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_short(self, "%%fg=red$A yawning chasm to the unknown below%%fg=reset$ (double click to jump into).")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_CHASM)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="four_dots", ascii_bg_col_name="black", ascii_fg_col_name="steelblue",
            tile="nothing")
    my.tp_update(self)


def init():
    chasm_init(name="chasm1", text_long_name="yawning chasm", tiles=[])


init()
