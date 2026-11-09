//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/water.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_water {

static void tp_init(const std::string &name, const std::string &text_long_name, const std::vector< std::string > &tiles);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name, const std::vector< std::string > &tiles)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name);
  self->dmg_chance_d1000_water_set(0, 1000);
  self->dmg_water_dice_set("1d4+1");
  self->environ_dislikes_fire_set(1);
  self->gfx_ascii_animated_set(true);
  self->gfx_ascii_bg_color_spread_blue_set(40);
  self->gfx_ascii_bg_color_spread_green_set(40);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->gfx_water_set(true);
  self->is_able_to_amplify_footsteps_set(true);
  self->is_able_to_fall_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_swamp_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_flat_set(true);
  self->is_interesting_set(true);
  self->is_obs_ai_set(true);
  self->is_one_per_tile_set(true);
  self->is_shallow_water_set(true);
  self->text_a_or_an_set("the");
  self->text_description_short_set("Some shallow water.");
  self->z_depth_set(MAP_DEPTH_LIQUID);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  delay = 3000;
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "middle_dot", .ascii_bg_col_name = "water", .ascii_fg_col_name = "deepwater", .delay_ms = delay});
  }
}

static void init(void)
{
  tp_init("water", "water", std::vector< std::string >{
      "water.1",
      "water.2",
      "water.3",
      "water.4",
      "water.5",
      "water.6",
      "water.7",
      "water.8",
      "water.9",
      "water.10",
      "water.11",
      "water.12",
      "water.13",
      "water.14",
      "water.15",
      "water.16",
      "water.17",
      "water.18",
      "water.19",
      "water.20",
      "water.21",
      "water.22",
      "water.23",
      "water.24",
      "water.25",
      "water.26",
      "water.27",
      "water.28",
      "water.29",
      "water.30",
      "water.31",
      "water.32",
    });
}

void module_init(void)
{
  init();
}

} // namespace mod_things_dungeon_water
