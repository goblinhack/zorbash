//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_TIME_UTIL_HPP_
#define _MY_TIME_UTIL_HPP_

#undef ONESEC
#define ONESEC 1000

#define MY_TIMESTAMP_SIZE 20

using ts_t = int;

#include <string> // do not remove

bool time_have_x_hundredths_passed_since(ts_t tenths, ts_t since);
bool time_have_x_ms_passed_since(ts_t tenths, ts_t since);
bool time_have_x_secs_passed_since(ts_t tenths, ts_t since);
bool time_have_x_tenths_passed_since(ts_t tenths, ts_t since);

const char *time2str(ts_t ms, char *buf, int len);
const char *timestamp(char *buf, int len);

ts_t time_get_elapsed_secs(ts_t val, ts_t since);
ts_t time_get_elapsed_tenths(ts_t val, ts_t since);

ts_t time_game_ms(void);
ts_t time_game_ms_cached(void);

ts_t time_ms(void);
ts_t time_ms_cached(void);

void get_timestamp(char *buf, int len);

std::string  current_date(void);
std::string &string_timestamp(void);

extern ts_t time_now;
extern ts_t time_game;
extern ts_t time_game_delta;

#endif
