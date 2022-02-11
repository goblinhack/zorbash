import my
import tp


def tp_init(name, tiles=[]):
    mytp = tp.Tp(name, "webball")
    my.tp_set_collision_check(mytp, True)
    my.tp_set_collision_hit_priority(mytp, 3)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_health_initial_dice(mytp, "1d40")
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_attackable_by_monst(mytp, True)
    my.tp_set_is_attackable_by_player(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_burnable(mytp, True)
    my.tp_set_is_combustible(mytp, True)
    my.tp_set_is_cursor_can_hover_over(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_hittable(mytp, True)
    my.tp_set_is_interesting(mytp, True)  # So robot can see and break out
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_spiderweb(mytp, True)
    my.tp_set_is_sticky(mytp, True)
    my.tp_set_normal_placement_rules(mytp, False)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "Thick and sticky webball.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_IN_FRONT)  # so appears behind spider

    for t in tiles:
        my.tp_set_tile(mytp, t)

    my.tp_update(mytp, )


def init():
    tp_init(
        name="webball",
        tiles=[
            "webball.1",
            "webball.2",
            "webball.3",
            "webball.4",
        ],
    )


init()
