import my
import tp


def on_you_are_hit_and_now_dead(me, hitter, real_hitter, x, y, crit, damage):
    if my.thing_is_fire(hitter):
        my.level_spawn_at_thing(me, "small_fire")
        my.thing_msg(me, "The dry grass burns!")
    my.level_place_at(me, "dry_grass_dead", x, y)


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "trampled grass")
    my.gfx_ascii_mode_shown(self, True)
    my.gfx_shown_in_bg(self, True)
    my.is_able_to_fall(self, True)
    my.is_biome_dungeon(self, True)
    my.is_burnable(self, True)
    my.is_combustible(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_dry_grass(self, True)
    my.is_interesting(self, True)
    my.on_you_are_hit_and_now_dead_do(self, "me.on_you_are_hit_and_now_dead()")
    my.text_a_or_an(self, "the")
    my.text_description(self, "Trampled grass.")
    my.z_depth(self, my.MAP_DEPTH_FLOOR2)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)

    for t in tiles:
        my.tile(self,
                ascii_fg_char="-", ascii_bg_col_name="", ascii_fg_col_name="darkgreen",
                tile=t)

    my.tp_update(self)


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
