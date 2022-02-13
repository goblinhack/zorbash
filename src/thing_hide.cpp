//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_monst.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
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

  auto on_fire_anim_id = on_fire_anim_id_get();
  if (on_fire_anim_id.ok()) {
    TRACE_NO_INDENT();
    auto w = level->thing_find(on_fire_anim_id);
    if (w) {
      w->hide();
    }
  }
}
