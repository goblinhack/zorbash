//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/food/turnip.py
//

#include "my_native.hpp"

namespace mod_things_food_turnip {

static void on_thrown(uint32_t owner, uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_thrown(uint32_t owner, uint32_t me, int x, int y)
{
  for (auto it : my::level_get_all(me, x, y)) {
    if (my::thing_is_interesting(it)) {
      if ((it == me)) {
        continue;
      }
      if ((it == owner)) {
        continue;
      }
      my::thing_hit_dmg_impact(owner, me, it, my::pcg_random_inclusive(1, 20), 0, true);
    }
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
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
  self->is_organic_set(true);
  self->is_throwable_set(true);
  self->is_thrown_as_a_weapon_set(true);
  self->item_height_set(4);
  self->item_width_set(4);
  self->noise_on_dropping_set(1);
  self->normal_placement_rules_set(true);
  self->nutrition_dice_set("10+1d15");
  self->on_thrown_do_set("me.on_thrown()");
  self->rarity_set(THING_RARITY_COMMON);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("turnips");
  self->text_apostrophize_set("turnip's");
  self->text_description_long_set("Grown locally and sustainably. In soil drenched with the blood of adventurers.");
  self->text_description_short_set("Organic battle turnip.");
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_ITEM);
  my::tile(self, {.tile = name, .ascii_fg_char = ";", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .is_hp_100_percent = true});
}

static void init(void)
{
  tp_init("turnip", "turnip", "turnip");
}

void module_init(void)
{
  native_register("turnip", "on_thrown", 4, [](const int64_t *a) -> NativeRet { (void) a; on_thrown((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  init();
}

} // namespace mod_things_food_turnip
