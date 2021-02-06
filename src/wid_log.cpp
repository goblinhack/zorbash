//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_time.h"
#include "my_string.h"
#include "my_wid.h"
#include "my_log.h"
#include "my_array_bounds_check.h"
#include "my_vector_bounds_check.h"
#include "my_ptrcheck.h"
#include "my_globals.h"

static void wid_log_ (Widp t, const char *fmt, va_list args)
{
    char buf[MAXSTR];
    int len;

    verify(t);
    buf[0] = '\0';
    get_timestamp(buf, MAXSTR);
    len = (int)strlen(buf);
    snprintf(buf + len, MAXSTR - len, "WID [%s]: ", to_string(t).c_str());
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

    if (!g_opt_debug3) {
        return;
    }

    verify(t);

    va_start(args, fmt);
    wid_log_(t, fmt, args);
    va_end(args);
}
