//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_LOG_H_
#define _MY_LOG_H_

#include "my_main.h"

void putf(FILE *fp, const char *s);

#define FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS()                                                                        \
  fflush(stdout);                                                                                                    \
  fflush(stderr);                                                                                                    \
  fflush(MY_STDOUT);                                                                                                 \
  fflush(MY_STDERR);

#ifdef _WIN32
//
// windows is such utter garbage that if the program crashes it does not flush
// the goddamned console! So we need this...
//
#define FLUSH_THE_CONSOLE() FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS()
#else
#define FLUSH_THE_CONSOLE() // sensible OS
#endif

#endif
