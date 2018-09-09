/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#include "my_main.h"
#include "my_backtrace.h"
#include "my_wid.h"
#include "my_wid_console.h"
#include "my_python.h"
#include "my_term.h"
#include "my_thing.h"

uint8_t croaked;

/*
 * putfg
 */
static void putfg (uint8_t fg, FILE *fp)
{_
    static const char *data[] = {
            "\033[1;30m", "\033[1;31m", "\033[1;32m", "\033[1;33m",
            "\033[1;34m", "\033[1;35m", "\033[1;36m", "\033[1;37m",
            "\033[m",
    };

    fputs(data[fg], fp);
}

/*
 * putbg
 */
static void putbg (uint8_t bg, FILE *fp)
{_
    static const char *data[] = {
            "\033[1;40m", "\033[1;41m", "\033[1;42m", "\033[1;43m",
            "\033[1;44m", "\033[1;45m", "\033[1;46m", "\033[1;47m",
            "\033[m",
    };

    fputs(data[bg], fp);
}

static int color_to_index (const char **s)
{_
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
{_
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
{_
    char buf[MAXSTR];
    uint32_t len;

    buf[0] = '\0';
    timestamp(buf, sizeof(buf));
    len = (uint32_t)strlen(buf);
    vsnprintf(buf + len, sizeof(buf) - len, fmt, args);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);

    // wid_console_log(buf + len);
}

void LOG (const char *fmt, ...)
{_
    va_list args;

    va_start(args, fmt);
    log_(fmt, args);
    va_end(args);
}

static void logs_ (const char *fmt, va_list args)
{_
    char buf[MAXSTR];

    buf[0] = '\0';
    vsnprintf(buf, sizeof(buf), fmt, args);

    fwrite(buf, strlen(buf), 1, MY_STDOUT);
    fflush(MY_STDOUT);
}

void LOGS (const char *fmt, ...)
{_
    va_list args;

    va_start(args, fmt);
    logs_(fmt, args);
    va_end(args);
}

static void warn_ (const char *fmt, va_list args)
{_
    char buf[MAXSTR];
    uint32_t len;

    buf[0] = '\0';
    timestamp(buf, sizeof(buf));
    len = (uint32_t)strlen(buf);
    vsnprintf(buf + len, sizeof(buf) - len, fmt, args);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);

    wid_console_log(buf);
}

void WARN (const char *fmt, ...)
{_
    va_list args;

    va_start(args, fmt);
    warn_(fmt, args);
    va_end(args);
}

static void con_ (const char *fmt, va_list args)
{_
    char buf[MAXSTR];
    uint32_t len;

    buf[0] = '\0';
    timestamp(buf, sizeof(buf));
    len = (uint32_t)strlen(buf);
    vsnprintf(buf + len, sizeof(buf) - len, fmt, args);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);

    term_log(buf);
    putchar('\n');
    fflush(stdout);

    wid_console_log(buf + len);
}

