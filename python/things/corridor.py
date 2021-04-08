import zx
import tp


def tp_init(name, tiles=[], bot3_tiles=[]):
    x = tp.Tp(name)
    x.set_gfx_shown_in_bg(True)
    x.set_is_able_to_fall(False)
    x.set_is_corridor(True)
    x.set_is_cursor_can_hover_over(True)
    x.set_is_interesting(False)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_text_a_or_an("the");
    x.set_text_description("The dirty dungeon corridor.")
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
    tp_init(name="corridor1",
        tiles=[
            "corridor1.1", "corridor1.2", "corridor1.3", "corridor1.4",
            "corridor1.5", "corridor1.6", "corridor1.7", "corridor1.8",
            "corridor1.9", "corridor1.10", "corridor1.11", "corridor1.12",
            "corridor1.13", "corridor1.14", "corridor1.15", "corridor1.16",
            "corridor1.17", "corridor1.18", "corridor1.19",
        ],
        bot3_tiles=[ 
                    "chasm1.1", "chasm1.2", "chasm1.3", "chasm1.4", "chasm1.5",
                    "chasm1.6", "chasm1.7", "chasm1.8", "chasm1.9", "chasm1.10",
                    "chasm1.11", "chasm1.12", "chasm1.13", "chasm1.14", "chasm1.15",
                    "chasm1.16", "chasm1.17", "chasm1.18", "chasm1.19",
            ])
    tp_init(name="corridor2",
        tiles=[
            "corridor2.1", "corridor2.2", "corridor2.3", "corridor2.4",
            "corridor2.5", "corridor2.6", "corridor2.7", "corridor2.8",
            "corridor2.9", "corridor2.10", "corridor2.11", "corridor2.12",
            "corridor2.13", "corridor2.14", "corridor2.15", "corridor2.16",
            "corridor2.17", "corridor2.18", "corridor2.19",
        ],
        bot3_tiles=[ 
                    "chasm1.1", "chasm1.2", "chasm1.3", "chasm1.4", "chasm1.5",
                    "chasm1.6", "chasm1.7", "chasm1.8", "chasm1.9", "chasm1.10",
                    "chasm1.11", "chasm1.12", "chasm1.13", "chasm1.14", "chasm1.15",
                    "chasm1.16", "chasm1.17", "chasm1.18", "chasm1.19",
            ])
    tp_init(name="corridor3",
        tiles=[
            "corridor3.1", "corridor3.2", "corridor3.3", "corridor3.4",
            "corridor3.5", "corridor3.6", "corridor3.7", "corridor3.8",
            "corridor3.9", "corridor3.10", "corridor3.11", "corridor3.12",
            "corridor3.13", "corridor3.14", "corridor3.15", "corridor3.16",
            "corridor3.17", "corridor3.18", "corridor3.19",
        ],
        bot3_tiles=[ 
                    "chasm1.1", "chasm1.2", "chasm1.3", "chasm1.4", "chasm1.5",
                    "chasm1.6", "chasm1.7", "chasm1.8", "chasm1.9", "chasm1.10",
                    "chasm1.11", "chasm1.12", "chasm1.13", "chasm1.14", "chasm1.15",
                    "chasm1.16", "chasm1.17", "chasm1.18", "chasm1.19",
            ])
init()
