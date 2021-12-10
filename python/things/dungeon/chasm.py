import my
import tp


#
# NOTE: chasm tiles are not blitted explicitly. Instead a floor tile
# will check for the presence of a chasm beneath it and blit the chasm
#
def chasm_init(name, text_name, tiles=[]):
    mytp = tp.Tp(name, text_name)
    mytp.set_ai_obstacle(True)
    mytp.set_is_chasm(True)
    mytp.set_is_cursor_can_hover_over_x2_click(True)
    mytp.set_is_cursor_path_hazard_for_player(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_hazard(True)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("%%fg=red$A yawning chasm to the unknown below%%fg=reset$ (double click to jump into)")
    mytp.set_z_depth(my.MAP_DEPTH_CHASM)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.update()


def init():
    chasm_init(name="chasm1", text_name="yawning chasm", tiles=[])


init()
