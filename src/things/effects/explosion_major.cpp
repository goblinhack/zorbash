//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/effects/explosion_major.py
//

#include "my_native.hpp"

namespace mod_things_effects_explosion_major {

static void attack(uint32_t me, uint32_t it);
static void on_born(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void attack(uint32_t me, uint32_t it)
{
  if ((my::thing_enchant_count_get(it) != 0)) {
    return;
  }
  if (my::thing_possible_to_attack(me, it)) {
    if ((it != me)) {
      my::thing_hit_dmg_fire(0, me, it);
      my::thing_hit_dmg_impact(0, me, it);
    }
  }
}

static void on_born(uint32_t me, int x, int y)
{
  int selection_x = 0;
  int selection_y = 0;
  my::thing_sound_play_channel(me, CHANNEL_EXPLOSION, "explosion_d");
  { auto pair21_ = my::thing_coords_get(me); selection_x = pair21_.first; selection_y = pair21_.second; }
  my::spawn_radius_range(me, "explosion_fire", 0, 3);
  for (int dx = (-2), dx_end_ = 3; dx < dx_end_; dx += 1) {
    for (int dy = (-2), dy_end_ = 3; dy < dy_end_; dy += 1) {
      if ((my::pcg_random_inclusive(1, 100) < 20)) {
        my::place_at(me, "small_fire", (x + dx), (y + dy));
      }
      if ((my::pcg_random_inclusive(1, 100) < 10)) {
        my::place_at(me, "fire", (x + dx), (y + dy));
      }
      for (auto it : my::level_get_all(me, (selection_x + dx), (selection_y + dy))) {
        attack(me, it);
      }
    }
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->dmg_chance_d1000_fire_set(0, 1000);
  self->dmg_chance_d1000_impact_set(0, 1000);
  self->dmg_fire_dice_set("6d6");
  self->dmg_impact_dice_set("3d6");
  self->dmg_nat_att_type_set("blast");
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_oversized_and_on_floor_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->is_explosion_set(true);
  self->is_fire_set(true);
  self->is_floating_set(true);
  self->is_loggable_set(true);
  self->is_one_per_tile_set(true);
  self->light_color_set("yellow");
  self->light_dist_set(4);
  self->noise_on_born_set(100);
  self->on_born_do_set("me.on_born()");
  self->temperature_set(100);
  self->text_hits_set("blasts");
  self->tick_prio_set(MAP_TICK_PRIO_VERY_HIGH);
  self->z_depth_set(MAP_DEPTH_TOP);
  self->z_prio_set(MAP_Z_PRIO_EFFECT);
  delay = 50;
  my::tile(self, {.tile = (name + ".1"), .ascii_bg_char = "block", .ascii_bg_col_name = "orange", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_bg_char = "block", .ascii_bg_col_name = "orange", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_bg_char = "block", .ascii_bg_col_name = "orange", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".4"), .ascii_bg_char = "block", .ascii_bg_col_name = "orange", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".5"), .ascii_bg_char = "block", .ascii_bg_col_name = "orange", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".6"), .ascii_bg_char = "block", .ascii_bg_col_name = "orange", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".7"), .ascii_bg_char = "block", .ascii_bg_col_name = "orange", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".8"), .ascii_bg_char = "block", .ascii_bg_col_name = "orange", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".9"), .ascii_bg_char = "block", .ascii_bg_col_name = "orange", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".10"), .ascii_bg_char = "block", .ascii_bg_col_name = "orange", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".11"), .ascii_bg_char = "block", .ascii_bg_col_name = "orange", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".12"), .ascii_bg_char = "block", .ascii_bg_col_name = "orange", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".13"), .ascii_bg_char = "block", .ascii_bg_col_name = "orange", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".14"), .ascii_bg_char = "block", .ascii_bg_col_name = "orange", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".15"), .ascii_bg_char = "block", .ascii_bg_col_name = "orange", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".16"), .ascii_bg_char = "block", .ascii_bg_col_name = "orange", .ascii_fg_col_name = "", .delay_ms = delay, .is_end_of_anim = true, .is_dead_on_end_of_anim = true});
}

static void init(void)
{
  tp_init("explosion_major", "huge explosion", "huge explosion");
}

void module_init(void)
{
  native_register("explosion_major", "attack", 2, [](const int64_t *a) -> NativeRet { (void) a; attack((uint32_t) a[0], (uint32_t) a[1]); return NativeRet {}; });
  native_register("explosion_major", "on_born", 3, [](const int64_t *a) -> NativeRet { (void) a; on_born((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_effects_explosion_major
