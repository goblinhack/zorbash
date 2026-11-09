//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/internal/cursor_select_fail.py
//

#include "my_native.hpp"

namespace mod_things_internal_cursor_select_fail {

static void tp_init(const std::string &name);
static void init(void);

static void tp_init(const std::string &name)
{
  int delay = 0;
  std::string text_long_name;
  text_long_name = std::string("cursor");
  Tpp self = my::tp_load(name, text_long_name);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->is_cursor_set(true);
  self->is_floating_set(true);
  self->is_internal_set(true);
  self->is_moveable_set(true);
  self->is_tmp_thing_set(true);
  self->text_a_or_an_set("the");
  self->text_description_short_set("Cursor.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_CURSOR);
  delay = 50;
  my::tile(self, {.tile = (name + ".1"), .ascii_bg_char = "block", .ascii_bg_col_name = "red", .ascii_fg_col_name = "", .ascii_bg_alpha = 200, .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_bg_char = "block", .ascii_bg_col_name = "red", .ascii_fg_col_name = "", .ascii_bg_alpha = 200, .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_bg_char = "block", .ascii_bg_col_name = "red", .ascii_fg_col_name = "", .ascii_bg_alpha = 200, .delay_ms = delay});
  my::tile(self, {.tile = (name + ".4"), .ascii_bg_char = "block", .ascii_bg_col_name = "red", .ascii_fg_col_name = "", .ascii_bg_alpha = 200, .delay_ms = delay});
  my::tile(self, {.tile = (name + ".5"), .ascii_bg_char = "block", .ascii_bg_col_name = "red", .ascii_fg_col_name = "", .ascii_bg_alpha = 200, .delay_ms = delay});
  my::tile(self, {.tile = (name + ".6"), .ascii_bg_char = "block", .ascii_bg_col_name = "red", .ascii_fg_col_name = "", .ascii_bg_alpha = 200, .delay_ms = delay});
  my::tile(self, {.tile = (name + ".7"), .ascii_bg_char = "block", .ascii_bg_col_name = "red", .ascii_fg_col_name = "", .ascii_bg_alpha = 200, .delay_ms = delay});
  my::tile(self, {.tile = (name + ".8"), .ascii_bg_char = "block", .ascii_bg_col_name = "red", .ascii_fg_col_name = "", .ascii_bg_alpha = 200, .delay_ms = delay});
  my::tile(self, {.tile = (name + ".9"), .ascii_bg_char = "block", .ascii_bg_col_name = "red", .ascii_fg_col_name = "", .ascii_bg_alpha = 200, .delay_ms = delay});
  my::tile(self, {.tile = (name + ".10"), .ascii_bg_char = "block", .ascii_bg_col_name = "red", .ascii_fg_col_name = "", .ascii_bg_alpha = 200, .delay_ms = delay});
  my::tile(self, {.tile = (name + ".11"), .ascii_bg_char = "block", .ascii_bg_col_name = "red", .ascii_fg_col_name = "", .ascii_bg_alpha = 200, .delay_ms = delay});
  my::tile(self, {.tile = (name + ".12"), .ascii_bg_char = "block", .ascii_bg_col_name = "red", .ascii_fg_col_name = "", .ascii_bg_alpha = 200, .delay_ms = delay});
}

static void init(void)
{
  tp_init("cursor_select_fail");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_internal_cursor_select_fail
