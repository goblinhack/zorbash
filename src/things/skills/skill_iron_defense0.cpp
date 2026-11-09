//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_iron_defense0.py
//

#include "my_native.hpp"
#include "things/skills/skill_iron_defense0.hpp"

namespace mod_things_skills_skill_iron_defense0 {

void tp_init(Tpp self)
{
  self->gfx_ascii_shown_set(true);
  self->is_loggable_set(true);
  self->is_skill_set(true);
  self->is_tickable_set(true);
  self->skill_base_name_set("skill_iron_defense");
  self->text_description_long_set("This skill allows you to focus all your energies purely on defense.");
  self->text_description_short_set("Iron defense skill.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "skill_iron_defense"});
  my::tile(self, {.tile = "skill_iron_defense_activated"});
}

void module_init(void)
{
}

} // namespace mod_things_skills_skill_iron_defense0
