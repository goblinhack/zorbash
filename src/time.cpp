//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_string.h"
#include "my_time.h"
#include "my_sdl.h"

ts_t        time_now;
ts_t        base_time_in_mill;
static char buf_[ MAXSHORTSTR ];

ts_t time_get_time_ms(void) {
  time_update_time_milli();

  return (time_now);
}

ts_t time_get_time_ms_cached(void) { return (time_now); }

const char *time2str(ts_t ms, char *buf, int len) {
  int log_msec = ms;
  int log_secs = log_msec / ONESEC;
  int log_mins = log_secs / 60;
  int log_hrs  = log_mins / 60;

  log_msec = log_msec % ONESEC;
  log_secs = log_secs % 60;
  log_mins = log_mins % 60;

  if (! buf) {
    buf = buf_;
    len = sizeof(buf_);
  }

  buf[ 0 ] = '\0';
  snprintf(buf, len, "%02d:%02d:%02d.%03d: ", log_hrs, log_mins, log_secs, log_msec);

  if (buf) {
    return (buf);
  }

  return (buf_);
}

const char *timestamp(char *buf, int len) {
  int log_msec = time_get_time_ms();
  int log_secs = log_msec / ONESEC;
  int log_mins = log_secs / 60;
  int log_hrs  = log_mins / 60;

  log_msec = log_msec % ONESEC;
  log_secs = log_secs % 60;
  log_mins = log_mins % 60;

  if (! buf) {
    buf = buf_;
    len = sizeof(buf_);
  }

  buf[ 0 ] = '\0';
  snprintf(buf, len, "%02d:%02d:%02d.%03d: ", log_hrs, log_mins, log_secs, log_msec);

  if (buf) {
    return (buf);
  }

  return (buf_);
}

bool time_have_x_hundredths_passed_since(ts_t val, ts_t since) {
  time_get_time_ms();

  //
  // Cater for negative future times.
  //
  ts_t delay = time_now - since;

  return ((ts_t) (delay / 10) > (ts_t) val);
}

bool time_have_x_ms_passed_since(ts_t val, ts_t since) {
  time_get_time_ms();

  //
  // Cater for negative future times.
  //
  ts_t delay = time_now - since;

  return ((ts_t) (delay) >= (ts_t) val);
}

bool time_have_x_tenths_passed_since(ts_t val, ts_t since) {
  time_get_time_ms();

  //
  // Cater for negative future times.
  //
  ts_t delay = time_now - since;

  return ((ts_t) (delay / 100) >= (ts_t) val);
}

bool time_have_x_secs_passed_since(ts_t val, ts_t since) {
  time_get_time_ms();

  //
  // Cater for negative future times.
  //
  ts_t delay = time_now - since;

  return ((ts_t) (delay / ONESEC) >= (ts_t) val);
}

ts_t time_get_elapsed_secs(ts_t val, ts_t since) {
  time_get_time_ms();

  ts_t delay = val - since;

  return ((ts_t) (delay / ONESEC));
}

ts_t time_get_elapsed_tenths(ts_t val, ts_t since) {
  time_get_time_ms();

  ts_t delay = val - since;

  return ((ts_t) (delay / (ONESEC / 10)));
}

void get_timestamp(char *buf, int32_t len) {
#ifdef ENABLE_LOG_TIMESTAMPS
  char tmp[ MAXSTR ];
  string_timestamp(tmp, len);
  snprintf(buf, len, "%s %s", timestamp().c_str(), tmp);
#else
  timestamp(buf, len);
#endif
}

ts_t time_update_time_milli(void) {
#ifdef NOT_NEEDED
  //
  // Some macos specific way of getting the time that looks like it could
  // be useful, so leaving around
  //
  uint64_t    abs_time  = mach_absolute_time();
  Nanoseconds nano_time = AbsoluteToNanoseconds(*(AbsoluteTime *) &abs_time);
  uint64_t    nano_val  = *(uint64_t *) &nano_time;
  ;
  uint32_t time_in_mill = nano_val / 1000000LLU;

  if (! base_time_in_mill) {
    base_time_in_mill = time_in_mill;
  }

  time_now = (time_in_mill - base_time_in_mill);

  return (time_now);
#endif
#ifdef NOT_NEEDED
  extern uint8_t sdl_main_loop_running;
  extern uint8_t sdl_init_video;

  if (unlikely(! sdl_main_loop_running || ! sdl_init_video)) {
    struct timeval tv;

    gettimeofday(&tv, NULL);

    uint32_t time_in_mill = ((uint32_t) (tv.tv_sec) * 1000) + (tv.tv_usec) / 1000;

    if (! base_time_in_mill) {
      base_time_in_mill = time_in_mill;
    }

    time_now = (time_in_mill - base_time_in_mill);

    return (time_now);
  }
#endif
  time_now = SDL_GetTicks();
  return (time_now);
}

std::string current_date(void) {
  struct tm *timeinfo;
  time_t     rawtime;
  char       buffer[ MAXSTR ];

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  // Code    Example Description
  //  %a  Sun Weekday as locale’s abbreviated name.
  //  %A  Sunday  Weekday as locale’s full name.
  //  %w  0   Weekday as a decimal number, where 0 is Sunday and 6 is Saturday.
  //  %d  08  Day of the month as a zero-padded decimal number.
  //  %-d 8   Day of the month as a decimal number. (Platform specific)
  //  %b  Sep Month as locale’s abbreviated name.
  //  %B  September   Month as locale’s full name.
  //  %m  09  Month as a zero-padded decimal number.
  //  %-m 9   Month as a decimal number. (Platform specific)
  //  %y  13  Year without century as a zero-padded decimal number.
  //  %Y  2013    Year with century as a decimal number.
  //  %H  07  Hour (24-hour clock) as a zero-padded decimal number.
  //  %-H 7   Hour (24-hour clock) as a decimal number. (Platform specific)
  //  %I  07  Hour (12-hour clock) as a zero-padded decimal number.
  //  %-I 7   Hour (12-hour clock) as a decimal number. (Platform specific)
  //  %p  AM  Locale’s equivalent of either AM or PM.
  //  %M  06  Minute as a zero-padded decimal number.
  //  %-M 6   Minute as a decimal number. (Platform specific)
  //  %S  05  Second as a zero-padded decimal number.
  //  %-S 5   Second as a decimal number. (Platform specific)
  //  %f  000000  Microsecond as a decimal number, zero-padded on the left.
  //  %z  +0000   UTC offset in the form ±HHMM[SS[.ffffff]] (empty string if the object is naive).
  //  %Z  UTC Time zone name (empty string if the object is naive).
  //  %j  251 Day of the year as a zero-padded decimal number.
  //  %-j 251 Day of the year as a decimal number. (Platform specific)
  //  %U  36  Week number of the year (Sunday as the first day of the week)
  //          as a zero padded decimal number. All days in a new year preceding the first Sunday
  //          are considered to be in week 0.
  //  %W  35  Week number of the year (Monday as the first day of the week)
  //          as a decimal number. All days in a new year preceding the first Monday are considered to be in week 0.
  //  %c  Sun Sep 8 07:06:05 2013 Locale’s appropriate date and time representation.
  //  %x  09/08/13    Locale’s appropriate date representation.
  //  %X  07:06:05    Locale’s appropriate time representation.
  //  %%  %   A literal '%' character.
  strftime(buffer, sizeof(buffer), "%c", timeinfo);
  return std::string(buffer);
}
