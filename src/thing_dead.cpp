//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"
#include "my_python.h"
#include "my_log.h"

void Thing::dead_ (Thingp killer, const char *fmt, va_list args)
{
    verify(this);
    char reason[MAXSTR];
    vsnprintf(reason, MAXSTR, fmt, args);
    kill(killer, reason);
}

void Thing::dead (Thingp killer, const char *fmt, ...)
{
    verify(this);
    auto t = this;
    va_list args;

    va_start(args, fmt);
    t->dead_(killer, fmt, args);
    va_end(args);
}

void Thing::dead_ (const char *fmt, va_list args)
{
    verify(this);
    char reason[MAXSTR];
    vsnprintf(reason, MAXSTR, fmt, args);
    kill(nullptr, reason);
}

void Thing::dead (Thingp killer, std::string &reason)
{
    verify(this);
    kill(killer, reason);
}

void Thing::dead (std::string &reason)
{
    verify(this);
    kill(nullptr, reason);
}

void Thing::dead (const char *fmt, ...)
{
    verify(this);
    auto t = this;
    va_list args;

    va_start(args, fmt);
    t->dead_(fmt, args);
    va_end(args);
}
