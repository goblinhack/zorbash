import zx
import tp

def spawn(me, x, y):
    zx.level_spawn_next_to(me, "jelly_baby")


def tp_init(name, tiles=[], left1_tiles=[]):

    mytp = tp.Tp(name)
    # mytp.set_is_minion_generator(True) # don't set to avoid auto place
    mytp.set_gfx_animated(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_gfx_shown_in_bg(True)
    mytp.set_is_able_to_fall(False)
    mytp.set_is_active(True)
    mytp.set_is_ascend_sewer(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_loggable_for_important_stuff(True)
    mytp.set_is_loggable_for_unimportant_stuff(True)
    mytp.set_light_color("lime")
    mytp.set_light_strength(1)
    mytp.set_long_text_description("A way out of these stinking sewers!")
    mytp.set_minion_limit(5)
    mytp.set_on_idle_dice("1d50+50:ascend_sewer.spawn()")
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A slime coated sewer pipe.")
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_BEHIND)

    delay = 1000
    for t in tiles:
        mytp.set_tile(tile=t, delay_ms=delay)

    mytp.update()

def init():
    tp_init(name="ascend_sewer1", tiles=[ "ascend_sewer1.1", "ascend_sewer1.2", ])
    tp_init(name="ascend_sewer2", tiles=[ "ascend_sewer2.1", "ascend_sewer2.2", ])
    tp_init(name="ascend_sewer3", tiles=[ "ascend_sewer3.1", "ascend_sewer3.2", ])
    tp_init(name="ascend_sewer4", tiles=[ "ascend_sewer4.1", "ascend_sewer4.2", ])
init()
