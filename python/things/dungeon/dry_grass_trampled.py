import my
import tp


def on_you_are_hit_and_now_dead(me, hitter, real_hitter, x, y, crit, damage):
    my.level_spawn_at_thing(me, "small_fire")
    my.level_place_at(me, "dry_grass_dead", x, y)
    my.topcon("The dry grass burns!")


def tp_init(name, tiles=[]):
    mytp = tp.Tp(name, "trampled grass")
    mytp.set_gfx_shown_in_bg(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_burnable(True)
    mytp.set_is_combustible(True)
    mytp.set_is_cursor_can_hover_over(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_dry_grass(True)
    mytp.set_is_interesting(True)
    mytp.set_on_you_are_hit_and_now_dead_do("me.on_you_are_hit_and_now_dead()")
    mytp.set_text_a_or_an("the")
    mytp.set_text_description("Trampled grass.")
    mytp.set_z_depth(my.MAP_DEPTH_FLOOR2)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    for t in tiles:
        mytp.set_tile(t)

    mytp.update()


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
