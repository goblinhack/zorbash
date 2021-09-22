//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_globals.h"
#include "my_game.h"
#include "my_main.h"
#include "my_tile.h"
#include "my_monst.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_sprintf.h"

//
// Return a score, higher is better for perceived value to you
//
int Thing::get_item_value (Thingp it)
{ TRACE_AND_INDENT();
  int value = 0;

  if (it->is_treasure_type()) {
    value += 100;
  }

  if (it->is_treasure_class_a()) {
    value += 100;
  }

  if (it->is_treasure_class_b()) {
    value += 1000;
  }

  if (it->is_treasure_class_c()) {
    value += 1000;
  }

  if (it->is_potion()) {
    value += 10000;
  }

  //
  // Things are more "valuable" if we need them now for a health boost
  //
  value += it->get_nutrition();
  value += health_boost_would_occur(it->get_nutrition());

  value += it->get_damage_max();

  value += it->get_gold_value();

  value += 100 * it->get_enchant();

  value *= 1 + it->get_charge_count();

  dbg4("Item value for %s is %d", it->to_string().c_str(), value);

  return value;
}
