//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/treasure/spellbook4.py
//

#include "my_native.hpp"

namespace mod_things_treasure_spellbook4 {

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->charge_count_set(4);
  self->collision_hit_priority_set(5);
  self->environ_dislikes_fire_set(10);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gold_value_dice_set("2000");
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_bag_item_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_biome_swamp_set(true);
  self->is_collectable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_droppable_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_moveable_set(true);
  self->is_spellbook_set(true);
  self->is_throwable_set(true);
  self->is_treasure_class_C_set(true);
  self->is_treasure_set(true);
  self->is_treasure_type_set(true);
  self->is_usable_set(true);
  self->item_height_set(5);
  self->item_width_set(5);
  self->noise_on_dropping_set(80);
  self->normal_placement_rules_set(true);
  self->rarity_set(THING_RARITY_VERY_RARE);
  self->stat_luck_bonus_set((-4));
  self->text_a_or_an_set("a");
  self->text_pluralize_set("spellbooks");
  self->text_apostrophize_set("spellbook's");
  self->text_description_long2_set("This book is emblazoned with a skull on its cover and the ink inside is a disconcerting red color. This book is very rare. Use its contents wisely.");
  self->text_description_long_set("Read this spellbook to learn some new spells into your brain matter thing.");
  self->text_description_short_set("A skull emblazoned dusty spellbook.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = name, .ascii_fg_char = "diamond_solid", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = 100});
}

static void init(void)
{
  tp_init("spellbook4", "spellbook", "spellbook");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_treasure_spellbook4
