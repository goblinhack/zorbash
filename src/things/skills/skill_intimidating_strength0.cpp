//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_intimidating_strength0.py
//

#include "my_native.hpp"
#include "things/skills/skill_intimidating_strength0.hpp"

namespace mod_things_skills_skill_intimidating_strength0 {

void tp_init(Tpp self)
{
  self->gfx_ascii_shown_set(true);
  self->is_always_activated_set(true);
  self->is_loggable_set(true);
  self->is_skill_set(true);
  self->is_tickable_set(true);
  self->skill_base_name_set("skill_intimidating_strength");
  self->text_description_long_set("No more will you cower on the dungeon beaches with your puny physique. With this skill, your muscles will bulge providing much needed strength bonuses on attacks, and shoving things into pits.");
  self->text_description_short_set("intimidating strength.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "skill_intimidating_strength"});
  my::tile(self, {.tile = "skill_intimidating_strength_activated"});
}

void module_init(void)
{
}

} // namespace mod_things_skills_skill_intimidating_strength0
