import my
import tp


#
# NOTE: chasm tiles are not blitted explicitly. Instead a floor tile
# will check for the presence of a chasm beneath it and blit the chasm
#
def chasm_init(name, text_name, tiles=[]):
    self = tp.Tp(name, text_name)
    my.gfx_ascii_mode_shown(self, True)
    my.ai_obstacle(self, True)
    my.is_biome_dungeon(self, True)
    my.is_chasm(self, True)
    my.is_cursor_can_hover_over_x2_click(self, True)
    my.is_cursor_path_hazard_for_player(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_hazard(self, True)
    my.text_a_or_an(self, "a")
    my.text_description(self, "%%fg=red$A yawning chasm to the unknown below%%fg=reset$ (self, double click to jump into).")
    my.z_depth(self, my.MAP_DEPTH_CHASM)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self,
            ascii_fg_char="four_dots", ascii_bg_col_name="black", ascii_fg_col_name="steelblue",
            tile="nothing")
    my.tp_update(self)


def init():
    chasm_init(name="chasm1", text_name="yawning chasm", tiles=[])


init()
