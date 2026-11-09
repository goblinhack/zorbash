//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/ooze.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_ooze {

static void try_to_grow(uint32_t me, int x, int y, int dx, int dy);
static void on_idle(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::vector< std::string > &tiles);
static void init(void);

static void try_to_grow(uint32_t me, int x, int y, int dx, int dy)
{
  if ((my::level_is_ooze_at(me, (x + dx), (y + dy)) || my::level_is_lava_at(me, (x + dx), (y + dy)) || my::level_is_chasm_at(me, (x + dx), (y + dy)) || my::level_is_brazier_at(me, (x + dx), (y + dy)) || my::level_is_fire_at(me, (x + dx), (y + dy)) || my::level_is_wall_at(me, (x + dx), (y + dy)) || my::level_is_water_at(me, (x + dx), (y + dy)))) {
    return;
  }
  if ((my::level_is_floor_at(me, (x + dx), (y + dy)) || my::level_is_corridor_at(me, (x + dx), (y + dy)))) {
    my::spawn_at(me, "ooze", (x + dx), (y + dy));
    return;
  }
}

static void on_idle(uint32_t me, int x, int y)
{
  try_to_grow(me, x, y, (-1), 0);
  try_to_grow(me, x, y, 1, 0);
  try_to_grow(me, x, y, 0, (-1));
  try_to_grow(me, x, y, 0, 1);
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::vector< std::string > &tiles)
{
  Tpp self = my::tp_load(name, text_long_name);
  self->dmg_acid_dice_set("1d4+1");
  self->dmg_chance_d1000_acid_set(0, 1000);
  self->dmg_chance_d1000_poison_set(0, 1000);
  self->dmg_nat_att_type_set("burn");
  self->dmg_poison_dice_set("1d4+1");
  self->environ_dislikes_cold_set(100);
  self->environ_dislikes_fire_set(100);
  self->gfx_ascii_animated_set(true);
  self->gfx_ascii_bg_color_spread_blue_set(40);
  self->gfx_ascii_bg_color_spread_red_set(40);
  self->gfx_ascii_color_is_animated_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_ooze_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->is_able_to_fall_set(true);
  self->is_acid_set(true);
  self->is_biome_dungeon_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_flat_set(true);
  self->is_hazard_set(true);
  self->is_interesting_set(true);
  self->is_obs_ai_set(true);
  self->is_one_per_tile_set(true);
  self->is_ooze_set(true);
  self->is_tickable_set(true);
  self->on_idle_tick_freq_dice_set("1d40:me.on_idle()");
  self->text_a_or_an_set("the");
  self->text_description_short_set("toxic ooze.");
  self->z_depth_set(MAP_DEPTH_LIQUID);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "o", .ascii_bg_col_name = "black", .ascii_fg_col_name = "purple", .delay_ms = 3000});
    my::tile(self, {.tile = t, .ascii_fg_char = "O", .ascii_bg_col_name = "black", .ascii_fg_col_name = "purple", .delay_ms = 1000});
  }
}

static void init(void)
{
  tp_init("ooze", "ooze", std::vector< std::string >{
      "ooze.1",
      "ooze.2",
      "ooze.3",
      "ooze.4",
      "ooze.5",
      "ooze.6",
      "ooze.7",
      "ooze.8",
      "ooze.9",
      "ooze.10",
      "ooze.11",
      "ooze.12",
      "ooze.13",
      "ooze.14",
      "ooze.15",
      "ooze.16",
      "ooze.17",
      "ooze.18",
      "ooze.19",
      "ooze.20",
      "ooze.21",
      "ooze.22",
      "ooze.23",
      "ooze.24",
      "ooze.25",
      "ooze.26",
      "ooze.27",
      "ooze.28",
      "ooze.29",
      "ooze.30",
      "ooze.31",
      "ooze.32",
    });
}

void module_init(void)
{
  native_register("ooze", "try_to_grow", 5, [](const int64_t *a) -> NativeRet { (void) a; try_to_grow((uint32_t) a[0], (int) a[1], (int) a[2], (int) a[3], (int) a[4]); return NativeRet {}; });
  native_register("ooze", "on_idle", 3, [](const int64_t *a) -> NativeRet { (void) a; on_idle((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_dungeon_ooze
