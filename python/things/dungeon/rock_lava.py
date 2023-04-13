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
    # begin sort marker
    my.collision_hit_priority(self, 1)
    my.gfx_ascii_bg_color_spread_hue(self, 10)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "999")
    my.is_always_hit(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_cursor_path_blocker(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_gas_blocker(self, True)
    my.is_hittable(self, True)
    my.is_light_blocker(self, True)
    my.is_obs_for_ai(self, True)
    my.is_obs_for_jump_landing(self, True)
    my.is_obs_for_shoving(self, True)
    my.is_obs_in_the_way_for_jumping(self, True)
    my.is_obs_in_the_way_for_shooting(self, True)
    my.is_obs_in_the_way_for_throwing(self, True)
    my.is_obs_wall_or_door(self, True)
    my.is_rock(self, True)
    my.is_stone(self, True)
    my.is_very_hard(self, True)
    my.is_wall(self, True)
    my.noise_blocker(self, True)
    my.temperature(self, -100)
    my.text_a_or_an(self, "the")
    my.text_description_short(self, "Melting rock.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="L", ascii_bg_col_name="gray20", ascii_fg_col_name="orange",
                tile=t)

    if left1_tiles is not None:
        for t in left1_tiles:
            my.left1_tile(self, t)
    else:
        my.left1_tile(self, left1_tile=name)

    if right1_tiles is not None:
        for t in right1_tiles:
            my.right1_tile(self, t)
    else:
        my.right1_tile(self, right1_tile=name)

    if top1_tiles is not None:
        for t in top1_tiles:
            my.top1_tile(self, t)
    else:
        my.top1_tile(self, top1_tile=name)

    if bot1_tiles is not None:
        for t in bot1_tiles:
            my.bot1_tile(self, t)
    else:
        my.bot1_tile(self, bot1_tile=name)

    if tl1_tiles is not None:
        for t in tl1_tiles:
            my.tl1_tile(self, t)
    else:
        my.tl1_tile(self, tl1_tile=name)

    if tr1_tiles is not None:
        for t in tr1_tiles:
            my.tr1_tile(self, t)
    else:
        my.tr1_tile(self, tr1_tile=name)

    if bl1_tiles is not None:
        for t in bl1_tiles:
            my.bl1_tile(self, t)
    else:
        my.bl1_tile(self, bl1_tile=name)

    if br1_tiles is not None:
        for t in br1_tiles:
            my.br1_tile(self, t)
    else:
        my.br1_tile(self, br1_tile=name)

    if left2_tiles is not None:
        for t in left2_tiles:
            my.left2_tile(self, t)
    else:
        my.left2_tile(self, left2_tile=name)

    if right2_tiles is not None:
        for t in right2_tiles:
            my.right2_tile(self, t)
    else:
        my.right2_tile(self, right2_tile=name)

    if top2_tiles is not None:
        for t in top2_tiles:
            my.top2_tile(self, t)
    else:
        my.top2_tile(self, top2_tile=name)

    if bot2_tiles is not None:
        for t in bot2_tiles:
            my.bot2_tile(self, t)
    else:
        my.bot2_tile(self, bot2_tile=name)

    if tl2_tiles is not None:
        for t in tl2_tiles:
            my.tl2_tile(self, t)
    else:
        my.tl2_tile(self, tl2_tile=name)

    if tr2_tiles is not None:
        for t in tr2_tiles:
            my.tr2_tile(self, t)
    else:
        my.tr2_tile(self, tr2_tile=name)

    if bl2_tiles is not None:
        for t in bl2_tiles:
            my.bl2_tile(self, t)
    else:
        my.bl2_tile(self, bl2_tile=name)

    if br2_tiles is not None:
        for t in br2_tiles:
            my.br2_tile(self, t)
    else:
        my.br2_tile(self, br2_tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="rock_lava",
        tiles=[
            "rock_lava.1",
            "rock_lava.2",
            "rock_lava.3",
            "rock_lava.4",
            "rock_lava.5",
            "rock_lava.6",
            "rock_lava.7",
            "rock_lava.8",
            "rock_lava.9",
            "rock_lava.10",
            "rock_lava.11",
            "rock_lava.12",
            "rock_lava.13",
            "rock_lava.14",
            "rock_lava.15",
            "rock_lava.16",
            "rock_lava.17",
            "rock_lava.18",
            "rock_lava.19",
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
