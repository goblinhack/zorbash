//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/items/block_of_ice.py
//

#include "my_native.hpp"

namespace mod_things_items_block_of_ice {

static void melt(uint32_t me, int x, int y);
static void on_fire(uint32_t me, int x, int y);
static void on_fall(uint32_t me, int x, int y);
static void on_death(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void melt(uint32_t me, int x, int y)
{
  if (my::thing_is_dead(me)) {
    return;
  }
  my::thing_msg(me, "The ice melts.");
  for (int dx = (-1), dx_end_ = 2; dx < dx_end_; dx += 1) {
    for (int dy = (-1), dy_end_ = 2; dy < dy_end_; dy += 1) {
      my::place_at(me, "water", (x + dx), (y + dy));
      my::thing_sound_play_channel(me, CHANNEL_IMPACT, "splash6");
      for (auto it : my::level_get_all(me, (x + dx), (y + dy))) {
        if ((my::thing_is_lava(it) || my::thing_is_fire(it))) {
          my::thing_dead(it, "by freezing");
        }
      }
    }
  }
}

static void on_fire(uint32_t me, int x, int y)
{
  melt(me, x, y);
}

static void on_fall(uint32_t me, int x, int y)
{
  melt(me, x, y);
}

static void on_death(uint32_t me, int x, int y)
{
  melt(me, x, y);
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  Tpp self = my::tp_load(name, text_long_name);
  self->chance_d1000_appearing_set(10);
  self->chance_d1000_melting_set(100);
  self->collision_check_set(true);
  self->collision_hit_priority_set(100);
  self->dmg_chance_d1000_cold_set(0, 1000);
  self->dmg_chance_d1000_crush_set(0, 1000);
  self->dmg_cold_dice_set("1d6");
  self->dmg_crush_dice_set("2d6");
  self->dmg_rcv_doubled_from_fire_set(true);
  self->environ_dislikes_fire_set(100);
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_oversized_and_on_floor_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->health_initial_dice_set("20+1d20");
  self->is_able_to_fall_set(true);
  self->is_able_to_melt_set(true);
  self->is_always_hit_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_block_of_ice_set(true);
  self->is_brittle_set(true);
  self->is_cursor_can_hover_over_set(true);
  self->is_cursor_path_blocker_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_gas_blocker_set(true);
  self->is_hard_set(true);
  self->is_hittable_set(true);
  self->is_immune_to_cold_set(true);
  self->is_immune_to_necrosis_set(true);
  self->is_immune_to_poison_set(true);
  self->is_immune_to_stamina_drain_set(true);
  self->is_interesting_set(true);
  self->is_light_blocker_for_monst_set(true);
  self->is_light_blocker_set(true);
  self->is_loggable_set(true);
  self->is_obs_ai_set(true);
  self->is_obs_jump_end_set(true);
  self->is_obs_jumping_set(true);
  self->is_obs_shooting_set(true);
  self->is_obs_shoving_set(true);
  self->is_obs_spawn_monst_set(true);
  self->is_obs_spell_casting_set(true);
  self->is_obs_throwing_set(true);
  self->is_one_per_tile_set(true);
  self->is_reflective_set(true);
  self->is_shootable_set(true);
  self->is_shovable_and_sticky_set(true);
  self->is_shovable_set(true);
  self->is_tickable_set(true);
  self->is_very_heavy_set(true);
  self->noise_blocker_set(true);
  self->normal_placement_rules_set(true);
  self->on_death_do_set("me.on_death()");
  self->on_fall_do_set("me.on_fall()");
  self->on_you_are_on_fire_do_set("me.on_fire()");
  self->temperature_max_set(0);
  self->temperature_set((-100));
  self->temperature_sensitive_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("blocks of ice");
  self->text_apostrophize_set("block of ice's");
  self->text_description_short_set("A block of ice.");
  self->thing_size_set(THING_SIZE_GIANT);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_EFFECT);
  my::tile(self, {.tile = name, .ascii_bg_char = "block", .ascii_bg_col_name = "cyan"});
}

static void init(void)
{
  tp_init("block_of_ice", "block of ice");
}

void module_init(void)
{
  native_register("block_of_ice", "melt", 3, [](const int64_t *a) -> NativeRet { (void) a; melt((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("block_of_ice", "on_fire", 3, [](const int64_t *a) -> NativeRet { (void) a; on_fire((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("block_of_ice", "on_fall", 3, [](const int64_t *a) -> NativeRet { (void) a; on_fall((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("block_of_ice", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_items_block_of_ice
