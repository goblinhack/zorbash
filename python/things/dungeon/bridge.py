import my
import tp


def on_death(me, x, y):
    my.level_spawn_using_items_radius_range(me, me, me, "explosion_destroy_floor")
    my.thing_msg(me, "The bridge collapses!")

    for bridge in my.level_flood_fill_get_all_things(me, x, y, "is_bridge"):
        if bridge != me:
            if not my.thing_is_dead_or_dying(bridge):
                my.thing_dead(bridge, "dead")


def tp_init(name, tiles=[], bot3_tiles=[]):
    mytp = tp.Tp(name, "bridge")
    my.tp_set_gfx_shown_in_bg(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_bridge(mytp, True)
    my.tp_set_is_cursor_can_hover_over(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_interesting(mytp, True)
    my.tp_set_is_tickable(mytp, True)
    my.tp_set_on_death_do(mytp, "bridge.on_death()")
    my.tp_set_text_a_or_an(mytp, "the")
    my.tp_set_text_description(mytp, "Shaky bridge.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_FLOOR)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL)

    for t in tiles:
        my.tp_set_tile(mytp, t)

    if bot3_tiles is not None:
        for t in bot3_tiles:
            my.tp_set_bot3_tile(mytp, t)
    else:
        my.tp_set_bot3_tile(mytp, bot3_tile=name)

    my.tp_update(mytp, )


def init():
    tp_init(
        name="bridge_x",
        tiles=[
            "bridge_x",
        ],
        bot3_tiles=[
            "chasm1.1",
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
            "chasm1.1",
            "chasm1.2",
            "chasm1.3",
            "chasm1.4",
            "chasm1.5",
            "chasm1.6",
            "chasm1.7",
            "chasm1.8",
            "chasm1.9",
            "chasm1.10",
            "chasm1.11",
            "chasm1.12",
            "chasm1.13",
            "chasm1.14",
            "chasm1.15",
            "chasm1.16",
            "chasm1.17",
            "chasm1.18",
            "chasm1.19",
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
            "chasm1.1",
            "chasm1.2",
            "chasm1.3",
            "chasm1.4",
            "chasm1.5",
            "chasm1.6",
            "chasm1.7",
            "chasm1.8",
            "chasm1.9",
            "chasm1.10",
            "chasm1.11",
            "chasm1.12",
            "chasm1.13",
            "chasm1.14",
            "chasm1.15",
            "chasm1.16",
            "chasm1.17",
            "chasm1.18",
            "chasm1.19",
        ],
    )


init()
