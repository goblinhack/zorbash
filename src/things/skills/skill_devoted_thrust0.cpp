//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_devoted_thrust0.py
//

#include "my_native.hpp"
#include "things/skills/skill_devoted_thrust0.hpp"

namespace mod_things_skills_skill_devoted_thrust0 {

void tp_init(Tpp self)
{
  self->gfx_ascii_shown_set(true);
  self->is_loggable_set(true);
  self->is_skill_set(true);
  self->is_tickable_set(true);
  self->on_tick_when_activated_do_set("me.on_tick_when_activated()");
  self->on_use_skill_do_set("me.on_use_skill()");
  self->skill_base_name_set("skill_devoted_thrust");
  self->text_description_long2_set("The Devoted Thrust skill directs your stamina into sheer vanquishing power.");
  self->text_description_long3_set("Be warned that at high levels of this skill, you will become drained very quickly and may render yourself unable to move or jump, or escape a trap.");
  self->text_description_long_set("With devotion to the god, gods, or whatever it is that you worship, you willingly sacrifice life energy in the pursuit of maximal damage.");
  self->text_description_short_set("Devoted thrust skill.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "skill_devoted_thrust"});
  my::tile(self, {.tile = "skill_devoted_thrust_activated"});
}

void module_init(void)
{
}

} // namespace mod_things_skills_skill_devoted_thrust0
