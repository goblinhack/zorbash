//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/potions/potion_invigoration.py
//

#include "my_native.hpp"

namespace mod_things_potions_potion_invigoration {

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
  bool did_something = false;
  int health = 0;
  int new_health = 0;
  int new_stamina = 0;
  int stamina = 0;
  my::thing_sound_play_channel(target, CHANNEL_WEAPON, "potion");
  my::thing_wake(target, "potion");
  did_something = false;
  health = my::thing_health(target);
  new_health = ((int) ((((double) ((double) (my::thing_health_max(target))) / (double) 100.0) * 80.0)));
  if ((new_health > health)) {
    did_something = true;
    my::thing_health_set(target, new_health);
  }
  stamina = my::thing_stamina(target);
  new_stamina = ((int) ((((double) ((double) (my::thing_stamina_max(target))) / (double) 100.0) * 80.0)));
  if ((new_stamina > stamina)) {
    did_something = true;
    my::thing_stamina_set(target, new_stamina);
  }
  if (did_something) {
    my::spawn_using_items_radius_range(target, item, target, "potion_effect");
    if (my::thing_is_player(target)) {
      my::thing_msg(target, "%%fg=pink$You glow with renewed health.%%fg=reset$");
    } else {
      my::thing_msg(target, ((std::string("The ") + my::thing_name_get(target) + " glows with health.")).c_str());
    }
  } else if (my::thing_is_player(target)) {
    my::thing_msg(target, "Hm. That potion didn't seem to do anything.");
  } else {
    my::thing_msg(target, ((std::string("The ") + my::thing_name_get(target) + " shrugs.")).c_str());
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
      my::thing_msg(me, "Your potion of invigoration shatters.");
    } else {
      my::thing_msg(me, ((std::string("The ") + my::thing_name_get(owner) + "'s potion of invigoration shatters.")).c_str());
    }
  } else {
    my::thing_msg(me, "The potion of invigoration shatters.");
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
  self->gold_value_dice_set("50");
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
  self->is_health_booster_set(true);
  self->is_hittable_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_moveable_set(true);
  self->is_obs_shooting_set(true);
  self->is_potion_set(true);
  self->is_throwable_set(true);
  self->is_treasure_class_A_set(true);
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
  self->text_pluralize_set("potions of invigoration");
  self->text_apostrophize_set("potion of invigoration's");
  self->text_description_long2_set("You'll feel like your old self again. Only even more awesome, if that could be possible...");
  self->text_description_long_set("A bubbling pink elixir that restores your health and stamina to at least 80 percent.");
  self->text_description_short_set("A potion of invigoration.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = name, .ascii_fg_char = "!", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = 500});
}

static void init(void)
{
  tp_init("potion_invigoration", "potion of invigoration", "potion, invigorate");
}

void module_init(void)
{
  native_register("potion_invigoration", "on_thrown", 4, [](const int64_t *a) -> NativeRet { (void) a; on_thrown((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("potion_invigoration", "on_use", 5, [](const int64_t *a) -> NativeRet { (void) a; on_use((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4]); return NativeRet {}; });
  native_register("potion_invigoration", "shatters", 3, [](const int64_t *a) -> NativeRet { (void) a; shatters((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("potion_invigoration", "on_hit_and_still_alive", 7, [](const int64_t *a) -> NativeRet { (void) a; on_hit_and_still_alive((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5], (int) a[6]); return NativeRet {}; });
  native_register("potion_invigoration", "on_fire", 3, [](const int64_t *a) -> NativeRet { (void) a; on_fire((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("potion_invigoration", "on_fall", 3, [](const int64_t *a) -> NativeRet { (void) a; on_fall((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_potions_potion_invigoration
