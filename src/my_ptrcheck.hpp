#pragma once

#ifndef _MY__PTRCHECK_HPP__
#define _MY__PTRCHECK_HPP__

//
// __FUNCTION__ is not a preprocessor directive so we can't convert it into a
// string
//
#define PTRCHECK_AT SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM

void *myzalloc_(int size, const char *what, const char *func, const char *file, int line);
void *mymalloc_(int size, const char *what, const char *func, const char *file, int line);
void *myrealloc_(void *ptr, int size, const char *what, const char *func, const char *file, int line);
void  myfree_(void *ptr, const char *func, const char *file, int line);
char *dupstr_(const char *in, const char *what, const char *func, const char *file, int line);
char *strsub_(const char *in, const char *old, const char *replace_with, const char *what, const char *file,
              const char *func, int line);

#define myzalloc(__size__, __what__) myzalloc_((__size__), (__what__), PTRCHECK_AT)

#define mymalloc(__size__, __what__) mymalloc_((__size__), (__what__), PTRCHECK_AT)

#define myrealloc(__ptr__, __size__, __what__) myrealloc_((__ptr__), (__size__), (__what__), PTRCHECK_AT)

#define myfree(__ptr__) myfree_((__ptr__), PTRCHECK_AT)

#define dupstr(__ptr__, __what__) dupstr_((__ptr__), (__what__), PTRCHECK_AT)

#define strsub(a, b, c, __what__) strsub_(a, b, c, (__what__), PTRCHECK_AT)

void *ptrcheck_alloc(int mtype, const void *ptr, const char *what, int size, const char *file, const char *func,
                     int line);
int   ptrcheck_verify(int mtype, const void *ptr, const char *file, const char *func, int line);
int   ptrcheck_free(int mtype, void *ptr, const char *file, const char *func, int line);
void  ptrcheck_leak_print(int mtype);
void  ptrcheck_leak_print(void);

#define newptr(__mtype__, __ptr__, __what__)                                                                         \
  {                                                                                                                  \
    if (DEBUG2) {                                                                                                    \
      TRACE_NO_INDENT();                                                                                             \
      ptrcheck_alloc(__mtype__, __ptr__, __what__, sizeof(*(__ptr__)), PTRCHECK_AT);                                 \
    }                                                                                                                \
  }

#define oldptr(__mtype__, __ptr__)                                                                                   \
  {                                                                                                                  \
    if (DEBUG2) {                                                                                                    \
      TRACE_NO_INDENT();                                                                                             \
      ptrcheck_free(__mtype__, __ptr__, PTRCHECK_AT);                                                                \
    }                                                                                                                \
  }

#define verify(__mtype__, __ptr__)                                                                                   \
  {                                                                                                                  \
    if (DEBUG2) {                                                                                                    \
      TRACE_NO_INDENT();                                                                                             \
      ptrcheck_verify(__mtype__, __ptr__, SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM);                               \
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

#endif // _MY__PTRCHECK_HPP__
