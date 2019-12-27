/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_main.h"
#include "my_traceback.h"
#include "my_wid.h"
#include "my_wid_console.h"
#include "my_wid_minicon.h"
#include "my_python.h"
#include "my_console.h"
#include "my_game.h"

uint8_t croaked;

static bool debug = false;

static std::string &timestamp(void)
{
    static timestamp_t time_last;
    static std::string last_timestamp;
    auto time_now = time_get_time_ms_cached();

    if (time_now - time_last < 1000) {
        return last_timestamp;
    }

    time_last = time_now;
    std::time_t result = std::time(nullptr);
    auto s = std::string(std::asctime(std::localtime(&result)));
    s.pop_back();
    last_timestamp = s;
    return last_timestamp;
}

static void get_timestamp (char *buf, int32_t len)
{
    char tmp[MAXSHORTSTR];
    timestamp(tmp, len);
    snprintf(buf, len, "%s %s", timestamp().c_str(), tmp);
}

static void putfg (uint8_t fg, FILE *fp)
{
    static const char *data[] = {
            "\033[1;30m", "\033[1;31m", "\033[1;32m", "\033[1;33m",
            "\033[1;34m", "\033[1;35m", "\033[1;36m", "\033[1;37m",
            "\033[m",
    };

    fputs(data[fg], fp);
}

static void putbg (uint8_t bg, FILE *fp)
{
    static const char *data[] = {
            "\033[1;40m", "\033[1;41m", "\033[1;42m", "\033[1;43m",
            "\033[1;44m", "\033[1;45m", "\033[1;46m", "\033[1;47m",
            "\033[m",
    };

    fputs(data[bg], fp);
}

static int color_to_index (const char **s)
{
    if (!strncmp(*s, "black$", sizeof("black$")-1)) {
        *s += sizeof("black$")-1;
        return (TERM_COLOR_BLACK);
    }
    if (!strncmp(*s, "red$", sizeof("red$")-1)) {
        *s += sizeof("red$")-1;
        return (TERM_COLOR_RED);
    }
    if (!strncmp(*s, "green$", sizeof("green$")-1)) {
        *s += sizeof("green$")-1;
        return (TERM_COLOR_GREEN);
    }
    if (!strncmp(*s, "yellow$", sizeof("yellow$")-1)) {
        *s += sizeof("yellow$")-1;
        return (TERM_COLOR_YELLOW);
    }
    if (!strncmp(*s, "blue$", sizeof("blue$")-1)) {
        *s += sizeof("blue$")-1;
        return (TERM_COLOR_BLUE);
    }
    if (!strncmp(*s, "pink$", sizeof("pink$")-1)) {
        *s += sizeof("pink$")-1;
        return (TERM_COLOR_PINK);
    }
    if (!strncmp(*s, "cyan$", sizeof("cyan$")-1)) {
        *s += sizeof("cyan$")-1;
        return (TERM_COLOR_CYAN);
    }
    if (!strncmp(*s, "white$", sizeof("white$")-1)) {
        *s += sizeof("white$")-1;
        return (TERM_COLOR_WHITE);
    }
    if (!strncmp(*s, "reset$", sizeof("reset$")-1)) {
        *s += sizeof("reset$")-1;
        return (TERM_COLOR_RESET);
    }

    return (TERM_COLOR_WHITE);
}

static void putf (FILE *fp, const char *s)
{
    char c;
    uint8_t looking_for_start = false;

    while ((c = *s++) != '\0') {
        if (!looking_for_start) {
            if (c == '%') {
                looking_for_start = true;
                continue;
            }
        } else if (looking_for_start) {
            if (c == '%') {
            if (!strncmp(s, "fg=", 3)) {
                s += 3;
                putfg(color_to_index(&s), fp);
                looking_for_start = false;
                continue;
            }

            if (!strncmp(s, "bg=", 3)) {
                s += 3;
                putbg(color_to_index(&s), fp);
                looking_for_start = false;
                continue;
            }
            }

            putc(c, fp);
        }

        looking_for_start = false;

        putc(c, fp);
    }

    putc('\n', fp);
}

static void log_ (const char *fmt, va_list args)
{
    char buf[MAXSHORTSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSHORTSTR);
    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);

    // wid_console_log(buf + len);
}

void LOG (const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    log_(fmt, args);
    va_end(args);
}

static void logs_ (const char *fmt, va_list args)
{
    char buf[MAXSHORTSTR];

    buf[0] = '\0';
    vsnprintf(buf, MAXSHORTSTR, fmt, args);

    fwrite(buf, strlen(buf), 1, MY_STDOUT);
    fflush(MY_STDOUT);
}

void LOGS (const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    logs_(fmt, args);
    va_end(args);
}

static void warn_ (const char *fmt, va_list args)
{
    char buf[MAXSHORTSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSHORTSTR);
    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);

    wid_console_log(buf);
}

