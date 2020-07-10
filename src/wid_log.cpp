//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"

#ifdef ENABLE_UI_DEBUG
static void wid_log_ (Widp t, const char *fmt, va_list args)
{
    char buf[MAXSTR];
    int len;

    verify(t);
    buf[0] = '\0';
    get_timestamp(buf, MAXSTR);
    len = (int)strlen(buf);
    snprintf(buf + len, MAXSTR - len, "wid   %s: ", to_string(t).c_str());
    len = (int)strlen(buf);
    vsnprintf(buf + len, MAXSTR - len, fmt, args);

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
