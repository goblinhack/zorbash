//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/zorb_all.py
//

#include "my_native.hpp"
#include "things/monsters/zorb_all.hpp"

namespace mod_things_monsters_zorb_all {

void on_born(uint32_t me, int x, int y)
{
  my::thing_friend(me, "zorb_wizard");
  my::thing_friend(me, "zorb_captain");
  my::thing_friend(me, "zorb_eldster");
  my::thing_friend(me, "zorb_necro");
  my::thing_friend(me, "zorb_pirate");
  my::thing_friend(me, "zorb_priest");
  my::thing_friend(me, "zorb_single");
  my::thing_friend(me, "zorb_soldier");
  my::thing_friend(me, "zorb_wizard");
}

void on_you_nat_attack_attempt(uint32_t me, int x, int y)
{
  std::string sound;
  sound = (std::string("hiss") + std::to_string(my::non_pcg_random_inclusive(1, 10)));
  my::thing_sound_play_channel(me, CHANNEL_MONST, (sound).c_str());
}

void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage)
{
  std::string sound;
  sound = (std::string("hiss") + std::to_string(my::non_pcg_random_inclusive(1, 10)));
  if ((! my::thing_sound_play_channel(me, CHANNEL_MONST, (sound).c_str()))) {
    my::thing_sound_play_channel(me, CHANNEL_MONST_DEATH, (sound).c_str());
  }
}

void on_hit_dodge_do(uint32_t me, uint32_t hitter, int x, int y)
{
  std::string sound;
  sound = (std::string("hiss") + std::to_string(my::non_pcg_random_inclusive(1, 10)));
  if ((! my::thing_sound_play_channel(me, CHANNEL_MONST, (sound).c_str()))) {
    my::thing_sound_play_channel(me, CHANNEL_MONST_DEATH, (sound).c_str());
  }
}

void on_death(uint32_t me, int x, int y)
{
  if ((! my::thing_sound_play_channel(me, CHANNEL_MONST, "monst_death1"))) {
    my::thing_sound_play_channel(me, CHANNEL_MONST_DEATH, "monst_death1");
  }
}

