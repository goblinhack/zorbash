//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_TERM_HPP_
#define _MY_TERM_HPP_

typedef enum {
  TERM_COLOR_BLACK,
  TERM_COLOR_RED,
  TERM_COLOR_GREEN,
  TERM_COLOR_YELLOW,
  TERM_COLOR_BLUE,
  TERM_COLOR_PINK,
  TERM_COLOR_CYAN,
  TERM_COLOR_WHITE,
  TERM_COLOR_RESET,
  TERM_COLOR_MAX,
} term_color;

extern void term_log(const wchar_t *buf);
extern void term_log(const char *buf);

#endif
