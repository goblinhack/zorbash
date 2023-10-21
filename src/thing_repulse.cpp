//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_thing.hpp"

bool Thing::repulse(Thingp target)
{
  TRACE_NO_INDENT();

  auto points = ::line(curr_at, target->curr_at, 0 /* max_elems*/);

  target->wake("repulsed");

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

  auto dest = target->curr_at + (target->curr_at - points[ points.size() - 2 ]);

  dbg("Repulse: %s to %s", target->to_string().c_str(), dest.to_string().c_str());
  TRACE_AND_INDENT();

  if (target->is_brazier()) {
    TRACE_AND_INDENT();
    target->log("knocked over");
    target->dead("falls over");
  }

  if (level->is_obs_shoving(dest)) {
    if (level->is_wall(dest)) {
      //
      // Slammed against a wall?
      //
      if (target->is_player()) {
        target->msg("%%fg=green$You are slammed against a wall.%%fg=reset$");
      } else if (target->is_monst() && is_player()) {
        msg("%%fg=yellow$%s is slammed against a wall.%%fg=reset$", target->text_The().c_str());
      }
      target->is_attacked_with_dmg_impact(this, this, d10());
    } else if (level->is_door(dest)) {
      //
      // Slammed against a door?
      //
      if (target->is_player()) {
        target->msg("%%fg=green$You are slammed against a door.%%fg=reset$");
      } else if (target->is_monst() && is_player()) {
        msg("%%fg=yellow$%s is slammed against a door.%%fg=reset$", target->text_The().c_str());
      }
      target->is_attacked_with_dmg_impact(this, this, d8());
    } else {
      //
      // Slammed against something.
      //
      if (target->is_player()) {
        target->msg("%%fg=green$You are slammed against an obstacle.%%fg=reset$");
      } else if (target->is_monst() && is_player()) {
        msg("%%fg=yellow$%s is slammed against an obstacle.%%fg=reset$", target->text_The().c_str());
      }
      target->is_attacked_with_dmg_impact(this, this, d6());
    }

    dbg("Beckon: %s is blocked by an obstacle", target->to_short_string().c_str());
    return false;
  }

  dbg("Repulse: %s", dest.to_string().c_str());
  target->move(dest);

  return true;
}
