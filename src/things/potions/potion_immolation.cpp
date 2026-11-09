//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/potions/potion_immolation.py
//

#include "my_native.hpp"

namespace mod_things_potions_potion_immolation {

static void on_thrown(uint32_t owner, uint32_t me, int x, int y);
static void on_use(uint32_t owner, uint32_t item, uint32_t target, int x, int y);
static void shatters(uint32_t item, uint32_t target, int x, int y);
static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage);
static void on_fire(uint32_t me, int x, int y);
static void on_fall(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_thrown(uint32_t owner, uint32_t me, int x, int y)
{
  for (auto it : my::level_get_all(me, x, y)) {
    if ((my::thing_is_alive_monst(it) || my::thing_is_player(it))) {
      on_use(owner, me, it, x, y);
      return;
    }
  }
  shatters(me, me, x, y);
}

static void on_use(uint32_t owner, uint32_t item, uint32_t target, int x, int y)
{
  my::thing_wake(target, "potion");
  my::spawn_set_fire_to_things_around_me(target, "fire");
  my::spawn_at_my_position(target, "fire");
  my::thing_debuff_add(owner, "debuff_temporary_immolation");
}

static void shatters(uint32_t item, uint32_t target, int x, int y)
{
  uint32_t owner = 0;
  if (my::thing_is_dead(item)) {
    return;
  }
  owner = my::thing_top_owner_id_get(item);
  if ((owner != 0)) {
    if (my::thing_is_player(owner)) {
      my::thing_msg(owner, "Your potion of immolation shatters.");
    } else {
      my::thing_msg(owner, ((std::string("The ") + my::thing_name_get(owner) + "'s potion of immolation shatters.")).c_str());
    }
  } else {
    my::thing_msg(item, "The potion of immolation shatters.");
  }
  my::spawn_at_my_position(target, "explosion_major");
  my::thing_dead(item, "broken");
}

static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage)
{
  shatters(me, me, x, y);
}

static void on_fire(uint32_t me, int x, int y)
{
  shatters(me, me, x, y);
}

static void on_fall(uint32_t me, int x, int y)
{
  shatters(me, me, x, y);
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->collision_hit_priority_set(5);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gold_value_dice_set("300");
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
  self->is_combustible_set(true);
  self->is_crushable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_drinkable_set(true);
  self->is_droppable_set(true);
  self->is_glass_set(true);
  self->is_hittable_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_moveable_set(true);
  self->is_obs_shooting_set(true);
  self->is_potion_set(true);
  self->is_throwable_set(true);
  self->is_treasure_class_B_set(true);
  self->is_treasure_set(true);
  self->is_treasure_type_set(true);
  self->is_usable_set(true);
  self->item_height_set(4);
  self->item_width_set(4);
  self->noise_on_dropping_set(10);
  self->normal_placement_rules_set(true);
  self->on_fall_do_set("me.on_fall()");
  self->on_hit_and_still_alive_do_set("me.on_hit_and_still_alive()");
  self->on_thrown_do_set("me.on_thrown()");
  self->on_use_do_set("me.on_use()");
  self->on_you_are_on_fire_do_set("me.on_fire()");
  self->temperature_max_set(50);
  self->temperature_min_set(0);
  self->temperature_set(20);
  self->temperature_sensitive_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("potions of immolation");
  self->text_apostrophize_set("potion of immolation's");
  self->text_description_long2_set("Drinking not recommended.");
  self->text_description_long_set("A bubbling orange elixir that when thrown will create an unpleasant surprise for the recipient!");
  self->text_description_short_set("A potion of immolation.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = "potion_fire_immunity", .ascii_fg_char = "!", .ascii_bg_col_name = "", .ascii_fg_col_name = "orange", .delay_ms = 500});
}

static void init(void)
{
  tp_init("potion_immolation", "potion of immolation", "potion, immolation");
}

void module_init(void)
{
  native_register("potion_immolation", "on_thrown", 4, [](const int64_t *a) -> NativeRet { (void) a; on_thrown((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("potion_immolation", "on_use", 5, [](const int64_t *a) -> NativeRet { (void) a; on_use((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4]); return NativeRet {}; });
  native_register("potion_immolation", "shatters", 4, [](const int64_t *a) -> NativeRet { (void) a; shatters((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("potion_immolation", "on_hit_and_still_alive", 7, [](const int64_t *a) -> NativeRet { (void) a; on_hit_and_still_alive((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5], (int) a[6]); return NativeRet {}; });
  native_register("potion_immolation", "on_fire", 3, [](const int64_t *a) -> NativeRet { (void) a; on_fire((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("potion_immolation", "on_fall", 3, [](const int64_t *a) -> NativeRet { (void) a; on_fall((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_potions_potion_immolation
