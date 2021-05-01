import zx
import tp


def tp_init(name, tiles=[], bot3_tiles=[]):
    x = tp.Tp(name)
    x.set_gfx_shown_in_bg(True)
    x.set_is_able_to_fall(True)
    x.set_is_interesting(True)
    x.set_is_bridge(True)
    x.set_is_cursor_can_hover_over(True)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_text_a_or_an("the");
    x.set_text_description("Shaky bridge.")
    x.set_z_depth(zx.MAP_DEPTH_FLOOR)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    for t in tiles:
        x.set_tile(t)

    if bot3_tiles is not None:
        for t in bot3_tiles:
            x.set_bot3_tile(t)
    else:
        x.set_bot3_tile(bot3_tile=name)

    x.update()

def init():
    tp_init(name="bridge_x", tiles=[ "bridge_x", ], bot3_tiles=[ "chasm1.1", ])
    tp_init(name="bridge_lr",
        tiles=[
            "bridge_lr.1", "bridge_lr.2", "bridge_lr.3", "bridge_lr.4",
            "bridge_lr.5", "bridge_lr.6", "bridge_lr.7", "bridge_lr.8",
            "bridge_lr.9", "bridge_lr.10", "bridge_lr.11", "bridge_lr.12",
            "bridge_lr.13", "bridge_lr.14", "bridge_lr.15", "bridge_lr.16",
            "bridge_lr.17", "bridge_lr.18", 
        ],
        bot3_tiles=[ 
                    "chasm1.1", "chasm1.2", "chasm1.3", "chasm1.4", "chasm1.5",
                    "chasm1.6", "chasm1.7", "chasm1.8", "chasm1.9", "chasm1.10",
                    "chasm1.11", "chasm1.12", "chasm1.13", "chasm1.14", "chasm1.15",
                    "chasm1.16", "chasm1.17", "chasm1.18", "chasm1.19",
            ])
    tp_init(name="bridge_ud",
        tiles=[
            "bridge_ud.1", "bridge_ud.2", "bridge_ud.3", "bridge_ud.4",
            "bridge_ud.5", "bridge_ud.6", "bridge_ud.7", "bridge_ud.8",
            "bridge_ud.9", "bridge_ud.10", "bridge_ud.11", "bridge_ud.12",
            "bridge_ud.13", "bridge_ud.14", "bridge_ud.15", "bridge_ud.16",
            "bridge_ud.17", "bridge_ud.18", 
            "bridge_ud.19",
        ],
        bot3_tiles=[ 
                    "chasm1.1", "chasm1.2", "chasm1.3", "chasm1.4", "chasm1.5",
                    "chasm1.6", "chasm1.7", "chasm1.8", "chasm1.9", "chasm1.10",
                    "chasm1.11", "chasm1.12", "chasm1.13", "chasm1.14", "chasm1.15",
                    "chasm1.16", "chasm1.17", "chasm1.18", "chasm1.19",
            ])
init()
