//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/items/four_leaf_clover.py
//

#include "my_native.hpp"

namespace mod_things_items_four_leaf_clover {

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->chance_d10000_enchanted_set(20);
  self->chance_d10000_set_on_fire_set(5000);
  self->chance_d1000_appearing_set(10);
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_bag_item_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_biome_swamp_set(true);
  self->is_collectable_set(true);
  self->is_crushable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_droppable_set(true);
  self->is_enchantable_set(true);
  self->is_food_set(true);
  self->is_four_leaf_clover_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_moveable_set(true);
  self->is_treasure_class_B_set(true);
  self->is_treasure_set(true);
  self->is_treasure_type_set(true);
  self->item_height_set(2);
  self->item_width_set(2);
  self->noise_on_dropping_set(25);
  self->normal_placement_rules_set(true);
  self->nutrition_dice_set("1d4");
  self->rarity_set(THING_RARITY_VERY_RARE);
  self->stat_luck_bonus_set(4);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("clover");
  self->text_apostrophize_set("four leaf clover's");
  self->text_description_enchant_set("+1 LUCK");
  self->text_description_long_set("Nutritious and lucky!");
  self->text_description_short_set("A four leaf clover.");
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = name, .ascii_fg_char = "*", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = 100});
}

static void init(void)
{
  tp_init("four_leaf_clover", "four leaf clover", "four leaf clover");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_items_four_leaf_clover
