//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/foliage_large.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_foliage_large {

static void tp_init(const std::string &name, const std::vector< std::string > &tiles);
static void init(void);

static void tp_init(const std::string &name, const std::vector< std::string > &tiles)
{
  Tpp self = my::tp_load(name, std::string("foliage"));
  self->collision_check_set(true);
  self->collision_hit_priority_set(1);
  self->collision_hit_priority_set(3);
  self->gfx_ascii_fg_color_spread_hue_set(10);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_oversized_and_on_floor_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_long_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_solid_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->health_initial_dice_set("1d20");
  self->is_able_to_amplify_footsteps_set(true);
  self->is_able_to_fall_set(true);
  self->is_always_hit_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_swamp_set(true);
  self->is_burnable_set(true);
  self->is_cursor_can_hover_over_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_foliage_set(true);
  self->is_hittable_set(true);
  self->is_interesting_set(true);
  self->is_light_blocker_for_monst_set(true);
  self->is_one_per_tile_set(true);
  self->is_shootable_set(true);
  self->noise_blocker_set(true);
  self->nutrition_dice_set("1d8");
  self->temperature_max_set(50);
  self->temperature_min_set(0);
  self->temperature_set(20);
  self->temperature_sensitive_set(true);
  self->temperature_sensitive_to_sudden_changes_set(true);
  self->text_a_or_an_set("the");
  self->text_description_long_set("Dense foliage. Monsters cannot see through these thick bushes. Use them for cover.");
  self->text_description_short_set("Dense foliage.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_FOLIAGE);
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "aries", .ascii_bg_col_name = "", .ascii_fg_col_name = "darkgreen"});
  }
}

static void init(void)
{
  tp_init("foliage_large", std::vector< std::string >{
      "foliage_large.1",
      "foliage_large.2",
      "foliage_large.3",
      "foliage_large.4",
      "foliage_large.5",
      "foliage_large.6",
      "foliage_large.7",
      "foliage_large.8",
      "foliage_large.9",
      "foliage_large.10",
      "foliage_large.11",
      "foliage_large.12",
      "foliage_large.13",
      "foliage_large.14",
      "foliage_large.15",
      "foliage_large.16",
    });
}

void module_init(void)
{
  init();
}

} // namespace mod_things_dungeon_foliage_large
