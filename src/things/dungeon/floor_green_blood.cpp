//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/floor_green_blood.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_floor_green_blood {

static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  std::string text_short_name;
  text_short_name = std::string("pool of blood");
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->collision_hit_priority_set(2);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_can_hflip_set(true);
  self->gfx_pixelart_animated_can_vflip_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->health_initial_dice_set("1d4");
  self->is_able_to_fall_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_flat_set(true);
  self->is_green_blood_set(true);
  self->is_interesting_set(true);
  self->is_one_per_tile_set(true);
  self->is_removable_if_out_of_slots_set(true);
  self->normal_placement_rules_set(true);
  self->nutrition_dice_set("1d4");
  self->text_a_or_an_set("a");
  self->text_description_short_set("An artwork comprised mainly of green blood.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_FLOOR2);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = (name + ".100"), .ascii_fg_char = "three_dots", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .is_hp_100_percent = true});
  my::tile(self, {.tile = (name + ".75"), .ascii_fg_char = "three_dots", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .is_hp_75_percent = true});
  my::tile(self, {.tile = (name + ".50"), .ascii_fg_char = "three_dots", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .is_hp_50_percent = true});
  my::tile(self, {.tile = (name + ".25"), .ascii_fg_char = "three_dots", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .is_hp_25_percent = true});
}

static void init(void)
{
  tp_init("floor_green_blood1", "pool of fluorescent blood");
  tp_init("floor_green_blood2", "pool of fluorescent blood");
  tp_init("floor_green_blood3", "pool of fluorescent blood with bits in it");
  tp_init("floor_green_blood4", "pool of fluorescent blood");
  tp_init("floor_green_blood5", "pool of yucky fluorescent blood");
  tp_init("floor_green_blood6", "pool of icky fluorescent blood");
  tp_init("floor_green_blood7", "pool of fluorescent blood");
  tp_init("floor_green_blood8", "pool of fluorescent blood");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_dungeon_floor_green_blood
