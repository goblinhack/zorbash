//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/death_hornet.py
//

#include "my_native.hpp"

namespace mod_things_monsters_death_hornet {

static void on_born(uint32_t me, int x, int y);
static void on_you_nat_attack_attempt(uint32_t me, int x, int y);
static void on_you_nat_attack_success(uint32_t me, int x, int y);
static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage);
static void on_hit_dodge_do(uint32_t me, uint32_t hitter, int x, int y);
static void on_death(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_born(uint32_t me, int x, int y)
{
  my::thing_friend(me, "is_death_hornet");
}

static void on_you_nat_attack_attempt(uint32_t me, int x, int y)
{
  std::string sound;
  sound = (std::string("growl") + std::to_string(my::non_pcg_random_inclusive(1, 10)));
  my::thing_sound_play_channel(me, CHANNEL_MONST, (sound).c_str());
}

static void on_you_nat_attack_success(uint32_t me, int x, int y)
{
  my::thing_dead(me, "by its own sting");
}

static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage)
{
  std::string sound;
  sound = (std::string("hiss") + std::to_string(my::non_pcg_random_inclusive(1, 10)));
  if ((! my::thing_sound_play_channel(me, CHANNEL_MONST, (sound).c_str()))) {
    my::thing_sound_play_channel(me, CHANNEL_MONST_DEATH, (sound).c_str());
  }
}

static void on_hit_dodge_do(uint32_t me, uint32_t hitter, int x, int y)
{
  std::string sound;
  sound = (std::string("hiss") + std::to_string(my::non_pcg_random_inclusive(1, 10)));
  if ((! my::thing_sound_play_channel(me, CHANNEL_MONST, (sound).c_str()))) {
    my::thing_sound_play_channel(me, CHANNEL_MONST_DEATH, (sound).c_str());
  }
}

