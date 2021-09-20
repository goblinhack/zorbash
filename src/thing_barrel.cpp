//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

void Thing::barrel_tick (void)
{_
  if (is_floating()) {
    return;
  }

  if (is_ethereal()) {
    return;
  }

  if (!is_soft_body()) {
    return;
  }

  if (!level->is_barrel(mid_at.x, mid_at.y)) {
    return;
  }

  dbg("Crushed by a barrel");

  FOR_ALL_THINGS(level, t, mid_at.x, mid_at.y) {
    if (!t->is_barrel()) {
      continue;
    }

    is_hit_by(t, t->get_damage_crush());
    break;
  } FOR_ALL_THINGS_END()
}
