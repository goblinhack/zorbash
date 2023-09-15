//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

bool Thing::attempt_to_tame_with(point target_at, Thingp what)
{
  TRACE_NO_INDENT();

  FOR_ALL_MONSTS(level, t, target_at.x, target_at.y)
  {
    if (! t->is_alive_monst()) {
      continue;
    }

    if (attempt_to_tame_with(t, what)) {
      return true;
    }
    break;
  }
  FOR_ALL_THINGS_END()

  return false;
}

bool Thing::attempt_to_tame_with(Thingp it, Thingp what)
{
  TRACE_NO_INDENT();

  if (d1000() >= it->chance_d1000_tameable()) {
    return false;
  }

  if (! it->can_eat(what)) {
    return false;
  }

  it->eat(what);

  it->leader_set(this);

  if (is_player()) {
    msg("You tame %s.", it->text_the().c_str());
  } else {
    msg("%s tames %s.", text_The().c_str(), it->text_the().c_str());
  }

  return true;
}
