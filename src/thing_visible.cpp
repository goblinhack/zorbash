//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

void Thing::visible(const std::string &reason)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);

  if (! is_hidden) {
    return;
  }

  if (is_loggable()) {
    dbg("Visible: %s", reason.c_str());
  }

  //
  // If this thing has an owner, should the thing stay hidden?
  //
  auto owner = top_owner();
  if (owner) {
    if (this == owner->equip_carry_anim(MONST_EQUIP_WEAPON)) {
      if (owner->equip_use_anim(MONST_EQUIP_WEAPON)) {
        //
        // Stay hidden until the weapon use is done.
        //
        dbg("Stay hidden until weapon use is done");
        return;
      }
    }
  }

  level_pop();
  is_hidden = false;
  level_push();

  //
  // Reveal the weapon again too.
  //
  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(iter)
  {
    if (equip_id_carry_anim(iter).ok()) {
      auto it = level->thing_find(equip_id_carry_anim(iter));
      if (it) {
        it->visible(reason);
      }
    }

    if (equip_id_use_anim(iter).ok()) {
      auto it = level->thing_find(equip_id_use_anim(iter));
      if (it) {
        it->visible(reason);
      }
    }
  }

  TRACE_NO_INDENT();
  FOR_ALL_BODYPART(iter)
  {
    if (bodypart_id_get(iter).ok()) {
      auto it = level->thing_find(bodypart_id_get(iter));
      if (it) {
        it->visible(reason);
      }
    }
  }

  auto on_fire_id = on_fire_anim_id();
  if (on_fire_id.ok()) {
    TRACE_NO_INDENT();
    auto it = level->thing_find(on_fire_id);
    if (it) {
      it->visible(reason);
    }
  }

  move_finish();
}

uint8_t Thing::is_visible(void)
{
  TRACE_NO_INDENT();
  return (! is_hidden);
}

void Thing::visible_callback(void) { visible("callback"); }
