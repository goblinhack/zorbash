//
// Copyright goblinhack@gmail.com
//

#include "my_thing.hpp"

int Thing::item_count_including_charges(Tpp tp)
{
  TRACE_NO_INDENT();
  auto count = 0;
  for (const auto o : carried_and_equipped_item_vector()) {
    if (o->tp() == tp) {
      if (o->is_bag_item_not_stackable()) {
        count = 1;
      } else {
        if (o->charge_count()) {
          count += o->charge_count();
        } else {
          count++;
        }
      }
    }
  }

  return count;
}

int Thing::item_count_excluding_charges(Tpp tp)
{
  TRACE_NO_INDENT();
  auto count = 0;
  for (const auto o : carried_and_equipped_item_vector()) {
    if (o->tp() == tp) {
      if (o->is_bag_item_not_stackable()) {
        count = 1;
      } else {
        count++;
      }
    }
  }

  return count;
}
