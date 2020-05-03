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
}

void Level::err (const char *fmt, ...)
{
    g_errored = true;

    verify(this);
    auto t = this;
    va_list args;

    va_start(args, fmt);
    t->err_(fmt, args);
    va_end(args);
}

void Level::dbg (const char *fmt, ...)
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
