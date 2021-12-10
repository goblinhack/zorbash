import my
import tp


def tp_init(name, tiles=[], left1_tiles=[], bot3_tiles=[]):
    mytp = tp.Tp(name)
    mytp.set_gfx_shown_in_bg(True)
    mytp.set_is_cursor_can_hover_over(True)
    mytp.set_is_floor(True)
    mytp.set_text_a_or_an("the")
    mytp.set_text_description("The unwashed dungeon foundation.")
    mytp.set_z_depth(my.MAP_DEPTH_FLOOR)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    for t in tiles:
        mytp.set_tile(t)

    if bot3_tiles is not None:
        for t in bot3_tiles:
            mytp.set_bot3_tile(t)
    else:
        mytp.set_bot3_tile(bot3_tile=name)

    mytp.update()


def init():
    tp_init(
        name="wall_floor1",
        tiles=[
            "floor1.1",
            "floor1.2",
            "floor1.3",
            "floor1.4",
            "floor1.5",
            "floor1.6",
            "floor1.7",
            "floor1.8",
            "floor1.9",
            "floor1.10",
            "floor1.11",
            "floor1.12",
            "floor1.13",
            "floor1.14",
            "floor1.15",
            "floor1.16",
            "floor1.17",
            "floor1.18",
            "floor1.19",
        ],
        bot3_tiles=[
            "chasm2.1",
            "chasm2.2",
            "chasm2.3",
            "chasm2.4",
            "chasm2.5",
            "chasm2.6",
            "chasm2.7",
            "chasm2.8",
            "chasm2.9",
            "chasm2.10",
            "chasm2.11",
            "chasm2.12",
            "chasm2.13",
            "chasm2.14",
            "chasm2.15",
            "chasm2.16",
            "chasm2.17",
            "chasm2.18",
            "chasm2.19",
        ],
    )


init()
