//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/carcas_creeper.py
//

#include "my_native.hpp"

namespace mod_things_monsters_carcas_creeper {

static void on_you_nat_attack_attempt(uint32_t me, int x, int y);
static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage);
static void on_hit_dodge_do(uint32_t me, uint32_t hitter, int x, int y);
static void on_death(uint32_t me, int x, int y);
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
  self->ai_resent_count_set(10);
  self->ai_wanderer_set(true);
  self->attack_eater_set(true);
  self->chance_d1000_tameable_set(0);
  self->collision_check_set(true);
  self->collision_hit_priority_set(20);
  self->consume_per_bite_amount_set(2);
  self->distance_avoid_set(5);
  self->distance_vision_set(10);
  self->dmg_bite_dice_set("1d8");
  self->dmg_chance_d1000_bite_set(0, 500);
  self->dmg_chance_d1000_claw_set(0, 500);
  self->dmg_chance_d1000_nat_att_set(0, 500);
  self->dmg_chance_d1000_poison_set(0, 200);
  self->dmg_claw_dice_set("1d6");
  self->dmg_limited_per_tick_set(true);
  self->dmg_nat_att_dice_set("1d6+2");
  self->dmg_nat_att_type_set("gore");
  self->dmg_poison_dice_set("1d10");
  self->dmg_rcv_doubled_from_fire_set(true);
  self->environ_hates_fire_set(10);
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
  self->health_initial_dice_set("2d8");
  self->hunger_clock_tick_freq_set(50);
  self->hunger_is_insatiable_set(true);
  self->is_able_to_be_surprised_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_eat_poisonous_food_set(true);
  self->is_able_to_eat_rotting_food_set(true);
  self->is_able_to_eat_unpleasant_food_set(true);
  self->is_able_to_fall_set(true);
  self->is_able_to_freeze_set(true);
  self->is_able_to_lunge_set(true);
  self->is_able_to_rest_set(true);
  self->is_able_to_see_in_the_dark_set(true);
  self->is_able_to_sleep_set(true);
  self->is_able_to_swim_set(true);
  self->is_able_to_tire_set(true);
  self->is_air_breather_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_sewer_set(true);
  self->is_biome_swamp_set(true);
  self->is_bleeder_set(true);
  self->is_buffable_set(true);
  self->is_burnable_set(true);
  self->is_cautious_set(true);
  self->is_corpse_on_death_set(true);
  self->is_corpse_with_bones_set(true);
  self->is_crushable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_eater_of_fungus_set(true);
  self->is_eater_of_meat_set(true);
  self->is_eater_of_red_blood_set(true);
  self->is_heavy_set(true);
  self->is_hittable_set(true);
  self->is_immune_to_poison_set(true);
  self->is_interesting_set(true);
  self->is_living_set(true);
  self->is_loggable_set(true);
  self->is_meat_set(true);
  self->is_monst_class_A_set(true);
  self->is_monst_set(true);
  self->is_moveable_set(true);
  self->is_msg_allowed_hears_something_set(true);
  self->is_msg_allowed_is_dead_set(true);
  self->is_msg_allowed_is_seen_set(true);
  self->is_msg_allowed_is_wounded_set(true);
  self->is_poisonous_danger_level_set(4);
  self->is_red_blooded_set(true);
  self->is_shootable_set(true);
  self->is_shovable_set(true);
  self->is_tickable_set(true);
  self->move_speed_set(50);
  self->noise_decibels_hearing_set(10);
  self->noise_on_moving_set(25);
  self->normal_placement_rules_set(true);
  self->nutrition_dice_set("-30");
  self->on_death_do_set("me.on_death()");
  self->on_hit_and_still_alive_do_set("me.on_hit_and_still_alive()");
  self->on_hit_dodge_do_set("me.on_hit_dodge_do()");
  self->on_you_nat_attack_attempt_do_set("me.on_you_nat_attack_attempt()");
  self->rarity_set(THING_RARITY_COMMON);
  self->spawn_group_radius_set(10);
  self->spawn_group_size_dice_set("1d3+2");
  self->stamina_set(100);
  self->stat_con_set(12);
  self->stat_def_set(10);
  self->stat_dex_set(10);
  self->stat_luck_set(10);
  self->stat_psi_set(0);
  self->stat_str_set(12);
  self->temperature_max_set(50);
  self->temperature_min_set(0);
  self->temperature_set(20);
  self->temperature_sensitive_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("carcas creepers");
  self->text_apostrophize_set("carcas creeper's");
  self->text_description_long2_set("Watch out for its poisonous mandibles!");
  self->text_description_long_set("A hideous, and thankfully slow moving, crawling insectoid with sickly flesh coloured skin. This creature has a use however, that of clearing the dungeon of extraneous meaty detritus. Like you.");
  self->text_description_short_set("A disgusting carcass creeper.");
  self->text_hits_set("gores");
  self->thing_size_set(THING_SIZE_LARGE);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_MONST);
  delay = 200;
  my::tile(self, {.tile = "carcas_creeper.1", .ascii_fg_char = "c", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay});
  my::tile(self, {.tile = "carcas_creeper.2", .ascii_fg_char = "c", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay});
  my::tile(self, {.tile = "carcas_creeper.3", .ascii_fg_char = "c", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay});
  my::tile(self, {.tile = "carcas_creeper.4", .ascii_fg_char = "c", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay});
  my::tile(self, {.tile = "carcas_creeper.5", .ascii_fg_char = "c", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay});
  my::tile(self, {.tile = "carcas_creeper.6", .ascii_fg_char = "c", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay});
  my::tile(self, {.tile = "carcas_creeper.dead", .ascii_fg_char = "c", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
  delay = 1500;
  my::tile(self, {.tile = "carcas_creeper.1", .ascii_fg_char = "c", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .is_sleeping = true});
  my::tile(self, {.tile = "carcas_creeper.2", .ascii_fg_char = "C", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .is_sleeping = true});
}

static void init(void)
{
  tp_init("carcas_creeper", "carcass creeper");
}

void module_init(void)
{
  native_register("carcas_creeper", "on_you_nat_attack_attempt", 3, [](const int64_t *a) -> NativeRet { (void) a; on_you_nat_attack_attempt((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("carcas_creeper", "on_hit_and_still_alive", 7, [](const int64_t *a) -> NativeRet { (void) a; on_hit_and_still_alive((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5], (int) a[6]); return NativeRet {}; });
  native_register("carcas_creeper", "on_hit_dodge_do", 4, [](const int64_t *a) -> NativeRet { (void) a; on_hit_dodge_do((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("carcas_creeper", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_monsters_carcas_creeper
