//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

std::list< Thingp > Thing::weapon_list(void)
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
        if (t->is_weapon()) {
          out.push_back(t);
        }
      }
    }
    if (t->is_weapon()) {
      out.push_back(t);
    }
  }

  //
  // Intentionally not including equipped things
  //

  return out;
}

std::vector< Thingp > Thing::weapon_vector(void)
{
  std::vector< Thingp > out;

  TRACE_NO_INDENT();
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
        if (t->is_weapon()) {
          out.push_back(t);
        }
      }
    }
    if (t->is_weapon()) {
      out.push_back(t);
    }
  }
  return out;
}

int Thing::carried_weapon_count(void)
{
  TRACE_NO_INDENT();
  int count = 0;

  if (! maybe_itemsp()) {
    return count;
  }

  for (const auto t : weapon_list()) {
    if (t->is_weapon()) {
      count++;
    }
  }
  return count;
}

int Thing::carried_weapon_least_value(Thingp *out)
{
  TRACE_NO_INDENT();
  int least_value = -1;

  *out = nullptr;
  if (! maybe_itemsp()) {
    return least_value;
  }

  for (const auto t : weapon_list()) {
    if (! t->is_weapon()) {
      continue;
    }

    auto v = value(t);
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

int Thing::carried_weapon_highest_value(Thingp *out)
{
  TRACE_NO_INDENT();
  int highest_value = -1;

  *out = nullptr;
  if (! maybe_itemsp()) {
    return highest_value;
  }

  for (const auto t : weapon_list()) {
    if (! t->is_weapon()) {
      continue;
    }

    auto v = value(t);
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
