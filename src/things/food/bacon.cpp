//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/food/bacon.py
//

#include "my_native.hpp"

namespace mod_things_food_bacon {

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->chance_d10000_set_on_fire_set(500);
  self->collision_hit_priority_set(6);
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_able_to_freeze_set(true);
  self->is_bag_item_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_burnable_set(true);
  self->is_collectable_set(true);
  self->is_crushable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_food_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_meat_set(true);
  self->is_organic_set(true);
  self->is_throwable_set(true);
  self->item_height_set(4);
  self->item_width_set(4);
  self->noise_on_dropping_set(1);
  self->normal_placement_rules_set(true);
  self->nutrition_dice_set("10+1d30");
  self->rarity_set(THING_RARITY_COMMON);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("bacon");
  self->text_apostrophize_set("bacon's");
  self->text_description_long_set("Some crunchy meat stuff that might be bacon");
  self->text_description_short_set("Bacon maybe.");
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_ITEM);
  my::tile(self, {.tile = name, .ascii_fg_char = ";", .ascii_bg_col_name = "", .ascii_fg_col_name = "brown", .is_hp_100_percent = true});
}

static void init(void)
{
  tp_init("bacon", "bacon", "bacon");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_food_bacon
