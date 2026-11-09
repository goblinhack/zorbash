//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/chasm.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_chasm {

static void chasm_init(const std::string &name, const std::string &text_long_name, const std::vector< std::string > &tiles);
static void init(void);

static void chasm_init(const std::string &name, const std::string &text_long_name, const std::vector< std::string > &tiles)
{
  Tpp self = my::tp_load(name, text_long_name);
  self->gfx_ascii_fg_color_spread_hue_set(20);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_chasm_set(true);
  self->is_cursor_can_hover_over_needs_confirm_set(true);
  self->is_cursor_path_hazard_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_hazard_set(true);
  self->is_obs_ai_set(true);
  self->is_one_per_tile_set(true);
  self->text_a_or_an_set("a");
  self->text_description_short_set("%%fg=red$A yawning chasm to the unknown below%%fg=reset$ (double click to jump into).");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_CHASM);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "four_dots", .ascii_bg_col_name = "black", .ascii_fg_col_name = "steelblue"});
}

static void init(void)
{
  chasm_init("chasm1", "yawning chasm", {});
}

void module_init(void)
{
  init();
}

} // namespace mod_things_dungeon_chasm
