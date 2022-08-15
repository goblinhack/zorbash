//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_MAIN_HPP_
#define _MY_MAIN_HPP_

#include "my_globals.hpp"

void BOTCON(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
void BOTCON(const wchar_t *fmt, ...);
void CON(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
void CON(const wchar_t *fmt, ...);
void GAME_UI_MSG_BOX(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
void LOG(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
void LOG_MISSING(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
void TOPCON(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
void TOPCON(const wchar_t *fmt, ...);
void SDL_MSG_BOX(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
void WARN(const char *fmt, ...) __attribute__((format(printf, 1, 2)));

void botcon(const wchar_t *fmt);
void con(const wchar_t *fmt);
void ctrlc_handler(int sig);
void die(void);
void log_catchup_missing_indent_levels(void);
void topcon(const wchar_t *fmt);
void myerr(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
void quit(void);
void restart(void);
void segv_handler(int sig);

#endif
