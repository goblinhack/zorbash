//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_dmap.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::barrel_tick(void)
{
  TRACE_AND_INDENT();
  if (is_floating()) {
    return;
  }

  if (is_ethereal()) {
    return;
  }

  if (! is_soft_body()) {
    return;
  }

  if (! level->is_barrel(mid_at.x, mid_at.y)) {
    return;
  }

  dbg("Crushed by a barrel");

  FOR_ALL_THINGS(level, t, mid_at.x, mid_at.y)
  {
    if (! t->is_barrel()) {
      continue;
    }

    is_hit_by(t, t->get_damage_crush());
    break;
  }
  FOR_ALL_THINGS_END()
}
