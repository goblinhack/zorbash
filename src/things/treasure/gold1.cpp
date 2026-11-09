//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/treasure/gold1.py
//

#include "my_native.hpp"

namespace mod_things_treasure_gold1 {

static void gold_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void gold_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->collision_hit_priority_set(6);
  self->gfx_ascii_show_light_once_seen_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_bounce_always_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_shadow_very_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gold_value_dice_set("1");
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_auto_collect_item_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_biome_swamp_set(true);
  self->is_collectable_set(true);
  self->is_collected_as_gold_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_gold_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_metal_set(true);
  self->is_moveable_set(true);
  self->is_treasure_class_A_set(true);
  self->is_treasure_set(true);
  self->is_treasure_type_set(true);
  self->light_color_set("yellow");
  self->light_dist_set(1);
  self->normal_placement_rules_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("gold coins");
  self->text_apostrophize_set("gold coin's");
  self->text_description_long_set("A lonely gold coin.");
  self->text_description_short_set("A lonely gold coin.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "circle", .ascii_bg_col_name = "", .ascii_fg_col_name = "yellow", .delay_ms = 50, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "circle", .ascii_bg_col_name = "", .ascii_fg_col_name = "yellow", .delay_ms = 50, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "circle", .ascii_bg_col_name = "", .ascii_fg_col_name = "yellow", .delay_ms = 50, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "circle", .ascii_bg_col_name = "", .ascii_fg_col_name = "yellow", .delay_ms = 50, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "circle", .ascii_bg_col_name = "", .ascii_fg_col_name = "yellow", .delay_ms = 50, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "circle", .ascii_bg_col_name = "", .ascii_fg_col_name = "yellow", .delay_ms = 50, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".7"), .ascii_fg_char = "circle", .ascii_bg_col_name = "", .ascii_fg_col_name = "yellow", .delay_ms = 50, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".8"), .ascii_fg_char = "circle", .ascii_bg_col_name = "", .ascii_fg_col_name = "yellow", .delay_ms = 50, .is_dir_none = true});
}

static void init(void)
{
  gold_init("gold1", "lone gold coin", "lone gold coin");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_treasure_gold1
