//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/grass_dry_dead.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_grass_dry_dead {

static void tp_init(const std::string &name, const std::vector< std::string > &tiles);
static void init(void);

static void tp_init(const std::string &name, const std::vector< std::string > &tiles)
{
  Tpp self = my::tp_load(name, std::string("dead grass"));
  self->collision_hit_priority_set(1);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->is_able_to_amplify_footsteps_set(true);
  self->is_able_to_fall_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_swamp_set(true);
  self->is_cursor_can_hover_over_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_grass_dead_set(true);
  self->is_grass_dry_set(true);
  self->is_grass_set(true);
  self->is_interesting_set(true);
  self->is_one_per_tile_set(true);
  self->nutrition_dice_set("1d2");
  self->temperature_max_set(50);
  self->temperature_min_set(0);
  self->temperature_sensitive_set(true);
  self->temperature_sensitive_to_sudden_changes_set(true);
  self->text_a_or_an_set("the");
  self->text_description_short_set("Dead grass.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_FLOOR2);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "three_dots", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray40"});
  }
}

static void init(void)
{
  tp_init("grass_dry_dead", std::vector< std::string >{
      "grass_dry_dead.1",
      "grass_dry_dead.2",
      "grass_dry_dead.3",
      "grass_dry_dead.4",
      "grass_dry_dead.5",
      "grass_dry_dead.6",
      "grass_dry_dead.7",
      "grass_dry_dead.8",
      "grass_dry_dead.9",
      "grass_dry_dead.10",
      "grass_dry_dead.11",
      "grass_dry_dead.12",
      "grass_dry_dead.13",
      "grass_dry_dead.14",
      "grass_dry_dead.15",
      "grass_dry_dead.16",
      "grass_dry_dead.17",
      "grass_dry_dead.18",
    });
}

void module_init(void)
{
  init();
}

} // namespace mod_things_dungeon_grass_dry_dead
