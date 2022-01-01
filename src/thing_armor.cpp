//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_wid_inventory.hpp"

std::list< Thingp > Thing::get_armor_list(void)
{
  TRACE_NO_INDENT();

  std::list< Thingp > out;

  if (! maybe_itemp()) {
    static std::list< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        if (t->is_armor()) {
          out.push_back(t);
        }
      }
    }
    if (t->is_armor()) {
      out.push_back(t);
    }
  }
  return out;
}

std::vector< Thingp > Thing::get_armor_vector(void)
{
  TRACE_NO_INDENT();

  std::vector< Thingp > out;

  if (! maybe_itemp()) {
    static std::vector< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemp()->carrying) {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemp()->carrying) {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        if (t->is_armor()) {
          out.push_back(t);
        }
      }
    }
    if (t->is_armor()) {
      out.push_back(t);
    }
  }
  return out;
}

int Thing::get_carried_armor_count(void)
{
  TRACE_NO_INDENT();
  int count = 0;

  if (! maybe_itemp()) {
    return count;
  }

  for (const auto t : get_armor_list()) {
    if (t->is_armor()) {
      count++;
    }
  }
  return count;
}

int Thing::get_carried_armor_least_value(Thingp *out)
{
  TRACE_NO_INDENT();
  int least_value = -1;

  *out = nullptr;
  if (! maybe_itemp()) {
    return least_value;
  }

  for (const auto t : get_armor_list()) {
    if (! t->is_armor()) {
      continue;
    }

    auto v = maybe_itemp_value(t);
    if (! *out) {
      *out        = t;
      least_value = v;
    } else {
      if (v < least_value) {
        *out        = t;
        least_value = v;
      }
    }
  }
  return least_value;
}

int Thing::get_carried_armor_highest_value(Thingp *out)
{
  TRACE_NO_INDENT();
  int highest_value = -1;

  *out = nullptr;
  if (! maybe_itemp()) {
    return highest_value;
  }

  for (const auto t : get_armor_list()) {
    if (! t->is_armor()) {
      continue;
    }

    auto v = maybe_itemp_value(t);
    if (! *out) {
      *out          = t;
      highest_value = v;
    } else {
      if (v > highest_value) {
        *out          = t;
        highest_value = v;
      }
    }
  }
  return highest_value;
}

int Thing::get_carried_armor_highest_value_for_target(Thingp *out, Thingp target)
{
  TRACE_NO_INDENT();
  int highest_value = -1;

  *out = nullptr;
  if (! maybe_itemp()) {
    return highest_value;
  }

  for (const auto t : get_armor_list()) {
    if (! t->is_armor()) {
      continue;
    }

    //
    // If intelligent don't use a armor that will hit you also
    //
    if (is_intelligent()) {
      if (distance(curr_at, target->curr_at) <= t->blast_max_radius()) {
        continue;
      }
    }

    auto v = maybe_itemp_value(t);
    if (! *out) {
      *out          = t;
      highest_value = v;
    } else {
      if (v > highest_value) {
        *out          = t;
        highest_value = v;
      }
    }
  }
  return highest_value;
}
