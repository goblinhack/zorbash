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

//
// Including items in bags
//
std::list< Thingp > Thing::get_item_list(void)
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
        out.push_back(t);
      }
    }
    out.push_back(t);
  }
  return out;
}

std::vector< Thingp > Thing::get_item_vector(void)
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
        out.push_back(t);
      }
    }
    out.push_back(t);
  }

  return out;
}
