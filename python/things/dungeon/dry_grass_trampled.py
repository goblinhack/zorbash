import my
import tp


def on_you_are_hit_and_now_dead(me, hitter, real_hitter, x, y, crit, damage):
    if my.thing_is_fire(hitter):
        my.spawn_at_my_position(me, "small_fire")
        my.thing_msg(me, "The dry grass burns!")
    my.spawn_at(me, "dry_grass_dead", x, y)


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "trampled grass")
    # start sort marker
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.is_able_to_burn(self, True)
    my.is_able_to_fall(self, True)
    my.is_biome_dungeon(self, True)
    my.is_combustible(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_dry_grass_trampled(self, True)
    my.is_interesting(self, True)
    my.is_temperature_change_sensitive(self, True)
    my.is_temperature_sensitive(self, True)
    my.on_you_are_hit_and_now_dead_do(self, "me.on_you_are_hit_and_now_dead()")
    my.text_a_or_an(self, "the")
    my.text_short_description(self, "Trampled grass.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_FLOOR2)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="_", ascii_bg_col_name="", ascii_fg_col_name="darkgreen",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(
        name="is_dry_grass_trampled",
        tiles=[
            "is_dry_grass_trampled.1",
            "is_dry_grass_trampled.2",
            "is_dry_grass_trampled.3",
            "is_dry_grass_trampled.4",
            "is_dry_grass_trampled.5",
            "is_dry_grass_trampled.6",
            "is_dry_grass_trampled.7",
            "is_dry_grass_trampled.8",
            "is_dry_grass_trampled.9",
            "is_dry_grass_trampled.10",
            "is_dry_grass_trampled.11",
            "is_dry_grass_trampled.12",
            "is_dry_grass_trampled.13",
            "is_dry_grass_trampled.14",
            "is_dry_grass_trampled.15",
            "is_dry_grass_trampled.16",
            "is_dry_grass_trampled.17",
            "is_dry_grass_trampled.18",
        ],
    )


init()
