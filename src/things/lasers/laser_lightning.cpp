//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/lasers/laser_lightning.py
//

#include "my_native.hpp"

namespace mod_things_lasers_laser_lightning {

static void on_born(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_born(uint32_t me, int x, int y)
{
  uint32_t it = 0;
  int water_x = 0;
  int water_y = 0;
  for (auto source : my::level_get_all(me, x, y)) {
    if (my::thing_is_water(source)) {
      for (auto water : my::level_flood_fill_get_all_things(me, x, y, "is_water")) {
        { auto pair14_ = my::thing_coords_get(water); water_x = pair14_.first; water_y = pair14_.second; }
        for (const auto &it_loop_ : my::level_get_all(water, water_x, water_y)) {
          it = it_loop_;
          if ((it != me)) {
            if (my::thing_is_reflective(it)) {
              continue;
            }
            if ((my::thing_is_player(it) || my::thing_is_monst(it))) {
              if (my::thing_possible_to_attack(me, it)) {
                if (my::thing_hit(0, me, it)) {
                  if (my::thing_is_player(it)) {
                    my::thing_msg(it, "Current surges through your body!");
                  }
                }
                my::thing_shoot_projectile_or_laser_at(source, "laser_lightning_fork", it);
              }
            }
          }
        }
      }
      return;
    }
    it = source;
    if (my::thing_is_reflective(it)) {
      continue;
    }
    if (my::thing_possible_to_attack(me, it)) {
      if (my::thing_hit(0, me, it)) {
        if (my::thing_is_player(it)) {
          my::thing_msg(it, "Current surges through your body!");
        }
      }
    }
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->dmg_chance_d1000_lightning_set(0, 1000);
  self->dmg_lightning_dice_set("1d20+4");
  self->gfx_ascii_shown_set(true);
  self->is_able_to_attack_owner_set(true);
  self->is_laser_set(true);
  self->is_lightning_set(true);
  self->is_loggable_set(true);
  self->is_no_tile_set(true);
  self->is_usable_set(true);
  self->on_born_do_set("me.on_born()");
  self->text_a_or_an_set("a");
  self->text_pluralize_set("rays of lightnings");
  self->text_apostrophize_set("ray of lightning's");
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
  tp_init("laser_lightning", "ray of lightning", "ray of lightning");
}

void module_init(void)
{
  native_register("laser_lightning", "on_born", 3, [](const int64_t *a) -> NativeRet { (void) a; on_born((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_lasers_laser_lightning
