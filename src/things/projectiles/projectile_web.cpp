//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/projectiles/projectile_web.py
//

#include "my_native.hpp"

namespace mod_things_projectiles_projectile_web {

static void on_born(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_born(uint32_t me, int x, int y)
{
  uint32_t it = 0;
  it = my::spawn_at_my_position(me, "webball");
  if ((it != 0)) {
    my::thing_set_mob(me, it);
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->collision_check_set(true);
  self->gfx_ascii_shown_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_no_tile_set(true);
  self->is_projectile_set(true);
  self->is_spiderweb_set(true);
  self->is_usable_set(true);
  self->on_born_do_set("me.on_born()");
  self->text_a_or_an_set("a");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "cross", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "cross", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "cross", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "cross", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "cross", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "cross", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "cross", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "cross", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "cross", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "cross", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "cross", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "cross", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "cross", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "cross", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "cross", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "cross", .ascii_fg_col_name = "white"});
}

static void init(void)
{
  tp_init("projectile_web", "web ball", "web ball");
}

void module_init(void)
{
  native_register("projectile_web", "on_born", 3, [](const int64_t *a) -> NativeRet { (void) a; on_born((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_projectiles_projectile_web
