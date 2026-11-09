//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/basalt.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_basalt {

static void basalt_init(const std::string &name, const std::string &text_long_name, const std::vector< std::string > &tiles);
static void init(void);

static void basalt_init(const std::string &name, const std::string &text_long_name, const std::vector< std::string > &tiles)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name);
  self->collision_check_set(true);
  self->collision_hit_priority_set(100);
  self->gfx_ascii_bg_color_spread_hue_set(30);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->is_able_to_fall_set(true);
  self->is_basalt_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_lava_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_obs_ai_set(true);
  self->is_one_per_tile_set(true);
  self->is_tickable_set(true);
  self->text_a_or_an_set("");
  self->text_description_short_set("Warm to the touch basalt.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_LIQUID);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  delay = 200;
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "L", .ascii_bg_col_name = "black", .ascii_fg_col_name = "white", .delay_ms = delay});
  }
}

static void init(void)
{
  basalt_init("basalt", "basalt", std::vector< std::string >{
      "lava.1",
      "lava.2",
      "lava.3",
      "lava.4",
      "lava.5",
      "lava.6",
      "lava.7",
      "lava.8",
      "lava.9",
      "lava.10",
      "lava.11",
      "lava.12",
      "lava.13",
      "lava.14",
      "lava.15",
      "lava.16",
    });
}

void module_init(void)
{
  init();
}

} // namespace mod_things_dungeon_basalt
