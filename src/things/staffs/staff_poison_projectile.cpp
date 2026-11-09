//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/staffs/staff_poison_projectile.py
//

#include "my_native.hpp"

namespace mod_things_staffs_staff_poison_projectile {

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->gfx_ascii_shown_set(true);
  self->gfx_targeted_projectile_set("projectile_poison");
  self->is_able_to_be_teleported_set(true);
  self->is_loggable_set(true);
  self->is_no_tile_set(true);
  self->is_projectile_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("poison projectiles");
  self->text_apostrophize_set("poison projectile's");
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
}

static void init(void)
{
  tp_init("staff_projectile_poison", "poison projectile", "poison projectile");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_staffs_staff_poison_projectile
