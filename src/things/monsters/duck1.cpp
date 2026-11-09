//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/duck1.py
//

#include "my_native.hpp"

namespace mod_things_monsters_duck1 {

static void on_born(uint32_t me, int x, int y);
static void on_you_nat_attack_attempt(uint32_t me, int x, int y);
static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage);
static void on_hit_dodge_do(uint32_t me, uint32_t hitter, int x, int y);
static void on_death(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_born(uint32_t me, int x, int y)
{
  my::thing_friend(me, "is_duck");
}

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

static void on_death(uint32_t me, int x, int y)
{
  std::string sound;
  sound = std::string("squeaky_toy");
  if ((! my::thing_sound_play_channel(me, CHANNEL_MONST, (sound).c_str()))) {
    my::thing_sound_play_channel(me, CHANNEL_MONST_DEATH, (sound).c_str());
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name);
  self->aggression_pct_set(50);
  self->ai_resent_count_set(100);
  self->ai_wanderer_set(true);
  self->attack_eater_set(true);
  self->chance_d1000_tameable_set(200);
  self->collision_check_set(true);
  self->collision_hit_priority_set(20);
  self->consume_per_bite_amount_set(5);
  self->distance_avoid_set(5);
  self->distance_vision_set(5);
  self->dmg_bite_dice_set("1d4");
  self->dmg_chance_d1000_bite_set(0, 500);
  self->dmg_chance_d1000_claw_set(0, 500);
  self->dmg_chance_d1000_nat_att_set(0, 900);
  self->dmg_claw_dice_set("1d3");
  self->dmg_limited_per_tick_set(true);
  self->dmg_nat_att_dice_set("1d3+1");
  self->dmg_nat_att_type_set("webbed");
  self->environ_hates_fire_set(100);
  self->environ_likes_shallow_water_set(true);
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
  self->health_initial_dice_set("1d8");
  self->hunger_clock_tick_freq_set(50);
  self->is_able_to_be_surprised_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_freeze_set(true);
  self->is_able_to_live_out_of_water_set(true);
  self->is_able_to_lunge_set(true);
  self->is_able_to_rest_set(true);
  self->is_able_to_see_in_the_dark_set(true);
  self->is_able_to_swim_set(true);
  self->is_able_to_tire_set(true);
  self->is_air_breather_set(true);
  self->is_always_submerged_in_water_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_swamp_set(true);
  self->is_bleeder_set(true);
  self->is_buffable_set(true);
  self->is_burnable_set(true);
  self->is_corpse_on_death_set(true);
  self->is_corpse_with_bones_set(true);
  self->is_crushable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_duck_set(true);
  self->is_eater_of_meat_set(true);
  self->is_eater_of_plants_set(true);
  self->is_hittable_set(true);
  self->is_immune_to_water_set(true);
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
  self->is_red_blooded_set(true);
  self->is_shootable_set(true);
  self->is_soft_set(true);
  self->is_tickable_set(true);
  self->move_speed_set(50);
  self->noise_decibels_hearing_set(0);
  self->noise_on_moving_set(15);
  self->normal_placement_rules_set(true);
  self->on_born_do_set("me.on_born()");
  self->on_death_do_set("me.on_death()");
  self->on_hit_and_still_alive_do_set("me.on_hit_and_still_alive()");
  self->on_hit_dodge_do_set("me.on_hit_dodge_do()");
  self->on_you_nat_attack_attempt_do_set("me.on_you_nat_attack_attempt()");
  self->rarity_set(THING_RARITY_RARE);
  self->stamina_set(100);
  self->stat_con_set(10);
  self->stat_def_set(12);
  self->stat_dex_set(8);
  self->stat_luck_set(10);
  self->stat_psi_set(0);
  self->stat_str_set(8);
  self->temperature_max_set(50);
  self->temperature_min_set(0);
  self->temperature_set(20);
  self->temperature_sensitive_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("dungeon ducks");
  self->text_apostrophize_set("dungeon duck's");
  self->text_description_long2_set("They are not overly aggressive, but if slighted will hunt you down until the end of your days; as long as there is some nice water nearby.");
  self->text_description_long3_set("Do not be the kind of fool that underestimates the dreaded dungeon duck. Many warriors have met their end at a pair of webbed feet!");
  self->text_description_long_set("Dungeon ducks are a proud race, not dissimilar in appearance to their surface dwelling kin, they have evolved in the dark to be ferocious and independent.");
  self->text_description_short_set("A dungeon duck.");
  self->text_hits_set("beaks");
  self->thing_size_set(THING_SIZE_SMALL);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_MONST);
  delay = 200;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "d", .ascii_bg_col_name = "", .ascii_fg_col_name = "yellow", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "d", .ascii_bg_col_name = "", .ascii_fg_col_name = "yellow", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "d", .ascii_bg_col_name = "", .ascii_fg_col_name = "yellow", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "d", .ascii_bg_col_name = "", .ascii_fg_col_name = "yellow", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "d", .ascii_bg_col_name = "", .ascii_fg_col_name = "yellow", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "d", .ascii_bg_col_name = "", .ascii_fg_col_name = "yellow", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".dead"), .ascii_fg_char = "d", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
}

static void init(void)
{
  tp_init("duck1", "giant dungeon duck");
}

void module_init(void)
{
  native_register("duck1", "on_born", 3, [](const int64_t *a) -> NativeRet { (void) a; on_born((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("duck1", "on_you_nat_attack_attempt", 3, [](const int64_t *a) -> NativeRet { (void) a; on_you_nat_attack_attempt((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("duck1", "on_hit_and_still_alive", 7, [](const int64_t *a) -> NativeRet { (void) a; on_hit_and_still_alive((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5], (int) a[6]); return NativeRet {}; });
  native_register("duck1", "on_hit_dodge_do", 4, [](const int64_t *a) -> NativeRet { (void) a; on_hit_dodge_do((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("duck1", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_monsters_duck1
