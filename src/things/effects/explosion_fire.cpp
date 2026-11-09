//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/effects/explosion_fire.py
//

#include "my_native.hpp"

namespace mod_things_effects_explosion_fire {

static void on_born(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_born(uint32_t me, int x, int y)
{
  my::thing_sound_play_channel(me, CHANNEL_EXPLOSION, "explosion_a");
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
  self->noise_on_born_set(70);
  self->on_born_do_set("me.on_born()");
  self->text_hits_set("blasts");
  self->tick_prio_set(MAP_TICK_PRIO_VERY_HIGH);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_EFFECT);
  my::tile(self, {.tile = "nothing", .ascii_bg_char = "block", .ascii_bg_col_name = "orange", .ascii_fg_col_name = ""});
  delay = 25;
  my::tile(self, {.tile = "explosion_fire.1", .ascii_bg_char = "block", .ascii_bg_col_name = "orange", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = "explosion_fire.2", .ascii_bg_char = "block", .ascii_bg_col_name = "orange", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = "explosion_fire.3", .ascii_bg_char = "block", .ascii_bg_col_name = "orange", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = "explosion_fire.4", .ascii_bg_char = "block", .ascii_bg_col_name = "orange", .ascii_fg_col_name = "", .delay_ms = delay, .is_end_of_anim = true, .is_dead_on_end_of_anim = true});
}

static void init(void)
{
  tp_init("explosion_fire", "fire burst", "fire burst");
}

void module_init(void)
{
  native_register("explosion_fire", "on_born", 3, [](const int64_t *a) -> NativeRet { (void) a; on_born((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_effects_explosion_fire
