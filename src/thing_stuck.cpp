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

bool Thing::is_stuck(void)
{
  if (is_sticky()) {
    return false;
  }

  if (! is_monst() && ! is_player()) {
    return false;
  }

  if (! level->is_sticky(curr_at.x, curr_at.y)) {
    return false;
  }

  if (buff_find_is_slippery()) {
    return false;
  }

  if (environ_prefers_spiderwebs() && level->is_spiderweb(curr_at.x, curr_at.y)) {
    return false;
  }

  //
  // Makes sure ghosts (or the cursor!) do not get stuck in webs.
  //
  if (is_ethereal()) {
    return false;
  }
  return true;
}
