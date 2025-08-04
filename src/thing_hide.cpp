//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
// REMOVED #include "my_monst.hpp"
// REMOVED #include "my_ptrcheck.hpp"
#include "my_thing.hpp"

void Thing::hide(const std::string &reason)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);

  if (is_hidden) {
    return;
  }

  if (is_loggable()) {
    dbg("Hide: %s", reason.c_str());
  }

  level_pop();
  is_hidden = true;
  level_push();

  //
  // Hide the weapon too or it just floats in the air.
  //
  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(iter)
  {
    if (equip_id_carry_anim(iter).ok()) {
      auto w = level->thing_find(equip_id_carry_anim(iter));
      if (w) {
        w->hide(reason);
      }
    }

    if (equip_id_use_anim(iter).ok()) {
      auto w = level->thing_find(equip_id_use_anim(iter));
      if (w) {
        w->hide(reason);
      }
    }
  }

  TRACE_NO_INDENT();
  FOR_ALL_BODYPART(iter)
  {
    if (bodypart_id_get(iter).ok()) {
      auto w = level->thing_find(bodypart_id_get(iter));
      if (w) {
        w->hide(reason);
      }
    }
  }

  auto id = on_fire_anim_id();
  if (id.ok()) {
    TRACE_NO_INDENT();
    auto w = level->thing_find(id);
    if (w) {
      w->hide(reason);
    }
  }
}

void Thing::hide_callback(void) { hide("callback"); }
