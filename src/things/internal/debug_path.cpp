//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/internal/debug_path.py
//

#include "my_native.hpp"

namespace mod_things_internal_debug_path {

static void tp_init(const std::string &name);
static void init(void);

static void tp_init(const std::string &name)
{
  std::string text_long_name;
  text_long_name = std::string("debug path");
  Tpp self = my::tp_load(name, text_long_name);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->is_debug_path_set(true);
  self->is_floating_set(true);
  self->is_internal_set(true);
  self->is_moveable_set(true);
  self->is_removable_if_out_of_slots_set(true);
  self->is_tmp_thing_set(true);
  self->text_a_or_an_set("the");
  self->text_description_short_set("debug path.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_CURSOR);
  my::tile(self, {.tile = "ai_path1.1", .ascii_bg_char = "block", .ascii_bg_col_name = "darkblue", .ascii_fg_col_name = ""});
}

static void init(void)
{
  tp_init("debug_path");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_internal_debug_path
