import my
import tp


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "webball")
    my.tp_set_collision_check(self, True)
    my.tp_set_collision_hit_priority(self, 3)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_health_initial_dice(self, "1d40")
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_attackable_by_monst(self, True)
    my.tp_set_is_attackable_by_player(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_burnable(self, True)
    my.tp_set_is_combustible(self, True)
    my.tp_set_is_cursor_can_hover_over(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_hittable(self, True)
    my.tp_set_is_interesting(self, True)  # So robot can see and break out
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_spiderweb(self, True)
    my.tp_set_is_sticky(self, True)
    my.tp_set_normal_placement_rules(self, False)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "Thick and sticky webball.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_IN_FRONT)  # so appears behind spider

    for t in tiles:
        my.tp_set_tile(self, t)

    my.tp_update(self)


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
