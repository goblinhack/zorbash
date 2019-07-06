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
    x.set_is_gravel(True)
    x.set_z_depth(zx.MAP_DEPTH_GRAVEL)

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
    tp_init(name="gravel1",
            tiles=[
                        "gravel1.1",
                        "gravel1.2",
                        "gravel1.3",
                        "gravel1.4",
                        "gravel1.5",
                        "gravel1.6",
                        "gravel1.7",
                        "gravel1.8",
                        "gravel1.9",
                        "gravel1.10",
                        "gravel1.11",
                        "gravel1.12",
                        "gravel1.13",
                        "gravel1.14",
                        "gravel1.15",
                        "gravel1.16",
                        "gravel1.17",
                        "gravel1.18",
                        "gravel1.19",
                        "gravel1.20",
                        "gravel1.21",
                ],
            left_tiles=[
                        "gravel1.left.1",
                        "gravel2.left.1",
                        "gravel3.left.1",
                        "gravel4.left.1",
                ],
            right_tiles=[
                        "gravel1.right.1",
                        "gravel2.right.1",
                        "gravel3.right.1",
                        "gravel4.right.1",
                ],
            top_tiles=[
                        "gravel1.top.1",
                        "gravel2.top.1",
                        "gravel3.top.1",
                        "gravel4.top.1",
                ],
            bot_tiles=[
                        "gravel1.bot.1",
                        "gravel2.bot.1",
                        "gravel3.bot.1",
                        "gravel4.bot.1",
                ],
            tl_tiles=[ 
                        "gravel1.tl.1",
                        "gravel2.tl.1",
                        "gravel3.tl.1",
                        "gravel4.tl.1",
                ],
            tr_tiles=[
                        "gravel1.tr.1",
                        "gravel2.tr.1",
                        "gravel3.tr.1",
                        "gravel4.tr.1",
                ],
            br_tiles=[
                        "gravel1.br.1",
                        "gravel2.br.1",
                        "gravel3.br.1",
                        "gravel4.br.1",
                ],
            bl_tiles=[
                        "gravel1.bl.1",
                        "gravel2.bl.1",
                        "gravel3.bl.1",
                        "gravel4.bl.1",
                ])

    tp_init(name="gravel2",
            tiles=[
                        "gravel2.1",
                        "gravel2.2",
                        "gravel2.3",
                        "gravel2.4",
                        "gravel2.5",
                        "gravel2.6",
                        "gravel2.7",
                        "gravel2.8",
                        "gravel2.9",
                        "gravel2.10",
                        "gravel2.11",
                        "gravel2.12",
                        "gravel2.13",
                        "gravel2.14",
                        "gravel2.15",
                        "gravel2.16",
                        "gravel2.17",
                        "gravel2.18",
                        "gravel2.19",
                        "gravel2.20",
                        "gravel2.21",
                ],
            left_tiles=[
                        "gravel1.left.1",
                        "gravel2.left.1",
                        "gravel3.left.1",
                        "gravel4.left.1",
                ],
            right_tiles=[
                        "gravel1.right.1",
                        "gravel2.right.1",
                        "gravel3.right.1",
                        "gravel4.right.1",
                ],
            top_tiles=[
                        "gravel1.top.1",
                        "gravel2.top.1",
                        "gravel3.top.1",
                        "gravel4.top.1",
                ],
            bot_tiles=[
                        "gravel1.bot.1",
                        "gravel2.bot.1",
                        "gravel3.bot.1",
                        "gravel4.bot.1",
                ],
            tl_tiles=[ 
                        "gravel1.tl.1",
                        "gravel2.tl.1",
                        "gravel3.tl.1",
                        "gravel4.tl.1",
                ],
            tr_tiles=[
                        "gravel1.tr.1",
                        "gravel2.tr.1",
                        "gravel3.tr.1",
                        "gravel4.tr.1",
                ],
            br_tiles=[
                        "gravel1.br.1",
                        "gravel2.br.1",
                        "gravel3.br.1",
                        "gravel4.br.1",
                ],
            bl_tiles=[
                        "gravel1.bl.1",
                        "gravel2.bl.1",
                        "gravel3.bl.1",
                        "gravel4.bl.1",
                ])

    tp_init(name="gravel3",
            tiles=[
                        "gravel3.1",
                        "gravel3.2",
                        "gravel3.3",
                        "gravel3.4",
                        "gravel3.5",
                        "gravel3.6",
                        "gravel3.7",
                        "gravel3.8",
                        "gravel3.9",
                        "gravel3.10",
                        "gravel3.11",
                        "gravel3.12",
                        "gravel3.13",
                        "gravel3.14",
                        "gravel3.15",
                        "gravel3.16",
                        "gravel3.17",
                        "gravel3.18",
                        "gravel3.19",
                        "gravel3.20",
                        "gravel3.21",
                        "gravel3.22",
                ],
            left_tiles=[
                        "gravel1.left.1",
                        "gravel2.left.1",
                        "gravel3.left.1",
                        "gravel4.left.1",
                ],
            right_tiles=[
                        "gravel1.right.1",
                        "gravel2.right.1",
                        "gravel3.right.1",
                        "gravel4.right.1",
                ],
            top_tiles=[
                        "gravel1.top.1",
                        "gravel2.top.1",
                        "gravel3.top.1",
                        "gravel4.top.1",
                ],
            bot_tiles=[
                        "gravel1.bot.1",
                        "gravel2.bot.1",
                        "gravel3.bot.1",
                        "gravel4.bot.1",
                ],
            tl_tiles=[ 
                        "gravel1.tl.1",
                        "gravel2.tl.1",
                        "gravel3.tl.1",
                        "gravel4.tl.1",
                ],
            tr_tiles=[
                        "gravel1.tr.1",
                        "gravel2.tr.1",
                        "gravel3.tr.1",
                        "gravel4.tr.1",
                ],
            br_tiles=[
                        "gravel1.br.1",
                        "gravel2.br.1",
                        "gravel3.br.1",
                        "gravel4.br.1",
                ],
            bl_tiles=[
                        "gravel1.bl.1",
                        "gravel2.bl.1",
                        "gravel3.bl.1",
                        "gravel4.bl.1",
                ])

init()
