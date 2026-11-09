//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/gnome_all.py
//

#pragma once
#ifndef _MOD_THINGS_MONSTERS_GNOME_ALL_HPP_
#define _MOD_THINGS_MONSTERS_GNOME_ALL_HPP_

#include "my_native.hpp"

namespace mod_things_monsters_gnome_all {
void on_born(uint32_t me, int x, int y);
void on_you_nat_attack_attempt(uint32_t me, int x, int y);
void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage);
void on_hit_dodge_do(uint32_t me, uint32_t hitter, int x, int y);
void on_death(uint32_t me, int x, int y);
Tpp tp_init(const std::string &name, const std::string &text_long_name);
void module_init(void);
} // namespace mod_things_monsters_gnome_all

#endif
