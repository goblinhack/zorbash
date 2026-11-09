//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/skel_giant.py
//

#include "my_native.hpp"

namespace mod_things_monsters_skel_giant {

static void on_you_nat_attack_attempt(uint32_t me, int x, int y);
static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage);
static void on_hit_dodge_do(uint32_t me, uint32_t hitter, int x, int y);
static void on_death(uint32_t me, int x, int y);
static int on_rcv_dmg_melee(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

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
  my::thing_msg(me, "The skeleton collapses into a huge pile of bones!");
  my::thing_sound_play_channel(me, CHANNEL_MONST_DEATH, "monst_death1");
}

static int on_rcv_dmg_melee(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  if (my::thing_is_pointy(hitter)) {
    if (my::thing_is_player(real_hitter)) {
      my::thing_msg(me, ([&]() { auto t1_0_ = my::thing_name_get(me); auto t1_1_ = my::thing_name_get(hitter); return (std::string("The ") + t1_0_ + " takes half damage from your " + t1_1_ + "."); }()).c_str());
    }
    return ((int) (((int) std::ceil((double) ((double) damage / (double) 2)))));
  }
  return damage;
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name);
  self->aggression_pct_set(100);
  self->ai_resent_count_set(10);
  self->ai_wanderer_set(true);
  self->attack_humanoid_set(true);
  self->attack_meat_set(true);
  self->chance_d1000_shove_set(200);
  self->chance_d1000_tameable_set(0);
  self->collision_check_set(true);
  self->collision_hit_priority_set(20);
  self->consume_per_bite_amount_set(50);
  self->distance_avoid_set(2);
  self->distance_vision_set(7);
  self->dmg_nat_att_dice_set("1d6");
  self->dmg_nat_att_type_set("gore");
  self->dmg_rcv_doubled_from_water_set(true);
  self->environ_hates_water_set(100);
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
  self->gfx_pixelart_show_outlined_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->has_a_head_set(true);
  self->health_initial_dice_set("10d8");
  self->is_able_to_be_resurrected_set(true);
  self->is_able_to_be_surprised_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_change_levels_set(true);
  self->is_able_to_fall_set(true);
  self->is_able_to_lunge_set(true);
  self->is_able_to_see_in_the_dark_set(true);
  self->is_able_to_see_through_doors_set(true);
  self->is_able_to_use_weapons_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_biome_swamp_set(true);
  self->is_buffable_set(true);
  self->is_corpse_on_death_set(true);
  self->is_corpse_with_bones_set(true);
  self->is_crushable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_eater_of_red_blood_set(true);
  self->is_fearless_set(true);
  self->is_heavy_set(true);
  self->is_hittable_set(true);
  self->is_immune_to_blinding_set(true);
  self->is_immune_to_cold_set(true);
  self->is_immune_to_necrosis_set(true);
  self->is_immune_to_paralysis_set(true);
  self->is_immune_to_poison_set(true);
  self->is_immune_to_stamina_drain_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_magical_set(true);
  self->is_monst_class_C_set(true);
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
  self->is_skeleton_set(true);
  self->is_tickable_set(true);
  self->is_undead_set(true);
  self->move_speed_set(50);
  self->noise_decibels_hearing_set(50);
  self->noise_on_moving_set(45);
  self->normal_placement_rules_set(true);
  self->on_death_do_set("me.on_death()");
  self->on_hit_and_still_alive_do_set("me.on_hit_and_still_alive()");
  self->on_hit_dodge_do_set("me.on_hit_dodge_do()");
  self->on_rcv_dmg_melee_do_set("me.on_rcv_dmg_melee()");
  self->on_you_nat_attack_attempt_do_set("me.on_you_nat_attack_attempt()");
  self->rarity_set(THING_RARITY_COMMON);
  self->resurrect_dice_set("1d20+30");
  self->stat_con_set(20);
  self->stat_def_set(17);
  self->stat_dex_set(10);
  self->stat_int_set(8);
  self->stat_luck_set(10);
  self->stat_psi_set(8);
  self->stat_str_set(21);
  self->temperature_set(5);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("giant skeletons");
  self->text_apostrophize_set("giant skeleton's");
  self->text_description_long2_set("Takes half damage from pointy weapons.");
  self->text_description_long_set("A monstrous skeleton. It towers above you. It seems unhappy. Quite what body this skeleton came from, you hope not to find out. Water and fire are your friends here with creatures like this. Watch, these can rise again!");
  self->text_description_short_set("A monstrous skeleton, possibly unfriendly.");
  self->text_hits_set("claws");
  self->thing_size_set(THING_SIZE_GIANT);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_MONST);
  delay = 200;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_moving = true, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_moving = true, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_moving = true, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_moving = true, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_moving = true, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_moving = true, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_moving = true, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_moving = true, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_moving = true, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_moving = true, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_moving = true, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_moving = true, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_moving = true, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_moving = true, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_moving = true, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_moving = true, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_dir_none = true});
  delay = 20;
  my::tile(self, {.tile = (name + ".dead.1"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
  my::tile(self, {.tile = (name + ".dead.2"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
  my::tile(self, {.tile = (name + ".dead.3"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
  my::tile(self, {.tile = (name + ".dead.4"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true, .is_end_of_anim = true});
  delay = 200;
  my::tile(self, {.tile = (name + ".dead.4"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_resurrecting = true});
  my::tile(self, {.tile = (name + ".dead.3"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_resurrecting = true});
  my::tile(self, {.tile = (name + ".dead.2"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay, .is_resurrecting = true});
  my::tile(self, {.tile = (name + ".dead.1"), .ascii_fg_char = "K", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .is_end_of_anim = true, .is_alive_on_end_of_anim = true, .is_resurrecting = true});
}

static void init(void)
{
  tp_init("skel_giant", "giant skeleton");
}

void module_init(void)
{
  native_register("skel_giant", "on_you_nat_attack_attempt", 3, [](const int64_t *a) -> NativeRet { (void) a; on_you_nat_attack_attempt((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("skel_giant", "on_hit_and_still_alive", 7, [](const int64_t *a) -> NativeRet { (void) a; on_hit_and_still_alive((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5], (int) a[6]); return NativeRet {}; });
  native_register("skel_giant", "on_hit_dodge_do", 4, [](const int64_t *a) -> NativeRet { (void) a; on_hit_dodge_do((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("skel_giant", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("skel_giant", "on_rcv_dmg_melee", 6, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_rcv_dmg_melee((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5]), {}}; });
  init();
}

} // namespace mod_things_monsters_skel_giant
