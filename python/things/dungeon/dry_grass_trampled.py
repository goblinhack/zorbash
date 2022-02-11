import my
import tp


def on_you_are_hit_and_now_dead(me, hitter, real_hitter, x, y, crit, damage):
    my.level_spawn_at_thing(me, "small_fire")
    my.level_place_at(me, "dry_grass_dead", x, y)
    my.thing_msg(me, "The dry grass burns!")


def tp_init(name, tiles=[]):
    mytp = tp.Tp(name, "trampled grass")
    my.tp_set_gfx_shown_in_bg(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_burnable(mytp, True)
    my.tp_set_is_combustible(mytp, True)
    my.tp_set_is_cursor_can_hover_over(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_dry_grass(mytp, True)
    my.tp_set_is_interesting(mytp, True)
    my.tp_set_on_you_are_hit_and_now_dead_do(mytp, "me.on_you_are_hit_and_now_dead()")
    my.tp_set_text_a_or_an(mytp, "the")
    my.tp_set_text_description(mytp, "Trampled grass.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_FLOOR2)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    for t in tiles:
        my.tp_set_tile(mytp, t)

    my.tp_update(mytp, )


def init():
    tp_init(
        name="dry_grass_trampled",
        tiles=[
            "dry_grass_trampled.1",
            "dry_grass_trampled.2",
            "dry_grass_trampled.3",
            "dry_grass_trampled.4",
            "dry_grass_trampled.5",
            "dry_grass_trampled.6",
            "dry_grass_trampled.7",
            "dry_grass_trampled.8",
            "dry_grass_trampled.9",
            "dry_grass_trampled.10",
            "dry_grass_trampled.11",
            "dry_grass_trampled.12",
            "dry_grass_trampled.13",
            "dry_grass_trampled.14",
            "dry_grass_trampled.15",
            "dry_grass_trampled.16",
            "dry_grass_trampled.17",
            "dry_grass_trampled.18",
        ],
    )


init()
