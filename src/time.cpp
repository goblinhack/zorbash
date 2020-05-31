//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_string.h"
#include "my_time.h"

timestamp_t time_now;
timestamp_t base_time_in_mill;
static char buf_[MAXSHORTSTR];

const char *time2str (timestamp_t ms, char *buf, int len)
{
    int log_msec = ms;
    int log_secs = log_msec / ONESEC;
    int log_mins = log_secs / 60;
    int log_hrs = log_mins / 60;

    log_msec = log_msec % ONESEC;
    log_secs = log_secs % 60;
    log_mins = log_mins % 60;

    if (!buf) {
        buf = buf_;
        len = sizeof(buf_);
    }

    buf[0] = '\0';
    snprintf(buf, len, "%02d:%02d:%02d.%03d: ",
             log_hrs, log_mins, log_secs, log_msec);

    if (buf) {
        return (buf);
    }

    return (buf_);
}

const char *timestamp (char *buf, int len)
{
    int log_msec = time_get_time_ms();
    int log_secs = log_msec / ONESEC;
    int log_mins = log_secs / 60;
    int log_hrs = log_mins / 60;

    log_msec = log_msec % ONESEC;
    log_secs = log_secs % 60;
    log_mins = log_mins % 60;

    if (!buf) {
        buf = buf_;
        len = sizeof(buf_);
    }

    buf[0] = '\0';
    snprintf(buf, len, "%02d:%02d:%02d.%03d: ",
             log_hrs, log_mins, log_secs, log_msec);

    if (buf) {
        return (buf);
    }

    return (buf_);
}

bool time_have_x_hundredths_passed_since (timestamp_t val, timestamp_t since)
{
    time_get_time_ms();

    /*
     * Cater for negative future times.
     */
    timestamp_t delay = time_now - since;

    return ((timestamp_t)(delay / 10) > (timestamp_t)val);
}

bool time_have_x_ms_passed_since (timestamp_t val, timestamp_t since)
{
    time_get_time_ms();

    /*
     * Cater for negative future times.
     */
    timestamp_t delay = time_now - since;

    return ((timestamp_t)(delay) >= (timestamp_t)val);
}

bool time_have_x_tenths_passed_since (timestamp_t val, timestamp_t since)
{
    time_get_time_ms();

    /*
     * Cater for negative future times.
     */
    timestamp_t delay = time_now - since;

    return ((timestamp_t)(delay / 100) >= (timestamp_t)val);
}

bool time_have_x_secs_passed_since (timestamp_t val, timestamp_t since)
{
    time_get_time_ms();

    /*
     * Cater for negative future times.
     */
    timestamp_t delay = time_now - since;

    return ((timestamp_t)(delay / ONESEC) >= (timestamp_t)val);
}

timestamp_t time_get_elapsed_secs (timestamp_t val, timestamp_t since)
{
    time_get_time_ms();

    timestamp_t delay = val - since;

    return ((timestamp_t)(delay / ONESEC));
}

timestamp_t time_get_elapsed_tenths (timestamp_t val, timestamp_t since)
{
    time_get_time_ms();

    timestamp_t delay = val - since;

    return ((timestamp_t)(delay / (ONESEC / 10)));
}

void get_timestamp (char *buf, int32_t len)
{
#ifdef ENABLE_LOG_TIMESTAMPS
    char tmp[MAXSTR];
    string_timestamp(tmp, len);
    snprintf(buf, len, "%s %s", timestamp().c_str(), tmp);
#else
    timestamp(buf, len);
#endif
}
