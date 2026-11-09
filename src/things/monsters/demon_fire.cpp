//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/demon_fire.py
//

#include "my_native.hpp"

namespace mod_things_monsters_demon_fire {

static void on_you_nat_attack_attempt(uint32_t me, int x, int y);
static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage);
static void on_hit_dodge_do(uint32_t me, uint32_t hitter, int x, int y);
static bool on_tick(uint32_t owner, uint32_t me, int x, int y);
static void on_death(uint32_t me, int x, int y);
static bool on_want_to_shoot_at(uint32_t me, uint32_t target, int target_x, int target_y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_you_nat_attack_attempt(uint32_t me, int x, int y)
{
  std::string sound;
  sound = (std::string("hiss") + std::to_string(my::non_pcg_random_inclusive(1, 10)));
  my::thing_sound_play_channel(me, CHANNEL_MONST, (sound).c_str());
}

static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage)
{
  std::string sound;
  sound = (std::string("hiss") + std::to_string(my::non_pcg_random_inclusive(1, 10)));
  my::thing_sound_play_channel(me, CHANNEL_MONST, (sound).c_str());
}

static void on_hit_dodge_do(uint32_t me, uint32_t hitter, int x, int y)
{
  std::string sound;
  sound = (std::string("hiss") + std::to_string(my::non_pcg_random_inclusive(1, 10)));
  my::thing_sound_play_channel(me, CHANNEL_MONST, (sound).c_str());
}

static bool on_tick(uint32_t owner, uint32_t me, int x, int y)
{
  if ((my::pcg_random_inclusive(1, 100) < 90)) {
    return false;
  }
  my::spawn_at_my_position(me, "fire");
  return true;
}

static void on_death(uint32_t me, int x, int y)
{
  std::string sound;
  my::thing_msg(me, "The demon screams angrily and vanishes!");
  my::spawn_at_my_position(me, "fire");
  sound = (std::string("growl") + std::to_string(my::non_pcg_random_inclusive(1, 10)));
  if ((! my::thing_sound_play_channel(me, CHANNEL_MONST, (sound).c_str()))) {
    my::thing_sound_play_channel(me, CHANNEL_MONST_DEATH, (sound).c_str());
  }
}

