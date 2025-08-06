//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_MAIN_HPP_
#define _MY_MAIN_HPP_

#include "my_format_str_attribute.hpp"
#include <string>

void BOTCON(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void BOTCON(const wchar_t *fmt, ...);
void CON(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void CON(const wchar_t *fmt, ...);
void GAME_UI_MSG_BOX(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void LOG(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void LOG_MISSING(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void TOPCON(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void TOPCON(const wchar_t *fmt, ...);
void SDL_MSG_BOX(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void WARN(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);

void botcon(const wchar_t *fmt);
void con(const wchar_t *fmt);
void ctrlc_handler(int sig);
void die(void);
void log_catchup_missing_indent_levels(void);
void topcon(const wchar_t *fmt);
void myerr(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void py_myerr(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void quit(void);
void restart(void);
void common_error_handler(const std::string &error);
void error_handler(const std::string &error);
void segv_handler(int sig);
void flush_the_console(void);

#endif
