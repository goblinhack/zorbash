import zx
import tp

def spawn(me, x, y):
    zx.tp_spawn_next_to(me, "jelly_baby")


def tp_init(name, tiles=[], left1_tiles=[]):

    x = tp.Tp(name)
    # x.set_is_minion_generator(True) # don't set to avoid auto place
    x.set_attackable(True)
    x.set_gfx_animated(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_shown_in_bg(True)
    x.set_is_able_to_fall(False)
    x.set_is_always_hit(True)
    x.set_is_active(True)
    x.set_is_interesting(False)
    x.set_is_light_strength(1)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_wall_deco(True)
    x.set_light_color("lime")
    x.set_is_described_when_hovering_over(True)
    x.set_long_text_description("A filthy sewer pipe. Watch out, they can spawn surprises. Don't fall in!")
    x.set_on_idle_dice("1d50+50:jelly_minion_generator.spawn()")
    x.set_text_a_or_an("a");
    x.set_text_description("A slime coated sewer pipe")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_INFRONT)

    delay = 2500
    for t in tiles:
        x.set_tile(tile=t, delay_ms=delay)

    x.update()

def init():
    tp_init(name="grate1", tiles=[ "grate1.1", "grate1.2", ])
    tp_init(name="grate2", tiles=[ "grate2.1", "grate2.2", ])
    tp_init(name="grate3", tiles=[ "grate3.1", "grate3.2", ])
    tp_init(name="grate4", tiles=[ "grate4.1", "grate4.2", ])
    tp_init(name="grate5", tiles=[ "grate5.1", "grate5.2", ])
    tp_init(name="grate6", tiles=[ "grate6.1", "grate6.2", ])
    tp_init(name="grate7", tiles=[ "grate7.1", "grate7.2", ])
    tp_init(name="grate8", tiles=[ "grate8.1", "grate8.2", ])
init()
