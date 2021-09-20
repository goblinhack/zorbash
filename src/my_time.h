//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#pragma once
#ifndef _MY_TIME_UTIL_H_
#define _MY_TIME_UTIL_H_

#undef ONESEC
#define ONESEC 1000

typedef int32_t ts_t;

#include <string>

bool time_have_x_hundredths_passed_since(ts_t tenths, ts_t since);
bool time_have_x_ms_passed_since(ts_t tenths, ts_t since);
bool time_have_x_secs_passed_since(ts_t tenths, ts_t since);
bool time_have_x_tenths_passed_since(ts_t tenths, ts_t since);
const char *time2str(ts_t ms, char *buf, int32_t len);
const char *timestamp(char *buf, int32_t len);
extern ts_t time_now;
ts_t time_get_elapsed_secs(ts_t val, ts_t since);
ts_t time_get_elapsed_tenths(ts_t val, ts_t since);
ts_t time_get_time_ms(void);
ts_t time_get_time_ms_cached(void);
ts_t time_update_time_milli(void);
void get_timestamp(char *buf, int32_t len);
std::string current_date(void);

#endif
