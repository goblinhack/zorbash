//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_wid_inventory.hpp"

std::list< Thingp > Thing::boots_list_get(void)
{
  TRACE_NO_INDENT();

  std::list< Thingp > out;

  if (! maybe_itemsp()) {
    static std::list< Thingp > empty;
    return empty;
  }

  FOR_ALL_CARRYING(item)
  {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      FOR_ALL_CARRIED_BY(t, item)
      {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        if (t->is_boots()) {
          out.push_back(t);
        }
      }
    }
    if (t->is_boots()) {
      out.push_back(t);
    }
  }
  return out;
}

std::vector< Thingp > Thing::boots_vector_get(void)
{
  TRACE_NO_INDENT();

  std::vector< Thingp > out;

  if (! maybe_itemsp()) {
    static std::vector< Thingp > empty;
    return empty;
  }

  FOR_ALL_CARRYING(item)
  {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      FOR_ALL_CARRIED_BY(t, item)
      {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        if (t->is_boots()) {
          out.push_back(t);
        }
      }
    }
    if (t->is_boots()) {
      out.push_back(t);
    }
  }
  return out;
}

int Thing::carried_boots_count_get(void)
{
  TRACE_NO_INDENT();
  int count = 0;

  if (! maybe_itemsp()) {
    return count;
  }

  for (const auto t : boots_list_get()) {
    if (t->is_boots()) {
      count++;
    }
  }
  return count;
}

int Thing::carried_boots_least_value_get(Thingp *out)
{
  TRACE_NO_INDENT();
  int least_value = -1;

  *out = nullptr;
  if (! maybe_itemsp()) {
    return least_value;
  }

  for (const auto t : boots_list_get()) {
    if (! t->is_boots()) {
      continue;
    }

    auto v = value_get(t);
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

int Thing::carried_boots_highest_value_get(Thingp *out)
{
  TRACE_NO_INDENT();
  int highest_value = -1;

  *out = nullptr;
  if (! maybe_itemsp()) {
    return highest_value;
  }

  for (const auto t : boots_list_get()) {
    if (! t->is_boots()) {
      continue;
    }

    auto v = value_get(t);
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

int Thing::carried_boots_highest_value_for_target_get(Thingp *out, Thingp target)
{
  TRACE_NO_INDENT();
  int highest_value = -1;

  *out = nullptr;
  if (! maybe_itemsp()) {
    return highest_value;
  }

  for (const auto t : boots_list_get()) {
    if (! t->is_boots()) {
      continue;
    }

    //
    // If intelligent don't use a boots that will hit you also
    //
    if (is_intelligent()) {
      if (distance(curr_at, target->curr_at) <= t->blast_max_radius()) {
        continue;
      }
    }

    auto v = value_get(t);
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
