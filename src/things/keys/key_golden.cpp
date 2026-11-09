//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/keys/key_golden.py
//

#include "my_native.hpp"

namespace mod_things_keys_key_golden {

static void key_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void key_init(const std::string &name, const std::string &text_long_name)
{
  Tpp self = my::tp_load(name, text_long_name);
  self->chance_d1000_appearing_set(2);
  self->chance_d1000_melting_set(20);
  self->collision_hit_priority_set(6);
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_bounce_always_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gold_value_dice_set("100");
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_able_to_melt_set(true);
  self->is_auto_collect_item_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_biome_swamp_set(true);
  self->is_collectable_set(true);
  self->is_collected_as_keys_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_key_set(10);
  self->is_loggable_set(true);
  self->is_metal_set(true);
  self->is_moveable_set(true);
  self->light_color_set("yellow");
  self->light_dist_set(2);
  self->normal_placement_rules_set(true);
  self->rarity_set(THING_RARITY_RARE);
  self->text_a_or_an_set("an");
  self->text_pluralize_set("golden keys");
  self->text_apostrophize_set("golden key's");
  self->text_description_long_set("A magical golden key that trans-mutates into ten keys upon carrying.");
  self->text_description_short_set("A magical golden key.");
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = name, .ascii_fg_char = "-", .ascii_bg_col_name = "", .ascii_fg_col_name = "gold"});
}

static void init(void)
{
  key_init("key_golden", "golden key");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_keys_key_golden
