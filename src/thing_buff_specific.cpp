//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

bool Thing::buff_find_is_slippery(void)
{
  TRACE_AND_INDENT();

  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_BUFFS(id)
  {
    auto t = level->thing_find(id);
    if (t) {
      if (t->is_slippery()) {
        return true;
      }
    }
  }
  return false;
}

bool Thing::buff_find_is_aquatic(void)
{
  TRACE_AND_INDENT();

  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_BUFFS(id)
  {
    auto t = level->thing_find(id);
    if (t) {
      if (t->is_aquatic()) {
        return true;
      }
    }
  }
  return false;
}
