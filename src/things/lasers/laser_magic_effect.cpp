//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/lasers/laser_magic_effect.py
//

#include "my_native.hpp"

namespace mod_things_lasers_laser_magic_effect {

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->gfx_ascii_shown_set(true);
  self->is_laser_set(true);
  self->is_loggable_set(true);
  self->is_no_tile_set(true);
  self->is_usable_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("burst of magic");
  self->text_apostrophize_set("burst of magic's");
  self->tick_prio_set(MAP_TICK_PRIO_VERY_HIGH);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "green", .ascii_fg_alpha = 255});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "darkgreen", .ascii_fg_alpha = 255});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "green", .ascii_fg_alpha = 255});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "darkgreen", .ascii_fg_alpha = 255});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "green", .ascii_fg_alpha = 255});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "darkgreen", .ascii_fg_alpha = 200});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "green", .ascii_fg_alpha = 200});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "darkgreen", .ascii_fg_alpha = 200});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "green", .ascii_fg_alpha = 200});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "darkgreen", .ascii_fg_alpha = 100});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "green", .ascii_fg_alpha = 100});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "darkgreen", .ascii_fg_alpha = 100});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "green", .ascii_fg_alpha = 100});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "darkgreen", .ascii_fg_alpha = 50});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "green", .ascii_fg_alpha = 50});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "darkgreen", .ascii_fg_alpha = 50});
}

static void init(void)
{
  tp_init("laser_magic_effect", "burst of magic", "burst of magic");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_lasers_laser_magic_effect
