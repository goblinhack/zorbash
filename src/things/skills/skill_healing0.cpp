//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_healing0.py
//

#include "my_native.hpp"
#include "things/skills/skill_healing0.hpp"

namespace mod_things_skills_skill_healing0 {

void tp_init(Tpp self)
{
  self->gfx_ascii_shown_set(true);
  self->is_loggable_set(true);
  self->is_skill_set(true);
  self->is_tickable_set(true);
  self->on_tick_when_activated_do_set("me.on_tick_when_activated()");
  self->skill_base_name_set("skill_healing");
  self->text_description_long_set("With this skill you are able to heal yourself quickly at the expense of your stamina.");
  self->text_description_short_set("Accelerated healing.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "skill_healing"});
  my::tile(self, {.tile = "skill_healing_activated"});
}

void module_init(void)
{
}

} // namespace mod_things_skills_skill_healing0
