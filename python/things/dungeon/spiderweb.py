import my
import tp


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "spiderweb")
    # start sort marker
    my.collision_check(self, True)
    my.collision_hit_priority(self, 3)
    my.gfx_ascii_mode_shown(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
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
    my.normal_placement_rules(self, True)
    my.text_a_or_an(self, "a")
    my.text_long_description(self, "Free real estate. All welcome, says a small sign next to this web.")
    my.text_short_description(self, "Thick and sticky spiderweb.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_WEB)
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="cross", ascii_fg_col_name="white", tile=t)

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
