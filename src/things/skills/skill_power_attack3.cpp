//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_power_attack3.py
//

#include "my_native.hpp"
#include "things/skills/skill_power_attack0.hpp"

namespace mod_things_skills_skill_power_attack3 {

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->skill_replaces_set("skill_power_attack2");
  self->stat_att_bonus_set(6);
  self->stat_def_bonus_set((-6));
  self->text_description_very_short_set("IronDef3");
  mod_things_skills_skill_power_attack0::tp_init(self);
}

static void init(void)
{
  tp_init("skill_power_attack3", "power attack 3", "power attack 3");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_skills_skill_power_attack3