static void con_ (const wchar_t *fmt, va_list args)
{_
    {
        char buf[MAXSTR];

        buf[0] = '\0';
        timestamp(buf, sizeof(buf));
        fprintf(MY_STDOUT, "%s", buf);
        fflush(MY_STDOUT);
        term_log(buf);
    }

    {
        wchar_t buf[MAXSTR];
        auto wrote = vswprintf(buf, sizeof(buf), fmt, args);

        /*
         * Only a single nul is written, but as we read 2 at a time...
         */
        if (wrote && (wrote < MAXSTR - 1)) {
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
    fflush(stdout);
}

void con (const wchar_t *fmt)
{_
    {
        char buf[MAXSTR];

        buf[0] = '\0';
        timestamp(buf, sizeof(buf));
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
    fflush(stdout);
}

static void tip_ (const wchar_t *fmt, va_list args)
{_
    wchar_t buf[MAXSTR];

    buf[0] = '\0';
    auto wrote = vswprintf(buf, sizeof(buf), fmt, args);

    /*
     * Only a single nul is written, but as we read 2 at a time...
     */
    if (wrote && (wrote < MAXSTR - 1)) {
        buf[wrote+1] = '\0';
    } else {
        fprintf(stderr, "Failed to console log: [%S]\n", fmt);
    }

    wid_tooltip_set(buf);
}

void tip (const wchar_t *fmt)
{_
    wid_tooltip_set(fmt);
}

static void tip2_ (const wchar_t *fmt, va_list args)
{_
    wchar_t buf[MAXSTR];

    buf[0] = '\0';
    auto wrote = vswprintf(buf, sizeof(buf), fmt, args);

    /*
     * Only a single nul is written, but as we read 2 at a time...
     */
    if (wrote && (wrote < MAXSTR - 1)) {
        buf[wrote+1] = '\0';
    } else {
        fprintf(stderr, "Failed to log: [%S]\n", fmt);
    }

    wid_tooltip2_set(buf);
}

void tip2 (const wchar_t *fmt)
{_
    wid_tooltip2_set(fmt);
}

static void tip_ (const char *fmt, va_list args)
{_
    char buf[MAXSTR];

    buf[0] = '\0';
    vsnprintf(buf, sizeof(buf), fmt, args);

    wid_tooltip_set(string_to_wstring(buf));
}

static void tip2_ (const char *fmt, va_list args)
{_
    char buf[MAXSTR];

    buf[0] = '\0';
    vsnprintf(buf, sizeof(buf), fmt, args);

    wid_tooltip2_set(string_to_wstring(buf));
}

void CON (const char *fmt, ...)
{_
    va_list args;

    va_start(args, fmt);
    con_(fmt, args);
    va_end(args);
}

void CON (const wchar_t *fmt, ...)
{_
    va_list args;

    va_start(args, fmt);
    con_(fmt, args);
    va_end(args);
}

static void dying_ (const char *fmt, va_list args)
{_
    char buf[MAXSTR];
    uint32_t len;

    global_callstack.dump();

    buf[0] = '\0';
    timestamp(buf, sizeof(buf));
    len = (uint32_t)strlen(buf);

    snprintf(buf + len, sizeof(buf) - len, "DYING: ");

    len = (uint32_t)strlen(buf);
    vsnprintf(buf + len, sizeof(buf) - len, fmt, args);

    fprintf(stderr, "%s\n", buf);
    fflush(stderr);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);
}

static void err_ (const char *fmt, va_list args)
{_
    char buf[MAXSTR];
    uint32_t len;

    buf[0] = '\0';
    timestamp(buf, sizeof(buf));
    len = (uint32_t)strlen(buf);

    snprintf(buf + len, sizeof(buf) - len, "ERROR: %%%%fg=red$");

    len = (uint32_t)strlen(buf);
    vsnprintf(buf + len, sizeof(buf) - len, fmt, args);

    len = (uint32_t)strlen(buf);
    snprintf(buf + len, sizeof(buf) - len, "%%%%fg=reset$");

    putf(MY_STDERR, buf);
    fflush(MY_STDERR);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);

    term_log(buf);
    putchar('\n');

    wid_console_log(buf);

    backtrace_print();
    fflush(MY_STDOUT);
}

static void croak_ (const char *fmt, va_list args)
{_
    static int croaked;
    if (croaked) {
        fprintf(stderr,"\nNESTED FATAL ERROR %s %s %d ",__FILE__,__FUNCTION__,__LINE__);
        exit(1);
    }
    croaked = 1;

    char buf[MAXSTR];
    uint32_t len;
    uint32_t tslen;

    buf[0] = '\0';
    timestamp(buf, sizeof(buf));
    tslen = len = (uint32_t)strlen(buf);

    snprintf(buf + len, sizeof(buf) - len, "FATAL ERROR: ");

    len = (uint32_t)strlen(buf);
    vsnprintf(buf + len, sizeof(buf) - len, fmt, args);

    fprintf(stderr, "%s\n", buf);
    fflush(stderr);

    ERR("%s", buf + tslen);

    if (croaked) {
        return;
    }

    py_trace();

    croaked = true;

    die();
}

void TIP (const wchar_t *fmt, ...)
{_
    va_list args;

    va_start(args, fmt);
    tip_(fmt, args);
    va_end(args);
}

void TIP2 (const wchar_t *fmt, ...)
{_
    va_list args;

    va_start(args, fmt);
    tip2_(fmt, args);
    va_end(args);
}

void TIP (const char *fmt, ...)
{_
    va_list args;

    va_start(args, fmt);
    tip_(fmt, args);
    va_end(args);
}

void TIP2 (const char *fmt, ...)
{_
    va_list args;

    va_start(args, fmt);
    tip2_(fmt, args);
    va_end(args);
}

void DYING (const char *fmt, ...)
{_
    va_list args;

    va_start(args, fmt);
    dying_(fmt, args);
    va_end(args);
}

void DBG (const char *fmt, ...)
{_
    return;
    va_list args;

    va_start(args, fmt);
    log_(fmt, args);
    va_end(args);
}

void ERR (const char *fmt, ...)
{_
    va_list args;

    va_start(args, fmt);
    err_(fmt, args);
    va_end(args);

    if (wid_console_window && !wid_console_window->visible) {
        wid_toggle_hidden(wid_console_window);
        wid_raise(wid_console_window);
    }

    wid_set_focus(0);
    wid_focus_lock(0);
}

void CROAK (const char *fmt, ...)
{_
    va_list args;

    va_start(args, fmt);
    croak_(fmt, args);
    va_end(args);

    quit();
}

void Thing::log_ (const char *fmt, va_list args)
{_
    auto t = this;

    char buf[MAXSTR];
    uint32_t len;

    buf[0] = '\0';
    timestamp(buf, sizeof(buf));
    len = (uint32_t)strlen(buf);
    snprintf(buf + len, sizeof(buf) - len, "c-thing %s: ",
             t->logname().c_str());

    len = (uint32_t)strlen(buf);
    vsnprintf(buf + len, sizeof(buf) - len, fmt, args);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);
}

