import zx
import tp

def spawn(me, x, y):
    zx.tp_spawn_next_to(me, "jelly_baby")


def tp_init(name, tiles=[], left1_tiles=[]):

    x = tp.Tp(name)
    # x.set_is_minion_generator(True) # don't set to avoid auto place
    x.set_gfx_animated(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_shown_in_bg(True)
    x.set_is_able_to_fall(False)
    x.set_is_active(True)
    x.set_is_described_when_hovering_over(True)
    x.set_is_interesting(False)
    x.set_is_light_strength(1)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_sewer_exit(True)
    x.set_light_color("lime")
    x.set_long_text_description("A way out of these stinking sewers!")
    x.set_minion_limit(10)
    x.set_on_idle_dice("1d50+50:sewer_exit.spawn()")
    x.set_text_a_or_an("a");
    x.set_text_description("A slime coated sewer pipe")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_INFRONT)

    delay = 2500
    for t in tiles:
        x.set_tile(tile=t, delay_ms=delay)

    x.update()

def init():
    tp_init(name="sewer_exit1", tiles=[ "sewer_exit1.1", "sewer_exit1.2", ])
    tp_init(name="sewer_exit2", tiles=[ "sewer_exit2.1", "sewer_exit2.2", ])
    tp_init(name="sewer_exit3", tiles=[ "sewer_exit3.1", "sewer_exit3.2", ])
    tp_init(name="sewer_exit4", tiles=[ "sewer_exit4.1", "sewer_exit4.2", ])
init()
