//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/projectiles/projectile_acid.py
//

#include "my_native.hpp"

namespace mod_things_projectiles_projectile_acid {

static void on_born(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_born(uint32_t me, int x, int y)
{
  int selection_x = 0;
  int selection_y = 0;
  { auto pair6_ = my::thing_coords_get(me); selection_x = pair6_.first; selection_y = pair6_.second; }
  for (auto it : my::level_get_all(me, selection_x, selection_y)) {
    if (my::thing_possible_to_attack(me, it)) {
      my::spawn_at_my_position(it, "green_splatter");
      return;
    }
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->collision_check_set(true);
  self->dmg_acid_dice_set("1d10");
  self->dmg_chance_d1000_acid_set(0, 1000);
  self->gfx_ascii_shown_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_acid_set(true);
  self->is_loggable_set(true);
  self->is_no_tile_set(true);
  self->is_projectile_set(true);
  self->is_usable_set(true);
  self->on_born_do_set("me.on_born()");
  self->text_a_or_an_set("a");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "lime"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "lime"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "lime"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "lime"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "lime"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "lime"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "lime"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "lime"});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "*", .ascii_fg_col_name = "green"});
}

static void init(void)
{
  tp_init("projectile_acid", "acidball", "acidball");
}

void module_init(void)
{
  native_register("projectile_acid", "on_born", 3, [](const int64_t *a) -> NativeRet { (void) a; on_born((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_projectiles_projectile_acid
