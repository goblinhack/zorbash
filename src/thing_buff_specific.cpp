//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid_buffbox.hpp"

bool Thing::buff_find_is_slippery(void)
{
  TRACE_AND_INDENT();

  if (! maybe_itemsp()) {
    return false;
  }

  for (auto id : get_itemsp()->buffs) {
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

  for (auto id : get_itemsp()->buffs) {
    auto t = level->thing_find(id);
    if (t) {
      if (t->is_aquatic()) {
        return true;
      }
    }
  }
  return false;
}

