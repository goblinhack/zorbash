import my
import tp


def on_you_are_hit_and_now_dead(me, hitter, real_hitter, x, y, crit, damage):
    if my.thing_is_fire(hitter):
        my.level_spawn_at_thing(me, "small_fire")
        my.thing_msg(me, "The dry grass burns!")
    my.level_place_at(me, "dry_grass_dead", x, y)


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "dry grass")
    my.gfx_ascii_mode_shown(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_shadow_very_short(self, True)
    my.gfx_shown_in_bg(self, True)
    my.is_able_to_fall(self, True)
    my.is_biome_dungeon(self, True)
    my.is_burnable(self, True)
    my.is_combustible(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_dry_grass(self, True)
    my.is_interesting(self, True)
    my.on_you_are_hit_and_now_dead_do(self, "dry_grass.on_you_are_hit_and_now_dead()")
    my.text_a_or_an(self, "the")
    my.text_description(self, "Parched grass.")
    my.z_depth(self, my.MAP_DEPTH_FLOOR2)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)

    for t in tiles:
        my.tile(self, delay_ms=300,
                ascii_fg_char="middle_dot", ascii_bg_col_name="", ascii_fg_col_name="darkgreen",
                tile=t)

    my.tp_update(self)


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
