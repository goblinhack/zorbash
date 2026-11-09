//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/grass_wet_trampled.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_grass_wet_trampled {

static void tp_init(const std::string &name, const std::vector< std::string > &tiles);
static void init(void);

static void tp_init(const std::string &name, const std::vector< std::string > &tiles)
{
  Tpp self = my::tp_load(name, std::string("wet grass"));
  self->collision_hit_priority_set(1);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->is_able_to_dampen_footsteps_set(true);
  self->is_able_to_fall_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_swamp_set(true);
  self->is_cursor_can_hover_over_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_grass_set(true);
  self->is_grass_trampled_set(true);
  self->is_grass_wet_set(true);
  self->is_grass_wet_trampled_set(true);
  self->is_interesting_set(true);
  self->is_one_per_tile_set(true);
  self->nutrition_dice_set("1d4");
  self->temperature_max_set(50);
  self->temperature_min_set(0);
  self->temperature_sensitive_set(true);
  self->temperature_sensitive_to_sudden_changes_set(true);
  self->text_a_or_an_set("the");
  self->text_description_short_set("Trampled subterranean grass.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_FLOOR2);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "three_dots", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = 600});
  }
}

static void init(void)
{
  tp_init("grass_wet_trampled1", std::vector< std::string >{
      "grass_wet_trampled1.1",
      "grass_wet_trampled1.2",
      "grass_wet_trampled1.3",
      "grass_wet_trampled1.4",
      "grass_wet_trampled1.5",
      "grass_wet_trampled1.4",
      "grass_wet_trampled1.3",
      "grass_wet_trampled1.2",
    });
  tp_init("grass_wet_trampled2", std::vector< std::string >{
      "grass_wet_trampled2.1",
      "grass_wet_trampled2.2",
      "grass_wet_trampled2.3",
      "grass_wet_trampled2.4",
      "grass_wet_trampled2.5",
      "grass_wet_trampled2.4",
      "grass_wet_trampled2.3",
      "grass_wet_trampled2.2",
    });
  tp_init("grass_wet_trampled3", std::vector< std::string >{
      "grass_wet_trampled3.1",
      "grass_wet_trampled3.2",
      "grass_wet_trampled3.3",
      "grass_wet_trampled3.4",
      "grass_wet_trampled3.5",
      "grass_wet_trampled3.4",
      "grass_wet_trampled3.3",
      "grass_wet_trampled3.2",
    });
  tp_init("grass_wet_trampled4", std::vector< std::string >{
      "grass_wet_trampled4.1",
      "grass_wet_trampled4.2",
      "grass_wet_trampled4.3",
      "grass_wet_trampled4.4",
      "grass_wet_trampled4.5",
      "grass_wet_trampled4.4",
      "grass_wet_trampled4.3",
      "grass_wet_trampled4.2",
    });
  tp_init("grass_wet_trampled5", std::vector< std::string >{
      "grass_wet_trampled5.1",
      "grass_wet_trampled5.2",
      "grass_wet_trampled5.3",
      "grass_wet_trampled5.4",
      "grass_wet_trampled5.5",
      "grass_wet_trampled5.4",
      "grass_wet_trampled5.3",
      "grass_wet_trampled5.2",
    });
  tp_init("grass_wet_trampled6", std::vector< std::string >{
      "grass_wet_trampled6.1",
      "grass_wet_trampled6.2",
      "grass_wet_trampled6.3",
      "grass_wet_trampled6.4",
      "grass_wet_trampled6.5",
      "grass_wet_trampled6.4",
      "grass_wet_trampled6.3",
      "grass_wet_trampled6.2",
    });
}

void module_init(void)
{
  init();
}

} // namespace mod_things_dungeon_grass_wet_trampled
