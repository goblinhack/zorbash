//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/belcher.py
//

#include "my_native.hpp"

namespace mod_things_monsters_belcher {

static void on_you_nat_attack_attempt(uint32_t me, int x, int y);
static void on_idle(uint32_t me, int x, int y);
static void on_death(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_you_nat_attack_attempt(uint32_t me, int x, int y)
{
  my::thing_sound_play_channel(me, CHANNEL_MONST, "squelch");
}

static void on_idle(uint32_t me, int x, int y)
{
  if ((! my::thing_is_sleeping(me))) {
    my::spawn_gas_poison_around_thing(me, 2);
  }
}

static void on_death(uint32_t me, int x, int y)
{
  my::spawn_at_my_position(me, "green_splatter");
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->aggression_pct_set(100);
  self->ai_wanderer_set(true);
  self->attack_eater_set(true);
  self->chance_d1000_attack_engulf_set(1000);
  self->chance_d1000_tameable_set(0);
  self->collision_check_set(true);
  self->collision_hit_priority_set(20);
  self->consume_per_bite_amount_set(30);
  self->distance_vision_set(5);
  self->dmg_chance_d1000_digest_set(0, 1000);
  self->dmg_chance_d1000_nat_att_set(0, 1000);
  self->dmg_digest_dice_set("1d10");
  self->dmg_limited_per_tick_set(true);
  self->dmg_nat_att_dice_set("1d20");
  self->dmg_nat_att_type_set("burn");
  self->dmg_rcv_doubled_from_fire_set(true);
  self->gfx_anim_use_set("green_splatter");
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_bounce_on_move_set(true);
  self->gfx_pixelart_health_bar_shown_set(true);
  self->gfx_pixelart_oversized_and_on_floor_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->health_initial_dice_set("1d10+10");
  self->hunger_clock_tick_freq_set(50);
  self->hunger_is_insatiable_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_able_to_freeze_set(true);
  self->is_able_to_see_in_the_dark_set(true);
  self->is_asleep_initially_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_swamp_set(true);
  self->is_buffable_set(true);
  self->is_burnable_set(true);
  self->is_carnivorous_plant_set(true);
  self->is_combustible_set(true);
  self->is_corpse_on_death_set(true);
  self->is_crushable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_eater_of_meat_set(true);
  self->is_engulfer_set(true);
  self->is_green_blooded_set(true);
  self->is_heavy_set(true);
  self->is_hittable_set(true);
  self->is_immune_to_confusion_set(true);
  self->is_immune_to_entrancement_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_monst_class_B_set(true);
  self->is_monst_set(true);
  self->is_msg_allowed_hears_something_set(true);
  self->is_msg_allowed_is_dead_set(true);
  self->is_msg_allowed_is_seen_set(true);
  self->is_msg_allowed_is_wounded_set(true);
  self->is_msg_allowed_senses_danger_set(true);
  self->is_obs_when_dead_set(true);
  self->is_plant_set(true);
  self->is_shootable_set(true);
  self->is_shovable_set(true);
  self->is_soft_set(true);
  self->is_sticky_set(true);
  self->is_tickable_set(true);
  self->light_color_set("green");
  self->light_dist_set(2);
  self->move_speed_set(100);
  self->noise_decibels_hearing_set(50);
  self->noise_on_moving_set(5);
  self->normal_placement_rules_set(true);
  self->nutrition_dice_set("1d4");
  self->on_death_do_set("me.on_death()");
  self->on_idle_tick_freq_dice_set("1d5:me.on_idle()");
  self->on_you_nat_attack_attempt_do_set("me.on_you_nat_attack_attempt()");
  self->rarity_set(THING_RARITY_COMMON);
  self->stat_con_set(20);
  self->stat_def_set(0);
  self->stat_dex_set(0);
  self->stat_luck_set(10);
  self->stat_psi_set(0);
  self->stat_str_set(10);
  self->temperature_max_set(50);
  self->temperature_min_set(0);
  self->temperature_set(20);
  self->temperature_sensitive_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("dungeon belchers");
  self->text_apostrophize_set("dungeon belcher's");
  self->text_description_long_set("Dungeon belchers are carnivorous plants that have evolved creative means of catching their prey. Beware their stench...");
  self->text_description_short_set("A gaseous belcher. But don't call it that to its face.");
  self->text_hits_set("burns");
  self->thing_size_set(THING_SIZE_LARGE);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  delay = 200;
  my::tile(self, {.tile = (name + "_awake.1"), .ascii_fg_char = "B", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  my::tile(self, {.tile = (name + "_awake.2"), .ascii_fg_char = "B", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  my::tile(self, {.tile = (name + "_awake.3"), .ascii_fg_char = "B", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  my::tile(self, {.tile = (name + "_awake.4"), .ascii_fg_char = "B", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  my::tile(self, {.tile = (name + "_dead.1"), .ascii_fg_char = "B", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
  delay = 500;
  my::tile(self, {.tile = (name + "_asleep.1"), .ascii_fg_char = "b", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay, .is_sleeping = true});
  my::tile(self, {.tile = (name + "_asleep.2"), .ascii_fg_char = "B", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay, .is_sleeping = true});
  my::tile(self, {.tile = (name + "_asleep.3"), .ascii_fg_char = "b", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay, .is_sleeping = true});
  my::tile(self, {.tile = (name + "_asleep.2"), .ascii_fg_char = "B", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay, .is_sleeping = true});
}

static void init(void)
{
  tp_init("belcher", "dungeon belcher", "belcher");
}

void module_init(void)
{
  native_register("belcher", "on_you_nat_attack_attempt", 3, [](const int64_t *a) -> NativeRet { (void) a; on_you_nat_attack_attempt((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("belcher", "on_idle", 3, [](const int64_t *a) -> NativeRet { (void) a; on_idle((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("belcher", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_monsters_belcher
