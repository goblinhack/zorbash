//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <cstring>
#include "my_sys.h"
#include "my_time.h"
#include "my_string.h"
#include "my_log.h"
#include "my_file.h"
#include "my_globals.h"

static void file_log_ (const char *fmt, va_list args)
{
    char buf[MAXLONGSTR];
    int len;

    buf[0] = '\0';
    get_timestamp(buf, MAXLONGSTR);
    len = (int)strlen(buf);
    snprintf(buf + len, MAXLONGSTR - len, "FILE: ");
    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

    putf(MY_STDOUT, buf);
}

void FILE_LOG (const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    file_log_(fmt, args);
    va_end(args);
}

void FILE_DBG (const char *fmt, ...)
{
    va_list args;

    if (!g_opt_debug4) {
        return;
    }

    va_start(args, fmt);
    file_log_(fmt, args);
    va_end(args);
}
