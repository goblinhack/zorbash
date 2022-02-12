import my
import tp


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "spiderweb")
    my.collision_check(self, True)
    my.collision_hit_priority(self, 3)
    my.health_initial_dice(self, "1d20")
    my.is_able_to_fall(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_burnable(self, True)
    my.is_combustible(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_hazard(self, True)
    my.is_hittable(self, True)
    my.is_interesting(self, True)  # So robot can see and break out
    my.is_loggable(self, True)
    my.is_spiderweb(self, True)
    my.is_sticky(self, True)
    my.long_text_description(self, "Free real estate. All welcome, says a small sign next to this web.")
    my.normal_placement_rules(self, True)
    my.text_a_or_an(self, "a")
    my.text_description(self, "Thick and sticky spiderweb.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_IN_FRONT)  # so appears behind spider

    for t in tiles:
        my.tile(self, t)

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
