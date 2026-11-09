//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/bodyparts/hat0.py
//

#include "my_native.hpp"

namespace mod_things_bodyparts_hat0 {

static void tp_init(const std::string &name);
static void init(void);

static void tp_init(const std::string &name)
{
  Tpp self = my::tp_load(name);
  self->gfx_pixelart_animated_can_hflip_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_anim_synced_with_owner_set(true);
  self->gfx_pixelart_bounce_on_move_set(true);
  self->gfx_pixelart_equip_carry_anim_set(true);
  self->is_animation_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->is_loggable_set(true);
  self->is_player_bodypart_hat_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->gfx_pixelart_show_square_outlined_set(true);
  self->is_player_bodypart_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->gfx_pixelart_show_square_outlined_set(true);
  self->is_moveable_set(true);
  self->text_a_or_an_set("a");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_PLAYER_HAT);
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
  my::tile(self, {.tile = "nothing"});
}

static void init(void)
{
  tp_init("bodypart_hat0");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_bodyparts_hat0