void WARN (const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    warn_(fmt, args);
    va_end(args);
}

static void con_ (const char *fmt, va_list args)
{
    char buf[MAXSHORTSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSHORTSTR);
    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);

    term_log(buf);
    putchar('\n');

    wid_console_log(buf);
}

static void con_ (const wchar_t *fmt, va_list args)
{
    {
        char buf[MAXSHORTSTR];

        buf[0] = '\0';
        get_timestamp(buf, MAXSHORTSTR);
        fprintf(MY_STDOUT, "%s", buf);
        fflush(MY_STDOUT);
        term_log(buf);
    }

    {
        wchar_t buf[MAXSHORTSTR];
        auto wrote = vswprintf(buf, MAXSHORTSTR, fmt, args);

        /*
        * Only a single nul is written, but as we read 2 at a time...
        */
        if (wrote && (wrote < MAXSHORTSTR - 1)) {
            buf[wrote+1] = '\0';
        } else {
            fprintf(stderr, "Failed to console log: [%S]\n", fmt);
        }

        fwprintf(MY_STDOUT, L"%S\n", buf);
        fflush(MY_STDOUT);
        term_log(buf);
        wid_console_log(buf);
    }
    putchar('\n');
}

void con (const wchar_t *fmt)
{
    {
        char buf[MAXSHORTSTR];

        buf[0] = '\0';
        get_timestamp(buf, MAXSHORTSTR);
        fprintf(MY_STDOUT, "%s", buf);
        fflush(MY_STDOUT);
        term_log(buf);
    }

    {
        fwprintf(MY_STDOUT, L"%S\n", fmt);
        fflush(MY_STDOUT);
        term_log(fmt);
        wid_console_log(fmt);
    }
    putchar('\n');
}

static void minicon_ (const char *fmt, va_list args)
{
    char buf[MAXSHORTSTR];
    char ts[MAXSHORTSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(ts, MAXSHORTSTR);
    sprintf(buf, "%sMINICON: ", ts);
    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);

    term_log(buf);
    putchar('\n');

    wid_minicon_log(buf + len);
    //wid_console_log(buf + len);
}

static void minicon_ (const wchar_t *fmt, va_list args)
{
    {
        char buf[MAXSHORTSTR];

        buf[0] = '\0';
        get_timestamp(buf, MAXSHORTSTR);
        fprintf(MY_STDOUT, "%s", buf);
        fflush(MY_STDOUT);
        term_log(buf);
    }

    {
        wchar_t buf[MAXSHORTSTR];
        auto wrote = vswprintf(buf, MAXSHORTSTR, fmt, args);

        /*
        * Only a single nul is written, but as we read 2 at a time...
        */
        if (wrote && (wrote < MAXSHORTSTR - 1)) {
            buf[wrote+1] = '\0';
        } else {
            fprintf(stderr, "Failed to minicon log: [%S]\n", fmt);
        }

        fwprintf(MY_STDOUT, L"%S\n", buf);
        fflush(MY_STDOUT);
        term_log(buf);
        wid_minicon_log(buf);
        //wid_console_log(buf);
    }
    putchar('\n');
}

void minicon (const wchar_t *fmt)
{
    {
        char buf[MAXSHORTSTR];

        buf[0] = '\0';
        get_timestamp(buf, MAXSHORTSTR);
        fprintf(MY_STDOUT, "%s", buf);
        fflush(MY_STDOUT);
        term_log(buf);
    }

    {
        fwprintf(MY_STDOUT, L"%S\n", fmt);
        fflush(MY_STDOUT);
        term_log(fmt);
        wid_minicon_log(fmt);
        //wid_console_log(fmt);
    }
    putchar('\n');
}

void CON (const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    con_(fmt, args);
    va_end(args);
}

void CON (const wchar_t *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    con_(fmt, args);
    va_end(args);
}

void MINICON (const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    minicon_(fmt, args);
    va_end(args);
}

void MINICON (const wchar_t *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    minicon_(fmt, args);
    va_end(args);
}

static void dying_ (const char *fmt, va_list args)
{
    char buf[MAXSHORTSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSHORTSTR);
    len = (int)strlen(buf);

    snprintf(buf + len, MAXSHORTSTR - len, "DYING: ");

    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

    fprintf(stderr, "%s\n", buf);
    fflush(stderr);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);
}

static void err_ (const char *fmt, va_list args)
{
    char buf[MAXSHORTSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSHORTSTR);
    len = (int)strlen(buf);

    snprintf(buf + len, MAXSHORTSTR - len, "ERROR: %%%%fg=red$");

    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

    len = (int)strlen(buf);
    snprintf(buf + len, MAXSHORTSTR - len, "%%%%fg=reset$");

    putf(MY_STDERR, buf);
    fflush(MY_STDERR);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);

    term_log(buf);
    putchar('\n');

    wid_console_log(buf);

    callstack_dump();
    traceback_dump();
    fflush(MY_STDOUT);
}

