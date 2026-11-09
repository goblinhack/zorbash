//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/ghost_minion.py
//

#include "my_native.hpp"

namespace mod_things_monsters_ghost_minion {

static void on_you_nat_attack_attempt(uint32_t me, int x, int y);
static void on_death(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_you_nat_attack_attempt(uint32_t me, int x, int y)
{
  std::string sound;
  sound = (std::string("hiss") + std::to_string(my::non_pcg_random_inclusive(1, 10)));
  my::thing_sound_play_channel(me, CHANNEL_MONST, (sound).c_str());
}

static void on_death(uint32_t me, int x, int y)
{
  my::spawn_at_my_position(me, "ghost_explosion");
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name);
  self->aggression_pct_set(100);
  self->attack_humanoid_set(true);
  self->chance_d1000_tameable_set(0);
  self->collision_check_set(true);
  self->collision_hit_priority_set(20);
  self->distance_minion_from_mob_max_set(4);
  self->distance_minion_vision_shared_set(true);
  self->distance_vision_set(7);
  self->dmg_cold_dice_set("1");
  self->dmg_nat_att_type_set("touches");
  self->gfx_anim_use_set("attack_red");
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_glows_set(true);
  self->gfx_pixelart_animated_can_hflip_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_health_bar_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->health_initial_dice_set("1");
  self->is_able_to_be_surprised_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_lunge_set(true);
  self->is_able_to_see_in_the_dark_set(true);
  self->is_able_to_see_invisible_set(true);
  self->is_able_to_walk_through_walls_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_buffable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_ethereal_set(true);
  self->is_fearless_set(true);
  self->is_floating_set(true);
  self->is_green_blooded_set(true);
  self->is_hittable_set(true);
  self->is_immune_to_acid_set(true);
  self->is_immune_to_cold_set(true);
  self->is_immune_to_fire_set(true);
  self->is_immune_to_necrosis_set(true);
  self->is_immune_to_poison_set(true);
  self->is_immune_to_stamina_drain_set(true);
  self->is_immune_to_water_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_minion_set(true);
  self->is_monst_class_A_set(true);
  self->is_monst_set(true);
  self->is_moveable_set(true);
  self->is_msg_allowed_hears_something_set(true);
  self->is_msg_allowed_is_dead_set(true);
  self->is_msg_allowed_is_seen_set(true);
  self->is_msg_allowed_is_surprised_set(true);
  self->is_msg_allowed_is_wounded_set(true);
  self->is_msg_allowed_senses_danger_set(true);
  self->is_one_per_tile_set(true);
  self->is_shootable_set(true);
  self->is_tickable_set(true);
  self->is_undead_set(true);
  self->light_color_set("green");
  self->light_dist_set(2);
  self->move_speed_set(200);
  self->noise_decibels_hearing_set(0);
  self->noise_on_moving_set(1);
  self->normal_placement_rules_set(true);
  self->on_death_do_set("me.on_death()");
  self->on_you_nat_attack_attempt_do_set("me.on_you_nat_attack_attempt()");
  self->rarity_set(THING_RARITY_COMMON);
  self->stat_con_set(10);
  self->stat_def_set(1);
  self->stat_dex_set(13);
  self->stat_int_set(0);
  self->stat_luck_set(8);
  self->stat_psi_set(0);
  self->stat_str_set(7);
  self->temperature_set(0);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("ghost minions");
  self->text_apostrophize_set("ghost minion's");
  self->text_description_long_set("The spirit of one less fortunate than you. Beware, ghosts can traverse chasms that you cannot.");
  self->text_description_short_set("The angry spirit of one long passed.");
  self->text_hits_set("touches");
  self->thing_size_set(THING_SIZE_NORMAL);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_MONST);
  delay = 200;
  my::tile(self, {.tile = "ghost.1", .ascii_fg_char = "g", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = "ghost.2", .ascii_fg_char = "g", .ascii_fg_col_name = "gray90", .delay_ms = delay});
  my::tile(self, {.tile = "ghost.3", .ascii_fg_char = "g", .ascii_fg_col_name = "gray80", .delay_ms = delay});
  my::tile(self, {.tile = "ghost.4", .ascii_fg_char = "g", .ascii_fg_col_name = "gray70", .delay_ms = delay});
  my::tile(self, {.tile = "ghost.5", .ascii_fg_char = "g", .ascii_fg_col_name = "gray60", .delay_ms = delay});
  my::tile(self, {.tile = "ghost.6", .ascii_fg_char = "g", .ascii_fg_col_name = "gray30", .delay_ms = delay});
  my::tile(self, {.tile = "ghost.7", .ascii_fg_char = "g", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_invisible = true});
  my::tile(self, {.tile = "ghost.8", .ascii_fg_char = "", .ascii_fg_col_name = "none", .delay_ms = delay, .is_invisible = true});
  my::tile(self, {.tile = "ghost.9", .ascii_fg_char = "", .ascii_fg_col_name = "none", .delay_ms = delay, .is_invisible = true});
  my::tile(self, {.tile = "ghost.10", .ascii_fg_char = "", .ascii_fg_col_name = "none", .delay_ms = delay, .is_invisible = true});
  my::tile(self, {.tile = "ghost.11", .ascii_fg_char = "", .ascii_fg_col_name = "none", .delay_ms = delay, .is_invisible = true});
}

static void init(void)
{
  tp_init("ghost_minion", "ghost minion");
}

void module_init(void)
{
  native_register("ghost_minion", "on_you_nat_attack_attempt", 3, [](const int64_t *a) -> NativeRet { (void) a; on_you_nat_attack_attempt((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("ghost_minion", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_monsters_ghost_minion
