//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/items/brazier.py
//

#include "my_native.hpp"

namespace mod_things_items_brazier {

static void tp_init(const std::string &name, const std::string &text_long_name, const std::vector< std::string > &tiles);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name, const std::vector< std::string > &tiles)
{
  std::string color;
  std::vector< std::string > colors;
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name);
  self->chance_d1000_appearing_set(100);
  self->collision_hit_priority_set(2);
  self->dmg_chance_d1000_crush_set(0, 1000);
  self->dmg_crush_dice_set("1d6");
  self->gfx_ascii_show_light_once_seen_set(true);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_glows_set(true);
  self->gfx_pixelart_animated_can_hflip_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_flickers_set(true);
  self->gfx_pixelart_oversized_and_on_floor_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->is_able_to_fall_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_brazier_set(true);
  self->is_corpse_on_death_set(true);
  self->is_cursor_path_blocker_set(true);
  self->is_dead_on_shove_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_fire_set(true);
  self->is_floor_deco_set(true);
  self->is_heavy_set(true);
  self->is_immune_to_fire_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_moveable_set(true);
  self->is_obs_ai_set(true);
  self->is_obs_shooting_set(true);
  self->is_obs_throwing_set(true);
  self->is_one_per_tile_set(true);
  self->is_shovable_set(true);
  self->is_tickable_set(true);
  self->light_color_set("orange");
  self->light_dist_set(2);
  self->normal_placement_rules_set(true);
  self->spawn_on_shoved_set("fire");
  self->temperature_set(100);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("braziers");
  self->text_apostrophize_set("brazier's");
  self->text_description_short_set("A beacon of light in this blighted place.");
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BARREL);
  delay = 60;
  for (const auto &t : tiles) {
    colors = std::vector< std::string >{"yellow", "red", "orange", "orange", "yellow", "white"};
    color = my::random_choice(colors);
    my::tile(self, {.tile = t, .ascii_fg_char = "currency_sign", .ascii_bg_col_name = "", .ascii_fg_col_name = color, .delay_ms = delay});
  }
  my::tile(self, {.tile = (name + ".dead"), .ascii_fg_char = "currency_sign", .ascii_bg_col_name = "", .ascii_fg_col_name = "darkgray", .delay_ms = delay, .is_dead = true});
}

static void init(void)
{
  tp_init("brazier", "brazier", std::vector< std::string >{
      "brazier.1",
      "brazier.2",
      "brazier.3",
      "brazier.4",
      "brazier.5",
      "brazier.6",
      "brazier.7",
      "brazier.8",
      "brazier.9",
      "brazier.10",
      "brazier.11",
      "brazier.12",
      "brazier.13",
      "brazier.14",
      "brazier.15",
      "brazier.16",
      "brazier.17",
      "brazier.18",
      "brazier.19",
      "brazier.20",
      "brazier.21",
      "brazier.22",
      "brazier.23",
      "brazier.24",
      "brazier.25",
      "brazier.26",
      "brazier.27",
      "brazier.28",
      "brazier.29",
      "brazier.30",
      "brazier.31",
      "brazier.32",
      "brazier.33",
      "brazier.34",
      "brazier.35",
      "brazier.36",
      "brazier.37",
    });
}

void module_init(void)
{
  init();
}

} // namespace mod_things_items_brazier