static void croak_ (const char *fmt, va_list args)
{
    static int croaked;
    if (croaked) {
        fprintf(stderr,"\nNESTED FATAL ERROR %s %s %d ",__FILE__,__FUNCTION__,__LINE__);
        exit(1);
    }
    croaked = 1;

    char buf[MAXSHORTSTR];
    int len;
    int tslen;

    buf[0] = '\0';
    get_timestamp(buf, MAXSHORTSTR);
    tslen = len = (int)strlen(buf);

    snprintf(buf + len, MAXSHORTSTR - len, "FATAL ERROR: ");

    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

    fprintf(stderr, "%s\n", buf);
    fflush(stderr);

    ERR("%s", buf + tslen);

    if (croaked) {
        return;
    }

    /*
     * Seems to hang on crashes. Is it useful?
     */
    py_trace();

    croaked = true;

    die();
}

void DYING (const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    dying_(fmt, args);
    va_end(args);
}

void DBG (const char *fmt, ...)
{
    if (!debug) {
        return;
    }
    va_list args;

    va_start(args, fmt);
    log_(fmt, args);
    va_end(args);
}

void ERR (const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    err_(fmt, args);
    va_end(args);

    if (wid_console_window && !(wid_console_window->visible)) {
        wid_toggle_hidden(wid_console_window);
        wid_raise(wid_console_window);
    }

    wid_unset_focus();
    wid_unset_focus_lock();
}

void CROAK (const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    croak_(fmt, args);
    va_end(args);

    // quit();
}

void Thing::log_ (const char *fmt, va_list args)
{
    verify(this);
    auto t = this;
    char buf[MAXSHORTSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSHORTSTR);
    len = (int)strlen(buf);
    snprintf(buf + len, MAXSHORTSTR - len, "thing %s: ",
            t->to_string().c_str());

    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);
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

    if (tp_is_loggable(tp())) {
        auto t = this;
        char buf[MAXSHORTSTR];
        int len;

        buf[0] = '\0';
        get_timestamp(buf, MAXSHORTSTR);
        len = (int)strlen(buf);
        snprintf(buf + len, MAXSHORTSTR - len, "thing %s: killed by %s: ",
                t->to_string().c_str(),
                killer->to_string().c_str());

        len = (int)strlen(buf);
        vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

        putf(MY_STDOUT, buf);
        fflush(MY_STDOUT);
    }

    kill();
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

    if (tp_is_loggable(tp())) {
        auto t = this;
        char buf[MAXSHORTSTR];
        int len;

        buf[0] = '\0';
        get_timestamp(buf, MAXSHORTSTR);
        len = (int)strlen(buf);
        snprintf(buf + len, MAXSHORTSTR - len, "thing %s: dead: ",
                t->to_string().c_str());

        len = (int)strlen(buf);
        vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

        putf(MY_STDOUT, buf);
        fflush(MY_STDOUT);
    }

    kill();
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
    char buf[MAXSHORTSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSHORTSTR);
    len = (int)strlen(buf);
    snprintf(buf + len, MAXSHORTSTR - len, "thing %s: ",
            t->to_string().c_str());

    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

    DIE("%s",buf);
}

void Thing::die (const char *fmt, ...)
{
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
    char buf[MAXSHORTSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSHORTSTR);
    len = (int)strlen(buf);
    snprintf(buf + len, MAXSHORTSTR - len, "thing %s: ",
            t->to_string().c_str());

    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);

    term_log(buf);
    putchar('\n');
    wid_console_log(buf);
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
    char buf[MAXSHORTSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSHORTSTR);
    len = (int)strlen(buf);
    snprintf(buf + len, MAXSHORTSTR - len, "ERROR: Thing %s: ",
            t->to_cstring());

    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);

    putf(MY_STDERR, buf);
    fflush(MY_STDERR);

    fprintf(stderr, "%s\n", buf);
    fflush(stderr);

    callstack_dump();
    traceback_dump();
    fflush(MY_STDOUT);

    wid_console_log(buf);
}

void Thing::err (const char *fmt, ...)
{
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
    if (!debug) {
        return;
    }
    auto t = this;

    va_list args;

    va_start(args, fmt);
    t->log_(fmt, args);
    va_end(args);
}

void Light::log_ (const char *fmt, va_list args)
{
    verify(this);
    char buf[MAXSHORTSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSHORTSTR);
    len = (int)strlen(buf);
    snprintf(buf + len, MAXSHORTSTR - len, "light: ");

    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);
}

void Light::log (const char *fmt, ...)
{
    verify(this);
    auto t = this;
    va_list args;

    va_start(args, fmt);
    t->log_(fmt, args);
    va_end(args);
}

