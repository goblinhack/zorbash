//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_power_attack0.py
//

#include "my_native.hpp"
#include "things/skills/skill_power_attack0.hpp"

namespace mod_things_skills_skill_power_attack0 {

void tp_init(Tpp self)
{
  self->gfx_ascii_shown_set(true);
  self->is_loggable_set(true);
  self->is_skill_set(true);
  self->is_tickable_set(true);
  self->skill_base_name_set("skill_power_attack");
  self->text_description_long_set("This skill allows you to increase your attack bonus at the expense of defense.");
  self->text_description_short_set("Power attack skill.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "skill_power_attack"});
  my::tile(self, {.tile = "skill_power_attack_activated"});
}

void module_init(void)
{
}

} // namespace mod_things_skills_skill_power_attack0
