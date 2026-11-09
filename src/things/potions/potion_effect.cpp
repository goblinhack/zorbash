//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/potions/potion_effect.py
//

#include "my_native.hpp"

namespace mod_things_potions_potion_effect {

static void tp_init(const std::string &name);
static void init(void);

static void tp_init(const std::string &name)
{
  Tpp self = my::tp_load(name);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->is_floating_set(true);
  self->is_loggable_set(true);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_EFFECT);
  my::tile(self, {.tile = "nothing", .ascii_fg_char = "block", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink"});
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "block", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = 50});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "block", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = 100});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "block", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = 100});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "block", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = 100});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "block", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = 100});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "block", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = 100});
  my::tile(self, {.tile = (name + ".7"), .ascii_fg_char = "block", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = 100, .is_end_of_anim = true, .is_dead_on_end_of_anim = true});
}

static void init(void)
{
  tp_init("potion_effect");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_potions_potion_effect
