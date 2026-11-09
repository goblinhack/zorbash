//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/ripple_large.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_ripple_large {

static void on_born(uint32_t me, int x, int y);
static void tp_init(const std::string &name);
static void init(void);

static void on_born(uint32_t me, int x, int y)
{
  int selection_x = 0;
  int selection_y = 0;
  { auto pair6_ = my::thing_coords_get(me); selection_x = pair6_.first; selection_y = pair6_.second; }
  for (auto it : my::level_get_all(me, selection_x, selection_y)) {
    if (my::thing_possible_to_attack(me, it)) {
      my::thing_hit(0, me, it);
    }
  }
  my::spawn_at_my_position(me, "green_splatter");
}

static void tp_init(const std::string &name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, std::string("ominous large ripple"), std::string("ominous large ripple"));
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->is_one_per_tile_set(true);
  self->is_removable_if_out_of_slots_set(true);
  self->is_ripple_set(true);
  self->is_tmp_thing_set(true);
  self->noise_on_born_set(50);
  self->text_a_or_an_set("a");
  self->text_description_short_set("An ominous large ripple.");
  self->thing_size_set(THING_SIZE_NORMAL);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  delay = 25;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "circle", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "circle", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "circle", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "circle", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "circle", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "circle", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".7"), .ascii_fg_char = "circle", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".8"), .delay_ms = delay, .is_end_of_anim = true, .is_dead_on_end_of_anim = true});
}

static void init(void)
{
  tp_init("ripple_large1");
  tp_init("ripple_large2");
}

void module_init(void)
{
  native_register("ripple_large", "on_born", 3, [](const int64_t *a) -> NativeRet { (void) a; on_born((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_dungeon_ripple_large
