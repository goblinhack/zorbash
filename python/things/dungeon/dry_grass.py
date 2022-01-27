import my
import tp


def on_you_are_hit_and_now_dead(me, hitter, real_hitter, x, y, crit, damage):
    my.level_spawn_at_thing(me, "small_fire")
    my.level_place_at(me, "dry_grass_dead", x, y)
    my.thing_msg(me, "The dry grass burns!")


def tp_init(name, tiles=[]):
    mytp = tp.Tp(name, "dry grass")
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_shown_in_bg(True)
    mytp.set_gfx_very_short_shadow_caster(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_biome_dungeon(True)
    mytp.set_is_burnable(True)
    mytp.set_is_combustible(True)
    mytp.set_is_cursor_can_hover_over(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_dry_grass(True)
    mytp.set_is_interesting(True)
    mytp.set_on_you_are_hit_and_now_dead_do("dry_grass.on_you_are_hit_and_now_dead()")
    mytp.set_text_a_or_an("the")
    mytp.set_text_description("Parched grass.")
    mytp.set_z_depth(my.MAP_DEPTH_FLOOR2)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    for t in tiles:
        mytp.set_tile(t)

    mytp.update()


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
