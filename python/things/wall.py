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

    x.set_collision_circle(True)
    x.set_collision_hit_priority(0)
    x.set_collision_radius(0.40)
    x.set_gfx_large_shadow(True)
    x.set_is_cursor_can_hover_over(True)
    x.set_is_interesting(False)
    x.set_is_loggable(False)
    x.set_is_movement_blocking(True)
    x.set_is_obstacle(True)
    x.set_is_wall(True)
    x.set_z_depth(zx.MAP_DEPTH_WALLS)

    if tiles is not None:
        for t in tiles:
            x.set_tile(t)
    else:
        x.set_tile(tile=name)

    if left_tiles is not None:
        for t in left_tiles:
            x.set_tile_left(t)
    else:
        x.set_tile_left(tile_left=name)

    if right_tiles is not None:
        for t in right_tiles:
            x.set_tile_right(t)
    else:
        x.set_tile_right(tile_right=name)

    if top_tiles is not None:
        for t in top_tiles:
            x.set_tile_top(t)
    else:
        x.set_tile_top(tile_top=name)

    if bot_tiles is not None:
        for t in bot_tiles:
            x.set_tile_bot(t)
    else:
        x.set_tile_bot(tile_bot=name)

    if tl_tiles is not None:
        for t in tl_tiles:
            x.set_tile_tl(t)
    else:
        x.set_tile_tl(tile_tl=name)

    if tr_tiles is not None:
        for t in tr_tiles:
            x.set_tile_tr(t)
    else:
        x.set_tile_tr(tile_tr=name)

    if bl_tiles is not None:
        for t in bl_tiles:
            x.set_tile_bl(t)
    else:
        x.set_tile_bl(tile_bl=name)

    if br_tiles is not None:
        for t in br_tiles:
            x.set_tile_br(t)
    else:
        x.set_tile_br(tile_br=name)

    x.update()

def init():
    tp_init(name="wall1",
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
                        "wall_deco1.left.1",
                        "wall_deco1.left.2",
                        "wall_deco1.left.3",
                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                ],
            right_tiles=[
                        "wall_deco1.right.1",
                        "wall_deco1.right.2",
                        "wall_deco1.right.3",
                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                ],
            top_tiles=[
                        "wall_deco1.top.1",
                        "wall_deco1.top.2",
                        "wall_deco1.top.3",
                        "wall_deco1.top.4",
                        "wall_deco1.top.5",
                        "wall_deco1.top.6",
                        "wall_deco1.top.7",
                        "wall_deco1.top.8",
                        "wall_deco1.top.9",
                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                ],
            bot_tiles=[
                        "wall_deco1.bot.1",
                        "wall_deco1.bot.2",
                        "wall_deco1.bot.3",
                        "wall_deco1.bot.4",
                        "wall_deco1.bot.5",
                        "wall_deco1.bot.6",
                        "wall_deco1.bot.7",
                        "wall_deco1.bot.8",
                        "wall_deco1.bot.9",
                        "wall_deco1.bot.10",
                        "wall_deco1.bot.11",
                        "wall_deco1.bot.12",
                        "wall_deco1.bot.13",
                        "wall_deco1.bot.14",
                        "wall_deco1.bot.15",
                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                ],
            tl_tiles=[
                        "wall_deco1.tl.1",
                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                ],
            tr_tiles=[
                        "wall_deco1.tr.1",
                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                ],
            br_tiles=[
                        "wall_deco1.br.1",
                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                ],
            bl_tiles=[
                        "wall_deco1.bl.1",
                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                ])

    tp_init(name="wall2",
            tiles=[
                        "wall2.1",
                        "wall2.2",
                        "wall2.3",
                        "wall2.4",
                        "wall2.5",
                        "wall2.6",
                        "wall2.7",
                        "wall2.8",
                        "wall2.9",
                        "wall2.10",
                        "wall2.11",
                        "wall2.12",
                        "wall2.13",
                        "wall2.14",
                        "wall2.15",
                        "wall2.16",
                ],
            left_tiles=[
                        "wall_deco1.left.1",
                        "wall_deco1.left.2",
                        "wall_deco1.left.3",
                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                ],
            right_tiles=[
                        "wall_deco1.right.1",
                        "wall_deco1.right.2",
                        "wall_deco1.right.3",
                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                ],
            top_tiles=[
                        "wall_deco1.top.1",
                        "wall_deco1.top.2",
                        "wall_deco1.top.3",
                        "wall_deco1.top.4",
                        "wall_deco1.top.5",
                        "wall_deco1.top.6",
                        "wall_deco1.top.7",
                        "wall_deco1.top.8",
                        "wall_deco1.top.9",
                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                ],
            bot_tiles=[
                        "wall_deco1.bot.1",
                        "wall_deco1.bot.2",
                        "wall_deco1.bot.3",
                        "wall_deco1.bot.4",
                        "wall_deco1.bot.5",
                        "wall_deco1.bot.6",
                        "wall_deco1.bot.7",
                        "wall_deco1.bot.8",
                        "wall_deco1.bot.9",
                        "wall_deco1.bot.10",
                        "wall_deco1.bot.11",
                        "wall_deco1.bot.12",
                        "wall_deco1.bot.13",
                        "wall_deco1.bot.14",
                        "wall_deco1.bot.15",
                ],
            tl_tiles=[
                        "wall_deco1.tl.1",
                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                ],
            tr_tiles=[
                        "wall_deco1.tr.1",
                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                ],
            br_tiles=[
                        "wall_deco1.br.1",
                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                ],
            bl_tiles=[
                        "wall_deco1.bl.1",
                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                ])
init()
