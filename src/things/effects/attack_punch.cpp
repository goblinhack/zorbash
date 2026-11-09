//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/effects/attack_punch.py
//

#include "my_native.hpp"

namespace mod_things_effects_attack_punch {

static void init1(const std::string &name, const std::string &text_long_name);
static void init(void);

static void init1(const std::string &name, const std::string &text_long_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name);
  self->collision_check_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_can_hflip_set(true);
  self->gfx_pixelart_animated_can_vflip_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_attack_anim_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->is_animation_set(true);
  self->is_loggable_set(true);
  self->is_moveable_set(true);
  self->is_one_per_tile_set(true);
  self->is_removable_if_out_of_slots_set(true);
  self->text_a_or_an_set("a");
  self->text_description_short_set("Punch out.");
  self->tick_prio_set(MAP_TICK_PRIO_VERY_HIGH);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_EFFECT);
  delay = 20;
  my::tile(self, {.tile = (name + ".1"), .ascii_bg_char = "", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_bg_char = "", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_bg_char = "", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_bg_char = "", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .is_dir_down = true, .is_end_of_anim = true, .is_dead_on_end_of_anim = true});
  my::tile(self, {.tile = (name + ".1"), .ascii_bg_char = "", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_bg_char = "", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_bg_char = "", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_bg_char = "", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .is_dir_up = true, .is_end_of_anim = true, .is_dead_on_end_of_anim = true});
  my::tile(self, {.tile = (name + ".1"), .ascii_bg_char = "", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_bg_char = "", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_bg_char = "", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_bg_char = "", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .is_dir_left = true, .is_end_of_anim = true, .is_dead_on_end_of_anim = true});
  my::tile(self, {.tile = (name + ".1"), .ascii_bg_char = "", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_bg_char = "", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_bg_char = "", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_bg_char = "", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .is_dir_right = true, .is_end_of_anim = true, .is_dead_on_end_of_anim = true});
  my::tile(self, {.tile = (name + ".1"), .ascii_bg_char = "", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_bg_char = "", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_bg_char = "", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_bg_char = "", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .is_dir_none = true, .is_end_of_anim = true, .is_dead_on_end_of_anim = true});
}

static void init(void)
{
  init1("attack_punch", "punch attack");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_effects_attack_punch
