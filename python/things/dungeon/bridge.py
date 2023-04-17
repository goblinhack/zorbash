import my
import tp


def on_death(me, x, y):
    my.spawn_using_items_radius_range(me, me, me, "explosion_destroy_floor")
    my.thing_msg(me, "The bridge collapses!")

    for bridge in my.level_flood_fill_get_all_things(me, x, y, "is_bridge"):
        if bridge != me:
            if not my.thing_is_dead_or_dying(bridge):
                my.thing_dead(bridge, "dead")


def tp_init(name, tiles=[], bot3_tiles=[]):
    self = tp.Tp(name, "bridge")
    # begin sort marker
    my.gfx_ascii_bg_color_spread_hue(self, 30)
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.health_initial_dice(self, "20+1d10")
    my.is_able_to_fall(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_bridge(self, True)
    my.is_burnable(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_flat(self, True)
    my.is_interesting(self, True)
    my.on_death_do(self, "bridge.on_death()")
    my.text_a_or_an(self, "the")
    my.text_description_short(self, "Shaky bridge.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_FLOOR)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="-", ascii_bg_col_name="brown", ascii_fg_col_name="black",
                tile=t)

    if bot3_tiles is not None:
        for t in bot3_tiles:
            my.bot3_tile(self, t)
    else:
        my.bot3_tile(self, bot3_tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="bridge_x",
        tiles=[
            "bridge_x",
        ],
        bot3_tiles=[
            "chasm_under_bridge.1",
        ],
    )
    tp_init(
        name="bridge_lr",
        tiles=[
            "bridge_lr.1",
            "bridge_lr.2",
            "bridge_lr.3",
            "bridge_lr.4",
            "bridge_lr.5",
            "bridge_lr.6",
            "bridge_lr.7",
            "bridge_lr.8",
            "bridge_lr.9",
            "bridge_lr.10",
            "bridge_lr.11",
            "bridge_lr.12",
            "bridge_lr.13",
            "bridge_lr.14",
            "bridge_lr.15",
            "bridge_lr.16",
            "bridge_lr.17",
            "bridge_lr.18",
        ],
        bot3_tiles=[
            "chasm_under_bridge.1",
            "chasm_under_bridge.2",
            "chasm_under_bridge.3",
            "chasm_under_bridge.4",
            "chasm_under_bridge.5",
            "chasm_under_bridge.6",
            "chasm_under_bridge.7",
            "chasm_under_bridge.8",
            "chasm_under_bridge.9",
            "chasm_under_bridge.10",
            "chasm_under_bridge.11",
            "chasm_under_bridge.12",
            "chasm_under_bridge.13",
            "chasm_under_bridge.14",
            "chasm_under_bridge.15",
            "chasm_under_bridge.16",
            "chasm_under_bridge.17",
            "chasm_under_bridge.18",
            "chasm_under_bridge.19",
        ],
    )
    tp_init(
        name="bridge_ud",
        tiles=[
            "bridge_ud.1",
            "bridge_ud.2",
            "bridge_ud.3",
            "bridge_ud.4",
            "bridge_ud.5",
            "bridge_ud.6",
            "bridge_ud.7",
            "bridge_ud.8",
            "bridge_ud.9",
            "bridge_ud.10",
            "bridge_ud.11",
            "bridge_ud.12",
            "bridge_ud.13",
            "bridge_ud.14",
            "bridge_ud.15",
            "bridge_ud.16",
            "bridge_ud.17",
            "bridge_ud.18",
            "bridge_ud.19",
        ],
        bot3_tiles=[
            "chasm_under_bridge.1",
            "chasm_under_bridge.2",
            "chasm_under_bridge.3",
            "chasm_under_bridge.4",
            "chasm_under_bridge.5",
            "chasm_under_bridge.6",
            "chasm_under_bridge.7",
            "chasm_under_bridge.8",
            "chasm_under_bridge.9",
            "chasm_under_bridge.10",
            "chasm_under_bridge.11",
            "chasm_under_bridge.12",
            "chasm_under_bridge.13",
            "chasm_under_bridge.14",
            "chasm_under_bridge.15",
            "chasm_under_bridge.16",
            "chasm_under_bridge.17",
            "chasm_under_bridge.18",
            "chasm_under_bridge.19",
        ],
    )


init()
