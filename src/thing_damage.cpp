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

int Thing::damage_max_get(void)
{
  TRACE_NO_INDENT();
  auto max_damage = damage_natural_dice_get().max_roll();
  max_damage      = std::max(max_damage, damage_digest_dice_get().max_roll());
  max_damage      = std::max(max_damage, damage_melee_dice_get().max_roll());
  max_damage      = std::max(max_damage, damage_poison_dice_get().max_roll());
  max_damage      = std::max(max_damage, damage_future1_dice_get().max_roll());
  max_damage      = std::max(max_damage, damage_future2_dice_get().max_roll());
  max_damage      = std::max(max_damage, damage_future3_dice_get().max_roll());
  max_damage      = std::max(max_damage, damage_cold_dice_get().max_roll());
  max_damage      = std::max(max_damage, damage_fire_dice_get().max_roll());
  max_damage      = std::max(max_damage, damage_crush_dice_get().max_roll());
  max_damage      = std::max(max_damage, damage_lightning_dice_get().max_roll());
  max_damage      = std::max(max_damage, damage_energy_dice_get().max_roll());
  max_damage      = std::max(max_damage, damage_acid_dice_get().max_roll());
  max_damage      = std::max(max_damage, damage_digest_dice_get().max_roll());
  max_damage      = std::max(max_damage, damage_necrosis_dice_get().max_roll());

  //
  // Add in weapons
  //
  Thingp curr_weapon = equip_get(MONST_EQUIP_WEAPON);
  if (curr_weapon) {
    max_damage = std::max(max_damage, curr_weapon->damage_max_get());
  }

  //
  // Don't include crush damage as it is non typical
  //
  return max_damage + enchant_get();
}

int Thing::damage_min_get(void)
{
  TRACE_NO_INDENT();
  auto min_damage = damage_natural_dice_get().min_roll();
  min_damage      = std::min(min_damage, damage_digest_dice_get().min_roll());
  min_damage      = std::min(min_damage, damage_melee_dice_get().min_roll());
  min_damage      = std::min(min_damage, damage_poison_dice_get().min_roll());
  min_damage      = std::min(min_damage, damage_future1_dice_get().min_roll());
  min_damage      = std::min(min_damage, damage_future2_dice_get().min_roll());
  min_damage      = std::min(min_damage, damage_future3_dice_get().min_roll());
  min_damage      = std::min(min_damage, damage_cold_dice_get().min_roll());
  min_damage      = std::min(min_damage, damage_fire_dice_get().min_roll());
  min_damage      = std::min(min_damage, damage_crush_dice_get().min_roll());
  min_damage      = std::min(min_damage, damage_lightning_dice_get().min_roll());
  min_damage      = std::min(min_damage, damage_energy_dice_get().min_roll());
  min_damage      = std::min(min_damage, damage_acid_dice_get().min_roll());
  min_damage      = std::min(min_damage, damage_digest_dice_get().min_roll());
  min_damage      = std::min(min_damage, damage_necrosis_dice_get().min_roll());

  //
  // Add in weapons
  //
  Thingp curr_weapon = equip_get(MONST_EQUIP_WEAPON);
  if (curr_weapon) {
    min_damage = std::min(min_damage, curr_weapon->damage_min_get());
  }

  //
  // Don't include crush damage as it is non typical
  //
  return min_damage + enchant_get();
}
