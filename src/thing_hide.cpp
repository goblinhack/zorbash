//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

// REMOVED #include "my_color.hpp"
// REMOVED #include "my_globals.hpp"
#include "my_level.hpp"
// REMOVED #include "my_main.hpp"
#include "my_monst.hpp"
// REMOVED #include "my_sprintf.hpp"
// REMOVED #include "my_sys.hpp"
#include "my_thing.hpp"

void Thing::hide(void)
{
  TRACE_NO_INDENT();
  if (is_hidden) {
    return;
  }

  is_hidden = true;

  //
  // Hide the weapon too or it just floats in the air.
  //
  FOR_ALL_EQUIP(e)
  {
    if (equip_id_carry_anim(e).ok()) {
      auto w = level->thing_find(equip_id_carry_anim(e));
      if (w) {
        w->hide();
      }
    }

    if (equip_id_use_anim(e).ok()) {
      auto w = level->thing_find(equip_id_use_anim(e));
      if (w) {
        w->hide();
      }
    }
  }

  auto id = on_fire_anim_id();
  if (id.ok()) {
    TRACE_NO_INDENT();
    auto w = level->thing_find(id);
    if (w) {
      w->hide();
    }
  }
}