void Thing::log (const char *fmt, ...)
{_
    auto t = this;

    va_list args;

    va_start(args, fmt);
    t->log_(fmt, args);
    va_end(args);
}

void Thing::die_ (const char *fmt, va_list args)
{_
    auto t = this;

    char buf[MAXSTR];
    uint32_t len;

    buf[0] = '\0';
    timestamp(buf, sizeof(buf));
    len = (uint32_t)strlen(buf);
    snprintf(buf + len, sizeof(buf) - len, "c-thing %s: ",
             t->logname().c_str());

    len = (uint32_t)strlen(buf);
    vsnprintf(buf + len, sizeof(buf) - len, fmt, args);

    DIE("%s",buf);
}

void Thing::die (const char *fmt, ...)
{_
    auto t = this;

    va_list args;

    va_start(args, fmt);
    t->die_(fmt, args);
    va_end(args);
}

void Thing::con_ (const char *fmt, va_list args)
{_
    auto t = this;

    char buf[MAXSTR];
    uint32_t len;

    buf[0] = '\0';
    timestamp(buf, sizeof(buf));
    len = (uint32_t)strlen(buf);
    snprintf(buf + len, sizeof(buf) - len, "c-thing %s: ",
             t->logname().c_str());

    len = (uint32_t)strlen(buf);
    vsnprintf(buf + len, sizeof(buf) - len, fmt, args);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);

    wid_console_log(buf);
}

void Thing::con (const char *fmt, ...)
{_
    auto t = this;

    va_list args;

    va_start(args, fmt);
    t->con_(fmt, args);
    va_end(args);
}

void Thing::err_ (const char *fmt, va_list args)
{_
    auto t = this;

    char buf[MAXSTR];
    uint32_t len;

    buf[0] = '\0';
    timestamp(buf, sizeof(buf));
    len = (uint32_t)strlen(buf);
    snprintf(buf + len, sizeof(buf) - len, "ERROR: Thing %s: ",
             t->logname().c_str());

    len = (uint32_t)strlen(buf);
    vsnprintf(buf + len, sizeof(buf) - len, fmt, args);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);

    putf(MY_STDERR, buf);
    fflush(MY_STDERR);

    fprintf(stderr, "%s\n", buf);
    fflush(stderr);

    backtrace_print();
    fflush(MY_STDOUT);

    wid_console_log(buf);
}

