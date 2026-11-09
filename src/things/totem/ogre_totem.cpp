//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/totem/ogre_totem.py
//

#include "my_native.hpp"

namespace mod_things_totem_ogre_totem {

static void on_idle_tick_freq_dice(uint32_t me, int x, int y);
static void on_death(uint32_t me, int x, int y);
static bool on_want_to_shoot_at(uint32_t me, uint32_t target, int target_x, int target_y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_idle_tick_freq_dice(uint32_t me, int x, int y)
{
  if (my::thing_is_frozen(me)) {
    return;
  }
  my::spawn_minion_next_to(me, "ogre");
  my::thing_sound_play_channel(me, CHANNEL_MONST_BIRTH, "bones1");
}

static void on_death(uint32_t me, int x, int y)
{
  if ((my::non_pcg_random_inclusive(1, 2) == 1)) {
    if ((! my::thing_sound_play_channel(me, CHANNEL_MONST, "bones1"))) {
      my::thing_sound_play_channel(me, CHANNEL_MONST_DEATH, "bones1");
    }
  } else if ((! my::thing_sound_play_channel(me, CHANNEL_MONST, "bones2"))) {
    my::thing_sound_play_channel(me, CHANNEL_MONST_DEATH, "bones2");
  }
  my::spawn_at_my_position(me, "mob_explosion");
}

static bool on_want_to_shoot_at(uint32_t me, uint32_t target, int target_x, int target_y)
{
  if (my::thing_is_same_mob(me, target)) {
    return false;
  }
  if ((my::thing_is_player(target) || my::thing_is_alive_monst(target))) {
    my::thing_spell_cast_at(me, "spell_of_beckoning", target);
  } else {
    my::thing_sound_play_channel(me, CHANNEL_WEAPON, "lightning_a");
    my::thing_shoot_projectile_or_laser_at(me, "laser_lightning", target);
  }
  return true;
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name);
  self->aggression_pct_set(100);
  self->attack_humanoid_set(true);
  self->chance_d1000_shooting_set(1000);
  self->collision_check_set(true);
  self->collision_hit_priority_set(5);
  self->distance_minion_from_mob_max_set(7);
  self->distance_spell_cast_set(7);
  self->distance_throw_set(7);
  self->distance_vision_set(8);
  self->dmg_chance_d1000_crush_set(0, 1000);
  self->dmg_crush_dice_set("6d6");
  self->dmg_num_of_attacks_set(0);
  self->dmg_rcv_doubled_from_water_set(true);
  self->environ_hates_water_set(100);
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_oversized_and_on_floor_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->health_initial_dice_set("3d6");
  self->is_able_to_fall_set(true);
  self->is_able_to_see_in_the_dark_set(true);
  self->is_able_to_shoot_at_close_range_set(true);
  self->is_able_to_shoot_at_set(true);
  self->is_always_hit_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_swamp_set(true);
  self->is_burnable_set(true);
  self->is_crushable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_heavy_set(true);
  self->is_hittable_set(true);
  self->is_immune_to_cold_set(true);
  self->is_immune_to_necrosis_set(true);
  self->is_immune_to_poison_set(true);
  self->is_immune_to_stamina_drain_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_mob_class_C_set(true);
  self->is_mob_set(true);
  self->is_obs_ai_set(true);
  self->is_obs_destructable_set(true);
  self->is_obs_jump_end_set(true);
  self->is_obs_jumping_set(true);
  self->is_obs_shooting_set(true);
  self->is_obs_shoving_set(true);
  self->is_obs_spawn_monst_set(true);
  self->is_obs_spell_casting_set(true);
  self->is_obs_throwing_set(true);
  self->is_one_per_tile_set(true);
  self->is_shootable_set(true);
  self->is_shovable_set(true);
  self->is_stone_set(true);
  self->is_tickable_set(true);
  self->is_totem_set(true);
  self->light_color_set("cyan");
  self->light_dist_set(3);
  self->minion_limit_set(2);
  self->normal_placement_rules_set(true);
  self->on_death_do_set("me.on_death()");
  self->on_idle_tick_freq_dice_set("1:me.on_idle_tick_freq_dice()");
  self->on_want_to_shoot_at_do_set("me.on_want_to_shoot_at()");
  self->text_a_or_an_set("a");
  self->text_pluralize_set("ogre totems");
  self->text_apostrophize_set("ogre totem's");
  self->text_description_long2_set("You may however find this revolting pillar oddly attracting.");
  self->text_description_long_set("A tall pillar of skulls, smeared in grease and blood. This is not a place to hang out.");
  self->text_description_short_set("Ogre holy place.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_MOB);
  delay = 200;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "neuter", .ascii_bg_col_name = "", .ascii_fg_col_name = "cyan", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "neuter", .ascii_bg_col_name = "", .ascii_fg_col_name = "cyan", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".dead"), .ascii_fg_char = "neuter", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray", .delay_ms = delay, .is_dead = true, .is_end_of_anim = true});
}

static void init(void)
{
  tp_init("ogre_totem", "ogre totem");
}

void module_init(void)
{
  native_register("ogre_totem", "on_idle_tick_freq_dice", 3, [](const int64_t *a) -> NativeRet { (void) a; on_idle_tick_freq_dice((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("ogre_totem", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("ogre_totem", "on_want_to_shoot_at", 4, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_want_to_shoot_at((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]), {}}; });
  init();
}

} // namespace mod_things_totem_ogre_totem
