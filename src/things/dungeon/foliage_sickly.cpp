//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/foliage_sickly.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_foliage_sickly {

static void tp_init(const std::string &name, const std::vector< std::string > &tiles);
static void init(void);

static void tp_init(const std::string &name, const std::vector< std::string > &tiles)
{
  Tpp self = my::tp_load(name, std::string("sickly foliage"));
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
  self->gfx_pixelart_submergible_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->health_initial_dice_set("1d3");
  self->is_able_to_amplify_footsteps_set(true);
  self->is_able_to_fall_set(true);
  self->is_always_hit_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_swamp_set(true);
  self->is_burnable_set(true);
  self->is_combustible_set(true);
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
  self->nutrition_dice_set("1d3");
  self->temperature_max_set(50);
  self->temperature_min_set(0);
  self->temperature_set(20);
  self->temperature_sensitive_set(true);
  self->temperature_sensitive_to_sudden_changes_set(true);
  self->text_a_or_an_set("the");
  self->text_description_long_set("Thick and sickly looking foliage and roots. Monsters cannot see through these thick bushes. Use them for cover.");
  self->text_description_short_set("Thick and sickly looking foliage and roots.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_FOLIAGE);
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "aries", .ascii_bg_col_name = "", .ascii_fg_col_name = "darkolivegreen"});
  }
}

static void init(void)
{
  tp_init("foliage_sickly", std::vector< std::string >{
      "foliage_sickly.1",
      "foliage_sickly.2",
      "foliage_sickly.3",
      "foliage_sickly.4",
      "foliage_sickly.5",
      "foliage_sickly.6",
      "foliage_sickly.7",
      "foliage_sickly.8",
      "foliage_sickly.9",
      "foliage_sickly.10",
      "foliage_sickly.11",
      "foliage_sickly.12",
      "foliage_sickly.13",
      "foliage_sickly.14",
      "foliage_sickly.15",
      "foliage_sickly.16",
      "foliage_sickly.17",
      "foliage_sickly.18",
      "foliage_sickly.19",
      "foliage_sickly.20",
      "foliage_sickly.21",
      "foliage_sickly.22",
      "foliage_sickly.23",
      "foliage_sickly.24",
      "foliage_sickly.25",
      "foliage_sickly.26",
      "foliage_sickly.27",
      "foliage_sickly.28",
      "foliage_sickly.29",
      "foliage_sickly.30",
      "foliage_sickly.31",
      "foliage_sickly.32",
    });
}

void module_init(void)
{
  init();
}

} // namespace mod_things_dungeon_foliage_sickly