void Light::die_ (const char *fmt, va_list args)
{
    verify(this);
    char buf[MAXSHORTSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSHORTSTR);
    len = (int)strlen(buf);
    snprintf(buf + len, MAXSHORTSTR - len, "light: ");

    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

    DIE("%s",buf);
}

void Light::die (const char *fmt, ...)
{
    verify(this);
    auto t = this;
    va_list args;

    va_start(args, fmt);
    t->die_(fmt, args);
    va_end(args);
}

void Light::con_ (const char *fmt, va_list args)
{
    verify(this);
    char buf[MAXSHORTSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSHORTSTR);
    len = (int)strlen(buf);
    snprintf(buf + len, MAXSHORTSTR - len, "light: ");

    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

    putf(MY_STDOUT, buf);

    term_log(buf);
    putchar('\n');
    wid_console_log(buf);
}

void Light::con (const char *fmt, ...)
{
    verify(this);
    auto t = this;
    va_list args;

    va_start(args, fmt);
    t->con_(fmt, args);
    va_end(args);
}

void Light::err_ (const char *fmt, va_list args)
{
    verify(this);
    char buf[MAXSHORTSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSHORTSTR);
    len = (int)strlen(buf);
    snprintf(buf + len, MAXSHORTSTR - len, "ERROR: Light: ");

    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);

    putf(MY_STDERR, buf);
    fflush(MY_STDERR);

    fprintf(stderr, "%s\n", buf);
    fflush(stderr);

    callstack_dump();
    traceback_dump();
    fflush(MY_STDOUT);

    wid_console_log(buf);
}

void Light::err (const char *fmt, ...)
{
    verify(this);
    auto t = this;
    va_list args;

    va_start(args, fmt);
    t->err_(fmt, args);
    va_end(args);
}

void Light::dbg (const char *fmt, ...)
{
    verify(this);
    if (!debug) {
        return;
    }
    auto t = this;

    va_list args;

    va_start(args, fmt);
    t->log_(fmt, args);
    va_end(args);
}

#ifdef ENABLE_WID_DEBUG
static void wid_log_ (Widp t, const char *fmt, va_list args)
{
    char buf[MAXSHORTSTR];
    int len;

    verify(t);
    buf[0] = '\0';
    get_timestamp(buf, MAXSHORTSTR);
    len = (int)strlen(buf);
    snprintf(buf + len, MAXSHORTSTR - len, "wid   %s: ", to_string(t).c_str());
    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

    putf(MY_STDOUT, buf);
}

void WID_LOG (Widp t, const char *fmt, ...)
{
    va_list args;

    verify(t);

    va_start(args, fmt);
    wid_log_(t, fmt, args);
    va_end(args);
}

void WID_DBG (Widp t, const char *fmt, ...)
{
    va_list args;

    verify(t);

    va_start(args, fmt);
    wid_log_(t, fmt, args);
    va_end(args);
}
#endif

static void msgerr_ (const char *fmt, va_list args)
{
    char buf[MAXSHORTSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSHORTSTR);
    len = (int)strlen(buf);

    snprintf(buf + len, MAXSHORTSTR - len, "ERROR: %%%%fg=red$");

    len = (int)strlen(buf);

    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

    len = (int)strlen(buf);
    snprintf(buf + len, MAXSHORTSTR - len, "%%%%fg=reset$");

    putf(MY_STDERR, buf);
    fflush(MY_STDERR);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);

    fprintf(stderr, "%s\n", buf);
    fflush(stderr);

    wid_console_log(buf);

    callstack_dump();
    traceback_dump();

    fflush(MY_STDOUT);
}

void MSG_BOX (const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    msgerr_(fmt, args);
    va_end(args);
}

static void sdl_msgerr_ (const char *fmt, va_list args)
{
    char buf[MAXSHORTSTR];
#if SDL_MAJOR_VERSION >= 2
    int ts_len;
#endif
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXSHORTSTR);
    len = (int)strlen(buf);

    snprintf(buf + len, MAXSHORTSTR - len, "ERROR: %%%%fg=red$");

    len = (int)strlen(buf);
#if SDL_MAJOR_VERSION >= 2
    ts_len = len;
#endif

    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

#if SDL_MAJOR_VERSION >= 2
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
        "zorbash", buf + ts_len, 0);
#endif

    len = (int)strlen(buf);
    snprintf(buf + len, MAXSHORTSTR - len, "%%%%fg=reset$");

    putf(MY_STDERR, buf);
    fflush(MY_STDERR);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);

    fprintf(stderr, "%s\n", buf);
    fflush(stderr);

    callstack_dump();
    traceback_dump();
}

void SDL_MSG_BOX (const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    sdl_msgerr_(fmt, args);
    va_end(args);
}
