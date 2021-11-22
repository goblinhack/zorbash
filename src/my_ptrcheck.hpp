#pragma once

#ifndef _MY__PTRCHECK_HPP__
#define _MY__PTRCHECK_HPP__

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include <ctime>
#include <string>

//
// __FUNCTION__ is not a preprocessor directive so we can't convert it into a
// string
//
#define PTRCHECK_AT std::string(__FILE__), std::string(__PRETTY_FUNCTION__), __LINE__

void *myzalloc_(int size, std::string what, std::string func, std::string file, int line);
void *mymalloc_(int size, std::string what, std::string func, std::string file, int line);
void *myrealloc_(void *ptr, int size, std::string what, std::string func, std::string file, int line);
void  myfree_(void *ptr, std::string func, std::string file, int line);
char *dupstr_(const char *in, std::string what, std::string func, std::string file, int line);
char *strsub_(const char *in, const char *old, const char *replace_with, std::string what, std::string file,
              std::string func, int line);

#define myzalloc(__size__, __what__) myzalloc_((__size__), (__what__), PTRCHECK_AT)

#define mymalloc(__size__, __what__) mymalloc_((__size__), (__what__), PTRCHECK_AT)

#define myrealloc(__ptr__, __size__, __what__) myrealloc_((__ptr__), (__size__), (__what__), PTRCHECK_AT)

#define myfree(__ptr__) myfree_((__ptr__), PTRCHECK_AT)

#define dupstr(__ptr__, __what__) dupstr_((__ptr__), (__what__), PTRCHECK_AT)

#define strsub(a, b, c, __what__) strsub_(a, b, c, (__what__), PTRCHECK_AT)

void *ptrcheck_alloc(int mtype, const void *ptr, std::string what, int size, std::string file, std::string func,
                     int line);
int   ptrcheck_verify(int mtype, const void *ptr, std::string &file, std::string &func, int line);
int   ptrcheck_free(int mtype, void *ptr, std::string file, std::string func, int line);
void  ptrcheck_leak_print(int mtype);
void  ptrcheck_leak_print(void);

#define newptr(__mtype__, __ptr__, __what__)                                                                         \
  {                                                                                                                  \
    if (DEBUG3) {                                                                                                    \
      TRACE_AND_INDENT();                                                                                            \
      ptrcheck_alloc(__mtype__, (__ptr__), (__what__), sizeof(*(__ptr__)), PTRCHECK_AT);                             \
    }                                                                                                                \
  }

#define oldptr(__mtype__, __ptr__)                                                                                   \
  {                                                                                                                  \
    if (DEBUG3) {                                                                                                    \
      TRACE_AND_INDENT();                                                                                            \
      ptrcheck_free(__mtype__, (__ptr__), PTRCHECK_AT);                                                              \
    }                                                                                                                \
  }

#define verify(__mtype__, __ptr__)                                                                                   \
  {                                                                                                                  \
    if (DEBUG3) {                                                                                                    \
      TRACE_AND_INDENT();                                                                                            \
      static std::string a = std::string(__FILE__);                                                                  \
      static std::string b = std::string(__PRETTY_FUNCTION__);                                                       \
      ptrcheck_verify(__mtype__, (__ptr__), a, b, __LINE__);                                                         \
    }                                                                                                                \
  }

enum {
  MTYPE_WID,
  MTYPE_THING,
  MTYPE_INFOP,
  MTYPE_AIP,
  MTYPE_ROOM,
  MTYPE_ITEMP,
  MTYPE_LIGHT,
  MTYPE_LEVEL,
  MTYPE_TP,
  MTYPE_TEX,
  MTYPE_TILE,
  MTYPE_STRING,
  MTYPE_MISC,
  MTYPE_SDL,
  MTYPE_MAX,
};

#endif // __PTRCHECK_HPP__
