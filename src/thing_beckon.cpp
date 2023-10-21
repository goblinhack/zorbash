//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_thing.hpp"

bool Thing::beckon(Thingp target)
{
  TRACE_NO_INDENT();

  auto points = ::line(curr_at, target->curr_at, 0 /* max_elems*/);

  if (points.size() < 2) {
    dbg("Beckon: %s too close", target->to_short_string().c_str());
    return false;
  }

  target->wake("beckoned");

  if (level->is_spell_of_holding_barrier(target->curr_at)) {
    //
    // Unable to beckon as shielded?
    //
    if (target->is_player()) {
      target->msg("%%fg=green$You are shielded from beckoning.%%fg=reset$");
    } else if (target->is_monst() && is_player()) {
      msg("%%fg=yellow$%s is shielded from beckoning.%%fg=reset$", target->text_The().c_str());
    }

    dbg("Beckon: %s is held in a magic barrier", target->to_short_string().c_str());
    return false;
  }

  auto dest = points[ points.size() - 2 ];

  if (target->is_able_to_fall_over()) {
    TRACE_AND_INDENT();
    target->log("knocked over");
    target->dead("falls over");
  }

  dbg("Beckon: %s", target->to_short_string().c_str());
  target->move_to_immediately(dest);

  return true;
}
