import zx
import tp


#
# NOTE: chasm tiles are not blitted explicitly. Instead a floor tile
# will check for the presence of a chasm beneath it and blit the chasm
#
def tp_init(name, tiles=[], left1_tiles=[], bot3_tiles=[]):
    x = tp.Tp(name)
    x.set_gfx_shown_in_bg(True)
    x.set_is_able_to_fall(False)
    x.set_is_cursor_can_hover_over(True)
    x.set_is_floor(True)
    x.set_is_interesting(False)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_text_a_or_an("the");
    x.set_text_description("The unwashed dungeon floor.")
    x.set_z_depth(zx.MAP_DEPTH_FLOOR)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    for t in tiles:
        x.set_tile(t)

    if bot3_tiles is not None:
        for t in bot3_tiles:
            x.set_bot3_tile(t)
    else:
        x.set_bot3_tile(bot3_tile=name)

    x.update()

def init():
    tp_init(name="floor1",
            tiles=[
                        "floor1.1", "floor1.2", "floor1.3", "floor1.4",
                        "floor1.5", "floor1.6", "floor1.7", "floor1.8",
                        "floor1.9", "floor1.10", "floor1.11", "floor1.12",
                        "floor1.13", "floor1.14", "floor1.15", "floor1.16",
                        "floor1.17", "floor1.18", "floor1.19", "floor1.20",
                        "floor1.21", "floor1.22", "floor1.23", "floor1.24",
                        "floor1.25", "floor1.26", "floor1.27", "floor1.28",
                        "floor1.29", "floor1.30", "floor1.31", "floor1.32",
                        "floor1.33", "floor1.34", "floor1.35", "floor1.36",
                        "floor1.37", "floor1.38",
                  ],
            bot3_tiles=[ 
                        "chasm1.1", "chasm1.2", "chasm1.3", "chasm1.4", "chasm1.5",
                        "chasm1.6", "chasm1.7", "chasm1.8", "chasm1.9", "chasm1.10",
                        "chasm1.11", "chasm1.12", "chasm1.13", "chasm1.14", "chasm1.15",
                        "chasm1.16", "chasm1.17", "chasm1.18", "chasm1.19",
                ])
    tp_init(name="floor2",
            tiles=[
                        "floor2.1", "floor2.2", "floor2.3", "floor2.4",
                        "floor2.5", "floor2.6", "floor2.7", "floor2.8",
                        "floor2.9", "floor2.10", "floor2.11", "floor2.12",
                        "floor2.13", "floor2.14", "floor2.15", "floor2.16",
                        "floor2.17", "floor2.18", "floor2.19", "floor2.20",
                        "floor2.21", "floor2.22", "floor2.23", "floor2.24",
                        "floor2.25", "floor2.26", "floor2.27", "floor2.28",
                        "floor2.29", "floor2.30", "floor2.31", "floor2.32",
                        "floor2.33", "floor2.34", "floor2.35", "floor2.36",
                        "floor2.37", "floor2.38",
                  ],
            bot3_tiles=[ 
                        "chasm1.1", "chasm1.2", "chasm1.3", "chasm1.4", "chasm1.5",
                        "chasm1.6", "chasm1.7", "chasm1.8", "chasm1.9", "chasm1.10",
                        "chasm1.11", "chasm1.12", "chasm1.13", "chasm1.14", "chasm1.15",
                        "chasm1.16", "chasm1.17", "chasm1.18", "chasm1.19",
                ])
    tp_init(name="floor3",
            tiles=[
                        "floor3.1", "floor3.2", "floor3.3", "floor3.4",
                        "floor3.5", "floor3.6", "floor3.7", "floor3.8",
                        "floor3.9", "floor3.10", "floor3.11", "floor3.12",
                        "floor3.13", "floor3.14", "floor3.15", "floor3.16",
                        "floor3.17", "floor3.18", "floor3.19", "floor3.20",
                        "floor3.21", "floor3.22", "floor3.23", "floor3.24",
                        "floor3.25", "floor3.26", "floor3.27", "floor3.28",
                        "floor3.29", "floor3.30", "floor3.31", "floor3.32",
                        "floor3.33", "floor3.34", "floor3.35", "floor3.36",
                        "floor3.37", "floor3.38",
                  ],
            bot3_tiles=[ 
                        "chasm1.1", "chasm1.2", "chasm1.3", "chasm1.4", "chasm1.5",
                        "chasm1.6", "chasm1.7", "chasm1.8", "chasm1.9", "chasm1.10",
                        "chasm1.11", "chasm1.12", "chasm1.13", "chasm1.14", "chasm1.15",
                        "chasm1.16", "chasm1.17", "chasm1.18", "chasm1.19",
                ])
    tp_init(name="floor4",
            tiles=[
                        "floor4.1", "floor4.2", "floor4.3", "floor4.4",
                        "floor4.5", "floor4.6", "floor4.7", "floor4.8",
                        "floor4.9", "floor4.10", "floor4.11", "floor4.12",
                        "floor4.13", "floor4.14", "floor4.15", "floor4.16",
                        "floor4.17", "floor4.18", "floor4.19", "floor4.20",
                        "floor4.21", "floor4.22", "floor4.23", "floor4.24",
                        "floor4.25", "floor4.26", "floor4.27", "floor4.28",
                        "floor4.29", "floor4.30", "floor4.31", "floor4.32",
                        "floor4.33", "floor4.34", "floor4.35", "floor4.36",
                        "floor4.37", "floor4.38",
                  ],
            bot3_tiles=[ 
                        "chasm1.1", "chasm1.2", "chasm1.3", "chasm1.4", "chasm1.5",
                        "chasm1.6", "chasm1.7", "chasm1.8", "chasm1.9", "chasm1.10",
                        "chasm1.11", "chasm1.12", "chasm1.13", "chasm1.14", "chasm1.15",
                        "chasm1.16", "chasm1.17", "chasm1.18", "chasm1.19",
                ])
    tp_init(name="floor5",
            tiles=[
                        "floor5.1", "floor5.2", "floor5.3", "floor5.4",
                        "floor5.5", "floor5.6", "floor5.7", "floor5.8",
                        "floor5.9", "floor5.10", "floor5.11", "floor5.12",
                        "floor5.13", "floor5.14", "floor5.15", "floor5.16",
                        "floor5.17", "floor5.18", "floor5.19", "floor5.20",
                        "floor5.21", "floor5.22", "floor5.23", "floor5.24",
                        "floor5.25", "floor5.26", "floor5.27", "floor5.28",
                        "floor5.29", "floor5.30", "floor5.31", "floor5.32",
                        "floor5.33", "floor5.34", "floor5.35", "floor5.36",
                        "floor5.37", "floor5.38",
                  ],
            bot3_tiles=[ 
                        "chasm1.1", "chasm1.2", "chasm1.3", "chasm1.4", "chasm1.5",
                        "chasm1.6", "chasm1.7", "chasm1.8", "chasm1.9", "chasm1.10",
                        "chasm1.11", "chasm1.12", "chasm1.13", "chasm1.14", "chasm1.15",
                        "chasm1.16", "chasm1.17", "chasm1.18", "chasm1.19",
                ])
init()
