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
    x = tp.Tp(name, is_wall = True)

    x.set_short_name(short_name)
    x.set_is_movement_blocking(True)
    x.set_is_wall(True)

    if tiles is not None:
        for t in tiles:
            x.set_tile(t, delay_ms=150)
    else:
        x.set_tile(tile=name, delay_ms=150)

    if left_tiles is not None:
        for t in left_tiles:
            x.set_left_tile(t, delay_ms=150)
    else:
        x.set_left_tile(left_tile=name, delay_ms=150)

    if right_tiles is not None:
        for t in right_tiles:
            x.set_right_tile(t, delay_ms=150)
    else:
        x.set_right_tile(right_tile=name, delay_ms=150)

    if top_tiles is not None:
        for t in top_tiles:
            x.set_top_tile(t, delay_ms=150)
    else:
        x.set_top_tile(top_tile=name, delay_ms=150)

    if bot_tiles is not None:
        for t in bot_tiles:
            x.set_bot_tile(t, delay_ms=150)
    else:
        x.set_bot_tile(bot_tile=name, delay_ms=150)

    if tl_tiles is not None:
        for t in tl_tiles:
            x.set_tl_tile(t, delay_ms=150)
    else:
        x.set_tl_tile(tl_tile=name, delay_ms=150)

    if tr_tiles is not None:
        for t in tr_tiles:
            x.set_tr_tile(t, delay_ms=150)
    else:
        x.set_tr_tile(tr_tile=name, delay_ms=150)

    if bl_tiles is not None:
        for t in bl_tiles:
            x.set_bl_tile(t, delay_ms=150)
    else:
        x.set_bl_tile(bl_tile=name, delay_ms=150)

    if br_tiles is not None:
        for t in br_tiles:
            x.set_br_tile(t, delay_ms=150)
    else:
        x.set_br_tile(br_tile=name, delay_ms=150)


def init():
    wall_init(name="wall1", short_name="A boring wall", 
            tiles=[
                        "wall1",
                ],
            left_tiles=[
                        "wall1",
                ],
            right_tiles=[
                        "wall1",
                ],
            top_tiles=[
                        "wall1",
                ],
            bot_tiles=[
                        "wall1",
                ],
            tl_tiles=[ 
                        "wall1",
                ],
            tr_tiles=[
                        "wall1",
                ],
            br_tiles=[
                        "wall1",
                ],
            bl_tiles=[
                        "wall1",
                ])
init()
