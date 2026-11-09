//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_double_strike0.py
//

#include "my_native.hpp"
#include "things/skills/skill_double_strike0.hpp"

namespace mod_things_skills_skill_double_strike0 {

void tp_init(Tpp self)
{
  self->dmg_num_of_attacks_set(2);
  self->gfx_ascii_shown_set(true);
  self->is_loggable_set(true);
  self->is_skill_set(true);
  self->is_tickable_set(true);
  self->on_tick_when_activated_do_set("me.on_tick_when_activated()");
  self->on_use_skill_do_set("me.on_use_skill()");
  self->skill_base_name_set("skill_double_strike");
  self->text_description_long_set("With this skill you will develop the ability to deliver a deadly second strike. Initially the extra damage will be minimal but over time you will become a true force to be reckoned with.");
  self->text_description_short_set("Double strike skill.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "skill_double_strike"});
  my::tile(self, {.tile = "skill_double_strike_activated"});
}

void module_init(void)
{
}

} // namespace mod_things_skills_skill_double_strike0
