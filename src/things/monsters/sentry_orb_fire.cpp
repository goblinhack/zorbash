//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/sentry_orb_fire.py
//

#include "my_native.hpp"

namespace mod_things_monsters_sentry_orb_fire {

static void on_death(uint32_t me, int x, int y);
static void explode(uint32_t me, int x, int y);
static bool on_want_to_shoot_at(uint32_t me, uint32_t target, int target_x, int target_y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_death(uint32_t me, int x, int y)
{
  explode(me, x, y);
}

static void explode(uint32_t me, int x, int y)
{
  if (my::thing_is_dead(me)) {
    return;
  }
  my::thing_msg(me, "The sentry orb explodes!");
  my::spawn_at_my_position(me, "explosion_major");
}

static bool on_want_to_shoot_at(uint32_t me, uint32_t target, int target_x, int target_y)
{
  my::thing_shoot_projectile_or_laser_at(me, "projectile_fire", target);
  return true;
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->aggression_pct_set(100);
  self->ai_wanderer_set(true);
  self->attack_humanoid_set(true);
  self->chance_d1000_shooting_set(800);
  self->chance_d1000_tameable_set(0);
  self->collision_check_set(true);
  self->collision_hit_priority_set(20);
  self->distance_vision_set(8);
  self->dmg_num_of_attacks_set(0);
  self->dmg_rcv_doubled_from_cold_set(true);
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_health_bar_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->health_initial_dice_set("1");
  self->is_able_to_be_surprised_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_see_in_the_dark_set(true);
  self->is_able_to_shoot_at_close_range_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_lava_set(true);
  self->is_buffable_set(true);
  self->is_crushable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_fearless_set(true);
  self->is_fire_elemental_set(true);
  self->is_floating_set(true);
  self->is_hittable_set(true);
  self->is_immune_to_blinding_set(true);
  self->is_immune_to_fire_set(true);
  self->is_immune_to_necrosis_set(true);
  self->is_immune_to_paralysis_set(true);
  self->is_immune_to_poison_set(true);
  self->is_interesting_set(true);
  self->is_lifeless_set(true);
  self->is_loggable_set(true);
  self->is_magical_set(true);
  self->is_monst_class_B_set(true);
  self->is_monst_set(true);
  self->is_moveable_set(true);
  self->is_msg_allowed_hears_something_set(true);
  self->is_msg_allowed_is_dead_set(true);
  self->is_msg_allowed_is_seen_set(true);
  self->is_msg_allowed_senses_danger_set(true);
  self->is_shootable_set(true);
  self->is_tickable_set(true);
  self->is_vanquished_on_negation_set(true);
  self->light_color_set("orange");
  self->light_dist_set(1);
  self->move_speed_set(50);
  self->noise_decibels_hearing_set(5);
  self->noise_on_moving_set(3);
  self->normal_placement_rules_set(true);
  self->on_death_do_set("me.on_death()");
  self->on_want_to_shoot_at_do_set("me.on_want_to_shoot_at()");
  self->rarity_set(THING_RARITY_UNCOMMON);
  self->stat_con_set(10);
  self->stat_def_set(10);
  self->stat_dex_set(10);
  self->stat_luck_set(10);
  self->stat_psi_set(0);
  self->stat_str_set(10);
  self->temperature_max_set(1000);
  self->temperature_min_set(0);
  self->temperature_set(200);
  self->temperature_sensitive_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("orbs of fire");
  self->text_apostrophize_set("orb of fire's");
  self->text_description_long2_set("Note that sentry orbs are fragile and prone to explosive outbursts...");
  self->text_description_long_set("Sentry orbs patrol the dungeon, raining down punishment on whomever should not be there. Essentially you... This one fires beams of fire.");
  self->text_description_short_set("A sentry orb.");
  self->text_hits_set("burns");
  self->thing_size_set(THING_SIZE_NORMAL);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_MONST);
  delay = 200;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "O", .ascii_bg_col_name = "", .ascii_fg_col_name = "orange", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "o", .ascii_bg_col_name = "", .ascii_fg_col_name = "orange", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "O", .ascii_bg_col_name = "", .ascii_fg_col_name = "orange", .delay_ms = delay});
}

static void init(void)
{
  tp_init("sentry_orb_fire", "orb of fire", "sentry orb");
}

void module_init(void)
{
  native_register("sentry_orb_fire", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("sentry_orb_fire", "explode", 3, [](const int64_t *a) -> NativeRet { (void) a; explode((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("sentry_orb_fire", "on_want_to_shoot_at", 4, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_want_to_shoot_at((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]), {}}; });
  init();
}

} // namespace mod_things_monsters_sentry_orb_fire
