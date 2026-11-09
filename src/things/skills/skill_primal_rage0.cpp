//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_primal_rage0.py
//

#include "my_native.hpp"
#include "things/skills/skill_primal_rage0.hpp"

namespace mod_things_skills_skill_primal_rage0 {

void tp_init(Tpp self)
{
  self->gfx_ascii_shown_set(true);
  self->is_auto_activated_set(true);
  self->is_loggable_set(true);
  self->is_skill_set(true);
  self->is_tickable_set(true);
  self->on_tick_when_activated_do_set("me.on_tick_when_activated()");
  self->on_tick_when_deactivated_do_set("me.on_tick_when_deactivated()");
  self->on_use_skill_do_set("me.on_use_skill()");
  self->skill_base_name_set("skill_primal_rage");
  self->text_description_long2_set("When raging your stamina will drain rapidly.");
  self->text_description_long_set("Engage your primal spirit with the ability to rage when low on health. In such a state of frenzy you will gain strength, to-hit and damage bonuses.");
  self->text_description_short_set("primal rage skill.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "skill_primal_rage"});
  my::tile(self, {.tile = "skill_primal_rage_activated"});
}

void module_init(void)
{
}

} // namespace mod_things_skills_skill_primal_rage0
