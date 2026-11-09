//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/projectiles/projectile_dart_poison.py
//

#include "my_native.hpp"

namespace mod_things_projectiles_projectile_dart_poison {

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->collision_check_set(true);
  self->gfx_ascii_shown_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_dead_on_falling_set(true);
  self->is_loggable_set(true);
  self->is_no_tile_set(true);
  self->is_projectile_set(true);
  self->is_usable_set(true);
  self->text_a_or_an_set("a");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = "projectile_dart_poison", .ascii_fg_char = "-", .ascii_fg_col_name = "gray50"});
  my::tile(self, {.tile = "projectile_dart_poison", .ascii_fg_char = "/", .ascii_fg_col_name = "gray50"});
  my::tile(self, {.tile = "projectile_dart_poison", .ascii_fg_char = "|", .ascii_fg_col_name = "gray50"});
  my::tile(self, {.tile = "projectile_dart_poison", .ascii_fg_char = "\\", .ascii_fg_col_name = "gray50"});
}

static void init(void)
{
  tp_init("projectile_dart_poison", "poison dart", "poison dart");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_projectiles_projectile_dart_poison
