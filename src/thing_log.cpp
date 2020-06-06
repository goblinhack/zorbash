//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_traceback.h"
#include "my_time.h"
#include "my_level.h"
#include "my_console.h"
#include "my_wid_console.h"
#include "my_log.h"
#include "my_thing.h"

void Thing::log_ (const char *fmt, va_list args)
{
    verify(this);
    auto t = this;
    char buf[MAXSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSTR);
    len = (int)strlen(buf);
    snprintf(buf + len, MAXSTR - len, "%35s:%*s",
             t->to_string().c_str(),
             callframes_depth - g_thing_callframes_depth, "");

    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSTR - len, fmt, args);

    putf(MY_STDOUT, buf);
}

void Thing::log (const char *fmt, ...)
{
    verify(this);
    auto t = this;
    va_list args;

    va_start(args, fmt);
    t->log_(fmt, args);
    va_end(args);
}

void Thing::dead_ (Thingp killer, const char *fmt, va_list args)
{
    verify(this);

    if (tp()->is_loggable_for_unimportant_stuff()) {
        auto t = this;
        char buf[MAXSTR];
        int len;

        buf[0] = '\0';
        get_timestamp(buf, MAXSTR);
        len = (int)strlen(buf);
        snprintf(buf + len, MAXSTR - len, "%s: killed by %s: ",
                t->to_string().c_str(),
                killer->to_string().c_str());

        len = (int)strlen(buf);
        vsnprintf(buf + len, MAXSTR - len, fmt, args);

        putf(MY_STDOUT, buf);

        char reason[MAXSTR];
        vsnprintf(reason, MAXSTR, fmt, args);
        kill(reason);
    } else {
        kill("no reason");
    }
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

    if (tp()->is_loggable_for_unimportant_stuff()) {
        auto t = this;
        char buf[MAXSTR];
        int len;

        buf[0] = '\0';
        get_timestamp(buf, MAXSTR);
        len = (int)strlen(buf);
        snprintf(buf + len, MAXSTR - len, "%s: dead: ",
                 t->to_string().c_str());

        len = (int)strlen(buf);
        vsnprintf(buf + len, MAXSTR - len, fmt, args);

        putf(MY_STDOUT, buf);
        char reason[MAXSTR];
        vsnprintf(reason, MAXSTR, fmt, args);
        kill(reason);
    } else {
        kill("no reason");
    }
}

void Thing::dead (Thingp killer, std::string &reason)
{
    verify(this);

    if (tp()->is_loggable_for_unimportant_stuff()) {
        auto t = this;
        char buf[MAXSTR];
        int len;

        buf[0] = '\0';
        get_timestamp(buf, MAXSTR);
        len = (int)strlen(buf);
        snprintf(buf + len, MAXSTR - len, "%s: killed by %s: ",
                t->to_string().c_str(),
                killer->to_string().c_str());

        putf(MY_STDOUT, reason.c_str());
        kill(reason);
    } else {
        kill("no reason");
    }
}

void Thing::dead (std::string &reason)
{
    verify(this);

    if (tp()->is_loggable_for_unimportant_stuff()) {
        auto t = this;
        char buf[MAXSTR];
        int len;

        buf[0] = '\0';
        get_timestamp(buf, MAXSTR);
        len = (int)strlen(buf);
        snprintf(buf + len, MAXSTR - len, "%s: dead: ",
                 t->to_string().c_str());

        putf(MY_STDOUT, reason.c_str());
        kill(reason);
    } else {
        kill("no reason");
    }
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

void Thing::die_ (const char *fmt, va_list args)
{
    verify(this);
    auto t = this;
    char buf[MAXSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSTR);
    len = (int)strlen(buf);
    snprintf(buf + len, MAXSTR - len, "%s: ",
            t->to_string().c_str());

    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSTR - len, fmt, args);

    DIE("%s",buf);
}

void Thing::die (const char *fmt, ...)
{
    g_errored = true;

    verify(this);
    auto t = this;
    va_list args;

    va_start(args, fmt);
    t->die_(fmt, args);
    va_end(args);
}

void Thing::con_ (const char *fmt, va_list args)
{
    verify(this);
    auto t = this;
    char buf[MAXSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSTR);
    len = (int)strlen(buf);
    snprintf(buf + len, MAXSTR - len, "%s: ",
            t->to_string().c_str());

    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSTR - len, fmt, args);

    putf(MY_STDOUT, buf);

    term_log(buf);
    putchar('\n');
    wid_console_log(buf);
    FLUSH_THE_CONSOLE();
}

void Thing::con (const char *fmt, ...)
{
    verify(this);
    auto t = this;
    va_list args;

    va_start(args, fmt);
    t->con_(fmt, args);
    va_end(args);
}

void Thing::err_ (const char *fmt, va_list args)
{
    verify(this);
    auto t = this;
    char buf[MAXSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSTR);
    len = (int)strlen(buf);
    snprintf(buf + len, MAXSTR - len, "ERROR: Thing %s: ",
            t->to_cstring());

    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSTR - len, fmt, args);

    putf(MY_STDOUT, buf);

    putf(MY_STDERR, buf);

    fprintf(stderr, "%s\n", buf);

    callstack_dump();
    traceback_dump();

    wid_console_log(buf);
    FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();
}

void Thing::err (const char *fmt, ...)
{
    g_errored = true;

    verify(this);
    auto t = this;
    va_list args;

    va_start(args, fmt);
    t->err_(fmt, args);
    va_end(args);
}

void Thing::dbg (const char *fmt, ...)
{
    verify(this);
    if (game && !game->config.debug_mode) {
        return;
    }
    auto t = this;

    va_list args;

    va_start(args, fmt);
    t->log_(fmt, args);
    va_end(args);
}
