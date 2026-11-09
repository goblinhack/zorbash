//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/doors/door_wood.py
//

#include "my_native.hpp"

namespace mod_things_doors_door_wood {

static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage);
static void on_death(uint32_t me, int x, int y);
static void on_open(uint32_t me, int x, int y);
static void tp_init(const std::string &name);
static void init(void);

static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage)
{
  my::thing_sound_play_channel(me, CHANNEL_IMPACT, ((std::string("door_hit") + std::to_string(my::non_pcg_random_inclusive(1, 2)))).c_str());
}

static void on_death(uint32_t me, int x, int y)
{
  my::thing_sound_play_channel(me, CHANNEL_IMPACT, "door_break");
}

static void on_open(uint32_t me, int x, int y)
{
  my::thing_sound_play_channel(me, CHANNEL_IMPACT, "door_open");
}

static void tp_init(const std::string &name)
{
  Tpp self = my::tp_load(name, std::string("wooden door"));
  self->collision_check_set(true);
  self->collision_hit_priority_set(9);
  self->dmg_chance_d1000_crush_set(0, 1000);
  self->dmg_crush_dice_set("2d6");
  self->dmg_rcv_doubled_from_fire_set(true);
  self->environ_dislikes_fire_set(100);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_health_bar_autohide_set(true);
  self->gfx_pixelart_oversized_and_on_floor_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->health_initial_dice_set("5d10");
  self->is_able_to_freeze_set(true);
  self->is_always_hit_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_biome_swamp_set(true);
  self->is_burnable_set(true);
  self->is_combustible_set(true);
  self->is_corpse_on_death_set(true);
  self->is_cursor_can_hover_over_set(true);
  self->is_cursor_path_blocker_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_door_set(true);
  self->is_gas_blocker_set(true);
  self->is_hittable_set(true);
  self->is_interesting_set(true);
  self->is_light_blocker_set(true);
  self->is_loggable_set(true);
  self->is_obs_jump_end_set(true);
  self->is_obs_jumping_set(true);
  self->is_obs_shooting_set(true);
  self->is_obs_shoving_set(true);
  self->is_obs_spawn_monst_set(true);
  self->is_obs_spawn_set(true);
  self->is_obs_wall_or_door_set(true);
  self->is_openable_set(true);
  self->is_shootable_set(true);
  self->is_tickable_set(true);
  self->noise_blocker_set(true);
  self->noise_on_hit_and_now_dead_set(70);
  self->noise_on_hit_and_still_alive_set(60);
  self->noise_on_open_or_close_set(60);
  self->normal_placement_rules_set(true);
  self->on_death_do_set("me.on_death()");
  self->on_death_is_open_set(true);
  self->on_hit_and_still_alive_do_set("me.on_hit_and_still_alive()");
  self->on_open_do_set("me.on_open()");
  self->stat_def_set(20);
  self->temperature_max_set(100);
  self->temperature_min_set((-50));
  self->temperature_set(20);
  self->temperature_sensitive_set(true);
  self->temperature_sensitive_to_sudden_changes_set(true);
  self->text_a_or_an_set("the");
  self->text_description_short_set("A door covered in claw marks.");
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = (name + ".100"), .ascii_fg_char = "+", .ascii_bg_col_name = "brown", .ascii_fg_col_name = "black", .is_hp_100_percent = true});
  my::tile(self, {.tile = (name + ".75"), .ascii_fg_char = "+", .ascii_bg_col_name = "brown2", .ascii_fg_col_name = "black", .is_hp_75_percent = true});
  my::tile(self, {.tile = (name + ".50"), .ascii_fg_char = "+", .ascii_bg_col_name = "orange", .ascii_fg_col_name = "black", .is_hp_50_percent = true});
  my::tile(self, {.tile = (name + ".25"), .ascii_fg_char = "+", .ascii_bg_col_name = "red", .ascii_fg_col_name = "black", .is_hp_25_percent = true});
  my::tile(self, {.tile = (name + ".dead"), .ascii_fg_char = "-", .ascii_bg_col_name = "gray10", .ascii_fg_col_name = "black", .is_dead = true});
  my::tile(self, {.tile = (name + ".open"), .ascii_fg_char = "-", .ascii_bg_col_name = "brown", .ascii_fg_col_name = "black", .is_hp_100_percent = true, .is_open = true});
  my::tile(self, {.tile = (name + ".open"), .ascii_fg_char = "-", .ascii_bg_col_name = "brown", .ascii_fg_col_name = "black", .is_hp_75_percent = true, .is_open = true});
  my::tile(self, {.tile = (name + ".open"), .ascii_fg_char = "-", .ascii_bg_col_name = "brown", .ascii_fg_col_name = "black", .is_hp_50_percent = true, .is_open = true});
  my::tile(self, {.tile = (name + ".open"), .ascii_fg_char = "-", .ascii_bg_col_name = "brown", .ascii_fg_col_name = "black", .is_hp_25_percent = true, .is_open = true});
}

static void init(void)
{
  tp_init("door_wood");
}

void module_init(void)
{
  native_register("door_wood", "on_hit_and_still_alive", 7, [](const int64_t *a) -> NativeRet { (void) a; on_hit_and_still_alive((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5], (int) a[6]); return NativeRet {}; });
  native_register("door_wood", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("door_wood", "on_open", 3, [](const int64_t *a) -> NativeRet { (void) a; on_open((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_doors_door_wood
