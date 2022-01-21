//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_color.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::barrel_tick(void)
{
  if (is_floating() || is_flying() || is_ethereal()) {
    return;
  }

  if (! is_toughness_soft() && ! is_barrel()) {
    return;
  }

  if (! level->is_barrel(curr_at.x, curr_at.y)) {
    return;
  }

  dbg("Barrel tick");
  TRACE_AND_INDENT();

  if (is_barrel()) {
    //
    // Find all non barrels and crush them
    //
    FOR_ALL_THINGS_THAT_INTERACT(level, t, curr_at.x, curr_at.y)
    {
      if (! t->is_barrel()) {
        t->log("Crushed by a barrel");
        t->is_attacked_with_damage_crush(this, get_damage_crush());
      }
    }
    FOR_ALL_THINGS_END()
  } else {
    //
    // See if we are under a barrel
    //
    FOR_ALL_THINGS_THAT_INTERACT(level, t, curr_at.x, curr_at.y)
    {
      if (t->is_barrel()) {
        dbg("Crushed by a barrel");
        is_attacked_with_damage_crush(t, t->get_damage_crush());
      }
    }
    FOR_ALL_THINGS_END()
  }
}
