import zx
import tp


#
# NOTE: chasm tiles are not blitted explicitly. Instead a floor tile
# will check for the presence of a chasm beneath it and blit the chasm
#
def chasm_init(name, text_name, tiles=[]):
    mytp = tp.Tp(name, text_name)
    mytp.set_ai_obstacle(True)
    mytp.set_is_chasm(True)
    mytp.set_is_cursor_can_hover_over_but_needs_double_click(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_extreme_hazard(True)
    mytp.set_is_hazard(True)
    mytp.set_is_loggable_for_important_stuff(False)
    mytp.set_is_loggable_for_unimportant_stuff(False)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("%%fg=red$A yawning chasm to the unknown below%%fg=reset$ (double click to jump into)")
    mytp.set_z_depth(zx.MAP_DEPTH_CHASM)
    mytp.set_z_prio(zx.MAP_PRIO_BEHIND)

    delay = 200

    mytp.update()

def init():
    chasm_init(name="chasm1", text_name="yawning chasm",
            tiles=[ ])

init()
