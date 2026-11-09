//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/lava.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_lava {

static void on_idle(uint32_t me, int x, int y);
static void on_death(uint32_t me, int x, int y);
static void lava_init(const std::string &name, const std::string &text_long_name, const std::vector< std::string > &tiles);
static void init(void);

static void on_idle(uint32_t me, int x, int y)
{
  my::spawn_at_my_position(me, "smoke");
}

static void on_death(uint32_t me, int x, int y)
{
  my::spawn_at_my_position(me, "basalt");
}

static void lava_init(const std::string &name, const std::string &text_long_name, const std::vector< std::string > &tiles)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name);
  self->collision_hit_priority_set(100);
  self->dmg_chance_d1000_fire_set(0, 1000);
  self->dmg_fire_dice_set("1d12+6");
  self->dmg_nat_att_type_set("burn");
  self->gfx_ascii_animated_set(true);
  self->gfx_ascii_bg_color_spread_green_set(30);
  self->gfx_ascii_bg_color_spread_red_set(30);
  self->gfx_ascii_color_fg_unchanged_by_lights_set(true);
  self->gfx_ascii_color_is_animated_set(true);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_glows_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->is_able_to_fall_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_lava_set(true);
  self->is_cursor_can_hover_over_needs_confirm_set(true);
  self->is_cursor_path_hazard_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_flat_set(true);
  self->is_hazard_set(true);
  self->is_interesting_set(true);
  self->is_lava_set(true);
  self->is_obs_ai_set(true);
  self->is_one_per_tile_set(true);
  self->is_tickable_set(true);
  self->light_color_set("red");
  self->light_dist_set(2);
  self->on_death_do_set("me.on_death()");
  self->on_idle_tick_freq_dice_set("1d200+50:me.on_idle()");
  self->temperature_min_set(0);
  self->temperature_set(800);
  self->temperature_sensitive_set(true);
  self->text_a_or_an_set("");
  self->text_description_short_set("%%fg=orange$Freshly scented lava%%fg=reset$ (double click to move onto).");
  self->text_hits_set("tickles");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_LIQUID);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  delay = 150;
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "~", .ascii_bg_col_name = "orange", .ascii_fg_col_name = "orange", .delay_ms = delay});
  }
}

static void init(void)
{
  lava_init("lava", "molten lava", std::vector< std::string >{
      "lava.1",
      "lava.2",
      "lava.3",
      "lava.4",
      "lava.5",
      "lava.6",
      "lava.7",
      "lava.8",
      "lava.9",
      "lava.10",
      "lava.11",
      "lava.12",
      "lava.13",
      "lava.14",
      "lava.15",
      "lava.16",
    });
}

void module_init(void)
{
  native_register("lava", "on_idle", 3, [](const int64_t *a) -> NativeRet { (void) a; on_idle((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("lava", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_dungeon_lava
