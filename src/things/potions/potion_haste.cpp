//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/potions/potion_haste.py
//

#include "my_native.hpp"

namespace mod_things_potions_potion_haste {

static void on_thrown(uint32_t owner, uint32_t me, int x, int y);
static void on_use(uint32_t owner, uint32_t item, uint32_t target, int x, int y);
static void shatters(uint32_t me, int x, int y);
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
  my::thing_dead(me, "used");
}

static void on_use(uint32_t owner, uint32_t item, uint32_t target, int x, int y)
{
  my::thing_buff_add(target, "buff_temporary_hasted");
  my::thing_wake(target, "potion");
  if (my::thing_is_player(target)) {
    my::thing_msg(target, "%%fg=pink$You are bursting with energy.%%fg=reset$");
  } else {
    my::thing_msg(target, ((std::string("The ") + my::thing_name_get(target) + " is bursting with energy.")).c_str());
  }
}

static void shatters(uint32_t me, int x, int y)
{
  uint32_t owner = 0;
  if (my::thing_is_dead(me)) {
    return;
  }
  owner = my::thing_top_owner_id_get(me);
  if ((owner != 0)) {
    if (my::thing_is_player(owner)) {
      my::thing_msg(me, "Your potion of haste shatters.");
    } else {
      my::thing_msg(me, ((std::string("The ") + my::thing_name_get(owner) + "'s potion of haste shatters.")).c_str());
    }
  } else {
    my::thing_msg(me, "The potion of haste shatters.");
  }
  my::spawn_at_my_position(me, "water");
  my::thing_dead(me, "broken");
}

static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage)
{
  shatters(me, x, y);
}

static void on_fire(uint32_t me, int x, int y)
{
  shatters(me, x, y);
}

static void on_fall(uint32_t me, int x, int y)
{
  shatters(me, x, y);
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->collision_hit_priority_set(5);
  self->environ_dislikes_fire_set(20);
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
  self->text_pluralize_set("potions of haste");
  self->text_apostrophize_set("potion of haste's");
  self->text_description_long_set("A bubbling cyan elixir that will provide you with a prolonged burst of speed. Watch out though, you will tire quickly.");
  self->text_description_short_set("A potion of haste.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = name, .ascii_fg_char = "!", .ascii_bg_col_name = "", .ascii_fg_col_name = "cyan", .delay_ms = 500});
}

static void init(void)
{
  tp_init("potion_haste", "potion of haste", "potion, haste");
}

void module_init(void)
{
  native_register("potion_haste", "on_thrown", 4, [](const int64_t *a) -> NativeRet { (void) a; on_thrown((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("potion_haste", "on_use", 5, [](const int64_t *a) -> NativeRet { (void) a; on_use((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4]); return NativeRet {}; });
  native_register("potion_haste", "shatters", 3, [](const int64_t *a) -> NativeRet { (void) a; shatters((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("potion_haste", "on_hit_and_still_alive", 7, [](const int64_t *a) -> NativeRet { (void) a; on_hit_and_still_alive((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5], (int) a[6]); return NativeRet {}; });
  native_register("potion_haste", "on_fire", 3, [](const int64_t *a) -> NativeRet { (void) a; on_fire((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("potion_haste", "on_fall", 3, [](const int64_t *a) -> NativeRet { (void) a; on_fall((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_potions_potion_haste
