//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

void Thing::visible(void)
{
  TRACE_NO_INDENT();

  if (! is_hidden) {
    return;
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
  FOR_ALL_EQUIP(e)
  {
    if (equip_id_carry_anim(e).ok()) {
      auto w = level->thing_find(equip_id_carry_anim(e));
      if (w) {
        w->visible();
      }
    }

    if (equip_id_use_anim(e).ok()) {
      auto w = level->thing_find(equip_id_use_anim(e));
      if (w) {
        w->visible();
      }
    }
  }

  auto on_fire_id = on_fire_anim_id();
  if (on_fire_id.ok()) {
    TRACE_NO_INDENT();
    auto w = level->thing_find(on_fire_id);
    if (w) {
      w->visible();
    }
  }

  move_finish();
}

uint8_t Thing::is_visible(void)
{
  TRACE_NO_INDENT();
  return (! is_hidden);
}
