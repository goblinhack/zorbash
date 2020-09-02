//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_globals.h"
#include "my_traceback.h"
#include "my_console.h"
#include "my_wid_console.h"
#include "my_log.h"

void Level::log_ (const char *fmt, va_list args)
{
    verify(this);
    auto t = this;
    char buf[MAXSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSTR);
    len = (int)strlen(buf);
    snprintf(buf + len, MAXSTR - len, "level %s: ", t->to_string().c_str());

    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSTR - len, fmt, args);

    putf(MY_STDOUT, buf);
}

void Level::log (const char *fmt, ...)
{
    verify(this);
    auto t = this;
    va_list args;

    va_start(args, fmt);
    t->log_(fmt, args);
    va_end(args);
}

void Level::con_ (const char *fmt, va_list args)
{
    verify(this);
    auto t = this;
    char buf[MAXSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSTR);
    len = (int)strlen(buf);
    snprintf(buf + len, MAXSTR - len, "Level %s: ", t->to_string().c_str());

    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSTR - len, fmt, args);

    putf(MY_STDOUT, buf);

    term_log(buf);
    putchar('\n');
    wid_console_log(buf);
    FLUSH_THE_CONSOLE();
}

void Level::con (const char *fmt, ...)
{
    verify(this);
    auto t = this;
    va_list args;

    va_start(args, fmt);
    t->con_(fmt, args);
    va_end(args);
}

void Level::err_ (const char *fmt, va_list args)
{
    static bool nested_error;
    if (nested_error) {
        return;
    }
    nested_error = true;

    verify(this);
    auto t = this;
    char buf[MAXSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSTR);
    len = (int)strlen(buf);
    snprintf(buf + len, MAXSTR - len, "ERROR: Level %s: ", t->to_cstring());

    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSTR - len, fmt, args);

    putf(MY_STDOUT, buf);

    putf(MY_STDERR, buf);

    fprintf(stderr, "%s\n", buf);

    callstack_dump();
    traceback_dump();

    wid_console_log(buf);
    FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();

    nested_error = false;
}

void Level::err (const char *fmt, ...)
{
    static bool nested_error;
    if (nested_error) {
        return;
    }
    bool old_nested_error = nested_error;
    nested_error = true;

    if (old_nested_error) {
        //
        // Subsequent errors on quitting, avoid error logging
        //
        va_list args;
        va_start(args, fmt);
        log_(fmt, args);
        va_end(args);
    } else {
        g_errored = true;
        va_list args;
        va_start(args, fmt);
        err_(fmt, args);
        va_end(args);
    }
    nested_error = false;
}

void Level::dbg (const char *fmt, ...)
{
    verify(this);
    if (!g_opt_debug) {
        return;
    }
    auto t = this;

    va_list args;

    va_start(args, fmt);
    t->log_(fmt, args);
    va_end(args);
}
