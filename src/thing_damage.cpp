//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include <algorithm>

int Thing::get_damage_max(void)
{
  TRACE_NO_INDENT();
  auto max_damage = get_damage_natural_attack_dice().max_roll();
  max_damage      = std::max(max_damage, get_damage_digest_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_melee_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_poison_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_future1_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_future2_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_future3_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_future4_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_fire_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_crush_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_lightning_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_energy_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_acid_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_digest_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_necrosis_dice().max_roll());

  //
  // Add in weapons
  //
  Thingp curr_weapon = get_equip(MONST_EQUIP_WEAPON);
  if (curr_weapon) {
    max_damage = std::max(max_damage, curr_weapon->get_damage_max());
  }

  //
  // Don't include crush damage as it is non typical
  //
  return max_damage + get_enchant();
}

int Thing::get_damage_min(void)
{
  TRACE_NO_INDENT();
  auto min_damage = get_damage_natural_attack_dice().min_roll();
  min_damage      = std::min(min_damage, get_damage_digest_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_melee_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_poison_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_future1_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_future2_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_future3_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_future4_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_fire_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_crush_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_lightning_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_energy_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_acid_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_digest_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_necrosis_dice().min_roll());

  //
  // Add in weapons
  //
  Thingp curr_weapon = get_equip(MONST_EQUIP_WEAPON);
  if (curr_weapon) {
    min_damage = std::min(min_damage, curr_weapon->get_damage_min());
  }

  //
  // Don't include crush damage as it is non typical
  //
  return min_damage + get_enchant();
}
