//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_main.h"
#include "my_globals.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"

void Thing::hide (void)
{_
  if (is_hidden) {
    return;
  }

  is_hidden = true;

  //
  // Hide the weapon too or it just floats in the air.
  //
  if (get_weapon_id_carry_anim().ok()) {
    auto w = level->thing_find(get_weapon_id_carry_anim());
    if (w) { w->hide(); }
  }

  if (get_weapon_id_use_anim().ok()) {
    auto w = level->thing_find(get_weapon_id_use_anim());
    if (w) { w->hide(); }
  }

  auto on_fire_anim_id = get_on_fire_anim_id();
  if (on_fire_anim_id.ok()) {_
    auto w = level->thing_find(on_fire_anim_id);
    if (w) { w->hide(); }
  }
}
