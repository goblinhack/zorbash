//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/weapons/mace_swing.py
//

#include "my_native.hpp"
#include "things/weapons/_common_sword_swing.hpp"

namespace mod_things_weapons_mace_swing {

static void tp_init(const std::string &name);
static void init(void);

static void tp_init(const std::string &name)
{
  Tpp self = my::tp_load(name);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_can_hflip_set(true);
  self->gfx_pixelart_animated_can_vflip_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_attack_anim_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->is_animation_set(true);
  self->is_loggable_set(true);
  mod_things_weapons__common_sword_swing::init(self, name);
}

static void init(void)
{
  tp_init("mace_swing");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_weapons_mace_swing
