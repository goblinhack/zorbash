//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/effects/red_splatter.py
//

#include "my_native.hpp"

namespace mod_things_effects_red_splatter {

static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_oversized_and_on_floor_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->is_able_to_fall_set(true);
  self->is_loggable_set(true);
  self->is_one_per_tile_set(true);
  self->is_red_splatter_set(true);
  self->is_removable_if_out_of_slots_set(true);
  self->is_splatter_set(true);
  self->is_tmp_thing_set(true);
  self->text_a_or_an_set("a");
  self->text_description_short_set("An artwork comprised mainly of blood.");
  self->tick_prio_set(MAP_TICK_PRIO_VERY_HIGH);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  delay = 5;
  my::tile(self, {.tile = (name + ".1"), .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "red", .delay_ms = delay, .is_end_of_ascii_anim = true, .is_dead_on_end_of_ascii_anim = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".4"), .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".5"), .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".6"), .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".7"), .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".8"), .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".9"), .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".10"), .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".11"), .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".12"), .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".13"), .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".14"), .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "red", .delay_ms = delay, .is_end_of_anim = true, .is_dead_on_end_of_anim = true});
}

static void init(void)
{
  tp_init("red_splatter", "blood splatter");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_effects_red_splatter
