import my
import tp


def tp_init(
    name,
    tiles=[],
    left1_tiles=[],
    right1_tiles=[],
    top1_tiles=[],
    bot1_tiles=[],
    tl1_tiles=[],
    tr1_tiles=[],
    bl1_tiles=[],
    br1_tiles=[],
    left2_tiles=[],
    right2_tiles=[],
    top2_tiles=[],
    bot2_tiles=[],
    tl2_tiles=[],
    tr2_tiles=[],
    bl2_tiles=[],
    br2_tiles=[],
):

    self = tp.Tp(name, "rock")
    my.tp_set_ai_obstacle(self, True)
    my.tp_set_collision_hit_priority(self, 1)
    my.tp_set_gfx_shown_in_bg(self, True)
    my.tp_set_health_initial_dice(self, "999")
    my.tp_set_is_always_hit(self, True)
    my.tp_set_is_attackable_by_monst(self, True)
    my.tp_set_is_attackable_by_player(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_cursor_can_hover_over(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_gas_blocker(self, True)
    my.tp_set_is_hittable(self, True)
    my.tp_set_is_light_blocker(self, True)
    my.tp_set_is_obs_wall_or_door(self, True)
    my.tp_set_is_rock(self, True)
    my.tp_set_is_stone(self, True)
    my.tp_set_is_toughness_very_hard(self, True)
    my.tp_set_is_wall(self, True)
    my.tp_set_noise_blocker(self, True)
    my.tp_set_text_a_or_an(self, "the")
    my.tp_set_text_description(self, "Rocky the rock.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_NORMAL)

    if tiles is not None:
        for t in tiles:
            my.tp_set_tile(self, t)
    else:
        my.tp_set_tile(self, tile=name)

    if left1_tiles is not None:
        for t in left1_tiles:
            my.tp_set_left1_tile(self, t)
    else:
        my.tp_set_left1_tile(self, left1_tile=name)

    if right1_tiles is not None:
        for t in right1_tiles:
            my.tp_set_right1_tile(self, t)
    else:
        my.tp_set_right1_tile(self, right1_tile=name)

    if top1_tiles is not None:
        for t in top1_tiles:
            my.tp_set_top1_tile(self, t)
    else:
        my.tp_set_top1_tile(self, top1_tile=name)

    if bot1_tiles is not None:
        for t in bot1_tiles:
            my.tp_set_bot1_tile(self, t)
    else:
        my.tp_set_bot1_tile(self, bot1_tile=name)

    if tl1_tiles is not None:
        for t in tl1_tiles:
            my.tp_set_tl1_tile(self, t)
    else:
        my.tp_set_tl1_tile(self, tl1_tile=name)

    if tr1_tiles is not None:
        for t in tr1_tiles:
            my.tp_set_tr1_tile(self, t)
    else:
        my.tp_set_tr1_tile(self, tr1_tile=name)

    if bl1_tiles is not None:
        for t in bl1_tiles:
            my.tp_set_bl1_tile(self, t)
    else:
        my.tp_set_bl1_tile(self, bl1_tile=name)

    if br1_tiles is not None:
        for t in br1_tiles:
            my.tp_set_br1_tile(self, t)
    else:
        my.tp_set_br1_tile(self, br1_tile=name)

    if left2_tiles is not None:
        for t in left2_tiles:
            my.tp_set_left2_tile(self, t)
    else:
        my.tp_set_left2_tile(self, left2_tile=name)

    if right2_tiles is not None:
        for t in right2_tiles:
            my.tp_set_right2_tile(self, t)
    else:
        my.tp_set_right2_tile(self, right2_tile=name)

    if top2_tiles is not None:
        for t in top2_tiles:
            my.tp_set_top2_tile(self, t)
    else:
        my.tp_set_top2_tile(self, top2_tile=name)

    if bot2_tiles is not None:
        for t in bot2_tiles:
            my.tp_set_bot2_tile(self, t)
    else:
        my.tp_set_bot2_tile(self, bot2_tile=name)

    if tl2_tiles is not None:
        for t in tl2_tiles:
            my.tp_set_tl2_tile(self, t)
    else:
        my.tp_set_tl2_tile(self, tl2_tile=name)

    if tr2_tiles is not None:
        for t in tr2_tiles:
            my.tp_set_tr2_tile(self, t)
    else:
        my.tp_set_tr2_tile(self, tr2_tile=name)

    if bl2_tiles is not None:
        for t in bl2_tiles:
            my.tp_set_bl2_tile(self, t)
    else:
        my.tp_set_bl2_tile(self, bl2_tile=name)

    if br2_tiles is not None:
        for t in br2_tiles:
            my.tp_set_br2_tile(self, t)
    else:
        my.tp_set_br2_tile(self, br2_tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="rock1",
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
            "rock1.17",
            "rock1.18",
            "rock1.19",
        ],
        left1_tiles=[
            "wall_deco1.left.1",
            "wall_deco2.left.1",
            "wall_deco1.left.2",
            "wall_deco2.left.2",
            "wall_deco1.left.3",
            "wall_deco2.left.3",
            "wall_deco1.left.4",
            "wall_deco2.left.4",
            "wall_deco1.left.5",
            "wall_deco2.left.5",
            "wall_deco1.left.6",
            "wall_deco2.left.6",
        ],
        right1_tiles=[
            "wall_deco1.right.1",
            "wall_deco2.right.1",
            "wall_deco1.right.2",
            "wall_deco2.right.2",
            "wall_deco1.right.3",
            "wall_deco2.right.3",
            "wall_deco1.right.4",
            "wall_deco2.right.4",
            "wall_deco1.right.5",
            "wall_deco2.right.5",
            "wall_deco1.right.6",
            "wall_deco2.right.6",
        ],
        top1_tiles=[
            "wall_deco1.top.1",
            "wall_deco2.top.1",
            "wall_deco1.top.2",
            "wall_deco2.top.2",
            "wall_deco1.top.3",
            "wall_deco2.top.3",
            "wall_deco1.top.4",
            "wall_deco2.top.4",
            "wall_deco1.top.5",
            "wall_deco2.top.5",
            "wall_deco1.top.6",
            "wall_deco2.top.6",
            "wall_deco1.top.7",
            "wall_deco2.top.7",
        ],
        bot1_tiles=[
            "wall_deco1.bot.1",
            "wall_deco2.bot.1",
            "wall_deco1.bot.2",
            "wall_deco2.bot.2",
            "wall_deco1.bot.3",
            "wall_deco2.bot.3",
            "wall_deco1.bot.4",
            "wall_deco2.bot.4",
            "wall_deco1.bot.5",
            "wall_deco2.bot.5",
            "wall_deco1.bot.6",
            "wall_deco2.bot.6",
            "wall_deco1.bot.7",
            "wall_deco2.bot.7",
        ],
        tl1_tiles=[
            "wall_deco1.tl.1",
            "wall_deco2.tl.1",
            "wall_deco1.tl.2",
            "wall_deco2.tl.2",
            "wall_deco1.tl.3",
            "wall_deco2.tl.3",
            "wall_deco1.tl.4",
            "wall_deco2.tl.4",
            "wall_deco1.tl.5",
            "wall_deco2.tl.5",
            "wall_deco1.tl.6",
            "wall_deco2.tl.6",
        ],
        tr1_tiles=[
            "wall_deco1.tr.1",
            "wall_deco2.tr.1",
            "wall_deco1.tr.2",
            "wall_deco2.tr.2",
            "wall_deco1.tr.3",
            "wall_deco2.tr.3",
            "wall_deco1.tr.4",
            "wall_deco2.tr.4",
            "wall_deco1.tr.5",
            "wall_deco2.tr.5",
            "wall_deco1.tr.6",
            "wall_deco2.tr.6",
        ],
        br1_tiles=[
            "wall_deco1.br.1",
            "wall_deco2.br.1",
            "wall_deco1.br.2",
            "wall_deco2.br.2",
            "wall_deco1.br.3",
            "wall_deco2.br.3",
            "wall_deco1.br.4",
            "wall_deco2.br.4",
            "wall_deco1.br.5",
            "wall_deco2.br.5",
            "wall_deco1.br.6",
            "wall_deco2.br.6",
        ],
        bl1_tiles=[
            "wall_deco1.bl.1",
            "wall_deco2.bl.1",
            "wall_deco1.bl.2",
            "wall_deco2.bl.2",
            "wall_deco1.bl.3",
            "wall_deco2.bl.3",
            "wall_deco1.bl.4",
            "wall_deco2.bl.4",
            "wall_deco1.bl.5",
            "wall_deco2.bl.5",
            "wall_deco1.bl.6",
            "wall_deco2.bl.6",
        ],
        left2_tiles=[
            "wall_shadow_deco1.left.1",
            "wall_shadow_deco2.left.1",
            "wall_shadow_deco1.left.2",
            "wall_shadow_deco2.left.2",
            "wall_shadow_deco1.left.3",
            "wall_shadow_deco2.left.3",
            "wall_shadow_deco1.left.4",
            "wall_shadow_deco2.left.4",
            "wall_shadow_deco1.left.5",
            "wall_shadow_deco2.left.5",
            "wall_shadow_deco1.left.6",
            "wall_shadow_deco2.left.6",
        ],
        right2_tiles=[
            "wall_shadow_deco1.right.1",
            "wall_shadow_deco2.right.1",
            "wall_shadow_deco1.right.2",
            "wall_shadow_deco2.right.2",
            "wall_shadow_deco1.right.3",
            "wall_shadow_deco2.right.3",
            "wall_shadow_deco1.right.4",
            "wall_shadow_deco2.right.4",
            "wall_shadow_deco1.right.5",
            "wall_shadow_deco2.right.5",
            "wall_shadow_deco1.right.6",
            "wall_shadow_deco2.right.6",
        ],
        top2_tiles=[
            "wall_shadow_deco1.top.1",
            "wall_shadow_deco2.top.1",
            "wall_shadow_deco1.top.2",
            "wall_shadow_deco2.top.2",
            "wall_shadow_deco1.top.3",
            "wall_shadow_deco2.top.3",
            "wall_shadow_deco1.top.4",
            "wall_shadow_deco2.top.4",
            "wall_shadow_deco1.top.5",
            "wall_shadow_deco2.top.5",
            "wall_shadow_deco1.top.6",
            "wall_shadow_deco2.top.6",
            "wall_shadow_deco1.top.7",
            "wall_shadow_deco2.top.7",
        ],
        bot2_tiles=[
            "wall_shadow_deco1.bot.1",
            "wall_shadow_deco2.bot.1",
            "wall_shadow_deco1.bot.2",
            "wall_shadow_deco2.bot.2",
            "wall_shadow_deco1.bot.3",
            "wall_shadow_deco2.bot.3",
            "wall_shadow_deco1.bot.4",
            "wall_shadow_deco2.bot.4",
            "wall_shadow_deco1.bot.5",
            "wall_shadow_deco2.bot.5",
            "wall_shadow_deco1.bot.6",
            "wall_shadow_deco2.bot.6",
            "wall_shadow_deco1.bot.7",
            "wall_shadow_deco2.bot.7",
        ],
        tl2_tiles=[
            "wall_shadow_deco1.tl.1",
            "wall_shadow_deco2.tl.1",
            "wall_shadow_deco1.tl.2",
            "wall_shadow_deco2.tl.2",
            "wall_shadow_deco1.tl.3",
            "wall_shadow_deco2.tl.3",
            "wall_shadow_deco1.tl.4",
            "wall_shadow_deco2.tl.4",
            "wall_shadow_deco1.tl.5",
            "wall_shadow_deco2.tl.5",
            "wall_shadow_deco1.tl.6",
            "wall_shadow_deco2.tl.6",
        ],
        tr2_tiles=[
            "wall_shadow_deco1.tr.1",
            "wall_shadow_deco2.tr.1",
            "wall_shadow_deco1.tr.2",
            "wall_shadow_deco2.tr.2",
            "wall_shadow_deco1.tr.3",
            "wall_shadow_deco2.tr.3",
            "wall_shadow_deco1.tr.4",
            "wall_shadow_deco2.tr.4",
            "wall_shadow_deco1.tr.5",
            "wall_shadow_deco2.tr.5",
            "wall_shadow_deco1.tr.6",
            "wall_shadow_deco2.tr.6",
        ],
        br2_tiles=[
            "wall_shadow_deco1.br.1",
            "wall_shadow_deco2.br.1",
            "wall_shadow_deco1.br.2",
            "wall_shadow_deco2.br.2",
            "wall_shadow_deco1.br.3",
            "wall_shadow_deco2.br.3",
            "wall_shadow_deco1.br.4",
            "wall_shadow_deco2.br.4",
            "wall_shadow_deco1.br.5",
            "wall_shadow_deco2.br.5",
            "wall_shadow_deco1.br.6",
            "wall_shadow_deco2.br.6",
        ],
        bl2_tiles=[
            "wall_shadow_deco1.bl.1",
            "wall_shadow_deco2.bl.1",
            "wall_shadow_deco1.bl.2",
            "wall_shadow_deco2.bl.2",
            "wall_shadow_deco1.bl.3",
            "wall_shadow_deco2.bl.3",
            "wall_shadow_deco1.bl.4",
            "wall_shadow_deco2.bl.4",
            "wall_shadow_deco1.bl.5",
            "wall_shadow_deco2.bl.5",
            "wall_shadow_deco1.bl.6",
            "wall_shadow_deco2.bl.6",
        ],
    )


init()
