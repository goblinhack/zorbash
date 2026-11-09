//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/golem_cement.py
//

#include "my_native.hpp"

namespace mod_things_monsters_golem_cement {

static void on_you_nat_attack_attempt(uint32_t me, int x, int y);
static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage);
static void on_hit_dodge_do(uint32_t me, uint32_t hitter, int x, int y);
static bool on_tick(uint32_t owner, uint32_t me, int x, int y);
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

static bool on_tick(uint32_t owner, uint32_t me, int x, int y)
{
  if ([&]() { auto t1_0_ = my::thing_health(me); auto t1_1_ = my::thing_health_max(me); return (t1_0_ < t1_1_); }()) {
    my::thing_health_incr(me, 1);
    return true;
  }
  return false;
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
  self->attack_living_set(true);
  self->attack_meat_set(true);
  self->chance_d1000_shove_set(500);
  self->chance_d1000_tameable_set(0);
  self->collision_check_set(true);
  self->collision_hit_priority_set(20);
  self->distance_vision_set(5);
  self->dmg_chance_d1000_nat_att_set(0, 1000);
  self->dmg_chance_d1000_nat_att_set(1, 1000);
  self->dmg_nat_att_dice_set("3d8+6");
  self->dmg_nat_att_type_set("gore");
  self->gfx_anim_use_set("attack_red");
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
  self->health_initial_dice_set("11d8+44");
  self->hunger_is_insatiable_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_change_levels_set(true);
  self->is_able_to_fall_set(true);
  self->is_able_to_freeze_set(true);
  self->is_able_to_lunge_set(true);
  self->is_able_to_see_in_the_dark_set(true);
  self->is_allied_with_set("golem_cement");
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_lava_set(true);
  self->is_buffable_set(true);
  self->is_burnable_set(true);
  self->is_corpse_on_death_set(true);
  self->is_crushable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_fearless_set(true);
  self->is_golem_set(true);
  self->is_heavy_set(true);
  self->is_hittable_set(true);
  self->is_immune_to_cold_set(true);
  self->is_immune_to_confusion_set(true);
  self->is_immune_to_entrancement_set(true);
  self->is_immune_to_fire_set(true);
  self->is_immune_to_poison_set(true);
  self->is_immune_to_stamina_drain_set(true);
  self->is_interesting_set(true);
  self->is_lifeless_set(true);
  self->is_loggable_set(true);
  self->is_made_of_rock_set(true);
  self->is_magical_set(true);
  self->is_monst_class_C_set(true);
  self->is_monst_set(true);
  self->is_moveable_set(true);
  self->is_msg_allowed_hears_something_set(true);
  self->is_msg_allowed_is_dead_set(true);
  self->is_msg_allowed_is_seen_set(true);
  self->is_msg_allowed_is_wounded_set(true);
  self->is_shootable_set(true);
  self->is_shovable_set(true);
  self->is_stone_set(true);
  self->is_tickable_set(true);
  self->is_tireless_set(true);
  self->is_vanquished_on_negation_set(true);
  self->is_very_hard_set(true);
  self->move_speed_set(30);
  self->noise_decibels_hearing_set(100);
  self->noise_on_moving_set(20);
  self->normal_placement_rules_set(true);
  self->on_hit_and_still_alive_do_set("me.on_hit_and_still_alive()");
  self->on_hit_dodge_do_set("me.on_hit_dodge_do()");
  self->on_you_nat_attack_attempt_do_set("me.on_you_nat_attack_attempt()");
  self->rarity_set(THING_RARITY_COMMON);
  self->shove_bonus_set(3);
  self->stat_att_penalty_when_in_deep_water_set(2);
  self->stat_att_penalty_when_in_shallow_water_set(1);
  self->stat_con_set(18);
  self->stat_def_penalty_when_in_deep_water_set(2);
  self->stat_def_penalty_when_in_shallow_water_set(1);
  self->stat_def_set(17);
  self->stat_dex_set(9);
  self->stat_int_set(0);
  self->stat_luck_set(1);
  self->stat_psi_set(0);
  self->stat_str_set(22);
  self->temperature_set(20);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("cement golems");
  self->text_apostrophize_set("cement golem's");
  self->text_description_long2_set("Cement men are able to slowly recharge health.");
  self->text_description_long3_set("Makes an excellent patio ornament.");
  self->text_description_long_set("A hideous mass of animated cement. Possibly brought into being by an evil necromancer who was annoyed with constant roadworks. Cement men are immune to cold, poison, fire and draining attacks.");
  self->text_description_short_set("A cement man.");
  self->text_hits_set("claws");
  self->thing_size_set(THING_SIZE_LARGE);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BIG_MONST);
  delay = 500;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "C", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray80", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "C", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray80", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "C", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray80", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "C", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray80", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "C", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray80", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".dead.1"), .ascii_fg_char = "C", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
  my::tile(self, {.tile = (name + ".dead.2"), .ascii_fg_char = "C", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
  my::tile(self, {.tile = (name + ".dead.3"), .ascii_fg_char = "C", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .is_dead = true, .is_end_of_anim = true});
}

static void init(void)
{
  tp_init("golem_cement", "cement man");
}

void module_init(void)
{
  native_register("golem_cement", "on_you_nat_attack_attempt", 3, [](const int64_t *a) -> NativeRet { (void) a; on_you_nat_attack_attempt((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("golem_cement", "on_hit_and_still_alive", 7, [](const int64_t *a) -> NativeRet { (void) a; on_hit_and_still_alive((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5], (int) a[6]); return NativeRet {}; });
  native_register("golem_cement", "on_hit_dodge_do", 4, [](const int64_t *a) -> NativeRet { (void) a; on_hit_dodge_do((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("golem_cement", "on_tick", 4, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_tick((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]), {}}; });
  init();
}

} // namespace mod_things_monsters_golem_cement
