//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_traceback.h"
#include "my_wid_console.h"
#include "my_wid_minicon.h"
#include "my_wid_botcon.h"
#include "my_python.h"
#include "my_console.h"
#include "my_log.h"

static void log_ (const char *fmt, va_list args)
{
    char buf[MAXSHORTSTR];
    if (callframes_depth) {
        int len;

        buf[0] = '\0';
        get_timestamp(buf, MAXSHORTSTR);
        len = (int)strlen(buf);

        if (!callframes_depth) {
            snprintf(buf + len, MAXSHORTSTR - len, "%60s: ", "");
        } else {
            snprintf(buf + len, MAXSHORTSTR - len, "%60s: %*s", "",
                    callframes_depth - g_thing_callframes_depth, "");
        }

        len = (int)strlen(buf);
        vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

        putf(MY_STDOUT, buf);
    } else {
        int len;

        buf[0] = '\0';
        get_timestamp(buf, MAXSHORTSTR);
        len = (int)strlen(buf);
        vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

        putf(MY_STDOUT, buf);

        // wid_console_log(buf + len);
    }
}

void LOG (const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    log_(fmt, args);
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
    FLUSH_THE_CONSOLE();

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

    term_log(buf);
    putchar('\n');

    wid_console_log(buf);

    FLUSH_THE_CONSOLE();
}

static void con_ (const wchar_t *fmt, va_list args)
{
    {
        char buf[MAXSHORTSTR];

        buf[0] = '\0';
        get_timestamp(buf, MAXSHORTSTR);
        fprintf(MY_STDOUT, "%s", buf);
        term_log(buf);
    }

    {
        wchar_t buf[MAXSHORTSTR];
        auto wrote = vswprintf(buf, MAXSHORTSTR, fmt, args);

        //
        // Only a single nul is written, but as we read 2 at a time...
        //
        if (wrote && (wrote < MAXSHORTSTR - 1)) {
            buf[wrote+1] = '\0';
        } else {
            fprintf(stderr, "Failed to console log: [%S]\n", fmt);
        }

        fwprintf(MY_STDOUT, L"%S\n", buf);
        term_log(buf);
        wid_console_log(buf);
    }

    putchar('\n');
    FLUSH_THE_CONSOLE();
}

void con (const wchar_t *fmt)
{
    {
        char buf[MAXSHORTSTR];

        buf[0] = '\0';
        get_timestamp(buf, MAXSHORTSTR);
        fprintf(MY_STDOUT, "%s", buf);
        term_log(buf);
    }

    {
        fwprintf(MY_STDOUT, L"%S\n", fmt);
        term_log(fmt);
        wid_console_log(fmt);
    }

    putchar('\n');
    FLUSH_THE_CONSOLE();
}

static void minicon_ (const char *fmt, va_list args)
{
    char buf[MAXSHORTSTR];
    char ts[MAXSHORTSTR/2];
    int len;

    buf[0] = '\0';
    get_timestamp(ts, MAXSHORTSTR);
    snprintf(buf, sizeof(buf) - 1, "%sMINICON: ", ts);
    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

    putf(MY_STDOUT, buf);

    term_log(buf);
    putchar('\n');

    wid_minicon_log(buf + len);
    wid_console_log(buf + len);
    FLUSH_THE_CONSOLE();
}

static void minicon_ (const wchar_t *fmt, va_list args)
{
    {
        char ts[MAXSHORTSTR];
        ts[0] = '\0';
        get_timestamp(ts, MAXSHORTSTR);
        fprintf(MY_STDOUT, "%sMINICON: ", ts);
        term_log(ts);
    }

    {
        wchar_t buf[MAXSHORTSTR];
        auto wrote = vswprintf(buf, MAXSHORTSTR, fmt, args);

        //
        // Only a single nul is written, but as we read 2 at a time...
        //
        if (wrote && (wrote < MAXSHORTSTR - 1)) {
            buf[wrote+1] = '\0';
        } else {
            fprintf(stderr, "Failed to minicon log: [%S]\n", fmt);
        }

        fwprintf(MY_STDOUT, L"%S\n", buf);
        term_log(buf);
        wid_minicon_log(buf);
        //wid_console_log(buf);
    }

    putchar('\n');
    FLUSH_THE_CONSOLE();
}

void minicon (const wchar_t *fmt)
{
    {
        char buf[MAXSHORTSTR];

        buf[0] = '\0';
        get_timestamp(buf, MAXSHORTSTR);
        fprintf(MY_STDOUT, "%s", buf);
        term_log(buf);
    }

    {
        fwprintf(MY_STDOUT, L"%S\n", fmt);
        term_log(fmt);
        wid_minicon_log(fmt);
        //wid_console_log(fmt);
    }
    putchar('\n');
    FLUSH_THE_CONSOLE();
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
    putf(MY_STDOUT, buf);

    FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();
}

