//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/slime_parent.py
//

#include "my_native.hpp"

namespace mod_things_monsters_slime_parent {

static void on_you_nat_attack_attempt(uint32_t me, int x, int y);
static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage);
static void on_death(uint32_t me, int x, int y);
static void on_jump(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_you_nat_attack_attempt(uint32_t me, int x, int y)
{
  my::thing_sound_play_channel(me, CHANNEL_MONST, "slime_attack");
}

static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage)
{
  my::thing_sound_play_channel(me, CHANNEL_MONST, "slime_attack");
}

static void on_death(uint32_t me, int x, int y)
{
  bool splits = false;
  splits = false;
  if (my::thing_is_frozen(me)) {
    return;
  }
  if (my::thing_is_burnt(me)) {
    return;
  }
  for (int i = 1, i_end_ = 8; i < i_end_; i += 1) {
    if ((my::pcg_random_inclusive(1, 100) < 80)) {
      if ((my::spawn_next_to(me, "slime_baby") != 0)) {
        splits = true;
      }
    }
  }
  if (splits) {
    my::thing_msg(me, "The slime splits!");
  }
  my::thing_sound_play_channel(me, CHANNEL_MONST, ((std::string("slime") + std::to_string(my::non_pcg_random_inclusive(1, 9)))).c_str());
}

