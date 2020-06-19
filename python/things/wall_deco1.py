import zx
import tp


def tp_init(name,
              tiles=[],
              left1_tiles=[]):

    x = tp.Tp(name)

    x.set_gfx_animated(True)
    x.set_is_interesting(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_wall_deco(True)
    x.set_text_a_or_an("a");
    x.set_z_prio(zx.MAP_PRIO_INFRONT)
    x.set_z_depth(zx.MAP_DEPTH_OBJ)

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
