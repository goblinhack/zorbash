import my
import tp


#
# NOTE: chasm tiles are not blitted explicitly. Instead a floor tile
# will check for the presence of a chasm beneath it and blit the chasm
#
def chasm_init(name, text_name, tiles=[]):
    self = tp.Tp(name, text_name)
    my.tp_set_ai_obstacle(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_chasm(self, True)
    my.tp_set_is_cursor_can_hover_over_x2_click(self, True)
    my.tp_set_is_cursor_path_hazard_for_player(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_hazard(self, True)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "%%fg=red$A yawning chasm to the unknown below%%fg=reset$ (self, double click to jump into).")
    my.tp_set_z_depth(self, my.MAP_DEPTH_CHASM)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_update(self)


def init():
    chasm_init(name="chasm1", text_name="yawning chasm", tiles=[])


init()
