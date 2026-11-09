//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/steam.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_steam {

static void on_fall(uint32_t me, int x, int y);
static void tp_init(const std::string &name);
static void init(void);

static void on_fall(uint32_t me, int x, int y)
{
  my::thing_dead(me, "dissipated");
}

static void tp_init(const std::string &name)
{
  int delay = 0;
  Tpp self = my::tp_load(name);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_oversized_and_on_floor_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_one_per_tile_set(true);
  self->is_removable_if_out_of_slots_set(true);
  self->is_steam_set(true);
  self->is_tickable_set(true);
  self->lifespan_dice_set("1d5+3");
  self->on_fall_do_set("me.on_fall()");
  self->temperature_min_set(0);
  self->temperature_set(100);
  self->temperature_sensitive_set(true);
  self->text_a_or_an_set("");
  self->text_description_short_set("Scalding steam.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  delay = 300;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "=", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "=", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "=", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "=", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "=", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "=", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".7"), .ascii_fg_char = "=", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".8"), .ascii_fg_char = "=", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".9"), .ascii_fg_char = "=", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".10"), .ascii_fg_char = "=", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".11"), .ascii_fg_char = "=", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".12"), .ascii_fg_char = "=", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".13"), .ascii_fg_char = "=", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".14"), .ascii_fg_char = "=", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".15"), .ascii_fg_char = "=", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".16"), .ascii_fg_char = "=", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".17"), .ascii_fg_char = "=", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".18"), .ascii_fg_char = "=", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".19"), .ascii_fg_char = "=", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
}

static void init(void)
{
  tp_init("steam");
}

void module_init(void)
{
  native_register("steam", "on_fall", 3, [](const int64_t *a) -> NativeRet { (void) a; on_fall((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_dungeon_steam
