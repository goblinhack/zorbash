import zx
import tp


def tp_init(name, tiles=[], left1_tiles=[], bot3_tiles=[]):
    x = tp.Tp(name)

    x.set_is_cursor_can_hover_over(True)
    x.set_is_floor(True)
    x.set_is_interesting(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_is_loggable_for_important_stuff(False)
    x.set_text_a_or_an("the");
    x.set_z_prio(zx.MAP_PRIO_NORMAL)
    x.set_text_description("The unwashed dungeon floor")
    x.set_z_depth(zx.MAP_DEPTH_FLOOR)

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
                        "floor1.17", "floor1.18", "floor1.19",
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
                        "floor2.17", "floor2.18", "floor2.19",
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
                        "floor3.17", "floor3.18", "floor3.19",
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
                        "floor4.17", "floor4.18", "floor4.19",
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
                        "floor5.17", "floor5.18", "floor5.19",
                  ],
            bot3_tiles=[ 
                        "chasm1.1", "chasm1.2", "chasm1.3", "chasm1.4", "chasm1.5",
                        "chasm1.6", "chasm1.7", "chasm1.8", "chasm1.9", "chasm1.10",
                        "chasm1.11", "chasm1.12", "chasm1.13", "chasm1.14", "chasm1.15",
                        "chasm1.16", "chasm1.17", "chasm1.18", "chasm1.19",
                ])
    tp_init(name="floor6",
            tiles=[
                        "floor6.1", "floor6.2", "floor6.3", "floor6.4",
                        "floor6.5", "floor6.6", "floor6.7", "floor6.8",
                        "floor6.9", "floor6.10", "floor6.11", "floor6.12",
                        "floor6.13", "floor6.14", "floor6.15", "floor6.16",
                        "floor6.17", "floor6.18", "floor6.19",
                  ],
            bot3_tiles=[ 
                        "chasm1.1", "chasm1.2", "chasm1.3", "chasm1.4", "chasm1.5",
                        "chasm1.6", "chasm1.7", "chasm1.8", "chasm1.9", "chasm1.10",
                        "chasm1.11", "chasm1.12", "chasm1.13", "chasm1.14", "chasm1.15",
                        "chasm1.16", "chasm1.17", "chasm1.18", "chasm1.19",
                ])
    tp_init(name="floor7",
            tiles=[
                        "floor7.1", "floor7.2", "floor7.3", "floor7.4",
                        "floor7.5", "floor7.6", "floor7.7", "floor7.8",
                        "floor7.9", "floor7.10", "floor7.11", "floor7.12",
                        "floor7.13", "floor7.14", "floor7.15", "floor7.16",
                        "floor7.17", "floor7.18", "floor7.19",
                  ],
            bot3_tiles=[ 
                        "chasm1.1", "chasm1.2", "chasm1.3", "chasm1.4", "chasm1.5",
                        "chasm1.6", "chasm1.7", "chasm1.8", "chasm1.9", "chasm1.10",
                        "chasm1.11", "chasm1.12", "chasm1.13", "chasm1.14", "chasm1.15",
                        "chasm1.16", "chasm1.17", "chasm1.18", "chasm1.19",
                ])
    tp_init(name="floor8",
            tiles=[
                        "floor8.1", "floor8.2", "floor8.3", "floor8.4",
                        "floor8.5", "floor8.6", "floor8.7", "floor8.8",
                        "floor8.9", "floor8.10", "floor8.11", "floor8.12",
                        "floor8.13", "floor8.14", "floor8.15", "floor8.16",
                        "floor8.17", "floor8.18", "floor8.19",
                  ],
            bot3_tiles=[ 
                        "chasm1.1", "chasm1.2", "chasm1.3", "chasm1.4", "chasm1.5",
                        "chasm1.6", "chasm1.7", "chasm1.8", "chasm1.9", "chasm1.10",
                        "chasm1.11", "chasm1.12", "chasm1.13", "chasm1.14", "chasm1.15",
                        "chasm1.16", "chasm1.17", "chasm1.18", "chasm1.19",
                ])
    tp_init(name="floor9",
            tiles=[
                        "floor9.1", "floor9.2", "floor9.3", "floor9.4",
                        "floor9.5", "floor9.6", "floor9.7", "floor9.8",
                        "floor9.9", "floor9.10", "floor9.11", "floor9.12",
                        "floor9.13", "floor9.14", "floor9.15", "floor9.16",
                        "floor9.17", "floor9.18", "floor9.19",
                  ],
            bot3_tiles=[ 
                        "chasm1.1", "chasm1.2", "chasm1.3", "chasm1.4", "chasm1.5",
                        "chasm1.6", "chasm1.7", "chasm1.8", "chasm1.9", "chasm1.10",
                        "chasm1.11", "chasm1.12", "chasm1.13", "chasm1.14", "chasm1.15",
                        "chasm1.16", "chasm1.17", "chasm1.18", "chasm1.19",
                ])
init()
