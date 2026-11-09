//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/ripple_small.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_ripple_small {

static void tp_init(const std::string &name);
static void init(void);

static void tp_init(const std::string &name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, std::string("small ripple"), std::string("small ripple"));
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->is_one_per_tile_set(true);
  self->is_removable_if_out_of_slots_set(true);
  self->is_ripple_set(true);
  self->is_tmp_thing_set(true);
  self->noise_on_born_set(10);
  self->text_a_or_an_set("a");
  self->text_description_short_set("A small ripple.");
  self->thing_size_set(THING_SIZE_SMALL);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  delay = 25;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "middle_dot", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "middle_dot", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "middle_dot", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "middle_dot", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "middle_dot", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "middle_dot", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".7"), .ascii_fg_char = "middle_dot", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".8"), .delay_ms = delay, .is_end_of_anim = true, .is_dead_on_end_of_anim = true});
}

static void init(void)
{
  tp_init("ripple_small1");
  tp_init("ripple_small2");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_dungeon_ripple_small
