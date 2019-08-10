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
    x.set_is_soil(True)
    x.set_z_depth(zx.MAP_DEPTH_SOIL)

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
            tile_lefts=[
                        "soil1.left.1",
                        "soil2.left.1",
                        "soil3.left.1",
                        "soil4.left.1",
                ],
            tile_rights=[
                        "soil1.right.1",
                        "soil2.right.1",
                        "soil3.right.1",
                        "soil4.right.1",
                ],
            tile_tops=[
                        "soil1.top.1",
                        "soil2.top.1",
                        "soil3.top.1",
                        "soil4.top.1",
                ],
            tile_bots=[
                        "soil1.bot.1",
                        "soil2.bot.1",
                        "soil3.bot.1",
                        "soil4.bot.1",
                ],
            tile_tls=[ 
                        "soil1.tl.1",
                        "soil2.tl.1",
                        "soil3.tl.1",
                        "soil4.tl.1",
                ],
            tile_trs=[
                        "soil1.tr.1",
                        "soil2.tr.1",
                        "soil3.tr.1",
                        "soil4.tr.1",
                ],
            tile_brs=[
                        "soil1.br.1",
                        "soil2.br.1",
                        "soil3.br.1",
                        "soil4.br.1",
                ],
            tile_bls=[
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
            tile_lefts=[
                        "soil1.left.1",
                        "soil2.left.1",
                        "soil3.left.1",
                        "soil4.left.1",
                ],
            tile_rights=[
                        "soil1.right.1",
                        "soil2.right.1",
                        "soil3.right.1",
                        "soil4.right.1",
                ],
            tile_tops=[
                        "soil1.top.1",
                        "soil2.top.1",
                        "soil3.top.1",
                        "soil4.top.1",
                ],
            tile_bots=[
                        "soil1.bot.1",
                        "soil2.bot.1",
                        "soil3.bot.1",
                        "soil4.bot.1",
                ],
            tile_tls=[ 
                        "soil1.tl.1",
                        "soil2.tl.1",
                        "soil3.tl.1",
                        "soil4.tl.1",
                ],
            tile_trs=[
                        "soil1.tr.1",
                        "soil2.tr.1",
                        "soil3.tr.1",
                        "soil4.tr.1",
                ],
            tile_brs=[
                        "soil1.br.1",
                        "soil2.br.1",
                        "soil3.br.1",
                        "soil4.br.1",
                ],
            tile_bls=[
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
            tile_lefts=[
                        "soil1.left.1",
                        "soil2.left.1",
                        "soil3.left.1",
                        "soil4.left.1",
                ],
            tile_rights=[
                        "soil1.right.1",
                        "soil2.right.1",
                        "soil3.right.1",
                        "soil4.right.1",
                ],
            tile_tops=[
                        "soil1.top.1",
                        "soil2.top.1",
                        "soil3.top.1",
                        "soil4.top.1",
                ],
            tile_bots=[
                        "soil1.bot.1",
                        "soil2.bot.1",
                        "soil3.bot.1",
                        "soil4.bot.1",
                ],
            tile_tls=[ 
                        "soil1.tl.1",
                        "soil2.tl.1",
                        "soil3.tl.1",
                        "soil4.tl.1",
                ],
            tile_trs=[
                        "soil1.tr.1",
                        "soil2.tr.1",
                        "soil3.tr.1",
                        "soil4.tr.1",
                ],
            tile_brs=[
                        "soil1.br.1",
                        "soil2.br.1",
                        "soil3.br.1",
                        "soil4.br.1",
                ],
            tile_bls=[
                        "soil1.bl.1",
                        "soil2.bl.1",
                        "soil3.bl.1",
                        "soil4.bl.1",
                ])

init()
