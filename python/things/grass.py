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

    x.set_does_nothing(True)
    x.set_is_grass(True)
    x.set_z_depth(zx.MAP_DEPTH_GRASS)

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
            tile_lefts=[
                        "grass1.left.1",
                        "grass2.left.1",
                        "grass3.left.1",
                        "grass4.left.1",
                ],
            tile_rights=[
                        "grass1.right.1",
                        "grass2.right.1",
                        "grass3.right.1",
                        "grass4.right.1",
                ],
            tile_tops=[
                        "grass1.top.1",
                        "grass2.top.1",
                        "grass3.top.1",
                        "grass4.top.1",
                ],
            tile_bots=[
                        "grass1.bot.1",
                        "grass2.bot.1",
                        "grass3.bot.1",
                        "grass4.bot.1",
                ],
            tile_tls=[ 
                        "grass1.tl.1",
                        "grass2.tl.1",
                        "grass3.tl.1",
                        "grass4.tl.1",
                ],
            tile_trs=[
                        "grass1.tr.1",
                        "grass2.tr.1",
                        "grass3.tr.1",
                        "grass4.tr.1",
                ],
            tile_brs=[
                        "grass1.br.1",
                        "grass2.br.1",
                        "grass3.br.1",
                        "grass4.br.1",
                ],
            tile_bls=[
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
            tile_lefts=[
                        "grass1.left.1",
                        "grass2.left.1",
                        "grass3.left.1",
                        "grass4.left.1",
                ],
            tile_rights=[
                        "grass1.right.1",
                        "grass2.right.1",
                        "grass3.right.1",
                        "grass4.right.1",
                ],
            tile_tops=[
                        "grass1.top.1",
                        "grass2.top.1",
                        "grass3.top.1",
                        "grass4.top.1",
                ],
            tile_bots=[
                        "grass1.bot.1",
                        "grass2.bot.1",
                        "grass3.bot.1",
                        "grass4.bot.1",
                ],
            tile_tls=[ 
                        "grass1.tl.1",
                        "grass2.tl.1",
                        "grass3.tl.1",
                        "grass4.tl.1",
                ],
            tile_trs=[
                        "grass1.tr.1",
                        "grass2.tr.1",
                        "grass3.tr.1",
                        "grass4.tr.1",
                ],
            tile_brs=[
                        "grass1.br.1",
                        "grass2.br.1",
                        "grass3.br.1",
                        "grass4.br.1",
                ],
            tile_bls=[
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
            tile_lefts=[
                        "grass1.left.1",
                        "grass2.left.1",
                        "grass3.left.1",
                        "grass4.left.1",
                ],
            tile_rights=[
                        "grass1.right.1",
                        "grass2.right.1",
                        "grass3.right.1",
                        "grass4.right.1",
                ],
            tile_tops=[
                        "grass1.top.1",
                        "grass2.top.1",
                        "grass3.top.1",
                        "grass4.top.1",
                ],
            tile_bots=[
                        "grass1.bot.1",
                        "grass2.bot.1",
                        "grass3.bot.1",
                        "grass4.bot.1",
                ],
            tile_tls=[ 
                        "grass1.tl.1",
                        "grass2.tl.1",
                        "grass3.tl.1",
                        "grass4.tl.1",
                ],
            tile_trs=[
                        "grass1.tr.1",
                        "grass2.tr.1",
                        "grass3.tr.1",
                        "grass4.tr.1",
                ],
            tile_brs=[
                        "grass1.br.1",
                        "grass2.br.1",
                        "grass3.br.1",
                        "grass4.br.1",
                ],
            tile_bls=[
                        "grass1.bl.1",
                        "grass2.bl.1",
                        "grass3.bl.1",
                        "grass4.bl.1",
                ])

init()
