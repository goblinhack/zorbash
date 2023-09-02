//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_thing.hpp"

bool Thing::repulse(Thingp target)
{
  TRACE_NO_INDENT();

  auto points = ::line(curr_at, target->curr_at, 0 /* max_elems*/);

  if (points.size() < 2) {
    dbg("Repulse: %s too close", target->to_short_string().c_str());
    return false;
  }

  if (level->is_spell_of_holding_barrier(target->curr_at)) {
    //
    // Unable to beckon as shielded?
    //
    if (target->is_player()) {
      target->msg("%%fg=green$You are shielded from repulsion.%%fg=reset$");
    } else if (target->is_monst() && is_player()) {
      msg("%%fg=yellow$%s is shielded from repulsion.%%fg=reset$", target->text_The().c_str());
    }

    dbg("Beckon: %s is held in a magic barrier", target->to_short_string().c_str());
    return false;
  }

  auto dest = points[ points.size() - 2 ];

  dbg("Repulse: %s", target->to_short_string().c_str());
  target->move_delta(target->curr_at - dest);

  return true;
}