Tpp tp_init(const std::string &name, const std::string &text_long_name)
{
  Tpp self = my::tp_load(name, text_long_name);
  self->aggression_pct_set(100);
  self->ai_detect_secret_doors_set(true);
  self->ai_resent_count_set(20);
  self->ai_wanderer_set(true);
  self->attack_eater_set(true);
  self->attack_humanoid_set(true);
  self->attack_meat_set(true);
  self->attack_undead_set(true);
  self->capacity_height_set(5);
  self->capacity_width_set(5);
  self->chance_d1000_shooting_avoid_friends_set(500);
  self->chance_d1000_shooting_set(50);
  self->chance_d1000_shove_set(500);
  self->chance_d1000_steal_item_set(50);
  self->chance_d1000_tameable_set(0);
  self->collision_check_set(true);
  self->collision_hit_priority_set(20);
  self->consume_per_bite_amount_set(10);
  self->distance_avoid_set(5);
  self->distance_leader_max_set(5);
  self->distance_throw_set(6);
  self->distance_vision_set(7);
  self->dmg_limited_per_tick_set(true);
  self->dmg_nat_att_dice_set("1d4+2");
  self->dmg_nat_att_type_set("gore");
  self->environ_dislikes_acid_set(100);
  self->environ_dislikes_fire_set(10);
  self->environ_dislikes_poison_set(100);
  self->gfx_anim_use_set("attack_red");
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_can_hflip_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_bounce_on_move_set(true);
  self->gfx_pixelart_health_bar_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_asleep_anim_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->has_a_head_set(true);
  self->health_initial_dice_set("2d6");
  self->hunger_clock_tick_freq_set(50);
  self->is_able_to_attack_mobs_set(true);
  self->is_able_to_attack_totems_set(true);
  self->is_able_to_be_surprised_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_break_down_doors_set(true);
  self->is_able_to_break_out_of_ice_set(true);
  self->is_able_to_break_out_of_webs_set(true);
  self->is_able_to_change_levels_set(true);
  self->is_able_to_collect_keys_set(true);
  self->is_able_to_enchant_items_set(true);
  self->is_able_to_fall_set(true);
  self->is_able_to_follow_set(true);
  self->is_able_to_freeze_set(true);
  self->is_able_to_jump_set(true);
  self->is_able_to_learn_skills_set(true);
  self->is_able_to_lunge_set(true);
  self->is_able_to_move_diagonally_set(true);
  self->is_able_to_open_doors_set(true);
  self->is_able_to_rest_set(true);
  self->is_able_to_see_in_the_dark_set(true);
  self->is_able_to_shoot_at_set(true);
  self->is_able_to_sleep_set(true);
  self->is_able_to_tire_set(true);
  self->is_able_to_use_amulet_set(true);
  self->is_able_to_use_boots_set(true);
  self->is_able_to_use_cloak_set(true);
  self->is_able_to_use_gauntlet_set(true);
  self->is_able_to_use_ranged_weapons_set(true);
  self->is_able_to_use_rings_set(true);
  self->is_able_to_use_staffs_set(true);
  self->is_air_breather_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_ice_set(true);
  self->is_bleeder_set(true);
  self->is_buffable_set(true);
  self->is_burnable_set(true);
  self->is_corpse_on_death_set(true);
  self->is_corpse_with_bones_set(true);
  self->is_crushable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_explorer_set(true);
  self->is_green_blooded_set(true);
  self->is_hittable_set(true);
  self->is_humanoid_set(true);
  self->is_interesting_set(true);
  self->is_item_carrier_set(true);
  self->is_item_collector_set(true);
  self->is_living_set(true);
  self->is_loggable_set(true);
  self->is_meat_set(true);
  self->is_monst_set(true);
  self->is_moveable_set(true);
  self->is_msg_allowed_hears_something_set(true);
  self->is_msg_allowed_is_dead_set(true);
  self->is_msg_allowed_is_seen_set(true);
  self->is_msg_allowed_is_surprised_set(true);
  self->is_msg_allowed_is_wounded_set(true);
  self->is_msg_allowed_senses_danger_set(true);
  self->is_shootable_set(true);
  self->is_shovable_set(true);
  self->is_thief_set(5);
  self->is_tickable_set(true);
  self->is_zorblin_set(true);
  self->jump_distance_set(3);
  self->move_speed_set(100);
  self->noise_decibels_hearing_set(10);
  self->noise_on_moving_set(5);
  self->normal_placement_rules_set(true);
  self->on_born_do_set("me.on_born()");
  self->on_death_do_set("zorb_all.on_death()");
  self->on_death_drop_all_items_set(true);
  self->on_hit_and_still_alive_do_set("zorb_all.on_hit_and_still_alive()");
  self->on_hit_dodge_do_set("zorb_all.on_hit_dodge_do()");
  self->on_you_nat_attack_attempt_do_set("zorb_all.on_you_nat_attack_attempt()");
  self->rarity_set(THING_RARITY_COMMON);
  self->stamina_set(100);
  self->stat_att_penalty_when_idle_max_set(0);
  self->stat_att_penalty_when_idle_set(0);
  self->stat_att_penalty_when_in_deep_water_set(2);
  self->stat_att_penalty_when_in_shallow_water_set(1);
  self->stat_att_penalty_when_stuck_max_set(2);
  self->stat_att_penalty_when_stuck_set(1);
  self->stat_con_set(10);
  self->stat_def_penalty_when_idle_max_set(5);
  self->stat_def_penalty_when_idle_set(5);
  self->stat_def_penalty_when_in_deep_water_set(2);
  self->stat_def_penalty_when_in_shallow_water_set(1);
  self->stat_def_penalty_when_stuck_max_set(15);
  self->stat_def_penalty_when_stuck_set(10);
  self->stat_def_set(10);
  self->stat_dex_set(12);
  self->stat_luck_set(8);
  self->stat_psi_set(8);
  self->stat_str_set(8);
  self->temperature_max_set(50);
  self->temperature_min_set(0);
  self->temperature_set(20);
  self->temperature_sensitive_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("zorblins");
  self->text_apostrophize_set("zorblin's");
  self->text_description_long_set("Zorblins are small, green skinned beings that lair in abandoned mines, despoiled dungeons and other dismal settings, otherwise known as their homes. They spend their time defending their natural habitat from invading marauders, like you. They often carry some meagre amounts of gold, dug from the depths with bare, shaking hands.");
  self->text_hits_set("claws");
  self->thing_size_set(THING_SIZE_NORMAL);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_MONST);
  return self;
}

void module_init(void)
{
  native_register("zorb_all", "on_born", 3, [](const int64_t *a) -> NativeRet { (void) a; on_born((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("zorb_all", "on_you_nat_attack_attempt", 3, [](const int64_t *a) -> NativeRet { (void) a; on_you_nat_attack_attempt((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("zorb_all", "on_hit_and_still_alive", 7, [](const int64_t *a) -> NativeRet { (void) a; on_hit_and_still_alive((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5], (int) a[6]); return NativeRet {}; });
  native_register("zorb_all", "on_hit_dodge_do", 4, [](const int64_t *a) -> NativeRet { (void) a; on_hit_dodge_do((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("zorb_all", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
}

} // namespace mod_things_monsters_zorb_all
