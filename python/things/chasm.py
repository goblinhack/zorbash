import zx
import tp


#
# NOTE: chasm tiles are not blitted explicitly. Instead a floor tile
# will check for the presence of a chasm beneath it and blit the chasm
#
def chasm_init(name, text_name, tiles=[]):
    x = tp.Tp(name, text_name)
    x.set_ai_obstacle(True)
    x.set_is_cursor_can_hover_over_but_needs_double_click(True)
    x.set_is_hazard(True)
    x.set_is_extreme_hazard(True)
    x.set_is_chasm(True)
    x.set_is_described_when_hovering_over(True)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_text_a_or_an("a")
    x.set_text_description("%%fg=red$A yawning chasm to the unknown below%%fg=reset$ (double click to jump into)")
    x.set_z_depth(zx.MAP_DEPTH_CHASM)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    delay = 200

    x.update()

def init():
    chasm_init(name="chasm1", text_name="yawning chasm",
            tiles=[ ])

init()
