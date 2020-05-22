//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_ascii.h"

void putf (FILE *fp, const char *s)
{
    std::string out = ascii_strip(s);
    fputs(out.c_str(), fp);
    putc('\n', fp);
}

#if 0
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
#endif
