//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_intimidating_strength3.py
//

#include "my_native.hpp"
#include "things/skills/skill_intimidating_strength0.hpp"

namespace mod_things_skills_skill_intimidating_strength3 {

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->shove_bonus_set(3);
  self->skill_replaces_set("skill_intimidating_strength2");
  self->stat_att_bonus_set(3);
  self->stat_str_bonus_set(4);
  self->text_description_very_short_set("IntimStr3");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  mod_things_skills_skill_intimidating_strength0::tp_init(self);
}

static void init(void)
{
  tp_init("skill_intimidating_strength3", "intimidating strength 3", "intimidating strength 3");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_skills_skill_intimidating_strength3
