//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/effects/green_splatter.py
//

#include "my_native.hpp"

namespace mod_things_effects_green_splatter {

static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_can_hflip_set(true);
  self->gfx_pixelart_animated_can_vflip_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_attack_anim_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->is_animation_set(true);
  self->is_green_splatter_set(true);
  self->is_moveable_set(true);
  self->is_one_per_tile_set(true);
  self->is_removable_if_out_of_slots_set(true);
  self->is_splatter_set(true);
  self->is_tmp_thing_set(true);
  self->text_a_or_an_set("a");
  self->text_description_short_set("Splat attack.");
  self->tick_prio_set(MAP_TICK_PRIO_VERY_HIGH);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_EFFECT);
  delay = 5;
  my::tile(self, {.tile = "green_splatter.1", .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "limegreen", .delay_ms = delay, .is_end_of_ascii_anim = true, .is_dead_on_end_of_ascii_anim = true});
  my::tile(self, {.tile = "green_splatter.2", .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "limegreen", .delay_ms = delay});
  my::tile(self, {.tile = "green_splatter.3", .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "limegreen", .delay_ms = delay});
  my::tile(self, {.tile = "green_splatter.4", .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "limegreen", .delay_ms = delay});
  my::tile(self, {.tile = "green_splatter.5", .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "limegreen", .delay_ms = delay});
  my::tile(self, {.tile = "green_splatter.6", .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "limegreen", .delay_ms = delay});
  my::tile(self, {.tile = "green_splatter.7", .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "limegreen", .delay_ms = delay});
  my::tile(self, {.tile = "green_splatter.8", .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "limegreen", .delay_ms = delay});
  my::tile(self, {.tile = "green_splatter.9", .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "limegreen", .delay_ms = delay});
  my::tile(self, {.tile = "green_splatter.10", .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "limegreen", .delay_ms = delay});
  my::tile(self, {.tile = "green_splatter.11", .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "limegreen", .delay_ms = delay});
  my::tile(self, {.tile = "green_splatter.12", .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "limegreen", .delay_ms = delay});
  my::tile(self, {.tile = "green_splatter.13", .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "limegreen", .delay_ms = delay});
  my::tile(self, {.tile = "green_splatter.14", .ascii_bg_char = "middle_dot", .ascii_bg_col_name = "limegreen", .delay_ms = delay, .is_end_of_anim = true, .is_dead_on_end_of_anim = true});
}

static void init(void)
{
  tp_init("green_splatter", "green slime splatter");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_effects_green_splatter
