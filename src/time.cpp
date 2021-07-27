//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_string.h"
#include "my_time.h"
#include "my_sdl.h"

timestamp_t time_now;
timestamp_t base_time_in_mill;
static char buf_[MAXSHORTSTR];

timestamp_t time_get_time_ms (void)
{
    time_update_time_milli();

    return (time_now);
}

timestamp_t time_get_time_ms_cached (void)
{
    return (time_now);
}

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

    //
    // Cater for negative future times.
    //
    timestamp_t delay = time_now - since;

    return ((timestamp_t)(delay / 10) > (timestamp_t)val);
}

bool time_have_x_ms_passed_since (timestamp_t val, timestamp_t since)
{
    time_get_time_ms();

    //
    // Cater for negative future times.
    //
    timestamp_t delay = time_now - since;

    return ((timestamp_t)(delay) >= (timestamp_t)val);
}

bool time_have_x_tenths_passed_since (timestamp_t val, timestamp_t since)
{
    time_get_time_ms();

    //
    // Cater for negative future times.
    //
    timestamp_t delay = time_now - since;

    return ((timestamp_t)(delay / 100) >= (timestamp_t)val);
}

bool time_have_x_secs_passed_since (timestamp_t val, timestamp_t since)
{
    time_get_time_ms();

    //
    // Cater for negative future times.
    //
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

timestamp_t time_update_time_milli (void)
{
#ifdef NOT_NEEDED
    //
    // Some macos specific way of getting the time that looks like it could
    // be useful, so leaving around
    //
    uint64_t abs_time = mach_absolute_time();
    Nanoseconds nano_time = AbsoluteToNanoseconds( *(AbsoluteTime *) &abs_time );
    uint64_t nano_val = * (uint64_t *) &nano_time;;
    uint32_t time_in_mill = nano_val / 1000000LLU;

    if (!base_time_in_mill) {
        base_time_in_mill = time_in_mill;
    }

    time_now = (time_in_mill - base_time_in_mill);

    return (time_now);
#endif
#ifdef NOT_NEEDED
    extern uint8_t sdl_main_loop_running;
    extern uint8_t sdl_init_video;

    if (unlikely(!sdl_main_loop_running || !sdl_init_video)) {
        struct timeval  tv;

        gettimeofday(&tv, NULL);

        uint32_t time_in_mill =
                ((uint32_t)(tv.tv_sec) * 1000) + (tv.tv_usec) / 1000;

        if (!base_time_in_mill) {
            base_time_in_mill = time_in_mill;
        }

        time_now = (time_in_mill - base_time_in_mill);

        return (time_now);
    }
#endif
    time_now = SDL_GetTicks();
    return (time_now);
}

std::string current_date (void)
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[MAXSTR];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
    return std::string(buffer);
}
