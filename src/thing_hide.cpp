//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

void Thing::hide(void)
{
  TRACE_NO_INDENT();
  if (is_hidden) {
    return;
  }
  dbg("hide");

  level_pop();
  is_hidden = true;
  level_push();

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
