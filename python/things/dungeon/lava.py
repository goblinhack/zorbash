import my
import tp


def on_idle(me, x, y):
    my.spawn_at_my_position(me, "smoke")


def on_death(me, x, y):
    my.spawn_at_my_position(me, "basalt")


def lava_init(name, text_long_name, tiles=[]):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.collision_hit_priority(self, 100)
    my.dmg_chance_d1000_fire(self, 0, 1000)
    my.dmg_fire_dice(self, "1d12+6")
    my.dmg_nat_att_type(self, "burn")
    my.gfx_ascii_animated(self, True)
    my.gfx_ascii_bg_color_spread_green(self, 30)
    my.gfx_ascii_bg_color_spread_red(self, 30)
    my.gfx_ascii_color_fg_unchanged_by_lights(self, True)
    my.gfx_ascii_color_is_animated(self, True)
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_glows(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.is_able_to_fall(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_lava(self, True)
    my.is_cursor_can_hover_over_needs_confirm(self, True)
    my.is_cursor_path_hazard(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_flat(self, True)
    my.is_hazard(self, True)
    my.is_interesting(self, True)
    my.is_lava(self, True)
    my.is_obs_ai(self, True)
    my.is_one_per_tile(self, True)
    my.is_tickable(self, True)
    my.light_color(self, "red")
    my.light_dist(self, 2)
    my.on_death_do(self, "me.on_death()")
    my.on_idle_tick_freq_dice(self, "1d200+50:me.on_idle()")
    my.temperature_min(self, 0)
    my.temperature(self, 800)
    my.temperature_sensitive(self, True)
    my.text_a_or_an(self, "")
    my.text_description_short(self, "%%fg=orange$Freshly scented lava%%fg=reset$ (double click to move onto).")
    my.text_hits(self, "tickles")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_LIQUID)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    delay = 150
    for t in tiles:
        my.tile(self,
                ascii_fg_char="~", ascii_bg_col_name="orange", ascii_fg_col_name="orange",
                tile=t, delay_ms=delay)

    my.tp_update(self)


def init():
    lava_init(
        name="lava",
        text_long_name="molten lava",
        tiles=[
            "lava.1",
            "lava.2",
            "lava.3",
            "lava.4",
            "lava.5",
            "lava.6",
            "lava.7",
            "lava.8",
            "lava.9",
            "lava.10",
            "lava.11",
            "lava.12",
            "lava.13",
            "lava.14",
            "lava.15",
            "lava.16",
        ],
    )


init()
