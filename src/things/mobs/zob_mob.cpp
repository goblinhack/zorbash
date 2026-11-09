//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/mobs/zob_mob.py
//

#include "my_native.hpp"

namespace mod_things_mobs_zob_mob {

static void on_idle_tick_freq_dice(uint32_t me, int x, int y);
static void on_death(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_idle_tick_freq_dice(uint32_t me, int x, int y)
{
  if (my::thing_is_frozen(me)) {
    return;
  }
  if ((my::spawn_next_to(me, "zoblin_minion") != 0)) {
    my::thing_sound_play_channel(me, CHANNEL_MONST_BIRTH, "bones1");
  }
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

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name);
  self->chance_d1000_shove_set(200);
  self->collision_check_set(true);
  self->collision_hit_priority_set(5);
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
  self->gfx_pixelart_show_outlined_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->health_initial_dice_set("6d6");
  self->is_able_to_fall_set(true);
  self->is_always_hit_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_biome_swamp_set(true);
  self->is_burnable_set(true);
  self->is_crushable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_immune_to_cold_set(true);
  self->is_immune_to_fire_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_mob_class_C_set(true);
  self->is_mob_set(true);
  self->is_obs_destructable_set(true);
  self->is_obs_spawn_monst_set(true);
  self->is_shootable_set(true);
  self->is_shovable_set(true);
  self->is_tickable_set(true);
  self->light_color_set("cyan");
  self->light_dist_set(1);
  self->minion_limit_set(4);
  self->normal_placement_rules_set(true);
  self->on_death_do_set("me.on_death()");
  self->on_idle_tick_freq_dice_set("1d10+10:me.on_idle_tick_freq_dice()");
  self->temperature_never_changes_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("zoblin mobs");
  self->text_apostrophize_set("zoblin mob's");
  self->text_description_long_set("A dark portal from which the undead crawl out.");
  self->text_description_short_set("The undead become a bit less dead here.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_MOB);
  delay = 500;
  my::tile(self, {.tile = (name + ".1.100"), .ascii_fg_char = "&", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray", .delay_ms = delay, .is_hp_100_percent = true});
  my::tile(self, {.tile = (name + ".2.100"), .ascii_fg_char = "&", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray", .delay_ms = delay, .is_hp_100_percent = true});
  my::tile(self, {.tile = (name + ".1.75"), .ascii_fg_char = "&", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray", .delay_ms = delay, .is_hp_75_percent = true});
  my::tile(self, {.tile = (name + ".2.75"), .ascii_fg_char = "&", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray", .delay_ms = delay, .is_hp_75_percent = true});
  my::tile(self, {.tile = (name + ".1.50"), .ascii_fg_char = "&", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray", .delay_ms = delay, .is_hp_50_percent = true});
  my::tile(self, {.tile = (name + ".2.50"), .ascii_fg_char = "&", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray", .delay_ms = delay, .is_hp_50_percent = true});
  my::tile(self, {.tile = (name + ".1.25"), .ascii_fg_char = "&", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray", .delay_ms = delay, .is_hp_25_percent = true});
  my::tile(self, {.tile = (name + ".2.25"), .ascii_fg_char = "&", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray", .delay_ms = delay, .is_hp_25_percent = true});
}

static void init(void)
{
  tp_init("zob_mob", "zoblin generator");
}

void module_init(void)
{
  native_register("zob_mob", "on_idle_tick_freq_dice", 3, [](const int64_t *a) -> NativeRet { (void) a; on_idle_tick_freq_dice((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("zob_mob", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_mobs_zob_mob
