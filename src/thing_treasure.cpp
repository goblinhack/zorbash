//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_gl.h"
#include "my_globals.h"
#include "my_main.h"
#include "my_monst.h"
#include "my_sprintf.h"
#include "my_sys.h"
#include "my_thing.h"

bool Thing::is_carrying_treasure(void)
{
  TRACE_AND_INDENT();
  if (! monst_infop) {
    return false;
  }

  for (const auto &item : monst_infop->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_treasure_type()) {
      return true;
    }
    if (t->monst_infop && t->monst_infop->carrying.size()) {
      if (t->is_carrying_treasure()) {
        return true;
      }
    }
  }

  auto owner = get_top_owner();
  if (owner) {
    return owner->is_carrying_treasure();
  }

  return false;
}

std::vector< Thingp > Thing::get_treasure_list(void)
{
  TRACE_AND_INDENT();
  std::vector< Thingp > tr;
  dbg("Treasure:");
  TRACE_AND_INDENT();
  if (! monst_infop) {
    dbg("Not carrying");
    return tr;
  }

  for (const auto &item : monst_infop->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }

    dbg("Treasure %s", t->to_string().c_str());

    if (t->monst_infop && t->monst_infop->carrying.size()) {
      auto tr2 = t->get_treasure_list();
      std::move(tr2.begin(), tr2.end(), std::back_inserter(tr));
    }

    if (t->is_treasure_type()) {
      tr.push_back(t);
    }
  }

  auto owner = get_immediate_owner();
  if (owner) {
    auto tr2 = owner->get_treasure_list();
    std::move(tr2.begin(), tr2.end(), std::back_inserter(tr));
  }

  return tr;
}
