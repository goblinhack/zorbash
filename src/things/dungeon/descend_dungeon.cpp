//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/descend_dungeon.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_descend_dungeon {

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->gfx_ascii_show_light_once_seen_set(true);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_oversized_and_on_floor_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->gfx_pixelart_show_square_outlined_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_biome_swamp_set(true);
  self->is_critical_to_level_set(true);
  self->is_cursor_can_hover_over_set(true);
  self->is_descend_dungeon_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_interesting_set(true);
  self->is_obs_spawn_monst_set(true);
  self->is_one_per_tile_set(true);
  self->light_color_set("white");
  self->light_dist_set(1);
  self->normal_placement_rules_set(true);
  self->text_a_or_an_set("the");
  self->text_description_long_set("This dark entrance leads to the next level of the dungeon.");
  self->text_description_short_set("%%fg=gold$The way down.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  delay = 50;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "omega", .ascii_bg_col_name = "", .ascii_fg_col_name = "gold", .delay_ms = delay, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "omega", .ascii_bg_col_name = "", .ascii_fg_col_name = "gold", .delay_ms = delay, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "omega", .ascii_bg_col_name = "", .ascii_fg_col_name = "gold", .delay_ms = delay, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "omega", .ascii_bg_col_name = "", .ascii_fg_col_name = "gold", .delay_ms = delay, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "omega", .ascii_bg_col_name = "", .ascii_fg_col_name = "gold", .delay_ms = delay, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "omega", .ascii_bg_col_name = "", .ascii_fg_col_name = "gold", .delay_ms = delay, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".7"), .ascii_fg_char = "omega", .ascii_bg_col_name = "", .ascii_fg_col_name = "gold", .delay_ms = delay, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".8"), .ascii_fg_char = "omega", .ascii_bg_col_name = "", .ascii_fg_col_name = "gold", .delay_ms = delay, .is_dir_none = true});
}

static void init(void)
{
  tp_init("exit1", "dungeon exit", "exit");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_dungeon_descend_dungeon
