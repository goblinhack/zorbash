//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/staffs/staff_shattering_carry.py
//

#include "my_native.hpp"

namespace mod_things_staffs_staff_shattering_carry {

static void tp_init(const std::string &name);
static void init(void);

static void tp_init(const std::string &name)
{
  int delay = 0;
  Tpp self = my::tp_load(name);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_can_hflip_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_anim_synced_with_owner_set(true);
  self->gfx_pixelart_bounce_on_move_set(true);
  self->gfx_pixelart_equip_carry_anim_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->is_animation_set(true);
  self->is_loggable_set(true);
  self->is_moveable_set(true);
  self->text_a_or_an_set("a");
  self->tick_prio_set(MAP_TICK_PRIO_LOW);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_CARRY);
  delay = 900;
  my::tile(self, {.tile = (name + ".1"), .delay_ms = delay, .frame = 1});
  my::tile(self, {.tile = (name + ".2"), .delay_ms = delay, .frame = 2});
  my::tile(self, {.tile = (name + ".3"), .delay_ms = delay, .frame = 3});
  my::tile(self, {.tile = (name + ".4"), .delay_ms = delay, .frame = 4});
  my::tile(self, {.tile = (name + ".5"), .delay_ms = delay, .frame = 5});
  my::tile(self, {.tile = (name + ".6"), .delay_ms = delay, .frame = 6});
}

static void init(void)
{
  tp_init("staff_shattering_carry");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_staffs_staff_shattering_carry
