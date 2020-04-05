import zx
import tp


def tp_init(name,
            tiles=[],
            left1_tiles=[],
            right1_tiles=[],
            top1_tiles=[],
            bot1_tiles=[],
            tl1_tiles=[],
            tr1_tiles=[],
            bl1_tiles=[],
            br1_tiles=[]):

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
    x.set_a_or_an("a");
    x.set_is_combustible(False)
    x.set_z_depth(zx.MAP_DEPTH_WALLS)

    if tiles is not None:
        for t in tiles:
            x.set_tile(t)
    else:
        x.set_tile(tile=name)

    if left1_tiles is not None:
        for t in left1_tiles:
            x.set_tile_left(t)
    else:
        x.set_tile_left(tile_left=name)

    if right1_tiles is not None:
        for t in right1_tiles:
            x.set_tile_right(t)
    else:
        x.set_tile_right(tile_right=name)

    if top1_tiles is not None:
        for t in top1_tiles:
            x.set_tile_top(t)
    else:
        x.set_tile_top(tile_top=name)

    if bot1_tiles is not None:
        for t in bot1_tiles:
            x.set_tile_bot(t)
    else:
        x.set_tile_bot(tile_bot=name)

    if tl1_tiles is not None:
        for t in tl1_tiles:
            x.set_tile_tl(t)
    else:
        x.set_tile_tl(tile_tl=name)

    if tr1_tiles is not None:
        for t in tr1_tiles:
            x.set_tile_tr(t)
    else:
        x.set_tile_tr(tile_tr=name)

    if bl1_tiles is not None:
        for t in bl1_tiles:
            x.set_tile_bl(t)
    else:
        x.set_tile_bl(tile_bl=name)

    if br1_tiles is not None:
        for t in br1_tiles:
            x.set_tile_br(t)
    else:
        x.set_tile_br(tile_br=name)

    x.update()

def init():
    tp_init(name="wall1",
            tiles=[       "wall1.1", "wall1.2", "wall1.3", "wall1.4",
                          "wall1.5", "wall1.6", "wall1.7", "wall1.8",
                          "wall1.9", "wall1.10", "wall1.11", "wall1.12",
                          "wall1.13", "wall1.14", "wall1.15", "wall1.16",
                          "wall1.17", "wall1.18", "wall1.19", ],
            left1_tiles=[  "wall_deco1.left.1", "wall_deco1.left.2",
                          "wall_deco1.left.3", "wall_deco1.left.4",
                          "wall_deco1.left.5", "wall_deco1.left.6", ],
            right1_tiles=[ "wall_deco1.right.1", "wall_deco1.right.2",
                          "wall_deco1.right.3", "wall_deco1.right.4",
                          "wall_deco1.right.5", "wall_deco1.right.6", ],
            top1_tiles=[   "wall_deco1.top.1", "wall_deco1.top.2",
                          "wall_deco1.top.3", "wall_deco1.top.4",
                          "wall_deco1.top.5", "wall_deco1.top.6",
                          "wall_deco1.top.7", ],
            bot1_tiles=[   "wall_deco1.bot.1", "wall_deco1.bot.2",
                          "wall_deco1.bot.3", "wall_deco1.bot.4",
                          "wall_deco1.bot.5", "wall_deco1.bot.6",
                          "wall_deco1.bot.7", ],
            tl1_tiles=[    "wall_deco1.tl.1", "wall_deco1.tl.2",
                          "wall_deco1.tl.3", "wall_deco1.tl.4",
                          "wall_deco1.tl.5", "wall_deco1.tl.6", ],
            tr1_tiles=[    "wall_deco1.tr.1", "wall_deco1.tr.2",
                          "wall_deco1.tr.3", "wall_deco1.tr.4",
                          "wall_deco1.tr.5", "wall_deco1.tr.6", ],
            br1_tiles=[    "wall_deco1.br.1", "wall_deco1.br.2",
                          "wall_deco1.br.3", "wall_deco1.br.4",
                          "wall_deco1.br.5", "wall_deco1.br.6", ],
            bl1_tiles=[    "wall_deco1.bl.1", "wall_deco1.bl.2",
                          "wall_deco1.bl.3", "wall_deco1.bl.4",
                          "wall_deco1.bl.5", "wall_deco1.bl.6", ])

init()
