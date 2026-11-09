//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/kraken.py
//

#include "my_native.hpp"

namespace mod_things_monsters_kraken {

static void on_born(uint32_t me, int x, int y);
static void on_you_nat_attack_attempt(uint32_t me, int x, int y);
static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage);
static void on_hit_dodge_do(uint32_t me, uint32_t hitter, int x, int y);
static void on_death(uint32_t me, int x, int y);
static void spawn_tentacle(uint32_t me, int x, int y, int dx, int dy);
static void on_awake(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_born(uint32_t me, int x, int y)
{
  my::place_at(me, "random_treasure_class_C", x, y);
}

static void on_you_nat_attack_attempt(uint32_t me, int x, int y)
{
  my::thing_sound_play_channel(me, CHANNEL_MONST, "monster_roar");
}

static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage)
{
  my::thing_sound_play_channel(me, CHANNEL_MONST, "monster_roar");
}

static void on_hit_dodge_do(uint32_t me, uint32_t hitter, int x, int y)
{
  my::thing_sound_play_channel(me, CHANNEL_MONST, "monster_roar");
}

static void on_death(uint32_t me, int x, int y)
{
  my::thing_sound_play_channel(me, CHANNEL_MONST_DEATH, "monst_death_epic");
}

static void spawn_tentacle(uint32_t me, int x, int y, int dx, int dy)
{
  if ((my::level_is_monst_at(me, (x + dx), (y + dy)) || my::level_is_lava_at(me, (x + dx), (y + dy)) || my::level_is_chasm_at(me, (x + dx), (y + dy)) || my::level_is_brazier_at(me, (x + dx), (y + dy)) || my::level_is_fire_at(me, (x + dx), (y + dy)) || my::level_is_wall_at(me, (x + dx), (y + dy)))) {
    return;
  }
  if ((! my::level_is_water_at(me, (x + dx), (y + dy)))) {
    return;
  }
  my::spawn_at(me, "kraken_tentacle", (x + dx), (y + dy));
}