static void on_jump(uint32_t me, int x, int y)
{
  my::thing_sound_play_channel(me, CHANNEL_MONST, "slime_jump");
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name);
  self->aggression_pct_set(100);
  self->ai_resent_count_set(10);
  self->ai_wanderer_set(true);
  self->attack_eater_set(true);
  self->capacity_height_set(8);
  self->capacity_width_set(8);
  self->chance_d1000_jump_attack_set(200);
  self->chance_d1000_jump_on_low_hp_set(500);
  self->chance_d1000_jump_randomly_set(2);
  self->chance_d1000_tameable_set(0);
  self->collision_check_set(true);
  self->collision_hit_priority_set(20);
  self->consume_per_bite_amount_set(5);
  self->distance_avoid_set(3);
  self->distance_vision_set(7);
  self->dmg_acid_dice_set("1d6");
  self->dmg_chance_d1000_acid_set(0, 500);
  self->dmg_chance_d1000_nat_att_set(0, 500);
  self->dmg_nat_att_dice_set("2d6+2");
  self->dmg_nat_att_type_set("bludgeon");
  self->dmg_rcv_doubled_from_cold_set(true);
  self->dmg_rcv_doubled_from_fire_set(true);
  self->environ_hates_fire_set(100);
  self->gfx_anim_use_set("green_splatter");
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
  self->gfx_pixelart_show_outlined_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->health_initial_dice_set("10");
  self->hunger_clock_tick_freq_set(50);
  self->hunger_is_insatiable_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_able_to_freeze_set(true);
  self->is_able_to_jump_attack_set(true);
  self->is_able_to_jump_escape_set(true);
  self->is_able_to_jump_set(true);
  self->is_able_to_lunge_set(true);
  self->is_able_to_see_in_the_dark_set(true);
  self->is_acid_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_swamp_set(true);
  self->is_bleeder_set(true);
  self->is_buffable_set(true);
  self->is_burnable_set(true);
  self->is_crushable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_eater_of_green_blood_set(true);
  self->is_eater_of_magical_items_set(true);
  self->is_eater_of_meat_set(true);
  self->is_eater_of_potions_set(true);
  self->is_eater_of_red_blood_set(true);
  self->is_eater_of_rings_set(true);
  self->is_eater_of_slime_set(true);
  self->is_fearless_set(true);
  self->is_green_blooded_set(true);
  self->is_hittable_set(true);
  self->is_immune_to_acid_set(true);
  self->is_immune_to_necrosis_set(true);
  self->is_interesting_set(true);
  self->is_item_collector_set(true);
  self->is_living_set(true);
  self->is_loggable_set(true);
  self->is_monst_class_A_set(true);
  self->is_monst_set(true);
  self->is_moveable_set(true);
  self->is_msg_allowed_hears_something_set(true);
  self->is_msg_allowed_is_dead_set(true);
  self->is_msg_allowed_is_seen_set(true);
  self->is_msg_allowed_is_wounded_set(true);
  self->is_msg_allowed_senses_danger_set(true);
  self->is_shootable_set(true);
  self->is_slime_set(true);
  self->is_soft_set(true);
  self->is_thief_set(true);
  self->is_tickable_set(true);
  self->jump_distance_set(3);
  self->move_speed_set(50);
  self->noise_decibels_hearing_set(50);
  self->noise_on_moving_set(25);
  self->normal_placement_rules_set(true);
  self->nutrition_dice_set("1d4");
  self->on_death_do_set("me.on_death()");
  self->on_hit_and_still_alive_do_set("me.on_hit_and_still_alive()");
  self->on_jump_do_set("me.on_jump()");
  self->on_you_nat_attack_attempt_do_set("me.on_you_nat_attack_attempt()");
  self->rarity_set(THING_RARITY_COMMON);
  self->stat_con_set(14);
  self->stat_def_set(8);
  self->stat_dex_set(10);
  self->stat_luck_set(10);
  self->stat_psi_set(0);
  self->stat_str_set(15);
  self->temperature_max_set(50);
  self->temperature_min_set(0);
  self->temperature_set(20);
  self->temperature_sensitive_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("slime jumpers");
  self->text_apostrophize_set("slime jumper's");
  self->text_description_long2_set("This is an adult. It will eat its own children, and you!");
  self->text_description_long_set("Slime jumpers are numerous, bouncy and carnivorous. They will eat almost anything, including their own. They have the annoying habit of jumping when threatened and dividing when defeated.");
  self->text_description_short_set("A gargantuan pile of sentient slime.");
  self->text_hits_set("splats");
  self->thing_size_set(THING_SIZE_LARGE);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_MONST);
  delay = 200;
  my::tile(self, {.tile = (name + ".1.100"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_100_percent = true});
  my::tile(self, {.tile = (name + ".2.100"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_100_percent = true});
  my::tile(self, {.tile = (name + ".3.100"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_100_percent = true});
  my::tile(self, {.tile = (name + ".4.100"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_100_percent = true});
  my::tile(self, {.tile = (name + ".5.100"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_100_percent = true});
  my::tile(self, {.tile = (name + ".6.100"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_100_percent = true});
  my::tile(self, {.tile = (name + ".7.100"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_100_percent = true});
  my::tile(self, {.tile = (name + ".8.100"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_100_percent = true});
  my::tile(self, {.tile = (name + ".1.75"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_75_percent = true});
  my::tile(self, {.tile = (name + ".2.75"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_75_percent = true});
  my::tile(self, {.tile = (name + ".3.75"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_75_percent = true});
  my::tile(self, {.tile = (name + ".4.75"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_75_percent = true});
  my::tile(self, {.tile = (name + ".5.75"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_75_percent = true});
  my::tile(self, {.tile = (name + ".6.75"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_75_percent = true});
  my::tile(self, {.tile = (name + ".7.75"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_75_percent = true});
  my::tile(self, {.tile = (name + ".8.75"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_75_percent = true});
  my::tile(self, {.tile = (name + ".1.50"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_50_percent = true});
  my::tile(self, {.tile = (name + ".2.50"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_50_percent = true});
  my::tile(self, {.tile = (name + ".3.50"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_50_percent = true});
  my::tile(self, {.tile = (name + ".4.50"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_50_percent = true});
  my::tile(self, {.tile = (name + ".5.50"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_50_percent = true});
  my::tile(self, {.tile = (name + ".6.50"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_50_percent = true});
  my::tile(self, {.tile = (name + ".7.50"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_50_percent = true});
  my::tile(self, {.tile = (name + ".8.50"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_50_percent = true});
  my::tile(self, {.tile = (name + ".1.25"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_25_percent = true});
  my::tile(self, {.tile = (name + ".2.25"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_25_percent = true});
  my::tile(self, {.tile = (name + ".3.25"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_25_percent = true});
  my::tile(self, {.tile = (name + ".4.25"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_25_percent = true});
  my::tile(self, {.tile = (name + ".5.25"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_25_percent = true});
  my::tile(self, {.tile = (name + ".6.25"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_25_percent = true});
  my::tile(self, {.tile = (name + ".7.25"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_25_percent = true});
  my::tile(self, {.tile = (name + ".8.25"), .ascii_fg_char = "J", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = delay, .is_hp_25_percent = true});
}

static void init(void)
{
  tp_init("slime_parent", "slime jumper");
}

void module_init(void)
{
  native_register("slime_parent", "on_you_nat_attack_attempt", 3, [](const int64_t *a) -> NativeRet { (void) a; on_you_nat_attack_attempt((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("slime_parent", "on_hit_and_still_alive", 7, [](const int64_t *a) -> NativeRet { (void) a; on_hit_and_still_alive((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5], (int) a[6]); return NativeRet {}; });
  native_register("slime_parent", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("slime_parent", "on_jump", 3, [](const int64_t *a) -> NativeRet { (void) a; on_jump((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_monsters_slime_parent
