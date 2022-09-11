//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

bool Thing::is_carrying_treasure(void)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) {
    return false;
  }

  if (! carried_and_equipped_item_vector().empty()) {
    return true;
  }

  auto owner = top_owner();
  if (owner) {
    return owner->is_carrying_treasure();
  }

  return false;
}

std::list< Thingp > Thing::treasure_list(void)
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
        if (t->is_treasure_type()) {
          out.push_back(t);
        }
      }
    }
    if (t->is_treasure_type()) {
      out.push_back(t);
    }
  }
  return out;
}

std::vector< Thingp > Thing::treasure_vector(void)
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
        if (t->is_treasure_type()) {
          out.push_back(t);
        }
      }
    }
    if (t->is_treasure_type()) {
      out.push_back(t);
    }
  }
  return out;
}
