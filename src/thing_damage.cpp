//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_dmap.hpp"
#include "my_level.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include <algorithm>

///////////////////////////////////////////////////////////////////////////
// melee
///////////////////////////////////////////////////////////////////////////
const Dice &Thing::get_damage_melee_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_melee_dice());
}

const std::string &Thing::get_damage_melee_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_melee_dice_str());
}

int Thing::get_damage_melee(void)
{
  TRACE_AND_INDENT();
  auto roll = tp()->get_damage_melee_dice().roll();
  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

///////////////////////////////////////////////////////////////////////////
// poison
///////////////////////////////////////////////////////////////////////////
const Dice &Thing::get_damage_poison_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_poison_dice());
}

const std::string &Thing::get_damage_poison_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_poison_dice_str());
}

int Thing::get_damage_poison(void)
{
  TRACE_AND_INDENT();
  auto roll = tp()->get_damage_poison_dice().roll();
  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

///////////////////////////////////////////////////////////////////////////
// necrosis
///////////////////////////////////////////////////////////////////////////
const Dice &Thing::get_damage_necrosis_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_necrosis_dice());
}

const std::string &Thing::get_damage_necrosis_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_necrosis_dice_str());
}

int Thing::get_damage_necrosis(void)
{
  TRACE_AND_INDENT();
  auto roll = tp()->get_damage_necrosis_dice().roll();
  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

///////////////////////////////////////////////////////////////////////////
// crush
///////////////////////////////////////////////////////////////////////////
const Dice &Thing::get_damage_crush_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_crush_dice());
}

const std::string &Thing::get_damage_crush_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_crush_dice_str());
}

int Thing::get_damage_crush(void)
{
  TRACE_AND_INDENT();
  auto roll = tp()->get_damage_crush_dice().roll();
  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

///////////////////////////////////////////////////////////////////////////
// bite
///////////////////////////////////////////////////////////////////////////
const Dice &Thing::get_damage_bite_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_bite_dice());
}

const std::string &Thing::get_damage_bite_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_bite_dice_str());
}

int Thing::get_damage_bite(void)
{
  TRACE_AND_INDENT();
  auto roll = tp()->get_damage_bite_dice().roll();
  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

///////////////////////////////////////////////////////////////////////////
// swallow
///////////////////////////////////////////////////////////////////////////
const Dice &Thing::get_damage_swallow_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_swallow_dice());
}

const std::string &Thing::get_damage_swallow_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_swallow_dice_str());
}

int Thing::get_damage_swallow(void)
{
  TRACE_AND_INDENT();
  auto roll = tp()->get_damage_swallow_dice().roll();
  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

///////////////////////////////////////////////////////////////////////////
// misc
///////////////////////////////////////////////////////////////////////////
int Thing::get_damage_max(void)
{
  TRACE_AND_INDENT();
  auto max_damage = get_damage_bite_dice().max_roll();
  max_damage      = std::max(max_damage, get_damage_swallow_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_melee_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_poison_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_necrosis_dice().max_roll());
  //
  // Don't include crush damage as it is non typical
  //
  return max_damage + get_enchant();
}

int Thing::get_damage_min(void)
{
  TRACE_AND_INDENT();
  auto min_damage = get_damage_bite_dice().min_roll();
  min_damage      = std::min(min_damage, get_damage_swallow_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_melee_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_poison_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_necrosis_dice().min_roll());
  //
  // Don't include crush damage as it is non typical
  //
  return min_damage + get_enchant();
}
