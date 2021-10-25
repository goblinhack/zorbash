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

  if (! get_item_vector().empty()) {
    return true;
  }

  auto owner = get_top_owner();
  if (owner) {
    return owner->is_carrying_treasure();
  }

  return false;
}
