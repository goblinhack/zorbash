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
    x.set_is_gravel(True)
    x.set_z_depth(zx.MAP_DEPTH_GRAVEL)

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
            tile_lefts=[
                        "gravel1.left.1",
                        "gravel2.left.1",
                        "gravel3.left.1",
                        "gravel4.left.1",
                ],
            tile_rights=[
                        "gravel1.right.1",
                        "gravel2.right.1",
                        "gravel3.right.1",
                        "gravel4.right.1",
                ],
            tile_tops=[
                        "gravel1.top.1",
                        "gravel2.top.1",
                        "gravel3.top.1",
                        "gravel4.top.1",
                ],
            tile_bots=[
                        "gravel1.bot.1",
                        "gravel2.bot.1",
                        "gravel3.bot.1",
                        "gravel4.bot.1",
                ],
            tile_tls=[ 
                        "gravel1.tl.1",
                        "gravel2.tl.1",
                        "gravel3.tl.1",
                        "gravel4.tl.1",
                ],
            tile_trs=[
                        "gravel1.tr.1",
                        "gravel2.tr.1",
                        "gravel3.tr.1",
                        "gravel4.tr.1",
                ],
            tile_brs=[
                        "gravel1.br.1",
                        "gravel2.br.1",
                        "gravel3.br.1",
                        "gravel4.br.1",
                ],
            tile_bls=[
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
            tile_lefts=[
                        "gravel1.left.1",
                        "gravel2.left.1",
                        "gravel3.left.1",
                        "gravel4.left.1",
                ],
            tile_rights=[
                        "gravel1.right.1",
                        "gravel2.right.1",
                        "gravel3.right.1",
                        "gravel4.right.1",
                ],
            tile_tops=[
                        "gravel1.top.1",
                        "gravel2.top.1",
                        "gravel3.top.1",
                        "gravel4.top.1",
                ],
            tile_bots=[
                        "gravel1.bot.1",
                        "gravel2.bot.1",
                        "gravel3.bot.1",
                        "gravel4.bot.1",
                ],
            tile_tls=[ 
                        "gravel1.tl.1",
                        "gravel2.tl.1",
                        "gravel3.tl.1",
                        "gravel4.tl.1",
                ],
            tile_trs=[
                        "gravel1.tr.1",
                        "gravel2.tr.1",
                        "gravel3.tr.1",
                        "gravel4.tr.1",
                ],
            tile_brs=[
                        "gravel1.br.1",
                        "gravel2.br.1",
                        "gravel3.br.1",
                        "gravel4.br.1",
                ],
            tile_bls=[
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
            tile_lefts=[
                        "gravel1.left.1",
                        "gravel2.left.1",
                        "gravel3.left.1",
                        "gravel4.left.1",
                ],
            tile_rights=[
                        "gravel1.right.1",
                        "gravel2.right.1",
                        "gravel3.right.1",
                        "gravel4.right.1",
                ],
            tile_tops=[
                        "gravel1.top.1",
                        "gravel2.top.1",
                        "gravel3.top.1",
                        "gravel4.top.1",
                ],
            tile_bots=[
                        "gravel1.bot.1",
                        "gravel2.bot.1",
                        "gravel3.bot.1",
                        "gravel4.bot.1",
                ],
            tile_tls=[ 
                        "gravel1.tl.1",
                        "gravel2.tl.1",
                        "gravel3.tl.1",
                        "gravel4.tl.1",
                ],
            tile_trs=[
                        "gravel1.tr.1",
                        "gravel2.tr.1",
                        "gravel3.tr.1",
                        "gravel4.tr.1",
                ],
            tile_brs=[
                        "gravel1.br.1",
                        "gravel2.br.1",
                        "gravel3.br.1",
                        "gravel4.br.1",
                ],
            tile_bls=[
                        "gravel1.bl.1",
                        "gravel2.bl.1",
                        "gravel3.bl.1",
                        "gravel4.bl.1",
                ])

init()
