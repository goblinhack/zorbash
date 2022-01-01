//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_monst.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

bool Thing::is_carrying_treasure(void)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) {
    return false;
  }

  if (! get_item_vector().empty()) {
    return true;
  }

  auto owner = get_top_owner();
  if (owner) {
    return owner->is_carrying_treasure();
  }

  return false;
}

std::list< Thingp > Thing::get_treasure_list(void)
{
  TRACE_NO_INDENT();

  std::list< Thingp > out;

  if (! maybe_itemsp()) {
    static std::list< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemsp()->carrying) {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemsp()->carrying) {
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

std::vector< Thingp > Thing::get_treasure_vector(void)
{
  TRACE_NO_INDENT();

  std::vector< Thingp > out;

  if (! maybe_itemsp()) {
    static std::vector< Thingp > empty;
    return empty;
  }

  for (const auto &item : get_itemsp()->carrying) {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      for (const auto &item : t->get_itemsp()->carrying) {
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
