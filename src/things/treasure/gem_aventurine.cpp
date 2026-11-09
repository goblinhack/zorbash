//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/treasure/gem_aventurine.py
//

#include "my_native.hpp"

namespace mod_things_treasure_gem_aventurine {

static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  Tpp self = my::tp_load(name, text_long_name);
  self->collision_hit_priority_set(6);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gold_value_dice_set("1d50");
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_collectable_set(true);
  self->is_collected_as_gold_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_stone_set(true);
  self->is_treasure_class_B_set(true);
  self->is_treasure_set(true);
  self->is_treasure_type_set(true);
  self->normal_placement_rules_set(true);
  self->rarity_set(THING_RARITY_COMMON);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("aventurine");
  self->text_apostrophize_set("aventurine's");
  self->text_description_long_set("If you are need of luck, a(d)venturine is the stone for you. It has a few drops of blood on it, ignore those. You will be more lucky.");
  self->text_description_short_set("Some a(d)venturine, the luckiest stone.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "diamond", .ascii_bg_col_name = "", .ascii_fg_col_name = "forestgreen", .delay_ms = 2000, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "diamond", .ascii_bg_col_name = "", .ascii_fg_col_name = "forestgreen", .delay_ms = 50, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "diamond", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = 50, .is_dir_none = true});
}

static void init(void)
{
  tp_init("gem_aventurine", "aventurine");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_treasure_gem_aventurine
