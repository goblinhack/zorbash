import zx
import tp


def tp_init(name, text_name, tiles=[]):
    mytp = tp.Tp(name, text_name)
    mytp.set_ai_obstacle(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_shown_in_bg(True)
    mytp.set_gfx_water(True)
    mytp.set_hates_fire(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_deep_water(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_hazard(True)
    mytp.set_is_loggable_for_important_stuff(False)
    mytp.set_is_loggable_for_unimportant_stuff(False)
    mytp.set_text_a_or_an("the")
    mytp.set_text_description("A pool of deep dank water, with things in it.")
    mytp.set_z_depth(zx.MAP_DEPTH_WATER)
    mytp.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 1250
    for t in tiles:
        mytp.set_tile(tile=t, delay_ms=delay)

    mytp.update()

def init():
    tp_init(name="deep_water1", text_name="deep water",
            tiles=[
                "deep_water1.1",
                "deep_water1.2",
                "deep_water1.3",
                "deep_water1.4",
                "deep_water1.5",
                "deep_water1.6",
                "deep_water1.7",
                "deep_water1.8",
                "deep_water1.9",
                "deep_water1.10",
                "deep_water1.11",
                "deep_water1.12",
                "deep_water1.13",
                "deep_water1.14",
                "deep_water1.15",
                "deep_water1.16",
                ])
init()
