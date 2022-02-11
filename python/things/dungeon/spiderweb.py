import my
import tp


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "spiderweb")
    my.tp_set_collision_check(self, True)
    my.tp_set_collision_hit_priority(self, 3)
    my.tp_set_health_initial_dice(self, "1d20")
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_attackable_by_monst(self, True)
    my.tp_set_is_attackable_by_player(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_burnable(self, True)
    my.tp_set_is_combustible(self, True)
    my.tp_set_is_cursor_can_hover_over(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_hazard(self, True)
    my.tp_set_is_hittable(self, True)
    my.tp_set_is_interesting(self, True)  # So robot can see and break out
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_spiderweb(self, True)
    my.tp_set_is_sticky(self, True)
    my.tp_set_long_text_description(self, "Free real estate. All welcome, says a small sign next to this web.")
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "Thick and sticky spiderweb.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_IN_FRONT)  # so appears behind spider

    for t in tiles:
        my.tp_set_tile(self, t)

    my.tp_update(self)


def init():
    tp_init(
        name="spiderweb",
        tiles=[
            "spiderweb.1",
            "spiderweb.2",
            "spiderweb.3",
            "spiderweb.4",
            "spiderweb.5",
            "spiderweb.6",
        ],
    )


init()
