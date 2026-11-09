//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/items/block_of_crystal.py
//

#include "my_native.hpp"

namespace mod_things_items_block_of_crystal {

static void on_death(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_death(uint32_t me, int x, int y)
{
  my::spawn_at_my_position(me, "crystal_explosion");
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  Tpp self = my::tp_load(name, text_long_name);
  self->chance_d1000_appearing_set(10);
  self->collision_check_set(true);
  self->collision_hit_priority_set(100);
  self->gfx_ascii_animated_set(true);
  self->gfx_ascii_bg_color_spread_blue_set(40);
  self->gfx_ascii_bg_color_spread_green_set(40);
  self->gfx_ascii_color_is_animated_set(true);
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_oversized_and_on_floor_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->health_initial_dice_set("40+1d20");
  self->is_able_to_fall_set(true);
  self->is_always_hit_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_block_of_crystal_set(true);
  self->is_brittle_set(true);
  self->is_cursor_can_hover_over_set(true);
  self->is_cursor_path_blocker_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_hittable_set(true);
  self->is_immune_to_cold_set(true);
  self->is_immune_to_fire_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_obs_ai_set(true);
  self->is_obs_jump_end_set(true);
  self->is_obs_jumping_set(true);
  self->is_obs_shooting_set(true);
  self->is_obs_shoving_set(true);
  self->is_obs_spawn_monst_set(true);
  self->is_obs_spell_casting_set(true);
  self->is_obs_throwing_set(true);
  self->is_one_per_tile_set(true);
  self->is_reflective_set(true);
  self->is_shootable_set(true);
  self->is_tickable_set(true);
  self->is_very_hard_set(true);
  self->is_very_heavy_set(true);
  self->light_color_set("white");
  self->light_dist_set(1);
  self->noise_blocker_set(true);
  self->normal_placement_rules_set(true);
  self->on_death_do_set("me.on_death()");
  self->temperature_max_set(300);
  self->temperature_set(10);
  self->temperature_sensitive_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("blocks of crystals");
  self->text_apostrophize_set("block of crystal's");
  self->text_description_short_set("A block of shining crystal.");
  self->thing_size_set(THING_SIZE_GIANT);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_EFFECT);
  my::tile(self, {.tile = "block_of_crystal.1", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.2", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.3", .ascii_fg_char = "middle_dot", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.4", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.5", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.6", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.7", .ascii_fg_char = "+", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.8", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.9", .ascii_fg_char = "+", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.10", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.11", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.12", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.13", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.14", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.15", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.16", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.17", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.18", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.19", .ascii_fg_char = "+", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.20", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.21", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.22", .ascii_fg_char = "middle_dot", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.23", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.24", .ascii_fg_char = "+", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.25", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.26", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.27", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.28", .ascii_fg_char = "+", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.29", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.30", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.31", .ascii_fg_char = "+", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.32", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.33", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.34", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.35", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.36", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.37", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.38", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.39", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.40", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.41", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.42", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.43", .ascii_fg_char = "middle_dot", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.44", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.45", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.46", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.47", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.48", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.49", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.50", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.51", .ascii_fg_char = "+", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.52", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.53", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.54", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.55", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.56", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.57", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.58", .ascii_fg_char = "+", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.59", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.60", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.61", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.62", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.63", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
  my::tile(self, {.tile = "block_of_crystal.64", .ascii_fg_char = "+", .ascii_bg_char = "block", .ascii_bg_col_name = "gray70"});
}

static void init(void)
{
  tp_init("block_of_crystal", "block of crystal");
}

void module_init(void)
{
  native_register("block_of_crystal", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_items_block_of_crystal
