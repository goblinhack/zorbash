//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_gold_to_health_effect.py
//

#include "my_native.hpp"

namespace mod_things_skills_skill_gold_to_health_effect {

static void tp_init(const std::string &name);
static void init(void);

static void tp_init(const std::string &name)
{
  int delay = 0;
  Tpp self = my::tp_load(name);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_oversized_and_on_floor_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->is_floating_set(true);
  self->is_loggable_set(true);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_EFFECT);
  delay = 25;
  my::tile(self, {.tile = (name + ".1"), .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .delay_ms = delay});
  my::tile(self, {.tile = (name + ".4"), .delay_ms = delay});
  my::tile(self, {.tile = (name + ".5"), .delay_ms = delay});
  my::tile(self, {.tile = (name + ".6"), .delay_ms = delay});
  my::tile(self, {.tile = (name + ".7"), .delay_ms = delay});
  my::tile(self, {.tile = (name + ".8"), .delay_ms = delay, .is_end_of_anim = true, .is_dead_on_end_of_anim = true});
}

static void init(void)
{
  tp_init("skill_gold_to_health_effect");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_skills_skill_gold_to_health_effect