static void err_ (const char *fmt, va_list args)
{
    static bool nested_error;
    if (nested_error) {
        return;
    }
    nested_error = true;

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

    putf(MY_STDOUT, buf);

    term_log(buf);
    putchar('\n');

    wid_console_log(buf);

    callstack_dump();
    traceback_dump();

    FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();
    nested_error = false;
}

static void croak_ (const char *fmt, va_list args)
{
    if (g_croaked) {
        fprintf(stderr,"\nNESTED FATAL ERROR %s %s %d ",__FILE__,__FUNCTION__,__LINE__);
        exit(1);
    }
    g_croaked = 1;

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

    ERR("%s", buf + tslen);
    FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();

    if (g_croaked) {
        return;
    }

    //
    // Seems to hang on crashes. Is it useful?
    //
    py_trace();

    g_croaked = true;

    FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();
    die();
}

void CROAK (const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    croak_(fmt, args);
    va_end(args);

    // quit();
}

static void croak_clean_ (const char *fmt, va_list args)
{
    if (g_croaked) {
        fprintf(stderr,"\nNESTED FATAL ERROR %s %s %d ",__FILE__,__FUNCTION__,__LINE__);
        exit(1);
    }
    g_croaked = 1;

    FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();

    if (g_croaked) {
        return;
    }

    g_croaked = true;

    FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();
    die();
}

void CROAK_CLEAN (const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    croak_clean_(fmt, args);
    va_end(args);

    // quit();
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
    if (!g_opt_debug) {
        return;
    }
    va_list args;

    va_start(args, fmt);
    log_(fmt, args);
    va_end(args);
}

void myerr (const char *fmt, ...)
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

    wid_unset_focus();
    wid_unset_focus_lock();

    nested_error = false;
}

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

    putf(MY_STDOUT, buf);

    fprintf(stderr, "%s\n", buf);

    wid_console_log(buf);

    callstack_dump();
    traceback_dump();

    FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();
}

void GAME_UI_MSG_BOX (const char *fmt, ...)
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

    putf(MY_STDOUT, buf);

    fprintf(stderr, "%s\n", buf);
    FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();

    callstack_dump();
    traceback_dump();

    FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();
}

void SDL_MSG_BOX (const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    sdl_msgerr_(fmt, args);
    va_end(args);
}

static void botcon_ (const char *fmt, va_list args)
{
    char buf[MAXSHORTSTR];
    char ts[MAXSHORTSTR/2];
    int len;

    buf[0] = '\0';
    get_timestamp(ts, MAXSHORTSTR);
    snprintf(buf, sizeof(buf) - 1, "%sBOTCON: ", ts);
    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSHORTSTR - len, fmt, args);

    //putf(MY_STDOUT, buf);
    //term_log(buf);
    //putchar('\n');

    wid_botcon_log(buf + len);
    //wid_console_log(buf + len);
    //FLUSH_THE_CONSOLE();
}

static void botcon_ (const wchar_t *fmt, va_list args)
{
    {
        char ts[MAXSHORTSTR];
        ts[0] = '\0';
        get_timestamp(ts, MAXSHORTSTR);
        fprintf(MY_STDOUT, "%sBOTCON: ", ts);
        term_log(ts);
    }

    {
        wchar_t buf[MAXSHORTSTR];
        auto wrote = vswprintf(buf, MAXSHORTSTR, fmt, args);

        //
        // Only a single nul is written, but as we read 2 at a time...
        //
        if (wrote && (wrote < MAXSHORTSTR - 1)) {
            buf[wrote+1] = '\0';
        } else {
            fprintf(stderr, "Failed to botcon log: [%S]\n", fmt);
        }

        // fwprintf(MY_STDOUT, L"%S\n", buf);
        // term_log(buf);
        wid_botcon_log(buf);
        //wid_console_log(buf);
    }

    //putchar('\n');
    //FLUSH_THE_CONSOLE();
}

void botcon (const wchar_t *fmt)
{
    if (0)
    {
        char buf[MAXSHORTSTR];

        buf[0] = '\0';
        get_timestamp(buf, MAXSHORTSTR);
        fprintf(MY_STDOUT, "%s", buf);
        term_log(buf);
    }

    {
        // fwprintf(MY_STDOUT, L"%S\n", fmt);
        // term_log(fmt);
        wid_botcon_log(fmt);
        //wid_console_log(fmt);
    }

    //putchar('\n');
    //FLUSH_THE_CONSOLE();
}

void BOTCON (const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    botcon_(fmt, args);
    va_end(args);
}

void BOTCON (const wchar_t *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    botcon_(fmt, args);
    va_end(args);
}
