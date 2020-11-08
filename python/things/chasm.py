import zx
import tp


def chasm_init(name, text_name, tiles=[]):
    x = tp.Tp(name, text_name)

    # x.set_is_cursor_can_hover_over(True)
    x.set_ai_obstacle(True)
    x.set_is_chasm(True)
    x.set_is_cursor_can_hover_over_but_needs_double_click(True)
    x.set_gfx_shown_in_bg(True)
    x.set_is_hazard(True)
    x.set_is_interesting(True)
    x.set_text_a_or_an("a");
    x.set_text_description("%%fg=red$A yawning chasm to the unknown below%%fg=reset$ (double click to jump)")
    x.set_z_depth(zx.MAP_DEPTH_CHASM)
    x.set_z_ascii_depth(zx.MAP_DEPTH_FLOOR)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    delay = 200
    for t in tiles:
        x.set_tile(tile=t, delay_ms=delay)

    x.update()

def init():
    chasm_init(name="chasm1", text_name="yawning chasm",
            tiles=[
                "ascii.chasm.1",
                "ascii.chasm.2",
                "ascii.chasm.3",
                "ascii.chasm.4",
                "ascii.chasm.5",
                "ascii.chasm.6"
                ])

init()
