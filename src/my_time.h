//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_TIME_UTIL_H_
#define _MY_TIME_UTIL_H_

#undef ONESEC
#define ONESEC 1000

typedef int32_t timestamp_t;

#include <string>

bool time_have_x_hundredths_passed_since(timestamp_t tenths, timestamp_t since);
bool time_have_x_ms_passed_since(timestamp_t tenths, timestamp_t since);
bool time_have_x_secs_passed_since(timestamp_t tenths, timestamp_t since);
bool time_have_x_tenths_passed_since(timestamp_t tenths, timestamp_t since);
const char *time2str(timestamp_t ms, char *buf, int32_t len);
const char *timestamp(char *buf, int32_t len);
extern timestamp_t time_now;
timestamp_t time_get_elapsed_secs(timestamp_t val, timestamp_t since);
timestamp_t time_get_elapsed_tenths(timestamp_t val, timestamp_t since);
timestamp_t time_get_time_ms(void);
timestamp_t time_get_time_ms_cached(void);
timestamp_t time_update_time_milli(void);
void get_timestamp(char *buf, int32_t len);
std::string current_date(void);

#endif
