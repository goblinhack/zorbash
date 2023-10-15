//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include <stdarg.h> // do not remove

void Thing::dead_(Thingp defeater, const char *fmt, va_list args)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);

  char reason[ MAXSTR ];
  vsnprintf(reason, MAXSTR, fmt, args);
  killed(defeater, reason);
}

void Thing::dead(Thingp defeater, const char *fmt, ...)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);

  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->dead_(defeater, fmt, args);
  va_end(args);
}

void Thing::dead_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);

  char reason[ MAXSTR ];
  vsnprintf(reason, MAXSTR, fmt, args);
  killed(nullptr, reason);
}

void Thing::dead(Thingp defeater, std::string &reason)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);

  killed(defeater, reason);
}

void Thing::dead(const std::string &reason)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);

  killed(nullptr, reason);
}

void Thing::dead(const char *fmt, ...)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);

  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->dead_(fmt, args);
  va_end(args);
}

void Thing::dead_scheduled(const std::string &reason)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);

  is_scheduled_for_death = true;
  dead_reason_set(reason);
  killed(nullptr, reason.c_str());
}

void Thing::dead_scheduled(const char *fmt, ...)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);

  va_list args;
  char    reason[ MAXSTR ];

  va_start(args, fmt);
  vsnprintf(reason, MAXSTR, fmt, args);
  va_end(args);

  is_scheduled_for_death = true;
  dead_reason_set(std::string(reason));
  killed(nullptr, reason);
}

bool Thing::if_matches_then_dead(const std::string &what, const point p)
{
  TRACE_NO_INDENT();

  //
  // Don't destroy the floor under critical items
  //
  if ((what == "is_floor") || (what == "is_corridor")) {
    TRACE_NO_INDENT();
    FOR_ALL_NON_INTERNAL_THINGS(level, t, p.x, p.y)
    {
      if (t->is_critical_to_level()) {
        return true;
      }
    }
    TRACE_NO_INDENT();
    FOR_ALL_THINGS_END()
  }

  TRACE_NO_INDENT();
  FOR_ALL_NON_INTERNAL_THINGS(level, t, p.x, p.y)
  {
    if (t->matches(what)) {
      t->dead(this, "defeated ");
      t->location_check_me();
    }
  }
  TRACE_NO_INDENT();
  FOR_ALL_THINGS_END()

  return true;
}