static void on_awake(uint32_t me, int x, int y)
{
  my::thing_sound_play_channel(me, CHANNEL_MONST, "monster_roar_epic");
  my::thing_popup(me, "Deafening roar!");
  spawn_tentacle(me, x, y, (-1), 1);
  spawn_tentacle(me, x, y, (-1), 0);
  spawn_tentacle(me, x, y, (-1), (-1));
  spawn_tentacle(me, x, y, 1, 1);
  spawn_tentacle(me, x, y, 1, 0);
  spawn_tentacle(me, x, y, 1, (-1));
  spawn_tentacle(me, x, y, 0, 1);
  spawn_tentacle(me, x, y, 0, (-1));
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
  self->chance_d1000_tameable_set(0);
  self->collision_check_set(true);
  self->collision_hit_priority_set(20);
  self->consume_per_bite_amount_set(100);
  self->distance_vision_set(10);
  self->dmg_bite_dice_set("3d8+10");
  self->dmg_chance_d1000_bite_set(0, 200);
  self->dmg_chance_d1000_digest_set(0, 200);
  self->dmg_chance_d1000_drown_set(0, 800);
  self->dmg_digest_dice_set("1d20");
  self->dmg_drown_dice_set("1d20");
  self->environ_likes_deep_water_set(true);
  self->gfx_anim_use_set("attack_major_green");
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_can_hflip_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_health_bar_only_when_awake_set(true);
  self->gfx_pixelart_health_bar_shown_set(true);
  self->gfx_pixelart_oversized_and_centered_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->has_a_head_set(true);
  self->has_tentacles_set(true);
  self->health_initial_dice_set("8d10");
  self->hunger_clock_tick_freq_set(50);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_break_out_of_crystal_set(true);
  self->is_able_to_break_out_of_ice_set(true);
  self->is_able_to_break_out_of_webs_set(true);
  self->is_able_to_fall_set(true);
  self->is_able_to_freeze_set(true);
  self->is_able_to_lunge_set(true);
  self->is_able_to_rest_set(true);
  self->is_able_to_see_in_the_dark_set(true);
  self->is_able_to_spawn_things_set(true);
  self->is_able_to_tire_set(true);
  self->is_always_submerged_in_water_set(true);
  self->is_asleep_initially_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_bleeder_set(true);
  self->is_buffable_set(true);
  self->is_corpse_on_death_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_eater_of_meat_set(true);
  self->is_engulfer_set(true);
  self->is_green_blooded_set(true);
  self->is_heavy_set(true);
  self->is_hittable_set(true);
  self->is_immune_to_water_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_meat_set(true);
  self->is_monst_class_D_set(true);
  self->is_monst_set(true);
  self->is_moveable_set(true);
  self->is_msg_allowed_hears_something_set(true);
  self->is_msg_allowed_is_dead_set(true);
  self->is_obs_when_dead_set(true);
  self->is_shootable_set(true);
  self->is_soft_set(true);
  self->is_swimmer_set(true);
  self->is_tickable_set(true);
  self->light_color_set("green");
  self->light_dist_set(4);
  self->move_speed_set(50);
  self->noise_decibels_hearing_set(40);
  self->noise_on_moving_set(25);
  self->normal_placement_rules_set(true);
  self->on_awake_do_set("me.on_awake()");
  self->on_born_do_set("me.on_born()");
  self->on_death_do_set("me.on_death()");
  self->on_hit_and_still_alive_do_set("me.on_hit_and_still_alive()");
  self->on_hit_dodge_do_set("me.on_hit_dodge_do()");
  self->on_you_nat_attack_attempt_do_set("me.on_you_nat_attack_attempt()");
  self->rarity_set(THING_RARITY_RARE);
  self->stamina_set(100);
  self->stat_con_set(18);
  self->stat_def_set(18);
  self->stat_dex_set(8);
  self->stat_int_set(18);
  self->stat_luck_set(10);
  self->stat_psi_set(12);
  self->stat_str_set(20);
  self->temperature_max_set(50);
  self->temperature_min_set((-20));
  self->temperature_set(20);
  self->temperature_sensitive_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("krakens");
  self->text_apostrophize_set("kraken's");
  self->text_description_long_set("A mighty baby kraken. Beware the grasp of its tentacles and intoxicating fishy breath.");
  self->text_description_short_set("A baby kraken.");
  self->text_hits_set("bites");
  self->thing_size_set(THING_SIZE_GARGANTUAN);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_MONST);
  delay = 500;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".7"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".8"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  delay = 5000;
  my::tile(self, {.tile = "kraken.sleeping.1", .ascii_fg_char = "", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay, .is_sleeping = true});
  my::tile(self, {.tile = "kraken.sleeping.2", .ascii_fg_char = "o", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay, .is_sleeping = true});
  my::tile(self, {.tile = "kraken.sleeping.3", .ascii_fg_char = "", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay, .is_sleeping = true});
  my::tile(self, {.tile = "kraken.dead", .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
}

static void init(void)
{
  tp_init("kraken", "baby kraken");
}

void module_init(void)
{
  native_register("kraken", "on_born", 3, [](const int64_t *a) -> NativeRet { (void) a; on_born((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("kraken", "on_you_nat_attack_attempt", 3, [](const int64_t *a) -> NativeRet { (void) a; on_you_nat_attack_attempt((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("kraken", "on_hit_and_still_alive", 7, [](const int64_t *a) -> NativeRet { (void) a; on_hit_and_still_alive((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5], (int) a[6]); return NativeRet {}; });
  native_register("kraken", "on_hit_dodge_do", 4, [](const int64_t *a) -> NativeRet { (void) a; on_hit_dodge_do((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("kraken", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("kraken", "spawn_tentacle", 5, [](const int64_t *a) -> NativeRet { (void) a; spawn_tentacle((uint32_t) a[0], (int) a[1], (int) a[2], (int) a[3], (int) a[4]); return NativeRet {}; });
  native_register("kraken", "on_awake", 3, [](const int64_t *a) -> NativeRet { (void) a; on_awake((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_monsters_kraken
