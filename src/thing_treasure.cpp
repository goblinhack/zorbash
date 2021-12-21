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
  if (! maybe_itemp()) {
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
