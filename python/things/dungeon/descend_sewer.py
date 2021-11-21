import my
import tp

def spawn(me, x, y):
    my.level_spawn_next_to(me, "jelly_baby")


def tp_init(name, tiles=[], left1_tiles=[]):
    # mytp.set_is_minion_generator(True) # don't set to avoid auto place
    mytp = tp.Tp(name)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_shown_in_bg(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_is_descend_sewer(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_loggable(True)
    mytp.set_is_tickable(True)
    mytp.set_light_color("lime")
    mytp.set_light_strength(1)
    mytp.set_long_text_description("A filthy sewer pipe. Watch out, they can spawn surprises. Don't fall in!")
    mytp.set_minion_limit(5)
    mytp.set_on_idle_dice("1d50+50:descend_sewer.spawn()")
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A slime coated sewer pipe.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_ALWAYS_BEHIND)

    delay = 2500
    for t in tiles:
        mytp.set_tile(tile=t, delay_ms=delay)

    mytp.update()

def init():
    tp_init(name="descend_sewer1", tiles=[ "descend_sewer1.1", "descend_sewer1.2", ])
    tp_init(name="descend_sewer2", tiles=[ "descend_sewer2.1", "descend_sewer2.2", ])
    tp_init(name="descend_sewer3", tiles=[ "descend_sewer3.1", "descend_sewer3.2", ])
    tp_init(name="descend_sewer4", tiles=[ "descend_sewer4.1", "descend_sewer4.2", ])
    tp_init(name="descend_sewer5", tiles=[ "descend_sewer5.1", "descend_sewer5.2", ])
init()
