//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/lasers/laser_lightning_fork.py
//

#include "my_native.hpp"

namespace mod_things_lasers_laser_lightning_fork {

static void on_born(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_born(uint32_t me, int x, int y)
{
  int selection_x = 0;
  int selection_y = 0;
  { auto pair6_ = my::thing_coords_get(me); selection_x = pair6_.first; selection_y = pair6_.second; }
  for (auto it : my::level_get_all(me, selection_x, selection_y)) {
    if (my::thing_is_reflective(it)) {
      continue;
    }
    if (my::thing_possible_to_attack(me, it)) {
      my::thing_hit(0, me, it);
    }
  }
  my::spawn_at_my_position(me, "explosion_fire");
  my::thing_sound_play_channel(me, CHANNEL_WEAPON, "lightning_b");
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->dmg_chance_d1000_lightning_set(0, 1000);
  self->dmg_lightning_dice_set("1d10+4");
  self->gfx_ascii_shown_set(true);
  self->is_able_to_attack_owner_set(true);
  self->is_laser_set(true);
  self->is_lightning_set(true);
  self->is_loggable_set(true);
  self->is_no_tile_set(true);
  self->is_usable_set(true);
  self->on_born_do_set("me.on_born()");
  self->text_a_or_an_set("a");
  self->text_pluralize_set("fork lightning");
  self->text_apostrophize_set("fork lightning's");
  self->tick_prio_set(MAP_TICK_PRIO_VERY_HIGH);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "cyan", .ascii_fg_alpha = 255});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "white", .ascii_fg_alpha = 255});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "cyan", .ascii_fg_alpha = 255});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "white", .ascii_fg_alpha = 255});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "cyan", .ascii_fg_alpha = 255});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "white", .ascii_fg_alpha = 200});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "cyan", .ascii_fg_alpha = 200});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "white", .ascii_fg_alpha = 200});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "cyan", .ascii_fg_alpha = 200});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "white", .ascii_fg_alpha = 100});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "cyan", .ascii_fg_alpha = 100});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "white", .ascii_fg_alpha = 100});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "cyan", .ascii_fg_alpha = 100});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "white", .ascii_fg_alpha = 50});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "cyan", .ascii_fg_alpha = 50});
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_fg_col_name = "white", .ascii_fg_alpha = 50});
}

static void init(void)
{
  tp_init("laser_lightning_fork", "fork lightning", "fork lightning");
}

void module_init(void)
{
  native_register("laser_lightning_fork", "on_born", 3, [](const int64_t *a) -> NativeRet { (void) a; on_born((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_lasers_laser_lightning_fork
