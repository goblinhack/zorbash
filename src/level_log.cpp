//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_globals.h"
#include "my_traceback.h"
#include "my_console.h"
#include "my_wid_console.h"
#include "my_log.h"

void Level::log_ (const char *fmt, va_list args)
{
    verify(this);
    auto l = this;
    char buf[MAXSHORTSTR];

    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSHORTSTR);
    len = (int)strlen(buf);

    snprintf(buf + len, MAXSHORTSTR - len, "%60s: %*s",
             l->to_string().c_str(),
             g_callframes_depth, "");

    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

    putf(MY_STDOUT, buf);
}

void Level::log (const char *fmt, ...)
{
    verify(this);
    log_catchup_missing_indent_levels();
    auto l = this;
    va_list args;
    va_start(args, fmt);
    l->log_(fmt, args);
    va_end(args);
}

void Level::con_ (const char *fmt, va_list args)
{
    verify(this);
    auto l = this;
    char buf[MAXSHORTSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSHORTSTR);
    len = (int)strlen(buf);
    snprintf(buf + len, MAXSHORTSTR - len, "Level %s: ", l->to_string().c_str());

    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

    putf(MY_STDOUT, buf);

    term_log(buf);
    putchar('\n');
    wid_console_log(buf);
    FLUSH_THE_CONSOLE();
}

void Level::con (const char *fmt, ...)
{
    verify(this);
    auto l = this;
    va_list args;

    va_start(args, fmt);
    l->con_(fmt, args);
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
    auto l = this;
    char buf[MAXSHORTSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSHORTSTR);
    len = (int)strlen(buf);
    snprintf(buf + len, MAXSHORTSTR - len, "ERROR: Level %s: ", l->to_cstring());

    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

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
    if (!g_opt_debug2) {
        return;
    }
    auto l = this;

    va_list args;

    va_start(args, fmt);
    l->log_(fmt, args);
    va_end(args);
}
