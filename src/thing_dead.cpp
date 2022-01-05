//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_color.hpp"
#include "my_game.hpp"
#include "my_log.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

void Thing::dead_(Thingp defeater, const char *fmt, va_list args)
{
  verify(MTYPE_THING, this);
  char reason[ MAXSTR ];
  vsnprintf(reason, MAXSTR, fmt, args);
  killed(defeater, reason);
}

void Thing::dead(Thingp defeater, const char *fmt, ...)
{
  verify(MTYPE_THING, this);
  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->dead_(defeater, fmt, args);
  va_end(args);
}

void Thing::dead_(const char *fmt, va_list args)
{
  verify(MTYPE_THING, this);
  char reason[ MAXSTR ];
  vsnprintf(reason, MAXSTR, fmt, args);
  killed(nullptr, reason);
}

void Thing::dead(Thingp defeater, std::string &reason)
{
  verify(MTYPE_THING, this);
  killed(defeater, reason);
}

void Thing::dead(const std::string &reason)
{
  verify(MTYPE_THING, this);
  killed(nullptr, reason);
}

void Thing::dead(const char *fmt, ...)
{
  verify(MTYPE_THING, this);
  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->dead_(fmt, args);
  va_end(args);
}

void Thing::dead_scheduled_(const char *fmt, va_list args)
{
  verify(MTYPE_THING, this);
  char reason[ MAXSTR ];
  vsnprintf(reason, MAXSTR, fmt, args);
  is_scheduled_for_death = true;
  set_dead_reason(std::string(reason));
}

void Thing::dead_scheduled(const std::string &reason)
{
  verify(MTYPE_THING, this);
  killed(nullptr, reason);
}

void Thing::dead_scheduled(const char *fmt, ...)
{
  verify(MTYPE_THING, this);
  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->dead_scheduled_(fmt, args);
  va_end(args);
}

bool Thing::if_matches_then_dead(const std::string &what, const point &p)
{
  TRACE_AND_INDENT();
  //
  // Don't destroy the floor under critical items
  //
  if ((what == "is_floor") || (what == "is_corridor")) {
    FOR_ALL_THINGS(level, t, p.x, p.y)
    {
      if (t->is_critical_to_level()) {
        return true;
      }
    }
    FOR_ALL_THINGS_END()
  }

  FOR_ALL_THINGS(level, t, p.x, p.y)
  {
    if (t->is_toughness_very_tough()) {
      continue;
    }

    if (t->matches(what)) {
      t->dead(this, "defeated ");

      //
      // Check if we are newly spawned over a chasm
      // Or if something we spawned at needs to react to us
      //
      location_check_forced_all_things_at();
    }
  }
  FOR_ALL_THINGS_END()

  return true;
}
