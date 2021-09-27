//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_globals.h"
#include "my_main.h"
#include "my_monst.h"
#include "my_sprintf.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_tile.h"

//
// Return a score, higher is better for perceived value to you
//
int Thing::get_item_value(Thingp it)
{
  TRACE_AND_INDENT();
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

  dbg4("Item value for %s is %d", it->to_string().c_str(), value);

  return value;
}