static void on_death(uint32_t me, int x, int y)
{
  std::string sound;
  sound = (std::string("hiss") + std::to_string(my::non_pcg_random_inclusive(1, 10)));
  if ((! my::thing_sound_play_channel(me, CHANNEL_MONST, (sound).c_str()))) {
    my::thing_sound_play_channel(me, CHANNEL_MONST_DEATH, (sound).c_str());
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name);
  self->aggression_pct_set(100);
  self->ai_resent_count_set(100);
  self->ai_wanderer_set(true);
  self->attack_blood_set(true);
  self->attack_eater_set(true);
  self->attack_humanoid_set(true);
  self->attack_meat_set(true);
  self->chance_d1000_tameable_set(0);
  self->collision_check_set(true);
  self->collision_hit_priority_set(20);
  self->consume_per_bite_amount_set(1);
  self->distance_avoid_set(3);
  self->distance_vision_set(3);
  self->dmg_bite_dice_set("1d10");
  self->dmg_chance_d1000_bite_set(0, 500);
  self->dmg_chance_d1000_nat_att_set(0, 900);
  self->dmg_chance_d1000_poison_set(0, 900);
  self->dmg_limited_per_tick_set(true);
  self->dmg_nat_att_dice_set("1d4+1");
  self->dmg_nat_att_type_set("pierce");
  self->dmg_poison_dice_set("1d10");
  self->gfx_anim_use_set("attack_red");
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_can_hflip_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_health_bar_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->has_a_head_set(true);
  self->health_initial_dice_set("1d8");
  self->hunger_clock_tick_freq_set(50);
  self->is_able_to_be_surprised_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_freeze_set(true);
  self->is_able_to_lunge_set(true);
  self->is_able_to_rest_set(true);
  self->is_able_to_see_in_the_dark_set(true);
  self->is_able_to_tire_set(true);
  self->is_air_breather_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_swamp_set(true);
  self->is_bleeder_set(true);
  self->is_buffable_set(true);
  self->is_burnable_set(true);
  self->is_corpse_on_death_set(true);
  self->is_corpse_with_bones_set(true);
  self->is_crushable_set(true);
  self->is_death_hornet_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_eater_of_blood_set(true);
  self->is_eater_of_meat_set(true);
  self->is_flying_set(true);
  self->is_hittable_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_meat_set(true);
  self->is_monst_class_A_set(true);
  self->is_monst_set(true);
  self->is_moveable_set(true);
  self->is_msg_allowed_hears_something_set(true);
  self->is_msg_allowed_is_dead_set(true);
  self->is_msg_allowed_is_seen_set(true);
  self->is_msg_allowed_is_surprised_set(true);
  self->is_msg_allowed_is_wounded_set(true);
  self->is_msg_allowed_senses_danger_set(true);
  self->is_poisonous_danger_level_set(2);
  self->is_red_blooded_set(true);
  self->is_shootable_set(true);
  self->is_soft_set(true);
  self->is_tickable_set(true);
  self->move_speed_set(250);
  self->noise_decibels_hearing_set(0);
  self->noise_on_moving_set(25);
  self->normal_placement_rules_set(true);
  self->on_born_do_set("me.on_born()");
  self->on_death_do_set("me.on_death()");
  self->on_hit_and_still_alive_do_set("me.on_hit_and_still_alive()");
  self->on_hit_dodge_do_set("me.on_hit_dodge_do()");
  self->on_you_nat_attack_attempt_do_set("me.on_you_nat_attack_attempt()");
  self->on_you_nat_attack_success_do_set("me.on_you_nat_attack_success()");
  self->rarity_set(THING_RARITY_UNCOMMON);
  self->spawn_group_radius_set(5);
  self->spawn_group_size_dice_set("1d3+5");
  self->stamina_set(100);
  self->stat_att_bonus_set(10);
  self->stat_con_set(10);
  self->stat_def_set(6);
  self->stat_dex_set(14);
  self->stat_luck_set(10);
  self->stat_psi_set(0);
  self->stat_str_set(4);
  self->temperature_max_set(50);
  self->temperature_min_set(0);
  self->temperature_set(20);
  self->temperature_sensitive_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("death hornets");
  self->text_apostrophize_set("death hornet's");
  self->text_description_long2_set("They have a unique attack method, that of a single massive sting, after which they die. It is believed in this way that the death hornet will finish you off in one go, leaving your fresh corpse for the benefit of its hive kin.");
  self->text_description_long_set("The death hornet is as unpleasant as it sounds and can often be found in large buzzing groups.");
  self->text_description_short_set("A stabby death.");
  self->text_hits_set("pierces");
  self->thing_size_set(THING_SIZE_SMALL);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_MONST);
  delay = 130;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "h", .ascii_bg_col_name = "", .ascii_fg_col_name = "yellow", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "h", .ascii_bg_col_name = "", .ascii_fg_col_name = "yellow", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "h", .ascii_bg_col_name = "", .ascii_fg_col_name = "yellow", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "h", .ascii_bg_col_name = "", .ascii_fg_col_name = "yellow", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".dead"), .ascii_fg_char = "h", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
}

static void init(void)
{
  tp_init("death_hornet", "death hornet");
}

void module_init(void)
{
  native_register("death_hornet", "on_born", 3, [](const int64_t *a) -> NativeRet { (void) a; on_born((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("death_hornet", "on_you_nat_attack_attempt", 3, [](const int64_t *a) -> NativeRet { (void) a; on_you_nat_attack_attempt((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("death_hornet", "on_you_nat_attack_success", 3, [](const int64_t *a) -> NativeRet { (void) a; on_you_nat_attack_success((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("death_hornet", "on_hit_and_still_alive", 7, [](const int64_t *a) -> NativeRet { (void) a; on_hit_and_still_alive((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5], (int) a[6]); return NativeRet {}; });
  native_register("death_hornet", "on_hit_dodge_do", 4, [](const int64_t *a) -> NativeRet { (void) a; on_hit_dodge_do((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("death_hornet", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_monsters_death_hornet
