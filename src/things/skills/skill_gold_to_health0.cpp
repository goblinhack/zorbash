//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_gold_to_health0.py
//

#include "my_native.hpp"
#include "things/skills/skill_gold_to_health0.hpp"

namespace mod_things_skills_skill_gold_to_health0 {

void tp_init(Tpp self)
{
  self->gfx_ascii_shown_set(true);
  self->is_loggable_set(true);
  self->is_skill_set(true);
  self->is_tickable_set(true);
  self->on_tick_when_activated_do_set("me.on_tick_when_activated()");
  self->skill_base_name_set("skill_gold_to_health");
  self->text_description_long2_set("When in use, your skin glows radiantly. However you will feel sluggish and less dextrous than normal as your slightly metallic skin becomes less agile.");
  self->text_description_long_set("With this skill you are able to trans-mutate your hard earned gold into life giving health energy.");
  self->text_description_short_set("golden health skill.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "skill_gold_to_health_activated"});
  my::tile(self, {.tile = "skill_gold_to_health"});
}

void module_init(void)
{
}

} // namespace mod_things_skills_skill_gold_to_health0
