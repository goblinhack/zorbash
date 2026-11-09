//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/food/frog.py
//

#include "my_native.hpp"

namespace mod_things_food_frog {

static void on_eaten(uint32_t eater, uint32_t item, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_eaten(uint32_t eater, uint32_t item, int x, int y)
{
  if ((my::thing_poisoned_amount_get(eater) != 0)) {
    my::thing_sound_play_channel(eater, CHANNEL_WEAPON, "potion");
    my::thing_poisoned_amount_set(eater, 0);
    if (((eater != 0) && my::thing_is_player(eater))) {
      my::thing_msg(eater, "%%fg=pink$That frog hit the spot! You feel much better!%%fg=reset$");
    }
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->chance_d1000_melting_set(500);
  self->collision_hit_priority_set(6);
  self->environ_dislikes_fire_set(100);
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_bounce_always_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_able_to_freeze_set(true);
  self->is_able_to_melt_set(true);
  self->is_bag_item_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
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
  self->item_height_set(3);
  self->item_width_set(3);
  self->noise_on_dropping_set(1);
  self->normal_placement_rules_set(true);
  self->nutrition_dice_set("50+1d100");
  self->on_eaten_do_set("me.on_eaten()");
  self->rarity_set(THING_RARITY_UNCOMMON);
  self->temperature_max_set(25);
  self->temperature_set(20);
  self->temperature_sensitive_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("chocolate frogs");
  self->text_apostrophize_set("chocolate frog's");
  self->text_description_long_set("The food of the Gods. May seem out of place in a dungeon and you'd be correct. It is rumored a helpful god left them here for brave adventurers to assist them on their path. Often found in a purple wrapper. Almost looks too good to eat.");
  self->text_description_short_set("The food of the Gods: a chocolate frog.");
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_ITEM);
  my::tile(self, {.tile = name, .ascii_fg_char = ";", .ascii_bg_col_name = "", .ascii_fg_col_name = "brown", .is_hp_100_percent = true});
}

static void init(void)
{
  tp_init("frog", "chocolate frog", "choc frog");
}

void module_init(void)
{
  native_register("frog", "on_eaten", 4, [](const int64_t *a) -> NativeRet { (void) a; on_eaten((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  init();
}

} // namespace mod_things_food_frog
