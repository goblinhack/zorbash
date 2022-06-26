import my
import tp


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # start sort marker
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.is_ascend_dungeon(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_critical_to_level(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_interesting(self, True)
    my.light_color(self, "yellow")
    my.light_dist(self, 2)
    my.normal_placement_rules(self, True)
    my.text_a_or_an(self, "the")
    my.text_long_description(self, "This imposing doorway leads up to the previous level.")
    my.text_short_description(self, "%%fg=gold$The way up.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    delay = 1000
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gray20",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gray20",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gray20",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gray20",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gray20",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gray20",
            tile=name + ".6", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gray20",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gray20",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gray20",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gray20",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gray20",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gray20",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".1.open", delay_ms=delay, is_open=True)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".2.open", delay_ms=delay, is_open=True)

    my.tp_update(self)


def init():
    tp_init(name="entrance", text_long_name="dungeon entrance", text_short_name="entrance")


init()
