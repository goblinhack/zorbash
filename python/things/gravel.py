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
    x.set_is_soil(True)
    x.set_z_depth(zx.MAP_DEPTH_SOIL)

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
    tp_init(name="soil1",
            tiles=[
                        "soil1.1",
                        "soil1.2",
                        "soil1.3",
                        "soil1.4",
                        "soil1.5",
                        "soil1.6",
                        "soil1.7",
                        "soil1.8",
                        "soil1.9",
                        "soil1.10",
                        "soil1.11",
                        "soil1.12",
                        "soil1.13",
                        "soil1.14",
                        "soil1.15",
                        "soil1.16",
                        "soil1.17",
                        "soil1.18",
                        "soil1.19",
                        "soil1.20",
                        "soil1.21",
                ],
            left_tiles=[
                        "soil1.left.1",
                        "soil2.left.1",
                        "soil3.left.1",
                        "soil4.left.1",
                ],
            right_tiles=[
                        "soil1.right.1",
                        "soil2.right.1",
                        "soil3.right.1",
                        "soil4.right.1",
                ],
            top_tiles=[
                        "soil1.top.1",
                        "soil2.top.1",
                        "soil3.top.1",
                        "soil4.top.1",
                ],
            bot_tiles=[
                        "soil1.bot.1",
                        "soil2.bot.1",
                        "soil3.bot.1",
                        "soil4.bot.1",
                ],
            tl_tiles=[ 
                        "soil1.tl.1",
                        "soil2.tl.1",
                        "soil3.tl.1",
                        "soil4.tl.1",
                ],
            tr_tiles=[
                        "soil1.tr.1",
                        "soil2.tr.1",
                        "soil3.tr.1",
                        "soil4.tr.1",
                ],
            br_tiles=[
                        "soil1.br.1",
                        "soil2.br.1",
                        "soil3.br.1",
                        "soil4.br.1",
                ],
            bl_tiles=[
                        "soil1.bl.1",
                        "soil2.bl.1",
                        "soil3.bl.1",
                        "soil4.bl.1",
                ])

    tp_init(name="soil2",
            tiles=[
                        "soil2.1",
                        "soil2.2",
                        "soil2.3",
                        "soil2.4",
                        "soil2.5",
                        "soil2.6",
                        "soil2.7",
                        "soil2.8",
                        "soil2.9",
                        "soil2.10",
                        "soil2.11",
                        "soil2.12",
                        "soil2.13",
                        "soil2.14",
                        "soil2.15",
                        "soil2.16",
                        "soil2.17",
                        "soil2.18",
                        "soil2.19",
                        "soil2.20",
                        "soil2.21",
                ],
            left_tiles=[
                        "soil1.left.1",
                        "soil2.left.1",
                        "soil3.left.1",
                        "soil4.left.1",
                ],
            right_tiles=[
                        "soil1.right.1",
                        "soil2.right.1",
                        "soil3.right.1",
                        "soil4.right.1",
                ],
            top_tiles=[
                        "soil1.top.1",
                        "soil2.top.1",
                        "soil3.top.1",
                        "soil4.top.1",
                ],
            bot_tiles=[
                        "soil1.bot.1",
                        "soil2.bot.1",
                        "soil3.bot.1",
                        "soil4.bot.1",
                ],
            tl_tiles=[ 
                        "soil1.tl.1",
                        "soil2.tl.1",
                        "soil3.tl.1",
                        "soil4.tl.1",
                ],
            tr_tiles=[
                        "soil1.tr.1",
                        "soil2.tr.1",
                        "soil3.tr.1",
                        "soil4.tr.1",
                ],
            br_tiles=[
                        "soil1.br.1",
                        "soil2.br.1",
                        "soil3.br.1",
                        "soil4.br.1",
                ],
            bl_tiles=[
                        "soil1.bl.1",
                        "soil2.bl.1",
                        "soil3.bl.1",
                        "soil4.bl.1",
                ])

    tp_init(name="soil3",
            tiles=[
                        "soil3.1",
                        "soil3.2",
                        "soil3.3",
                        "soil3.4",
                        "soil3.5",
                        "soil3.6",
                        "soil3.7",
                        "soil3.8",
                        "soil3.9",
                        "soil3.10",
                        "soil3.11",
                        "soil3.12",
                        "soil3.13",
                        "soil3.14",
                        "soil3.15",
                        "soil3.16",
                        "soil3.17",
                        "soil3.18",
                        "soil3.19",
                        "soil3.20",
                        "soil3.21",
                        "soil3.22",
                ],
            left_tiles=[
                        "soil1.left.1",
                        "soil2.left.1",
                        "soil3.left.1",
                        "soil4.left.1",
                ],
            right_tiles=[
                        "soil1.right.1",
                        "soil2.right.1",
                        "soil3.right.1",
                        "soil4.right.1",
                ],
            top_tiles=[
                        "soil1.top.1",
                        "soil2.top.1",
                        "soil3.top.1",
                        "soil4.top.1",
                ],
            bot_tiles=[
                        "soil1.bot.1",
                        "soil2.bot.1",
                        "soil3.bot.1",
                        "soil4.bot.1",
                ],
            tl_tiles=[ 
                        "soil1.tl.1",
                        "soil2.tl.1",
                        "soil3.tl.1",
                        "soil4.tl.1",
                ],
            tr_tiles=[
                        "soil1.tr.1",
                        "soil2.tr.1",
                        "soil3.tr.1",
                        "soil4.tr.1",
                ],
            br_tiles=[
                        "soil1.br.1",
                        "soil2.br.1",
                        "soil3.br.1",
                        "soil4.br.1",
                ],
            bl_tiles=[
                        "soil1.bl.1",
                        "soil2.bl.1",
                        "soil3.bl.1",
                        "soil4.bl.1",
                ])

init()
