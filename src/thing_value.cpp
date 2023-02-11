//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_thing.hpp"

//
// Return a score, higher is better for perceived value to you
//
int Thing::value(Thingp it)
{
  TRACE_NO_INDENT();
  int value = 0;

  if (it->is_treasure_type()) {
    value++;
  }

  if (it->is_treasure_class_A()) {
    value++;
  }

  if (it->is_treasure_class_B()) {
    value++;
  }

  if (it->is_treasure_class_C()) {
    value++;
  }

  if (it->is_weapon_class_A()) {
    value++;
  }

  if (it->is_weapon_class_B()) {
    value++;
  }

  if (it->is_weapon_class_C()) {
    value++;
  }

  //
  // Things are more "valuable" if we need them now for a health boost
  //
  value += it->nutrition_get();
  value += health_boost_would_occur(it->nutrition_get());
  value += hunger_boost_would_occur(it->nutrition_get());
  value += it->dmg_max();
  value += it->gold_value();
  //
  // Enchant is included in damage, but enchanting also has other benefits like
  // less corrosive. So give a boost in relation to the enchangt level.
  //
  value += it->enchant_count_get();

  value *= 1 + it->charge_count();

  dbg3("Item value for %s is %d", it->to_short_string().c_str(), value);

  return value;
}
