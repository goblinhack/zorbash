//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/items/dart_confusion.py
//

#include "my_native.hpp"

namespace mod_things_items_dart_confusion {

static void on_thrown(uint32_t owner, uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_thrown(uint32_t owner, uint32_t me, int x, int y)
{
  for (auto it : my::level_get_all(me, x, y)) {
    if ((my::thing_is_alive_monst(it) || my::thing_is_player(it))) {
      if ((! (my::thing_confused_count_incr(it, 10) != 0))) {
        if (my::thing_is_player(it)) {
          my::thing_msg(it, "%%fg=red$The confusion dart has no effect on you.");
        }
        if (((owner != 0) && my::thing_is_player(owner))) {
          my::thing_msg(owner, "%%fg=red$Your confusion dart has no effect.");
        }
      } else {
        if (my::thing_is_player(it)) {
          my::thing_msg(it, ((std::string("%%fg=red$You are struck by a ") + my::thing_name_get(me) + "!%%fg=reset$")).c_str());
        }
        if (((owner != 0) && my::thing_is_player(owner))) {
          if ((owner == it)) {
            my::thing_msg(owner, "%%fg=red$You confuse yourself!%%fg=reset$");
          } else {
            my::thing_msg(owner, ((std::string("%%fg=red$You confuse the ") + my::thing_name_get(it) + "!%%fg=reset$")).c_str());
          }
        }
      }
    }
  }
  if ((my::pcg_random_inclusive(1, 100) < 90)) {
    my::thing_dead(me, "used");
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->chance_d10000_enchanted_set(200);
  self->chance_d1000_appearing_set(10);
  self->dmg_chance_d1000_missile_set(0, 1000);
  self->dmg_missile_dice_set("1d4");
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gfx_targeted_projectile_set("projectile_dart_confusion");
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_aerodynamic_set(true);
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
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_light_set(true);
  self->is_loggable_set(true);
  self->is_missile_set(true);
  self->is_moveable_set(true);
  self->is_pointy_set(true);
  self->is_ranged_weapon_set(true);
  self->is_throwable_set(true);
  self->is_thrown_as_a_weapon_set(true);
  self->is_treasure_class_A_set(true);
  self->is_treasure_set(true);
  self->is_treasure_type_set(true);
  self->item_height_set(3);
  self->item_width_set(3);
  self->noise_on_dropping_set(1);
  self->normal_placement_rules_set(true);
  self->on_thrown_do_set("me.on_thrown()");
  self->rarity_set(THING_RARITY_COMMON);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("confusion darts");
  self->text_apostrophize_set("confusion dart's");
  self->text_description_enchant_set("+1 DMG");
  self->text_description_long_set("This dart will bring a confused look to your enemies faces. If they have faces...");
  self->text_description_short_set("A confusion tipped dart.");
  self->thing_size_set(THING_SIZE_TINY);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = name, .ascii_fg_char = "'", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray90", .delay_ms = 100});
}

static void init(void)
{
  tp_init("dart_confusion", "confusion dart", "confusion dart");
}

void module_init(void)
{
  native_register("dart_confusion", "on_thrown", 4, [](const int64_t *a) -> NativeRet { (void) a; on_thrown((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  init();
}

} // namespace mod_things_items_dart_confusion
