//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
// REMOVED #include "my_monst.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"

//
// Return a score, higher is better for perceived value to you
//
int Thing::maybe_itemsp_value(Thingp it)
{
  TRACE_NO_INDENT();
  int value = 0;

  if (it->is_treasure_type()) {
    value++;
  }

  if (it->is_treasure_class_a()) {
    value++;
  }

  if (it->is_treasure_class_b()) {
    value++;
  }

  if (it->is_treasure_class_c()) {
    value++;
  }

  if (it->is_weapon_class_a()) {
    value++;
  }

  if (it->is_weapon_class_b()) {
    value++;
  }

  if (it->is_weapon_class_c()) {
    value++;
  }

  //
  // Things are more "valuable" if we need them now for a health boost
  //
  value += it->get_nutrition();
  value += health_boost_would_occur(it->get_nutrition());
  value += it->get_damage_max();
  value += it->get_gold_value();
  //
  // Enchant is included in damage, but enchanting also has other benefits like
  // less corrosive. So give a boost in relation to the enchangt level.
  //
  value += it->get_enchant();

  value *= 1 + it->get_charge_count();

  dbg3("Item value for %s is %d", it->to_short_string().c_str(), value);

  return value;
}
