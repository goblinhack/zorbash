import zx
import tp


#
# NOTE: chasm tiles are not blitted explicitly. Instead a floor tile
# will check for the presence of a chasm beneath it and blit the chasm
#
def tp_init(name, tiles=[], left1_tiles=[], bot3_tiles=[]):
    mytp = tp.Tp(name)
    mytp.set_is_cursor_can_hover_over(True)
    mytp.set_is_dirt(True)
    mytp.set_is_loggable_for_important_stuff(False)
    mytp.set_is_loggable_for_unimportant_stuff(False)
    mytp.set_text_a_or_an("the")
    mytp.set_text_description("Some dirt, what more can I say?")
    mytp.set_z_depth(zx.MAP_DEPTH_FLOOR)
    mytp.set_z_prio(zx.MAP_PRIO_NORMAL)

    for t in tiles:
        mytp.set_tile(t)

    if bot3_tiles is not None:
        for t in bot3_tiles:
            mytp.set_bot3_tile(t)
    else:
        mytp.set_bot3_tile(bot3_tile=name)

    mytp.update()

def init():
    tp_init(name="dirt1",
            tiles=[
                        "dirt1.1", "dirt1.2", "dirt1.3", "dirt1.4",
                        "dirt1.5", "dirt1.6", "dirt1.7", "dirt1.8",
                        "dirt1.9", "dirt1.10", "dirt1.11", "dirt1.12",
                        "dirt1.13", "dirt1.14", "dirt1.15", "dirt1.16",
                        "dirt1.17", "dirt1.18", "dirt1.19",
                ],
            bot3_tiles=[ 
                        "chasm1.1", "chasm1.2", "chasm1.3", "chasm1.4", "chasm1.5",
                        "chasm1.6", "chasm1.7", "chasm1.8", "chasm1.9", "chasm1.10",
                        "chasm1.11", "chasm1.12", "chasm1.13", "chasm1.14", "chasm1.15",
                        "chasm1.16", "chasm1.17", "chasm1.18", "chasm1.19",
                ])
    tp_init(name="dirt2",
            tiles=[
                        "dirt2.1", "dirt2.2", "dirt2.3", "dirt2.4",
                        "dirt2.5", "dirt2.6", "dirt2.7", "dirt2.8",
                        "dirt2.9", "dirt2.10", "dirt2.11", "dirt2.12",
                        "dirt2.13", "dirt2.14", "dirt2.15", "dirt2.16",
                        "dirt2.17", "dirt2.18", "dirt2.19",
                ],
            bot3_tiles=[ 
                        "chasm1.1", "chasm1.2", "chasm1.3", "chasm1.4", "chasm1.5",
                        "chasm1.6", "chasm1.7", "chasm1.8", "chasm1.9", "chasm1.10",
                        "chasm1.11", "chasm1.12", "chasm1.13", "chasm1.14", "chasm1.15",
                        "chasm1.16", "chasm1.17", "chasm1.18", "chasm1.19",
                ])
    tp_init(name="dirt3",
            tiles=[
                        "dirt3.1", "dirt3.2", "dirt3.3", "dirt3.4",
                        "dirt3.5", "dirt3.6", "dirt3.7", "dirt3.8",
                        "dirt3.9", "dirt3.10", "dirt3.11", "dirt3.12",
                        "dirt3.13", "dirt3.14", "dirt3.15", "dirt3.16",
                        "dirt3.17", "dirt3.18", "dirt3.19",
                ],
            bot3_tiles=[ 
                        "chasm1.1", "chasm1.2", "chasm1.3", "chasm1.4", "chasm1.5",
                        "chasm1.6", "chasm1.7", "chasm1.8", "chasm1.9", "chasm1.10",
                        "chasm1.11", "chasm1.12", "chasm1.13", "chasm1.14", "chasm1.15",
                        "chasm1.16", "chasm1.17", "chasm1.18", "chasm1.19",
                ])
init()
