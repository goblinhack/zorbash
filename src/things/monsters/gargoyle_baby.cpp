//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/gargoyle_baby.py
//

#include "my_native.hpp"

namespace mod_things_monsters_gargoyle_baby {

static void on_you_nat_attack_attempt(uint32_t me, int x, int y);
static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage);
static void on_hit_dodge_do(uint32_t me, uint32_t hitter, int x, int y);
static void on_death(uint32_t me, int x, int y);
static void on_awake(uint32_t me, int x, int y);
static bool on_want_to_shoot_at(uint32_t me, uint32_t target, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_you_nat_attack_attempt(uint32_t me, int x, int y)
{
  std::string sound;
  sound = (std::string("growl") + std::to_string(my::non_pcg_random_inclusive(1, 10)));
  my::thing_sound_play_channel(me, CHANNEL_MONST, (sound).c_str());
}

static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage)
{
  std::string sound;
  sound = (std::string("growl") + std::to_string(my::non_pcg_random_inclusive(1, 10)));
  my::thing_sound_play_channel(me, CHANNEL_MONST, (sound).c_str());
}

static void on_hit_dodge_do(uint32_t me, uint32_t hitter, int x, int y)
{
  my::thing_sound_play_channel(me, CHANNEL_MONST, "monster_roar");
}

static void on_death(uint32_t me, int x, int y)
{
  my::thing_sound_play_channel(me, CHANNEL_MONST_DEATH, "monst_death1");
}

static void on_awake(uint32_t me, int x, int y)
{
  std::string sound;
  sound = (std::string("growl") + std::to_string(my::non_pcg_random_inclusive(1, 10)));
  my::thing_sound_play_channel(me, CHANNEL_MONST, (sound).c_str());
  my::thing_speaks(me, "Who dares wake me\?");
  my::thing_popup(me, "Tiny roar!");
}

static bool on_want_to_shoot_at(uint32_t me, uint32_t target, int x, int y)
{
  std::string sound;
  sound = (std::string("growl") + std::to_string(my::non_pcg_random_inclusive(1, 10)));
  my::thing_sound_play_channel(me, CHANNEL_MONST, (sound).c_str());
  my::thing_shoot_projectile_or_laser_at(me, "projectile_fire", target);
  return true;
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name);
  self->aggression_pct_set(100);
  self->ai_resent_count_set(100);
  self->attack_humanoid_set(true);
  self->attack_meat_set(true);
  self->chance_d1000_shooting_set(250);
  self->chance_d1000_tameable_set(0);
  self->collision_check_set(true);
  self->collision_hit_priority_set(20);
  self->distance_vision_set(10);
  self->dmg_nat_att_dice_set("1d6");
  self->dmg_nat_att_type_set("gore");
  self->gfx_anim_use_set("attack_red");
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_health_bar_only_when_awake_set(true);
  self->gfx_pixelart_health_bar_shown_set(true);
  self->gfx_pixelart_oversized_and_on_floor_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->has_a_head_set(true);
  self->health_initial_dice_set("1d8+20");
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_able_to_freeze_set(true);
  self->is_able_to_see_in_the_dark_set(true);
  self->is_able_to_shoot_at_set(true);
  self->is_able_to_sleep_set(true);
  self->is_asleep_initially_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_buffable_set(true);
  self->is_corpse_on_death_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_hittable_set(true);
  self->is_immune_to_cold_set(true);
  self->is_immune_to_necrosis_set(true);
  self->is_immune_to_poison_set(true);
  self->is_immune_to_stamina_drain_set(true);
  self->is_immune_to_vorpal_weapons_set(true);
  self->is_immune_to_water_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_monst_class_C_set(true);
  self->is_monst_set(true);
  self->is_msg_allowed_hears_something_set(true);
  self->is_msg_allowed_is_dead_set(true);
  self->is_msg_allowed_is_seen_set(true);
  self->is_msg_allowed_is_wounded_set(true);
  self->is_msg_allowed_senses_danger_set(true);
  self->is_shootable_set(true);
  self->is_shovable_set(true);
  self->is_stone_set(true);
  self->is_tickable_set(true);
  self->is_very_hard_set(true);
  self->is_very_heavy_set(true);
  self->move_speed_set(100);
  self->noise_decibels_hearing_set(50);
  self->noise_on_moving_set(5);
  self->normal_placement_rules_set(true);
  self->on_awake_do_set("me.on_awake()");
  self->on_death_do_set("me.on_death()");
  self->on_hit_and_still_alive_do_set("me.on_hit_and_still_alive()");
  self->on_hit_dodge_do_set("me.on_hit_dodge_do()");
  self->on_want_to_shoot_at_do_set("me.on_want_to_shoot_at()");
  self->on_you_nat_attack_attempt_do_set("me.on_you_nat_attack_attempt()");
  self->rarity_set(THING_RARITY_COMMON);
  self->stat_con_set(16);
  self->stat_def_set(10);
  self->stat_dex_set(0);
  self->stat_int_set(14);
  self->stat_luck_set(10);
  self->stat_psi_set(14);
  self->stat_str_set(12);
  self->temperature_set(20);
  self->temperature_sensitive_to_sudden_changes_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("gargoyle babies");
  self->text_apostrophize_set("baby gargoyle's");
  self->text_description_long2_set("This particular gargoyle is just starting out in its career, hence the diminutive stature. It is not as capable as its mature form, but is still to be feared...");
  self->text_description_long_set("This small creature guards the dungeon from the likes of you. Gargoyles lurk amongst the ruins and delight in the art of surprise...");
  self->text_description_short_set("A fearsome gargoyle.");
  self->text_hits_set("slashes");
  self->thing_size_set(THING_SIZE_NORMAL);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  delay = 10000;
  my::tile(self, {.tile = "gargoyle_baby.sleeping", .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray70", .delay_ms = delay, .is_sleeping = true});
  delay = 300;
  my::tile(self, {.tile = "gargoyle_baby.1", .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray70", .delay_ms = delay});
  my::tile(self, {.tile = "gargoyle_baby.2", .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray70", .delay_ms = delay});
  my::tile(self, {.tile = "gargoyle_baby.3", .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray70", .delay_ms = delay});
  my::tile(self, {.tile = "gargoyle_baby.dead", .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
}

static void init(void)
{
  tp_init("gargoyle_baby", "gargoyle baby");
}

void module_init(void)
{
  native_register("gargoyle_baby", "on_you_nat_attack_attempt", 3, [](const int64_t *a) -> NativeRet { (void) a; on_you_nat_attack_attempt((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("gargoyle_baby", "on_hit_and_still_alive", 7, [](const int64_t *a) -> NativeRet { (void) a; on_hit_and_still_alive((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5], (int) a[6]); return NativeRet {}; });
  native_register("gargoyle_baby", "on_hit_dodge_do", 4, [](const int64_t *a) -> NativeRet { (void) a; on_hit_dodge_do((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("gargoyle_baby", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("gargoyle_baby", "on_awake", 3, [](const int64_t *a) -> NativeRet { (void) a; on_awake((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("gargoyle_baby", "on_want_to_shoot_at", 4, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_want_to_shoot_at((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]), {}}; });
  init();
}

} // namespace mod_things_monsters_gargoyle_baby
