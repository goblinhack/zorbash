import zx
import tp


def tp_init(name, text_name, tiles=[]):

    x = tp.Tp(name, text_name)

    x.set_ai_obstacle(True)
    x.set_gfx_animated(True)
    x.set_is_gfx_shown_in_bg(True)
    x.set_is_hazard(True)
    x.set_is_interesting(True)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_is_water(True)
    x.set_text_a_or_an("the");
    x.set_text_description("Some shallow water")
    x.set_z_depth(zx.MAP_DEPTH_WATER)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 1250
    for t in tiles:
        x.set_tile(tile=t, delay_ms=delay)

    x.update()

def init():
    tp_init(name="water1", text_name="water",
            tiles=[
                "water1.1",
                "water1.2",
                "water1.3",
                "water1.4",
                "water1.5",
                "water1.6",
                "water1.7",
                "water1.8",
                "water1.9",
                "water1.10",
                "water1.11",
                "water1.12",
                "water1.13",
                "water1.14",
                "water1.15",
                "water1.16",
                "water1.17",
                "water1.18",
                "water1.19",
                "water1.20",
                "water1.21",
                "water1.22",
                "water1.23",
                "water1.24",
                "water1.25",
                "water1.26",
                "water1.27",
                "water1.28",
                "water1.29",
                "water1.30",
                "water1.31",
                "water1.32",
                ])
init()
