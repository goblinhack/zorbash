//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_vampiric_touch0.py
//

#pragma once
#ifndef _MOD_THINGS_SKILLS_SKILL_VAMPIRIC_TOUCH0_HPP_
#define _MOD_THINGS_SKILLS_SKILL_VAMPIRIC_TOUCH0_HPP_

#include "my_native.hpp"

namespace mod_things_skills_skill_vampiric_touch0 {
int do_vampiric_touch(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage, int damage_reduction_percent);
void tp_init(Tpp self);
void module_init(void);
} // namespace mod_things_skills_skill_vampiric_touch0

#endif
