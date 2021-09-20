//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_main.h"
#include "my_globals.h"
#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_monst.h"
#include "my_gl.h"

bool Thing::is_carrying_treasure (void)
{_
  if (!monstp) {
    return false;
  }

  for (const auto& item : monstp->carrying) {
    auto t = level->thing_find(item.id);
    if (!t) {
      continue;
    }
    if (t->is_treasure_type()) {
      return true;
    }
    if (t->monstp && t->monstp->carrying.size()) {
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

std::vector<Thingp> Thing::get_treasure_list (void)
{_
  std::vector<Thingp> tr;
  dbg("Treasure:");
_
  if (!monstp) {
    dbg("Not carrying");
    return tr;
  }

  for (const auto& item : monstp->carrying) {
    auto t = level->thing_find(item.id);
    if (!t) {
      continue;
    }

    dbg("Treasure %s", t->to_string().c_str());

    if (t->monstp && t->monstp->carrying.size()) {
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