static bool on_want_to_shoot_at(uint32_t me, uint32_t target, int target_x, int target_y)
{
  my::thing_shoot_projectile_or_laser_at(me, "projectile_fire", target);
  return true;
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name);
  self->aggression_pct_set(100);
  self->ai_resent_count_set(100);
  self->ai_wanderer_set(true);
  self->attack_eater_set(true);
  self->attack_humanoid_set(true);
  self->attack_meat_set(true);
  self->chance_d1000_jump_attack_set(800);
  self->chance_d1000_jump_onto_set(100);
  self->chance_d1000_jump_randomly_set(20);
  self->chance_d1000_shooting_set(300);
  self->chance_d1000_shove_set(200);
  self->chance_d1000_tameable_set(20);
  self->chance_d1000_teleport_self_set(50);
  self->collision_check_set(true);
  self->collision_hit_priority_set(20);
  self->consume_per_bite_amount_set(10);
  self->distance_vision_set(7);
  self->dmg_chance_d1000_fire_set(1, 1000);
  self->dmg_chance_d1000_nat_att_set(0, 1000);
  self->dmg_fire_dice_set("1d6+6");
  self->dmg_nat_att_dice_set("1d14+4");
  self->dmg_nat_att_type_set("bludgeon");
  self->dmg_num_of_attacks_set(2);
  self->dmg_rcv_doubled_from_cold_set(true);
  self->dmg_rcv_doubled_from_water_set(true);
  self->environ_hates_cold_set(100);
  self->environ_hates_water_set(100);
  self->gfx_anim_use_set("attack_major_orange");
  self->gfx_anim_use_set("sword_plutonium_swing");
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_can_hflip_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_bounce_on_move_set(true);
  self->gfx_pixelart_health_bar_shown_set(true);
  self->gfx_pixelart_oversized_and_on_floor_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->has_a_head_set(true);
  self->health_initial_dice_set("10d8");
  self->hunger_is_insatiable_set(true);
  self->is_able_to_be_surprised_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_able_to_lunge_set(true);
  self->is_able_to_rest_set(true);
  self->is_able_to_see_in_magical_darkness_set(true);
  self->is_able_to_see_in_the_dark_set(true);
  self->is_able_to_see_through_doors_set(true);
  self->is_able_to_teleport_escape_set(true);
  self->is_able_to_teleport_self_set(true);
  self->is_able_to_teleport_without_tiring_set(true);
  self->is_always_submerged_in_lava_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_lava_set(true);
  self->is_buffable_set(true);
  self->is_demon_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_eater_of_meat_set(true);
  self->is_eater_of_red_blood_set(true);
  self->is_fearless_set(true);
  self->is_fire_elemental_set(true);
  self->is_heavy_set(true);
  self->is_hittable_set(true);
  self->is_humanoid_set(true);
  self->is_immune_to_fire_set(true);
  self->is_immune_to_necrosis_set(true);
  self->is_immune_to_poison_set(true);
  self->is_immune_to_vorpal_weapons_set(true);
  self->is_intelligent_set(true);
  self->is_interesting_set(true);
  self->is_lifeless_set(true);
  self->is_loggable_set(true);
  self->is_monst_class_D_set(true);
  self->is_monst_set(true);
  self->is_moveable_set(true);
  self->is_msg_allowed_hears_something_set(true);
  self->is_msg_allowed_is_dead_set(true);
  self->is_msg_allowed_is_seen_set(true);
  self->is_msg_allowed_is_surprised_set(true);
  self->is_msg_allowed_is_wounded_set(true);
  self->is_msg_allowed_senses_danger_set(true);
  self->is_obs_when_dead_set(true);
  self->is_shootable_set(true);
  self->is_tickable_set(true);
  self->is_very_intelligent_set(true);
  self->light_color_set("red");
  self->light_dist_set(2);
  self->move_speed_set(150);
  self->noise_decibels_hearing_set(50);
  self->noise_on_moving_set(25);
  self->normal_placement_rules_set(true);
  self->on_death_do_set("me.on_death()");
  self->on_hit_and_still_alive_do_set("me.on_hit_and_still_alive()");
  self->on_hit_dodge_do_set("me.on_hit_dodge_do()");
  self->on_tick_do_set("me.on_tick()");
  self->on_want_to_shoot_at_do_set("me.on_want_to_shoot_at()");
  self->on_you_nat_attack_attempt_do_set("me.on_you_nat_attack_attempt()");
  self->rarity_set(THING_RARITY_UNCOMMON);
  self->shove_bonus_set(1);
  self->stamina_set(100);
  self->stat_con_set(20);
  self->stat_def_set(14);
  self->stat_dex_set(8);
  self->stat_int_set(22);
  self->stat_luck_set(2);
  self->stat_psi_set(18);
  self->stat_str_set(18);
  self->teleport_distance_set(5);
  self->temperature_min_set(50);
  self->temperature_set(100);
  self->temperature_sensitive_set(true);
  self->temperature_sensitive_to_sudden_changes_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("fire demons");
  self->text_apostrophize_set("fire demon's");
  self->text_description_long2_set("Fire demons are formidable enemies. Execute extreme caution or be executed extremely...");
  self->text_description_long_set("Accursed creature of the abyss. Devoid of life. Full of hatred, and just wants to get back to the pit so it can take care of its pet cats. And you are in the way...");
  self->text_description_short_set("A hot fire demon.");
  self->text_hits_set("whips");
  self->thing_size_set(THING_SIZE_GIANT);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_MONST);
  delay = 350;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "D", .ascii_bg_col_name = "", .ascii_fg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "D", .ascii_bg_col_name = "", .ascii_fg_col_name = "orange", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "D", .ascii_bg_col_name = "", .ascii_fg_col_name = "yellow", .delay_ms = delay});
  my::tile(self, {.tile = "demon_fire.dead", .ascii_fg_char = "D", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
}

static void init(void)
{
  tp_init("demon_fire", "fire demon");
}

void module_init(void)
{
  native_register("demon_fire", "on_you_nat_attack_attempt", 3, [](const int64_t *a) -> NativeRet { (void) a; on_you_nat_attack_attempt((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("demon_fire", "on_hit_and_still_alive", 7, [](const int64_t *a) -> NativeRet { (void) a; on_hit_and_still_alive((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5], (int) a[6]); return NativeRet {}; });
  native_register("demon_fire", "on_hit_dodge_do", 4, [](const int64_t *a) -> NativeRet { (void) a; on_hit_dodge_do((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("demon_fire", "on_tick", 4, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_tick((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]), {}}; });
  native_register("demon_fire", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("demon_fire", "on_want_to_shoot_at", 4, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_want_to_shoot_at((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]), {}}; });
  init();
}

} // namespace mod_things_monsters_demon_fire
