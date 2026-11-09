//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/staffs/staff_discord_laser.py
//

#include "my_native.hpp"

namespace mod_things_staffs_staff_discord_laser {

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->gfx_ascii_shown_set(true);
  self->gfx_targeted_laser_set("laser_discord");
  self->is_able_to_be_reflected_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_laser_set(true);
  self->is_loggable_set(true);
  self->is_no_tile_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("beams of discord");
  self->text_apostrophize_set("beam of discord's");
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "red", .ascii_fg_alpha = 255});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "red", .ascii_fg_alpha = 255});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "red", .ascii_fg_alpha = 255});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "red", .ascii_fg_alpha = 255});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "red", .ascii_fg_alpha = 255});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "red", .ascii_fg_alpha = 200});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "red", .ascii_fg_alpha = 200});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "red", .ascii_fg_alpha = 200});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "red", .ascii_fg_alpha = 200});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "red", .ascii_fg_alpha = 100});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "red", .ascii_fg_alpha = 100});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "red", .ascii_fg_alpha = 100});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "red", .ascii_fg_alpha = 100});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "red", .ascii_fg_alpha = 50});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "red", .ascii_fg_alpha = 50});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "red", .ascii_fg_alpha = 50});
}

static void init(void)
{
  tp_init("laser_discord", "beam of discord", "laser.discord");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_staffs_staff_discord_laser
