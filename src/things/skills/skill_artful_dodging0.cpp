//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_artful_dodging0.py
//

#include "my_native.hpp"
#include "things/skills/skill_artful_dodging0.hpp"

namespace mod_things_skills_skill_artful_dodging0 {

void tp_init(Tpp self)
{
  self->gfx_ascii_shown_set(true);
  self->is_always_activated_set(true);
  self->is_loggable_set(true);
  self->is_skill_set(true);
  self->is_tickable_set(true);
  self->on_tick_when_activated_do_set("me.on_tick_when_activated()");
  self->skill_base_name_set("skill_artful_dodging");
  self->text_description_long2_set("As part of your training you will receive enhanced dexterity and defensive bonuses and the ability to recover stamina more quickly.");
  self->text_description_long_set("This skill allows you to artfully dodge blows that rains down upon you with cat-like reflexes.");
  self->text_description_short_set("Artful dodging skill.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "skill_artful_dodging"});
  my::tile(self, {.tile = "skill_artful_dodging_activated"});
}

void module_init(void)
{
}

} // namespace mod_things_skills_skill_artful_dodging0
