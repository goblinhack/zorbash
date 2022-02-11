import my
import tp


#
# NOTE: chasm tiles are not blitted explicitly. Instead a floor tile
# will check for the presence of a chasm beneath it and blit the chasm
#
def chasm_init(name, text_name, tiles=[]):
    mytp = tp.Tp(name, text_name)
    my.tp_set_ai_obstacle(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_chasm(mytp, True)
    my.tp_set_is_cursor_can_hover_over_x2_click(mytp, True)
    my.tp_set_is_cursor_path_hazard_for_player(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_hazard(mytp, True)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "%%fg=red$A yawning chasm to the unknown below%%fg=reset$ (mytp, double click to jump into).")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_CHASM)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    my.tp_update(mytp, )


def init():
    chasm_init(name="chasm1", text_name="yawning chasm", tiles=[])


init()