void Thing::err (const char *fmt, ...)
{_
    auto t = this;

    va_list args;

    va_start(args, fmt);
    t->err_(fmt, args);
    va_end(args);
}

void Thing::dbg (const char *fmt, ...)
{_
    auto t = this;

    va_list args;

    va_start(args, fmt);
    t->log_(fmt, args);
    va_end(args);
}

#ifdef ENABLE_WID_DEBUG
static void wid_log_ (widp t, const char *fmt, va_list args)
{_
    char buf[MAXSTR];
    uint32_t len;

    buf[0] = '\0';
    timestamp(buf, sizeof(buf));
    len = (uint32_t)strlen(buf);
    snprintf(buf + len, sizeof(buf) - len, "wid   %s: ", wid_logname(t).c_str());
    len = (uint32_t)strlen(buf);
    vsnprintf(buf + len, sizeof(buf) - len, fmt, args);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);
}

void WID_LOG (widp t, const char *fmt, ...)
{_
    va_list args;

    verify(t.get());

    va_start(args, fmt);
    wid_log_(t, fmt, args);
    va_end(args);
}

void WID_DBG (widp t, const char *fmt, ...)
{_
    va_list args;

    verify(t.get());

    va_start(args, fmt);
    wid_log_(t, fmt, args);
    va_end(args);
}
#endif

static void msgerr_ (const char *fmt, va_list args)
{_
    char buf[MAXSTR];
    uint32_t len;

    buf[0] = '\0';
    timestamp(buf, sizeof(buf));
    len = (uint32_t)strlen(buf);

    snprintf(buf + len, sizeof(buf) - len, "ERROR: %%%%fg=red$");

    len = (uint32_t)strlen(buf);

    vsnprintf(buf + len, sizeof(buf) - len, fmt, args);

    len = (uint32_t)strlen(buf);
    snprintf(buf + len, sizeof(buf) - len, "%%%%fg=reset$");

    putf(MY_STDERR, buf);
    fflush(MY_STDERR);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);

    fprintf(stderr, "%s\n", buf);
    fflush(stderr);

    wid_console_log(buf);

    backtrace_print();
    fflush(MY_STDOUT);
}

void MSG_BOX (const char *fmt, ...)
{_
    va_list args;

    va_start(args, fmt);
    msgerr_(fmt, args);
    va_end(args);
}

static void sdl_msgerr_ (const char *fmt, va_list args)
{_
    char buf[MAXSTR];
#if SDL_MAJOR_VERSION >= 2
    uint32_t ts_len;
#endif
    uint32_t len;

    buf[0] = '\0';
    timestamp(buf, sizeof(buf));
    len = (uint32_t)strlen(buf);

    snprintf(buf + len, sizeof(buf) - len, "ERROR: %%%%fg=red$");

    len = (uint32_t)strlen(buf);
#if SDL_MAJOR_VERSION >= 2
    ts_len = len;
#endif

    vsnprintf(buf + len, sizeof(buf) - len, fmt, args);

#if SDL_MAJOR_VERSION >= 2
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
	"zorbash", buf + ts_len, 0);
#endif

    len = (uint32_t)strlen(buf);
    snprintf(buf + len, sizeof(buf) - len, "%%%%fg=reset$");

    putf(MY_STDERR, buf);
    fflush(MY_STDERR);

    putf(MY_STDOUT, buf);
    fflush(MY_STDOUT);

    fprintf(stderr, "%s\n", buf);
    fflush(stderr);

    backtrace_print();
}

void SDL_MSG_BOX (const char *fmt, ...)
{_
    va_list args;

    va_start(args, fmt);
    sdl_msgerr_(fmt, args);
    va_end(args);
}
