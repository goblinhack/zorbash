import zx
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
              br_tiles=[]):
    
    x = tp.Tp(name)

    x.set_is_boring(True)
    x.set_is_movement_blocking(True)
    x.set_is_shadow_caster(True)
    x.set_is_wall(True)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_WALLS)

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

def init():
    wall_init(name="wall1", short_name="A boring wall", 
            tiles=[
                        "wall1.1",
                        "wall1.2",
                        "wall1.3",
                        "wall1.4",
                        "wall1.5",
                        "wall1.6",
                        "wall1.7",
                        "wall1.8",
                        "wall1.9",
                        "wall1.10",
                        "wall1.11",
                        "wall1.12",
                        "wall1.13",
                        "wall1.14",
                        "wall1.15",
                        "wall1.16",
                ],
            left_tiles=[
                        "deco1.left.1",
                        "deco1.left.2",
                        "deco1.left.3",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                ],
            right_tiles=[
                        "deco1.right.1",
                        "deco1.right.2",
                        "deco1.right.3",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                ],
            top_tiles=[
                        "deco1.top.1",
                        "deco1.top.2",
                        "deco1.top.3",
                        "deco1.top.4",
                        "deco1.top.5",
                        "deco1.top.6",
                        "deco1.top.7",
                        "deco1.top.8",
                        "deco1.top.9",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                ],
            bot_tiles=[
                        "deco1.bot.1",
                        "deco1.bot.2",
                        "deco1.bot.3",
                        "deco1.bot.4",
                        "deco1.bot.5",
                        "deco1.bot.6",
                        "deco1.bot.7",
                        "deco1.bot.8",
                        "deco1.bot.9",
                        "deco1.bot.10",
                        "deco1.bot.11",
                        "deco1.bot.12",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                        "",
                ],
            tl_tiles=[ 
                        "deco1.tl.1",
                        "",
                        "",
                        "",
                        "",
                ],
            tr_tiles=[
                        "deco1.tr.1",
                        "",
                        "",
                        "",
                        "",
                ],
            br_tiles=[
                        "deco1.br.1",
                        "",
                        "",
                        "",
                        "",
                ],
            bl_tiles=[
                        "deco1.bl.1",
                        "",
                        "",
                        "",
                        "",
                ])
init()
