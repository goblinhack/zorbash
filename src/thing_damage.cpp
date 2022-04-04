//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>

#include "my_main.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

int Thing::damage_max(void)
{
  TRACE_NO_INDENT();
  auto max_damage = damage_natural_dice().max_roll();
  max_damage      = std::max(max_damage, damage_digest_dice().max_roll());
  max_damage      = std::max(max_damage, damage_melee_dice().max_roll());
  max_damage      = std::max(max_damage, damage_poison_dice().max_roll());
  max_damage      = std::max(max_damage, damage_future1_dice().max_roll());
  max_damage      = std::max(max_damage, damage_future2_dice().max_roll());
  max_damage      = std::max(max_damage, damage_future3_dice().max_roll());
  max_damage      = std::max(max_damage, damage_cold_dice().max_roll());
  max_damage      = std::max(max_damage, damage_fire_dice().max_roll());
  max_damage      = std::max(max_damage, damage_crush_dice().max_roll());
  max_damage      = std::max(max_damage, damage_lightning_dice().max_roll());
  max_damage      = std::max(max_damage, damage_energy_dice().max_roll());
  max_damage      = std::max(max_damage, damage_acid_dice().max_roll());
  max_damage      = std::max(max_damage, damage_digest_dice().max_roll());
  max_damage      = std::max(max_damage, damage_necrosis_dice().max_roll());

  //
  // Add in weapons
  //
  Thingp curr_weapon = equip_get(MONST_EQUIP_WEAPON);
  if (curr_weapon) {
    max_damage = std::max(max_damage, curr_weapon->damage_max());
  }

  //
  // Don't include crush damage as it is non typical
  //
  return max_damage + enchant_get();
}

int Thing::damage_min(void)
{
  TRACE_NO_INDENT();
  auto min_damage = damage_natural_dice().min_roll();
  min_damage      = std::min(min_damage, damage_digest_dice().min_roll());
  min_damage      = std::min(min_damage, damage_melee_dice().min_roll());
  min_damage      = std::min(min_damage, damage_poison_dice().min_roll());
  min_damage      = std::min(min_damage, damage_future1_dice().min_roll());
  min_damage      = std::min(min_damage, damage_future2_dice().min_roll());
  min_damage      = std::min(min_damage, damage_future3_dice().min_roll());
  min_damage      = std::min(min_damage, damage_cold_dice().min_roll());
  min_damage      = std::min(min_damage, damage_fire_dice().min_roll());
  min_damage      = std::min(min_damage, damage_crush_dice().min_roll());
  min_damage      = std::min(min_damage, damage_lightning_dice().min_roll());
  min_damage      = std::min(min_damage, damage_energy_dice().min_roll());
  min_damage      = std::min(min_damage, damage_acid_dice().min_roll());
  min_damage      = std::min(min_damage, damage_digest_dice().min_roll());
  min_damage      = std::min(min_damage, damage_necrosis_dice().min_roll());

  //
  // Add in weapons
  //
  Thingp curr_weapon = equip_get(MONST_EQUIP_WEAPON);
  if (curr_weapon) {
    min_damage = std::min(min_damage, curr_weapon->damage_min());
  }

  //
  // Don't include crush damage as it is non typical
  //
  return min_damage + enchant_get();
}
