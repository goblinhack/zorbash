//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/effects/explosion_destroy_floor.py
//

#include "my_native.hpp"

namespace mod_things_effects_explosion_destroy_floor {

static void on_born(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_born(uint32_t me, int x, int y)
{
  my::thing_sound_play_channel(me, CHANNEL_EXPLOSION, "explosion_e");
  if ((my::level_is_floor_at(me, x, y) || my::level_is_dirt_at(me, x, y) || my::level_is_corridor_at(me, x, y))) {
    if (my::level_is_bridge_at(me, (x + 1), y)) {
      my::place_at(me, "explosion_destroy_floor", (x + 1), y);
    }
    if (my::level_is_bridge_at(me, (x - 1), y)) {
      my::place_at(me, "explosion_destroy_floor", (x - 1), y);
    }
    if (my::level_is_bridge_at(me, x, (y + 1))) {
      my::place_at(me, "explosion_destroy_floor", x, (y + 1));
    }
    if (my::level_is_bridge_at(me, x, (y - 1))) {
      my::place_at(me, "explosion_destroy_floor", x, (y - 1));
    }
  }
  my::if_matches_then_dead(me, "is_floor", x, y);
  my::if_matches_then_dead(me, "is_bridge", x, y);
  my::if_matches_then_dead(me, "is_corridor", x, y);
  my::if_matches_then_dead(me, "is_dirt", x, y);
  my::place_at(me, "chasm1", x, y);
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->is_explosion_set(true);
  self->is_floating_set(true);
  self->is_loggable_set(true);
  self->is_one_per_tile_set(true);
  self->noise_on_born_set(100);
  self->on_born_do_set("me.on_born()");
  self->text_hits_set("blasts");
  self->tick_prio_set(MAP_TICK_PRIO_VERY_HIGH);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_EFFECT);
  delay = 50;
  my::tile(self, {.tile = "nothing", .ascii_bg_char = "block", .ascii_bg_col_name = "cyan", .ascii_fg_col_name = ""});
  my::tile(self, {.tile = "explosion_fire.1", .ascii_bg_char = "block", .ascii_bg_col_name = "cyan", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = "explosion_fire.2", .ascii_bg_char = "block", .ascii_bg_col_name = "cyan", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = "explosion_fire.3", .ascii_bg_char = "block", .ascii_bg_col_name = "cyan", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = "explosion_fire.4", .ascii_bg_char = "block", .ascii_bg_col_name = "cyan", .ascii_fg_col_name = "", .delay_ms = delay, .is_end_of_anim = true, .is_dead_on_end_of_anim = true});
}

static void init(void)
{
  tp_init("explosion_destroy_floor", "earthquake", "earthquake");
}

void module_init(void)
{
  native_register("explosion_destroy_floor", "on_born", 3, [](const int64_t *a) -> NativeRet { (void) a; on_born((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_effects_explosion_destroy_floor
