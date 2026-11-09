//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_iron_defense1.py
//

#include "my_native.hpp"
#include "things/skills/skill_iron_defense0.hpp"

namespace mod_things_skills_skill_iron_defense1 {

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->stat_def_bonus_set(2);
  self->text_description_very_short_set("IronDef1");
  mod_things_skills_skill_iron_defense0::tp_init(self);
}

static void init(void)
{
  tp_init("skill_iron_defense1", "iron defense 1", "iron defense 1");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_skills_skill_iron_defense1
