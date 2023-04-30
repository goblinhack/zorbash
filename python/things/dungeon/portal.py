import my
import tp


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.collision_check(self, True)
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_oversized_and_on_floor(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.gfx_pixelart_show_square_outlined(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.is_attackable_by_magic(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_flooded(self, True)
    my.is_biome_ice(self, True)
    my.is_biome_lava(self, True)
    my.is_biome_swamp(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_interesting(self, True)
    my.is_magical(self, True)
    my.is_obs_shooting(self, True)
    my.is_obs_spawn_monst(self, True)
    my.is_obs_throwing(self, True)
    my.is_portal(self, True)
    my.light_color(self, "purple")
    my.light_dist(self, 3)
    my.normal_placement_rules(self, True)
    my.text_a_or_an(self, "the")
    my.text_description_long(self, "A magical portal to places undreamed of. Depends how boring your dreams are.")
    my.text_description_short(self, "A magical portal.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    delay = 100
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="purple",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="purple",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="purple",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="purple",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="purple",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="purple",
            tile=name + ".6", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="purple",
            tile=name + ".7", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="purple",
            tile=name + ".8", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="purple",
            tile=name + ".9", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="purple",
            tile=name + ".10", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="purple",
            tile=name + ".11", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="purple",
            tile=name + ".12", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="purple",
            tile=name + ".13", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="purple",
            tile=name + ".14", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="purple",
            tile=name + ".15", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="purple",
            tile=name + ".16", delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="portal", text_long_name="magic portal", text_short_name="magic portal")


init()
