import zx
import tp


def tp_init(name, 
            tiles=[],
            left_tiles=[],
            right_tiles=[],
            top_tiles=[],
            bot_tiles=[],
            tl_tiles=[],
            tr_tiles=[],
            bl_tiles=[],
            br_tiles=[]):
    
    x = tp.Tp(name)

    x.set_does_nothing(True)
    x.set_is_grass(True)
    x.set_z_depth(zx.MAP_DEPTH_GRASS)

    if tiles is not None:
        for t in tiles:
            x.set_tile(t)
    else:
        x.set_tile(tile=name)

    if left_tiles is not None:
        for t in left_tiles:
            x.set_left_tile(t)
    else:
        x.set_left_tile(left_tile=name)

    if right_tiles is not None:
        for t in right_tiles:
            x.set_right_tile(t)
    else:
        x.set_right_tile(right_tile=name)

    if top_tiles is not None:
        for t in top_tiles:
            x.set_top_tile(t)
    else:
        x.set_top_tile(top_tile=name)

    if bot_tiles is not None:
        for t in bot_tiles:
            x.set_bot_tile(t)
    else:
        x.set_bot_tile(bot_tile=name)

    if tl_tiles is not None:
        for t in tl_tiles:
            x.set_tl_tile(t)
    else:
        x.set_tl_tile(tl_tile=name)

    if tr_tiles is not None:
        for t in tr_tiles:
            x.set_tr_tile(t)
    else:
        x.set_tr_tile(tr_tile=name)

    if bl_tiles is not None:
        for t in bl_tiles:
            x.set_bl_tile(t)
    else:
        x.set_bl_tile(bl_tile=name)

    if br_tiles is not None:
        for t in br_tiles:
            x.set_br_tile(t)
    else:
        x.set_br_tile(br_tile=name)

    x.update()
    
def init():
    tp_init(name="grass1",
            tiles=[
                        "grass1.1",
                        "grass1.2",
                        "grass1.3",
                        "grass1.4",
                        "grass1.5",
                        "grass1.6",
                        "grass1.7",
                        "grass1.8",
                        "grass1.9",
                        "grass1.10",
                        "grass1.11",
                        "grass1.12",
                        "grass1.13",
                        "grass1.14",
                        "grass1.15",
                        "grass1.16",
                        "grass1.17",
                        "grass1.18",
                        "grass1.19",
                        "grass1.20",
                        "grass1.21",
                ],
            left_tiles=[
                        "grass1.left.1",
                        "grass2.left.1",
                        "grass3.left.1",
                        "grass4.left.1",
                ],
            right_tiles=[
                        "grass1.right.1",
                        "grass2.right.1",
                        "grass3.right.1",
                        "grass4.right.1",
                ],
            top_tiles=[
                        "grass1.top.1",
                        "grass2.top.1",
                        "grass3.top.1",
                        "grass4.top.1",
                ],
            bot_tiles=[
                        "grass1.bot.1",
                        "grass2.bot.1",
                        "grass3.bot.1",
                        "grass4.bot.1",
                ],
            tl_tiles=[ 
                        "grass1.tl.1",
                        "grass2.tl.1",
                        "grass3.tl.1",
                        "grass4.tl.1",
                ],
            tr_tiles=[
                        "grass1.tr.1",
                        "grass2.tr.1",
                        "grass3.tr.1",
                        "grass4.tr.1",
                ],
            br_tiles=[
                        "grass1.br.1",
                        "grass2.br.1",
                        "grass3.br.1",
                        "grass4.br.1",
                ],
            bl_tiles=[
                        "grass1.bl.1",
                        "grass2.bl.1",
                        "grass3.bl.1",
                        "grass4.bl.1",
                ])

    tp_init(name="grass2",
            tiles=[
                        "grass2.1",
                        "grass2.2",
                        "grass2.3",
                        "grass2.4",
                        "grass2.5",
                        "grass2.6",
                        "grass2.7",
                        "grass2.8",
                        "grass2.9",
                        "grass2.10",
                        "grass2.11",
                        "grass2.12",
                        "grass2.13",
                        "grass2.14",
                        "grass2.15",
                        "grass2.16",
                        "grass2.17",
                        "grass2.18",
                        "grass2.19",
                        "grass2.20",
                        "grass2.21",
                ],
            left_tiles=[
                        "grass1.left.1",
                        "grass2.left.1",
                        "grass3.left.1",
                        "grass4.left.1",
                ],
            right_tiles=[
                        "grass1.right.1",
                        "grass2.right.1",
                        "grass3.right.1",
                        "grass4.right.1",
                ],
            top_tiles=[
                        "grass1.top.1",
                        "grass2.top.1",
                        "grass3.top.1",
                        "grass4.top.1",
                ],
            bot_tiles=[
                        "grass1.bot.1",
                        "grass2.bot.1",
                        "grass3.bot.1",
                        "grass4.bot.1",
                ],
            tl_tiles=[ 
                        "grass1.tl.1",
                        "grass2.tl.1",
                        "grass3.tl.1",
                        "grass4.tl.1",
                ],
            tr_tiles=[
                        "grass1.tr.1",
                        "grass2.tr.1",
                        "grass3.tr.1",
                        "grass4.tr.1",
                ],
            br_tiles=[
                        "grass1.br.1",
                        "grass2.br.1",
                        "grass3.br.1",
                        "grass4.br.1",
                ],
            bl_tiles=[
                        "grass1.bl.1",
                        "grass2.bl.1",
                        "grass3.bl.1",
                        "grass4.bl.1",
                ])

    tp_init(name="grass3",
            tiles=[
                        "grass3.1",
                        "grass3.2",
                        "grass3.3",
                        "grass3.4",
                        "grass3.5",
                        "grass3.6",
                        "grass3.7",
                        "grass3.8",
                        "grass3.9",
                        "grass3.10",
                        "grass3.11",
                        "grass3.12",
                        "grass3.13",
                        "grass3.14",
                        "grass3.15",
                        "grass3.16",
                        "grass3.17",
                        "grass3.18",
                        "grass3.19",
                        "grass3.20",
                        "grass3.21",
                        "grass3.22",
                ],
            left_tiles=[
                        "grass1.left.1",
                        "grass2.left.1",
                        "grass3.left.1",
                        "grass4.left.1",
                ],
            right_tiles=[
                        "grass1.right.1",
                        "grass2.right.1",
                        "grass3.right.1",
                        "grass4.right.1",
                ],
            top_tiles=[
                        "grass1.top.1",
                        "grass2.top.1",
                        "grass3.top.1",
                        "grass4.top.1",
                ],
            bot_tiles=[
                        "grass1.bot.1",
                        "grass2.bot.1",
                        "grass3.bot.1",
                        "grass4.bot.1",
                ],
            tl_tiles=[ 
                        "grass1.tl.1",
                        "grass2.tl.1",
                        "grass3.tl.1",
                        "grass4.tl.1",
                ],
            tr_tiles=[
                        "grass1.tr.1",
                        "grass2.tr.1",
                        "grass3.tr.1",
                        "grass4.tr.1",
                ],
            br_tiles=[
                        "grass1.br.1",
                        "grass2.br.1",
                        "grass3.br.1",
                        "grass4.br.1",
                ],
            bl_tiles=[
                        "grass1.bl.1",
                        "grass2.bl.1",
                        "grass3.bl.1",
                        "grass4.bl.1",
                ])

init()
