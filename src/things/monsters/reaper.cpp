//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/reaper.py
//

#include "my_native.hpp"

namespace mod_things_monsters_reaper {

static void on_you_nat_attack_attempt(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_you_nat_attack_attempt(uint32_t me, int x, int y)
{
  std::string sound;
  sound = (std::string("hiss") + std::to_string(my::non_pcg_random_inclusive(1, 10)));
  my::thing_sound_play_channel(me, CHANNEL_MONST, (sound).c_str());
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name);
  self->aggression_pct_set(100);
  self->ai_resent_count_set(100);
  self->ai_wanderer_set(true);
  self->attack_humanoid_set(true);
  self->chance_d1000_tameable_set(0);
  self->collision_check_set(true);
  self->collision_hit_priority_set(20);
  self->distance_vision_set(7);
  self->dmg_chance_d1000_nat_att_set(0, 1000);
  self->dmg_chance_d1000_nat_att_set(1, 1000);
  self->dmg_nat_att_dice_set("1d6+6");
  self->dmg_nat_att_type_set("icy touch");
  self->dmg_num_of_attacks_set(2);
  self->dmg_rcv_doubled_from_water_set(true);
  self->environ_hates_water_set(100);
  self->gfx_anim_use_set("scythe_swing");
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
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->health_initial_dice_set("20d8");
  self->is_able_to_be_resurrected_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_change_levels_set(true);
  self->is_able_to_lunge_set(true);
  self->is_able_to_see_in_magical_darkness_set(true);
  self->is_able_to_see_in_the_dark_set(true);
  self->is_able_to_see_invisible_set(true);
  self->is_able_to_walk_through_walls_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_ice_set(true);
  self->is_buffable_set(true);
  self->is_corpse_on_death_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_ethereal_set(true);
  self->is_fearless_set(true);
  self->is_floating_set(true);
  self->is_hittable_set(true);
  self->is_immune_to_acid_set(true);
  self->is_immune_to_blinding_set(true);
  self->is_immune_to_cold_set(true);
  self->is_immune_to_confusion_set(true);
  self->is_immune_to_entrancement_set(true);
  self->is_immune_to_fire_set(true);
  self->is_immune_to_holy_damage_set(true);
  self->is_immune_to_necrosis_set(true);
  self->is_immune_to_negation_set(true);
  self->is_immune_to_non_magical_weapons_set(true);
  self->is_immune_to_paralysis_set(true);
  self->is_immune_to_poison_set(true);
  self->is_immune_to_spell_of_holding_set(true);
  self->is_immune_to_spell_of_sanctuary_set(true);
  self->is_immune_to_spell_of_slowness_set(true);
  self->is_immune_to_stamina_drain_set(true);
  self->is_immune_to_vorpal_weapons_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_monst_class_E_set(true);
  self->is_monst_set(true);
  self->is_moveable_set(true);
  self->is_msg_allowed_hears_something_set(true);
  self->is_msg_allowed_is_dead_set(true);
  self->is_msg_allowed_is_seen_set(true);
  self->is_msg_allowed_is_wounded_set(true);
  self->is_msg_allowed_senses_danger_set(true);
  self->is_one_per_tile_set(true);
  self->is_shootable_set(true);
  self->is_tickable_set(true);
  self->is_undead_set(true);
  self->is_very_intelligent_set(true);
  self->move_speed_set(100);
  self->noise_decibels_hearing_set(0);
  self->noise_on_moving_set(0);
  self->normal_placement_rules_set(true);
  self->on_you_nat_attack_attempt_do_set("me.on_you_nat_attack_attempt()");
  self->rarity_set(THING_RARITY_COMMON);
  self->resurrect_dice_set("1d10+30");
  self->stat_con_set(25);
  self->stat_def_set(25);
  self->stat_dex_set(10);
  self->stat_int_set(25);
  self->stat_luck_set(10);
  self->stat_psi_set(20);
  self->stat_str_set(25);
  self->temperature_set((-10));
  self->text_a_or_an_set("a");
  self->text_pluralize_set("reapers");
  self->text_apostrophize_set("reaper's");
  self->text_description_long_set("A lesser reaper. You cannot defeat what does not live!");
  self->text_description_short_set("A lesser reaper. Death incarnate.");
  self->text_hits_set("claws");
  self->thing_size_set(THING_SIZE_NORMAL);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_MONST);
  delay = 1000;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "R", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "R", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay});
  delay = 20;
  my::tile(self, {.tile = (name + ".dead.1"), .ascii_fg_char = "R", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
  my::tile(self, {.tile = (name + ".dead.2"), .ascii_fg_char = "R", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
  my::tile(self, {.tile = (name + ".dead.3"), .ascii_fg_char = "R", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
  my::tile(self, {.tile = (name + ".dead.4"), .ascii_fg_char = "R", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
  my::tile(self, {.tile = (name + ".dead.5"), .ascii_fg_char = "R", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .is_dead = true, .is_end_of_anim = true});
  my::tile(self, {.tile = (name + ".dead.5"), .ascii_fg_char = "R", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_resurrecting = true});
  my::tile(self, {.tile = (name + ".dead.4"), .ascii_fg_char = "R", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_resurrecting = true});
  my::tile(self, {.tile = (name + ".dead.3"), .ascii_fg_char = "R", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_resurrecting = true});
  my::tile(self, {.tile = (name + ".dead.2"), .ascii_fg_char = "R", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_resurrecting = true});
  my::tile(self, {.tile = (name + ".dead.1"), .ascii_fg_char = "R", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .is_end_of_anim = true, .is_alive_on_end_of_anim = true, .is_resurrecting = true});
}

static void init(void)
{
  tp_init("reaper", "reaper");
}

void module_init(void)
{
  native_register("reaper", "on_you_nat_attack_attempt", 3, [](const int64_t *a) -> NativeRet { (void) a; on_you_nat_attack_attempt((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_monsters_reaper
