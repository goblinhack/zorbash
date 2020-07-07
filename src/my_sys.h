//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once
#ifndef _MY_SYS_H_
#define _MY_SYS_H_

//
// Settings to override compiler errors
//
// `error' to treat this diagnostic as an error,
// `warning' to treat it like a warning (even if -Werror is in effect)
// `ignored' if the diagnostic is to be ignored
//
// #pragma GCC diagnostic warning "-Wformat"
// #pragma GCC diagnostic error "-Wformat"
// #pragma GCC diagnostic ignored "-Wformat"
//
#ifdef __clang__
/*code specific to clang compiler*/
#elif __GNUC__
/*code for GNU C compiler */
#elif _MSC_VER
/*usually has the version number in _MSC_VER*/
/*code specific to MSVC compiler*/
#elif __BORLANDC__
/*code specific to borland compilers*/
#elif __MINGW32__
/*code specific to mingw compilers*/
#endif

// %d--> for int
//
// %u--> for unsigned int
//
// %ld--> for long int
//
// %lu--> for unsigned long int
//
// %lld--> for long long int
//
// %llu--> for unsigned long long int
//
// "%zu" workaround for moronic windows
// https://stackoverflow.com/questions/44382862/how-to-printf-a-size-t-without-warning-in-mingw-w64-gcc-7-1
//
#ifdef _WIN32
#  ifdef _WIN64
#    ifdef __MINGW32__
#      define PRI_SIZET "llu"
#    else
#      define PRI_SIZET PRIu64
#    endif
#  else
#    define PRI_SIZET PRIu32
#  endif
#else
#  define PRI_SIZET "zu"
#endif

////////////////////////////////////////////////////////////////////////////
// Random numbers
////////////////////////////////////////////////////////////////////////////

//
// Enhanced random number generator.
//
#include "my_pcg_basic.h"

#define myrand()                     pcg32_random()
#define mysrand(a)                   pcg32_srandom(a, a)

#define random_range(a, b)           (pcg32_boundedrand((b) - (a)) + (a))
#define random_range_inclusive(a, b) (pcg32_boundedrand((b) - (a) + 1) + (a))

////////////////////////////////////////////////////////////////////////////
// Misc
////////////////////////////////////////////////////////////////////////////

//
// Simple array routines
//
#define ARRAY_SIZE(_array_) (sizeof(_array_)/sizeof(_array_[0]))

#define FOR_ALL_IN_ARRAY(iterator, _array_)                                 \
    __typeof__(&_array_[0]) iterator;                                       \
    for ((iterator) = (_array_);                                            \
         (iterator) < ((_array_) + ARRAY_SIZE(_array_));                    \
         (iterator)++)

//
// GCC extensions
//
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

//
// Types
//
#ifndef _BITS_STDINT_INTN_H
#ifndef __int8_t_defined
#ifndef _INT8_T
#define _INT8_T
typedef signed char          int8_t;
#endif //_INT8_T

#ifndef _INT16_T
#define _INT16_T
typedef short                int16_t;
#endif // _INT16_T

#ifndef _INT32_T
#define _INT32_T
typedef int                  int32_t;
#endif // _INT32_T

#ifndef _INT64_T
#define _INT64_T
typedef long long            int64_t;
#endif // _INT64_T
#endif

#ifndef _UINT8_T
#define _UINT8_T
typedef unsigned char        uint8_t;
#endif //_UINT8_T

#ifndef _UINT16_T
#define _UINT16_T
typedef unsigned short       uint16_t;
#endif // _UINT16_T

#ifndef _UINT32_T
#define _UINT32_T
typedef unsigned int         uint32_t;
#endif // _UINT32_T

#ifndef _UINT64_T
#define _UINT64_T
typedef unsigned long int   uint64_t;
#endif // _UINT64_T
#endif

//
// msys functions seem to accept either / or \ so we don't need to worry.
//
#ifdef _WIN32
#define PATHSEP ";"
#define DIR_SEP "\\"
#define DIR_SEP_CHAR '\\'
#else
#define PATHSEP ":"
#define DIR_SEP "/"
#define DIR_SEP_CHAR '/'
#endif

void CROAK(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void DYING(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
#define DIE(args...)                                                          \
    _                                                                         \
    DYING("Died at %s:%s():%u", __FILE__, __FUNCTION__, __LINE__);            \
    CROAK(args);                                                              \
    exit(1);

#ifdef ENABLE_ASSERT
#define ASSERT(x)                                                             \
    if (!(x)) {                                                               \
        DIE("Failed assert:" #x);                                             \
    }
#else
#define ASSERT(x)
#endif

//
// Serious errors
//
void WARN(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
#define ERR _ myerr

//
// Also serious. UI msg box popups, in game and pre game with SDL
//
void SDL_MSG_BOX(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void GAME_UI_MSG_BOX(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

//
// Add _ so we get a traceback element.
//
void myerr(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
#define ERR _ myerr

//
// Normal logging
//
void LOG(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

//
// Consoles
//
void BOTCON(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void BOTCON(const wchar_t *fmt, ...);
void CON(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void CON(const wchar_t *fmt, ...);
void MINICON(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void MINICON(const wchar_t *fmt, ...);
void con(const wchar_t *fmt);
void minicon(const wchar_t *fmt);
void botcon(const wchar_t *fmt);

//
// Enabled only when debug_mode is on
//
void DBG(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

//
// main.c
//
#define MY_STDOUT (g_log_stdout ? g_log_stdout : stdout)
#define MY_STDERR (g_log_stderr ? g_log_stderr : stderr)

extern void quit(void);
extern void restart(void);
extern void die(void);

//
// Memory debugging
//
#include "my_ptrcheck.h"

//
// Code tracing
// https://github.com/goblinhack/callstack
//
#include "my_callstack.h"

//
// Array bounds checks
// https://github.com/goblinhack/c-plus-plus-array-bounds-checker
//
#include "my_array_bounds_check.h"
#include "my_vector_bounds_check.h"

//
// Serialization support
// https://github.com/goblinhack/simple-c-plus-plus-serializer
//
#include "c_plus_plus_serializer.h"

#include "my_globals.h"

#endif
