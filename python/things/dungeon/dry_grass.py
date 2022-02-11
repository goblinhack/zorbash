import my
import tp


def on_you_are_hit_and_now_dead(me, hitter, real_hitter, x, y, crit, damage):
    my.level_spawn_at_thing(me, "small_fire")
    my.level_place_at(me, "dry_grass_dead", x, y)
    my.thing_msg(me, "The dry grass burns!")


def tp_init(name, tiles=[]):
    mytp = tp.Tp(name, "dry grass")
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_shown_in_bg(mytp, True)
    my.tp_set_gfx_very_short_shadow_caster(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_burnable(mytp, True)
    my.tp_set_is_combustible(mytp, True)
    my.tp_set_is_cursor_can_hover_over(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_dry_grass(mytp, True)
    my.tp_set_is_interesting(mytp, True)
    my.tp_set_on_you_are_hit_and_now_dead_do(mytp, "dry_grass.on_you_are_hit_and_now_dead()")
    my.tp_set_text_a_or_an(mytp, "the")
    my.tp_set_text_description(mytp, "Parched grass.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_FLOOR2)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    for t in tiles:
        my.tp_set_tile(mytp, t)

    my.tp_update(mytp, )


def init():
    tp_init(
        name="dry_grass",
        tiles=[
            "dry_grass.1",
            "dry_grass.2",
            "dry_grass.3",
            "dry_grass.4",
            "dry_grass.5",
            "dry_grass.6",
            "dry_grass.7",
            "dry_grass.8",
            "dry_grass.9",
            "dry_grass.10",
            "dry_grass.11",
            "dry_grass.12",
            "dry_grass.13",
            "dry_grass.14",
            "dry_grass.15",
            "dry_grass.16",
            "dry_grass.17",
            "dry_grass.18",
        ],
    )


init()
