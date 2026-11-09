//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/deep_water.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_deep_water {

static void tp_init(const std::string &name, const std::string &text_long_name, const std::vector< std::string > &tiles);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name, const std::vector< std::string > &tiles)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name);
  self->dmg_chance_d1000_water_set(0, 1000);
  self->dmg_water_dice_set("1d6+1");
  self->environ_dislikes_fire_set(1);
  self->gfx_ascii_animated_set(true);
  self->gfx_ascii_bg_color_spread_green_set(20);
  self->gfx_ascii_color_is_animated_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->gfx_water_set(true);
  self->is_able_to_fall_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_swamp_set(true);
  self->is_deep_water_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_flat_set(true);
  self->is_hazard_set(true);
  self->is_interesting_set(true);
  self->is_obs_ai_set(true);
  self->is_one_per_tile_set(true);
  self->text_a_or_an_set("the");
  self->text_description_short_set("A pool of deep dank water, with things in it.");
  self->z_depth_set(MAP_DEPTH_LIQUID);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  delay = 3000;
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "~", .ascii_bg_col_name = "deepwater", .ascii_fg_col_name = "water", .delay_ms = delay});
  }
}

static void init(void)
{
  tp_init("deep_water", "deep water", std::vector< std::string >{
      "deep_water1.1",
      "deep_water1.2",
      "deep_water1.3",
      "deep_water1.4",
      "deep_water1.5",
      "deep_water1.6",
      "deep_water1.7",
      "deep_water1.8",
      "deep_water1.9",
      "deep_water1.10",
      "deep_water1.11",
      "deep_water1.12",
      "deep_water1.13",
      "deep_water1.14",
      "deep_water1.15",
      "deep_water1.16",
    });
}

void module_init(void)
{
  init();
}

} // namespace mod_things_dungeon_deep_water
