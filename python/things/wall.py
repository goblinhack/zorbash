import tp


def wall_init(name, short_name, 
              tiles=[],
              left_tiles=[],
              right_tiles=[],
              top_tiles=[],
              bot_tiles=[],
              tl_tiles=[],
              tr_tiles=[],
              bl_tiles=[],
              br_tiles=[],
              block_1x2_tiles=[],
              block_2x1_tiles=[],
              block_2x2_tiles=[],
              block_3x3_tiles=[],
              block_6x3_tiles=[],
              block_3x6_tiles=[],
              block_6x6_tiles=[]):
    
    x = tp.Tp(name, is_wall = True)

    x.set_short_name(short_name)
    x.set_is_movement_blocking(True)
    x.set_is_wall(True)

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

    if block_1x2_tiles is not None:
        for t in block_1x2_tiles:
            x.set_block_1x2_tile(t)
    else:
        x.set_block_1x2_tile(block_1x2_tile=name)

    if block_2x1_tiles is not None:
        for t in block_2x1_tiles:
            x.set_block_2x1_tile(t)
    else:
        x.set_block_2x1_tile(block_2x1_tile=name)

    if block_2x2_tiles is not None:
        for t in block_2x2_tiles:
            x.set_block_2x2_tile(t)
    else:
        x.set_block_2x2_tile(block_2x2_tile=name)

    if block_3x3_tiles is not None:
        for t in block_3x3_tiles:
            x.set_block_3x3_tile(t)
    else:
        x.set_block_3x3_tile(block_3x3_tile=name)

    if block_6x3_tiles is not None:
        for t in block_6x3_tiles:
            x.set_block_6x3_tile(t)
    else:
        x.set_block_6x3_tile(block_6x3_tile=name)

    if block_6x3_tiles is not None:
        for t in block_6x3_tiles:
            x.set_block_6x3_tile(t)
    else:
        x.set_block_6x3_tile(block_6x3_tile=name)

    if block_3x6_tiles is not None:
        for t in block_3x6_tiles:
            x.set_block_3x6_tile(t)
    else:
        x.set_block_3x6_tile(block_3x6_tile=name)

    if block_6x6_tiles is not None:
        for t in block_6x6_tiles:
            x.set_block_6x6_tile(t)
    else:
        x.set_block_6x6_tile(block_6x6_tile=name)

def init():
    wall_init(name="wall1", short_name="A boring wall", 
            tiles=[
                        "wall1.1",
                        "wall1.2",
                        "wall1.3",
                        "wall1.4",
                        "wall1.5",
                        "wall1.6",
                ],
            block_1x2_tiles=[
                        "wall1.1x2.1", "wall1.1x2.2",
                ],
            block_2x1_tiles=[
                        "wall1.2x1.1", "wall1.2x1.2",
                ],
            block_2x2_tiles=[
                        "wall1.2x2.1", "wall1.2x2.2",
                        "wall1.2x2.3", "wall1.2x2.4",
                ],
            block_3x3_tiles=[
                        "wall1.3x3.1", "wall1.3x3.2", "wall1.3x3.3", 
                        "wall1.3x3.4", "wall1.3x3.5", "wall1.3x3.6",
                        "wall1.3x3.7", "wall1.3x3.8", "wall1.3x3.9",
                ],
            block_3x6_tiles=[
                        "wall1.3x6.1",  "wall1.3x6.2",  "wall1.3x6.3", 
                        "wall1.3x6.4",  "wall1.3x6.5",  "wall1.3x6.6",
                        "wall1.3x6.7",  "wall1.3x6.8",  "wall1.3x6.9",
                        "wall1.3x6.10", "wall1.3x6.11", "wall1.3x6.12",
                        "wall1.3x6.13", "wall1.3x6.14", "wall1.3x6.15",
                        "wall1.3x6.16", "wall1.3x6.17", "wall1.3x6.18",
                ],
            block_6x3_tiles=[
                        "wall1.6x3.1",  "wall1.6x3.2",  "wall1.6x3.3", 
                        "wall1.6x3.4",  "wall1.6x3.5",  "wall1.6x3.6",
                        "wall1.6x3.7",  "wall1.6x3.8",  "wall1.6x3.9",
                        "wall1.6x3.10", "wall1.6x3.11", "wall1.6x3.12",
                        "wall1.6x3.13", "wall1.6x3.14", "wall1.6x3.15",
                        "wall1.6x3.16", "wall1.6x3.17", "wall1.6x3.18",
                ],
            block_6x6_tiles=[
                        "wall1.6x6.1",  "wall1.6x6.2",  "wall1.6x6.3", 
                        "wall1.6x6.4",  "wall1.6x6.5",  "wall1.6x6.6",
                        "wall1.6x6.7",  "wall1.6x6.8",  "wall1.6x6.9",
                        "wall1.6x6.10", "wall1.6x6.11", "wall1.6x6.12",
                        "wall1.6x6.13", "wall1.6x6.14", "wall1.6x6.15",
                        "wall1.6x6.16", "wall1.6x6.17", "wall1.6x6.18",
                        "wall1.6x6.19", "wall1.6x6.20", "wall1.6x6.21",
                        "wall1.6x6.22", "wall1.6x6.23", "wall1.6x6.24",
                        "wall1.6x6.25", "wall1.6x6.26", "wall1.6x6.27",
                        "wall1.6x6.28", "wall1.6x6.29", "wall1.6x6.30",
                        "wall1.6x6.31", "wall1.6x6.32", "wall1.6x6.33",
                        "wall1.6x6.34", "wall1.6x6.35", "wall1.6x6.36",
                ],
            left_tiles=[
                        "deco1.left.1",
                        "deco1.left.2",
                        "deco1.left.3",
                ],
            right_tiles=[
                        "deco1.right.1",
                        "deco1.right.2",
                        "deco1.right.3",
                ],
            top_tiles=[
                        "deco1.top.1",
                        "deco1.top.2",
                        "deco1.top.3",
                ],
            bot_tiles=[
                        "deco1.bot.1",
                        "deco1.bot.2",
                        "deco1.bot.3",
                ],
            tl_tiles=[ 
                        "deco1.tl.1",
                ],
            tr_tiles=[
                        "deco1.tr.1",
                ],
            br_tiles=[
                        "deco1.br.1",
                ],
            bl_tiles=[
                        "deco1.bl.1",
                ])
init()
