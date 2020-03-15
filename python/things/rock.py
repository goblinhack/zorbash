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
    x.set_is_rock(True)
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
    tp_init(name="rock1",
            tiles=[
                        "rock1.1",
                        "rock1.2",
                        "rock1.3",
                        "rock1.4",
                        "rock1.5",
                        "rock1.6",
                        "rock1.7",
                        "rock1.8",
                        "rock1.9",
                        "rock1.10",
                        "rock1.11",
                        "rock1.12",
                        "rock1.13",
                        "rock1.14",
                        "rock1.15",
                        "rock1.16",
                ])

    tp_init(name="rock2",
            tiles=[
                        "rock2.1",
                        "rock2.2",
                        "rock2.3",
                        "rock2.4",
                        "rock2.5",
                        "rock2.6",
                        "rock2.7",
                        "rock2.8",
                        "rock2.9",
                        "rock2.10",
                        "rock2.11",
                        "rock2.12",
                        "rock2.13",
                        "rock2.14",
                        "rock2.15",
                        "rock2.16",
                ])
init()
