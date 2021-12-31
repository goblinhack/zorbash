import my
import tp


def tp_init(name, tiles=[]):
    mytp = tp.Tp(name, "webball")
    mytp.set_collision_check(True)
    mytp.set_collision_hit_priority(2)
    mytp.set_health_initial_dice("1d40")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_burnable(True)
    mytp.set_is_combustible(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_is_cursor_can_hover_over(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_hittable(True)
    mytp.set_is_interesting(True)  # So robot can see and break out
    mytp.set_is_loggable(True)
    mytp.set_is_spiderweb(True)
    mytp.set_is_sticky(True)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("Thick and sticky webball.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_IN_FRONT)  # so appears behind spider

    for t in tiles:
        mytp.set_tile(t)

    mytp.update()


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
