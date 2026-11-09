//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_super_health0.py
//

#include "my_native.hpp"
#include "things/skills/skill_super_health0.hpp"

namespace mod_things_skills_skill_super_health0 {

void tp_init(Tpp self)
{
  self->gfx_ascii_shown_set(true);
  self->is_always_activated_set(true);
  self->is_loggable_set(true);
  self->is_skill_set(true);
  self->is_tickable_set(true);
  self->on_owner_rcv_dmg_cold_do_set("me.on_owner_rcv_dmg_cold()");
  self->on_owner_rcv_dmg_necrosis_do_set("me.on_owner_rcv_dmg_necrosis()");
  self->on_owner_rcv_dmg_poison_do_set("me.on_owner_rcv_dmg_poison()");
  self->on_owner_rcv_dmg_stat_con_do_set("me.on_owner_rcv_dmg_stat_con()");
  self->on_tick_when_activated_do_set("me.on_tick_when_activated()");
  self->skill_base_name_set("skill_super_health");
  self->text_description_long2_set("You will gain damage reduction from cold, poison and draining.");
  self->text_description_long3_set("Overall, this skill will make you sickeningly healthy and the envy of all that visit the dungeon gym.");
  self->text_description_long_set("With this skill you are able to heal yourself quickly with no impact on stamina and recover from exhaustion quicker.");
  self->text_description_short_set("annoyingly good health.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "skill_super_health"});
  my::tile(self, {.tile = "skill_super_health_activated"});
}

void module_init(void)
{
}

} // namespace mod_things_skills_skill_super_health0
