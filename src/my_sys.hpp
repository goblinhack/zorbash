//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_SYS_HPP_
#define _MY_SYS_HPP_

#include "my_format_str_attribute.hpp"
#include "my_source_loc.hpp"

#include <stdint.h>

#if __GNUC__ >= 8
// warns about intentional truncation like % 10s!
#pragma GCC diagnostic ignored "-Wformat-truncation"
#endif

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
#ifdef _WIN64
#ifdef __MINGW32__
#define PRI_SIZET "llu"
#else
#define PRI_SIZET PRIu64
#endif
#else
#define PRI_SIZET PRIu32
#endif
#else
#define PRI_SIZET "zu"
#endif

////////////////////////////////////////////////////////////////////////////
// Misc
////////////////////////////////////////////////////////////////////////////

//
// Simple array routines
//
#define ARRAY_SIZE(_array_) (sizeof(_array_) / sizeof(_array_[ 0 ]))

#define FOR_ALL_IN_ARRAY(iterator, _array_)                                                                          \
  __typeof__(&_array_[ 0 ]) iterator;                                                                                \
  for ((iterator) = (_array_); (iterator) < ((_array_) + ARRAY_SIZE(_array_)); (iterator)++)

//
// GCC extensions
//
#define likely(x)   __builtin_expect((x), 1)
#define unlikely(x) __builtin_expect((x), 0)

//
// Types
//
#ifndef _BITS_STDINT_INTN_H
#ifndef __int8_t_defined
#ifndef _INT8_T
#define _INT8_T
typedef signed char int8_t;
#endif //_INT8_T

#ifndef _INT16_T
#define _INT16_T
typedef short int16_t;
#endif // _INT16_T

#ifndef _INT32_T
#define _INT32_T
typedef int int32_t;
#endif // _INT32_T

#ifndef _INT64_T
#define _INT64_T
typedef long long int64_t;
#endif // _INT64_T
#endif

#ifndef _UINT8_T
#define _UINT8_T
typedef unsigned char uint8_t;
#endif //_UINT8_T

#ifndef _UINT16_T
#define _UINT16_T
typedef unsigned short uint16_t;
#endif // _UINT16_T

#ifndef _UINT32_T
#define _UINT32_T
typedef unsigned int uint32_t;
#endif // _UINT32_T

#ifndef _UINT64_T
#define _UINT64_T
typedef unsigned long int uint64_t;
#endif // _UINT64_T
#endif

//
// msys functions seem to accept either / or \ so we don't need to worry.
//
#ifdef _WIN32
#define PATHSEP      ";"
#define DIR_SEP      "\\"
#define DIR_SEP_CHAR '\\'
#else
#define PATHSEP      ":"
#define DIR_SEP      "/"
#define DIR_SEP_CHAR '/'
#endif

//
// Code tracing
// https://github.com/goblinhack/callstack
//
#include "my_callstack.hpp"

void DYING(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void CROAK(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void CROAK_CLEAN(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);

#define DIE(...)                                                                                                 \
  DYING("Died at %s:%s():%u", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM);                                       \
  CROAK(__VA_ARGS__);                                                                                            \
  exit(1);

#define DIE_CLEAN(...)                                                                                           \
  DYING("Exiting at %s:%s():%u", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM);                                    \
  CROAK_CLEAN(__VA_ARGS__);                                                                                      \
  exit(1);

#ifdef DEBUG
#define DODEBUG(x) x
#else
#define DODEBUG(x)
#endif

#ifdef ENABLE_ASSERT
#undef ASSERT
#define ASSERT(x)                                                                                                    \
  if (! (x)) {                                                                                                       \
    TRACE_AND_INDENT();                                                                                              \
    std::stringstream ss;                                                                                            \
    ss << "Assert '" << #x << "' failed at line " << __LINE__ << ", file " << __FILE__ << ", function "              \
       << __FUNCTION__ << "()";                                                                                      \
    {                                                                                                                \
      auto s = ss.str();                                                                                             \
      DIE("%s", s.c_str());                                                                                          \
    }                                                                                                                \
  }
#else
#define ASSERT(x)
#endif

// Based on
// https://stackoverflow.com/questions/2193544/how-to-print-additional-information-when-assert-fails
#ifdef ENABLE_ASSERT
#define ASSERT_EX(left, operator, right)                                                                             \
  if (! ((left) operator (right))) {                                                                                 \
    TRACE_AND_INDENT();                                                                                              \
    std::cerr << "ASSERT FAILED: " << #left << " " << #operator << " " << #right                                     \
              << " @ " << SRC_FILE_NAME << ":" << SRC_FUNC_NAME << " line " << SRC_LINE_NUM                          \
              << " " << #left << "=" << (left)                                                                       \
              << "; " << #right << "=" << (right) << std::endl;                                                      \
    ASSERT(left operator right);                                                                                     \
  }
#else
#define ASSERT_EX(left, operator, right)
#endif

#endif
