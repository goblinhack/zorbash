//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_dmap.hpp"
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
  verify(this);
  char reason[ MAXSTR ];
  vsnprintf(reason, MAXSTR, fmt, args);
  defeat(defeater, reason);
}

void Thing::dead(Thingp defeater, const char *fmt, ...)
{
  verify(this);
  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->dead_(defeater, fmt, args);
  va_end(args);
}

void Thing::dead_(const char *fmt, va_list args)
{
  verify(this);
  char reason[ MAXSTR ];
  vsnprintf(reason, MAXSTR, fmt, args);
  defeat(nullptr, reason);
}

void Thing::dead(Thingp defeater, std::string &reason)
{
  verify(this);
  defeat(defeater, reason);
}

void Thing::dead(const std::string &reason)
{
  verify(this);
  defeat(nullptr, reason);
}

void Thing::dead(const char *fmt, ...)
{
  verify(this);
  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->dead_(fmt, args);
  va_end(args);
}

void Thing::dead_scheduled_(const char *fmt, va_list args)
{
  verify(this);
  char reason[ MAXSTR ];
  vsnprintf(reason, MAXSTR, fmt, args);
  is_scheduled_for_death = true;
  set_dead_reason(std::string(reason));
}

void Thing::dead_scheduled(const std::string &reason)
{
  verify(this);
  defeat(nullptr, reason);
}

void Thing::dead_scheduled(const char *fmt, ...)
{
  verify(this);
  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->dead_scheduled_(fmt, args);
  va_end(args);
}
