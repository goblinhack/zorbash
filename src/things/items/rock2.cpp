//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/items/rock2.py
//

#include "my_native.hpp"

namespace mod_things_items_rock2 {

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
      my::thing_hit_dmg_missile(owner, me, it, 0, 0, true);
    }
  }
  if ((my::pcg_random_inclusive(1, 100) < 50)) {
    my::thing_dead(me, "used");
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->chance_d10000_enchanted_set(20);
  self->chance_d1000_appearing_set(10);
  self->dmg_chance_d1000_missile_set(0, 1000);
  self->dmg_missile_dice_set("1d8+3");
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gfx_targeted_projectile_set("projectile_rock");
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
  self->is_enchantable_as_a_group_set(true);
  self->is_enchantable_set(true);
  self->is_hard_set(true);
  self->is_heavy_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_made_of_rock_set(true);
  self->is_missile_set(true);
  self->is_moveable_set(true);
  self->is_ranged_weapon_set(true);
  self->is_throwable_set(true);
  self->is_thrown_as_a_weapon_set(true);
  self->is_treasure_class_A_set(true);
  self->is_treasure_set(true);
  self->is_treasure_type_set(true);
  self->item_height_set(3);
  self->item_width_set(3);
  self->noise_on_dropping_set(20);
  self->normal_placement_rules_set(true);
  self->on_thrown_do_set("me.on_thrown()");
  self->rarity_set(THING_RARITY_COMMON);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("heavy rocks");
  self->text_apostrophize_set("heavy rock's");
  self->text_description_enchant_set("+1 DMG");
  self->text_description_long_set("An elegant weapon for a more civilized age, this professional level rock, is a cut above the average rock, in terms of impact.");
  self->text_description_short_set("A menacing rock.");
  self->thing_size_set(THING_SIZE_TINY);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = name, .ascii_fg_char = "o", .ascii_bg_col_name = "", .ascii_fg_col_name = "brown", .delay_ms = 100});
}

static void init(void)
{
  tp_init("rock2", "heavy rock", "heavy rock");
}

void module_init(void)
{
  native_register("rock2", "on_thrown", 4, [](const int64_t *a) -> NativeRet { (void) a; on_thrown((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  init();
}

} // namespace mod_things_items_rock2
