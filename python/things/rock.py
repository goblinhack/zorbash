import zx
import tp


def tp_init(name,
            tiles=[],
            tile_lefts=[],
            tile_rights=[],
            tile_tops=[],
            tile_bots=[],
            tile_tls=[],
            tile_trs=[],
            tile_bls=[],
            tile_brs=[]):

    x = tp.Tp(name)

    x.set_gfx_large_shadow_caster(True)
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

    if tile_lefts is not None:
        for t in tile_lefts:
            x.set_tile_left(t)
    else:
        x.set_tile_left(tile_left=name)

    if tile_rights is not None:
        for t in tile_rights:
            x.set_tile_right(t)
    else:
        x.set_tile_right(tile_right=name)

    if tile_tops is not None:
        for t in tile_tops:
            x.set_tile_top(t)
    else:
        x.set_tile_top(tile_top=name)

    if tile_bots is not None:
        for t in tile_bots:
            x.set_tile_bot(t)
    else:
        x.set_tile_bot(tile_bot=name)

    if tile_tls is not None:
        for t in tile_tls:
            x.set_tile_tl(t)
    else:
        x.set_tile_tl(tile_tl=name)

    if tile_trs is not None:
        for t in tile_trs:
            x.set_tile_tr(t)
    else:
        x.set_tile_tr(tile_tr=name)

    if tile_bls is not None:
        for t in tile_bls:
            x.set_tile_bl(t)
    else:
        x.set_tile_bl(tile_bl=name)

    if tile_brs is not None:
        for t in tile_brs:
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
