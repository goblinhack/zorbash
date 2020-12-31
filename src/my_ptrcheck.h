#pragma once

#ifndef _MY__PTRCHECK_H__
#define _MY__PTRCHECK_H__

// REMOVED #include <string>
// REMOVED #include <ctime>
#include "my_globals.h"

//
// __FUNCTION__ is not a preprocessor directive so we can't convert it into a
// string
//
#define PTRCHECK_AT \
  std::string(__FILE__), std::string(__PRETTY_FUNCTION__), __LINE__

void *myzalloc_(int size, std::string what, std::string func, std::string file, int line);
void *mymalloc_(int size, std::string what, std::string func, std::string file, int line);
void *myrealloc_(void *ptr, int size, std::string what, std::string func, std::string file, int line);
void myfree_(void *ptr, std::string func, std::string file, int line);
char *dupstr_(const char *in, std::string what, std::string func, std::string file, int line);
char *strsub_(const char *in, const char *old, const char *replace_with, std::string what, std::string file, std::string func, int line);

#define myzalloc(__size__, __what__) \
    myzalloc_((__size__), (__what__), PTRCHECK_AT)

#define mymalloc(__size__, __what__) \
    mymalloc_((__size__), (__what__), PTRCHECK_AT)

#define myrealloc(__ptr__, __size__, __what__) \
    myrealloc_((__ptr__), (__size__), (__what__), PTRCHECK_AT)

#define myfree(__ptr__)             \
    myfree_((__ptr__), PTRCHECK_AT)

#define dupstr(__ptr__, __what__)   \
    dupstr_((__ptr__), (__what__), PTRCHECK_AT)

#define strsub(a, b, c, __what__) \
    strsub_(a, b, c, (__what__), PTRCHECK_AT)

void *ptrcheck_alloc(const void *ptr, std::string what, int size, std::string file, std::string func, int line);
int ptrcheck_verify(const void *ptr, std::string &file, std::string &func, int line);
int ptrcheck_free(void *ptr, std::string file, std::string func, int line);
void ptrcheck_leak_print(void);

#define newptr(__ptr__, __what__)                                 \
{                                                                 \
    if (g_opt_debug) {_                                           \
        ptrcheck_alloc((__ptr__), (__what__), sizeof(*(__ptr__)), \
                       PTRCHECK_AT);                              \
    }                                                             \
}

#define oldptr(__ptr__)                                           \
{                                                                 \
    if (g_opt_debug) {_                                           \
        ptrcheck_free((__ptr__), PTRCHECK_AT);                    \
    }                                                             \
}

#define verify(__ptr__)                                           \
{                                                                 \
    if (g_opt_debug) {_                                           \
        static std::string a = std::string(__FILE__);             \
        static std::string b = std::string(__PRETTY_FUNCTION__);  \
        ptrcheck_verify((__ptr__), a, b, __LINE__);               \
    }                                                             \
}

#endif // __PTRCHECK_H__
