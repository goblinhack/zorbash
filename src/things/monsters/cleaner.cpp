//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/cleaner.py
//

#include "my_native.hpp"

namespace mod_things_monsters_cleaner {

static void on_you_nat_attack_attempt(uint32_t me, int x, int y);
static void on_idle(uint32_t me, int x, int y);
static void on_move(uint32_t me, int x, int y);
static void on_death(uint32_t me, int x, int y);
static void explode(uint32_t me, int x, int y);
static void on_fire(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_you_nat_attack_attempt(uint32_t me, int x, int y)
{
  my::thing_sound_play_channel(me, CHANNEL_MONST, "squelch");
}

static void on_idle(uint32_t me, int x, int y)
{
  if ((! my::level_is_acid_at(me, x, y))) {
    my::spawn_at_my_position(me, "acid1");
  }
}

static void on_move(uint32_t me, int x, int y)
{
  for (auto it : my::level_get_all(me, x, y)) {
    if (my::thing_possible_to_attack(me, it)) {
      if (my::thing_is_player(it)) {
        my::thing_msg(me, "The dungeon cleaner engulfs you!");
      } else {
        my::thing_msg(me, ((std::string("The dungeon cleaner engulfs the ") + my::thing_name_get(it) + ".")).c_str());
      }
    }
  }
}

static void on_death(uint32_t me, int x, int y)
{
  my::spawn_at_my_position(me, "green_splatter");
}

static void explode(uint32_t me, int x, int y)
{
  if (my::thing_is_dead(me)) {
    return;
  }
  my::thing_dead(me, "exploded");
  my::thing_msg(me, "The dungeon cleaner erupts in flaming goo!");
  my::spawn_at_my_position(me, "explosion_major");
  my::spawn_set_fire_to_things_around_me(me, "fire");
  my::spawn_at_my_position(me, "fire");
}

static void on_fire(uint32_t me, int x, int y)
{
  explode(me, x, y);
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->aggression_pct_set(100);
  self->ai_wanderer_set(true);
  self->attack_eater_set(true);
  self->capacity_height_set(10);
  self->capacity_width_set(10);
  self->chance_d1000_attack_engulf_set(1000);
  self->chance_d1000_carrier_of_treasure_class_A_set(1000);
  self->chance_d1000_carrier_of_treasure_class_B_set(500);
  self->chance_d1000_carrier_of_treasure_class_C_set(100);
  self->chance_d1000_steal_item_set(200);
  self->chance_d1000_tameable_set(0);
  self->collision_check_set(true);
  self->collision_hit_priority_set(20);
  self->consume_per_bite_amount_set(50);
  self->distance_vision_set(3);
  self->dmg_chance_d1000_digest_set(0, 1000);
  self->dmg_chance_d1000_nat_att_set(0, 1000);
  self->dmg_digest_dice_set("1d40");
  self->dmg_nat_att_dice_set("1d10");
  self->dmg_nat_att_type_set("burn");
  self->dmg_rcv_doubled_from_cold_set(true);
  self->dmg_rcv_doubled_from_fire_set(true);
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
  self->gfx_pixelart_submergible_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->health_initial_dice_set("8d10+40");
  self->hunger_clock_tick_freq_set(50);
  self->hunger_is_insatiable_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_eat_rotting_food_set(true);
  self->is_able_to_eat_unpleasant_food_set(true);
  self->is_able_to_fall_set(true);
  self->is_able_to_freeze_set(true);
  self->is_able_to_lunge_set(true);
  self->is_able_to_see_in_the_dark_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_bleeder_set(true);
  self->is_buffable_set(true);
  self->is_burnable_set(true);
  self->is_combustible_set(true);
  self->is_crushable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_eater_of_amulets_set(true);
  self->is_eater_of_armor_set(true);
  self->is_eater_of_boots_set(true);
  self->is_eater_of_cloaks_set(true);
  self->is_eater_of_food_set(true);
  self->is_eater_of_gauntlets_set(true);
  self->is_eater_of_green_blood_set(true);
  self->is_eater_of_helmets_set(true);
  self->is_eater_of_magical_items_set(true);
  self->is_eater_of_meat_set(true);
  self->is_eater_of_potions_set(true);
  self->is_eater_of_red_blood_set(true);
  self->is_eater_of_rings_set(true);
  self->is_eater_of_shields_set(true);
  self->is_eater_of_slime_set(true);
  self->is_eater_of_staffs_set(true);
  self->is_eater_of_treasure_set(true);
  self->is_eater_of_weapons_set(true);
  self->is_engulfer_set(true);
  self->is_gelatinous_set(true);
  self->is_green_blooded_set(true);
  self->is_heavy_set(true);
  self->is_hittable_set(true);
  self->is_immune_to_acid_set(true);
  self->is_immune_to_necrosis_set(true);
  self->is_interesting_set(true);
  self->is_item_collector_set(true);
  self->is_loggable_set(true);
  self->is_monst_class_B_set(true);
  self->is_monst_set(true);
  self->is_moveable_set(true);
  self->is_msg_allowed_hears_something_set(true);
  self->is_msg_allowed_is_dead_set(true);
  self->is_msg_allowed_is_seen_set(true);
  self->is_msg_allowed_is_wounded_set(true);
  self->is_msg_allowed_senses_danger_set(true);
  self->is_shootable_set(true);
  self->is_soft_set(true);
  self->is_sticky_set(true);
  self->is_thief_set(true);
  self->is_tickable_set(true);
  self->light_color_set("green");
  self->light_dist_set(2);
  self->move_speed_set(50);
  self->noise_decibels_hearing_set(50);
  self->noise_on_moving_set(15);
  self->normal_placement_rules_set(true);
  self->nutrition_dice_set("1d4");
  self->on_death_do_set("me.on_death()");
  self->on_death_drop_all_items_set(true);
  self->on_idle_tick_freq_dice_set("1d5:me.on_idle()");
  self->on_move_do_set("me.on_move()");
  self->on_you_are_on_fire_do_set("me.on_fire()");
  self->on_you_nat_attack_attempt_do_set("me.on_you_nat_attack_attempt()");
  self->rarity_set(THING_RARITY_COMMON);
  self->stat_con_set(20);
  self->stat_def_set(6);
  self->stat_dex_set(3);
  self->stat_luck_set(10);
  self->stat_psi_set(0);
  self->stat_str_set(14);
  self->stat_thv_set(14);
  self->temperature_max_set(50);
  self->temperature_min_set(0);
  self->temperature_set(20);
  self->temperature_sensitive_set(true);
  self->temperature_sensitive_to_sudden_changes_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("dungeon cleaners");
  self->text_apostrophize_set("dungeon cleaner's");
  self->text_description_long_set("Dungeon cleaners have evolved to scrub their domain of all messy organic matter. That means you. Cleaners leave a trail of corrosive slime in their wake. Avoid this. Cleaners also have a habit of eating your hard fought items.");
  self->text_description_short_set("A dungeon auto cleaner slime thingy.");
  self->text_hits_set("burns");
  self->thing_size_set(THING_SIZE_LARGE);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_CONSUMER);
  delay = 200;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "C", .ascii_bg_char = "block", .ascii_bg_col_name = "deeppink2", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "C", .ascii_bg_char = "block", .ascii_bg_col_name = "deeppink3", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "C", .ascii_bg_char = "block", .ascii_bg_col_name = "deeppink", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "C", .ascii_bg_char = "block", .ascii_bg_col_name = "deeppink4", .ascii_fg_col_name = "white", .delay_ms = delay});
}

static void init(void)
{
  tp_init("cleaner", "dungeon cleaner", "cleaner");
}

void module_init(void)
{
  native_register("cleaner", "on_you_nat_attack_attempt", 3, [](const int64_t *a) -> NativeRet { (void) a; on_you_nat_attack_attempt((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("cleaner", "on_idle", 3, [](const int64_t *a) -> NativeRet { (void) a; on_idle((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("cleaner", "on_move", 3, [](const int64_t *a) -> NativeRet { (void) a; on_move((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("cleaner", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("cleaner", "explode", 3, [](const int64_t *a) -> NativeRet { (void) a; explode((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("cleaner", "on_fire", 3, [](const int64_t *a) -> NativeRet { (void) a; on_fire((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_monsters_cleaner
