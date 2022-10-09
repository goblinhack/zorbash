import my
import tp


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_critical_to_level(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_descend_dungeon(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_interesting(self, True)
    my.light_color(self, "white")
    my.light_dist(self, 2)
    my.normal_placement_rules(self, True)
    my.text_a_or_an(self, "the")
    my.text_long_description(self, "This dark entrance leads to the next level of the dungeon.")
    my.text_short_description(self, "%%fg=gold$The way down.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    delay = 50
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile=name + ".1", is_dir_none=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile=name + ".2", is_dir_none=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile=name + ".3", is_dir_none=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile=name + ".4", is_dir_none=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile=name + ".5", is_dir_none=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile=name + ".6", is_dir_none=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile=name + ".7", is_dir_none=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile=name + ".8", is_dir_none=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="exit1", text_long_name="dungeon exit", text_short_name="exit")


init()
