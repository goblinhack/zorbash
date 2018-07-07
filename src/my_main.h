/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_MAIN_H_
#define _MY_MAIN_H_

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include <memory>
#include <iostream>     // std::cout
#include <algorithm>    // std::max
#include <iterator>
#include <map>
#include <vector>

/*
#include <mcheck.h>
 */

/*
 * Enhanced random number generator.
 */
#include "my_pcg_basic.h"
#include "my_config.h"
#define myrand() pcg32_random()
#define mysrand(a) pcg32_srandom(a,a)
//#define myrand() rand()
//#define mysrand(a) srand(a)

extern size_t
strlcpy_(char * dst, const char * src, size_t size);

extern size_t
strlcat_(char * dst, const char * src, size_t size);

/*
 * Max long string size
 */
#define MAXSTR                          4096

/*
 * Misc
 */
#undef ONESEC
#define ONESEC                          1000

#ifndef true
#define true                            1
#endif

#ifndef false
#define false                           0
#endif

#define swapval(a,b) {                              \
            __typeof__ (a) c;                       \
            c = a;                                  \
            a = b;                                  \
            b = c;                                  \
        }

/*
 * Simple array routines
 */
#define ARRAY_SIZE(_array_)             (sizeof(_array_)/sizeof(_array_[0]))

#define FOR_ALL_IN_ARRAY(iterator, _array_)                                 \
    __typeof__(&_array_[0]) iterator;                                       \
    for ((iterator) = (_array_);                                            \
         (iterator) < ((_array_) + ARRAY_SIZE(_array_));                    \
         (iterator)++)

#define FOR_NEXT_IN_ARRAY(iterator, _array_)                                \
    for ((iterator)++;                                                      \
         (iterator) < ((_array_) + ARRAY_SIZE(_array_));                    \
         (iterator)++)

/*
 * GCC extension for offset
 */
#ifdef __GNUC__
#if defined(__GNUC__) && __GNUC__ > 3
#define STRUCT_OFFSET(STRUCT, MEMBER) __builtin_offsetof(STRUCT, MEMBER)
#else
#define STRUCT_OFFSET(STRUCT, MEMBER) \
                     ((size_t) ( (char *)&((st *)0)->m - (char *)0 ))
#endif
#else
#define STRUCT_OFFSET(STRUCT, MEMBER) \
                     ((size_t) ( (char *)&((st *)0)->m - (char *)0 ))
#endif

#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

/*
 * Types
 */
#ifndef _BITS_STDINT_INTN_H
#ifndef __int8_t_defined
#ifndef _INT8_T
#define _INT8_T
typedef signed char          int8_t;
#endif /*_INT8_T */

#ifndef _INT16_T
#define _INT16_T
typedef short                int16_t;
#endif /* _INT16_T */

#ifndef _INT32_T
#define _INT32_T
typedef int                  int32_t;
#endif /* _INT32_T */

#ifndef _INT64_T
#define _INT64_T
typedef long long            int64_t;
#endif /* _INT64_T */
#endif

#ifndef _UINT8_T
#define _UINT8_T
typedef unsigned char        uint8_t;
#endif /*_UINT8_T */

#ifndef _UINT16_T
#define _UINT16_T
typedef unsigned short       uint16_t;
#endif /* _UINT16_T */

#ifndef _UINT32_T
#define _UINT32_T
typedef unsigned int         uint32_t;
#endif /* _UINT32_T */

#ifndef _UINT64_T
#define _UINT64_T
typedef unsigned long long   uint64_t;
#endif /* _UINT64_T */
#endif

/*
 * msys functions seem to accept either / or \ so we don't need to worry.
 */
#define DSEP "/"
#define DCHAR '/'

/*
 * shared_ptr wrappers
 */
typedef std::shared_ptr< std::vector< std::string > > shared_vector_string;
typedef std::shared_ptr< std::vector< std::wstring > > shared_vector_wstring;
typedef std::shared_ptr< class tex > texp;
typedef std::shared_ptr< class font > fontp;
typedef std::shared_ptr< class music > musicp;
typedef std::shared_ptr< class wid_tiles > wid_tilesp;
typedef std::shared_ptr< class sound > soundp;
typedef std::shared_ptr< class tile > tilep;

typedef std::shared_ptr< class file_node > file_nodep;
typedef std::map< std::string, std::shared_ptr< class file_node > > file_nodes;

typedef std::shared_ptr< class thing_tile > thing_tilep;
typedef std::map< unsigned int, std::shared_ptr< class thing_tile > > thing_tiles;

typedef std::shared_ptr< class thing_template > tpp;
typedef std::map< std::string, tpp > thing_templates;
typedef std::map< unsigned int, tpp > thing_templates_create_order;

typedef std::shared_ptr< class thing > thingp;
typedef std::map< std::string, thingp > things;

typedef std::shared_ptr< class wid > widp;

#include "my_color.h"

/*
 * Globals:
 */
typedef struct wid_console *wid_consolep;
typedef struct game_ *gamep;
typedef struct action_init_fn_ *init_fnp;
typedef struct tokens_t_ *tokenp;
typedef struct tokens_t_ *tokensp;

extern fontp fixed_font;
extern wid_consolep wid_console;
extern gamep config;

typedef uint8_t (*tp_is_callback)(tpp);

#define DIE(args...)                                                          \
    DYING("Died at %s:%s():%u", __FILE__, __FUNCTION__, __LINE__);            \
    CROAK(args);                                                              \
    exit(1);

extern uint8_t croaked;

#ifdef ENABLE_ASSERT
#define ASSERT(x)                                                             \
    if (!(x)) {                                                               \
        DIE("Failed assert");                                                 \
    }
#else
#define ASSERT(x)
#endif

void CROAK(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void DYING(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void LOG(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void LOGS(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void WARN(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void CON(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void TIP(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void TIP2(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

void CON(const wchar_t *fmt, ...);
void TIP(const wchar_t *fmt, ...);
void TIP2(const wchar_t *fmt, ...);

void con (const wchar_t *fmt);
void tip2 (const wchar_t *fmt);
void tip (const wchar_t *fmt);

#include "my_callstack.h"

enum {
    INFO,
    WARNING,
    CRITICAL,
};

/*
 * Bloody windows uses MSG hence MESG
 */
void SDL_MSG_BOX(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void MSG_BOX(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void ERR(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void DBG(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

#ifdef ENABLE_WID_DEBUG
void WID_LOG(widp, const char *fmt, ...) \
                     __attribute__ ((format (printf, 2, 3)));

void WID_DBG(widp, const char *fmt, ...) \
                     __attribute__ ((format (printf, 2, 3)));
#else
#define WID_DBG(...)
#define WID_LOG(...)
#endif

extern uint8_t debug_enabled;
uint8_t debug_enable(tokensp, void *context);
uint8_t fps_enable(tokensp, void *context);

/*
 * util.c
 */
void *myzalloc_(uint32_t size, const char *what, const char *func,
                const char *file, const uint32_t line);

void *mymalloc_(uint32_t size, const char *what, const char *func,
                const char *file, const uint32_t line);

void *myrealloc_(void *ptr, uint32_t size, const char *what, const char *func,
                 const char *file, const uint32_t line);

void myfree_(void *ptr, const char *func, const char *file,
             const uint32_t line);

char *dupstr_(const char *in, const char *what, const char *func,
              const char *file, const uint32_t line);

#include "my_ptrcheck.h"
#include "my_math_util.h"

/*
 * main.c
 */
extern FILE *LOG_STDOUT;
extern FILE *LOG_STDERR;

#define MY_STDOUT (LOG_STDOUT ? LOG_STDOUT : stdout)
#define MY_STDERR (LOG_STDERR ? LOG_STDERR : stderr)

extern char *EXEC_FULL_PATH_AND_NAME;
extern char *EXEC_DIR;
extern char *DATA_PATH;
extern char *PYTHON_PATH;
extern char *GFX_PATH;
extern char *TTF_PATH;
extern uint8_t quitting;

void quit(void);
void restart(void);
void die(void);

/*
 * config.c
 */
void config_fini(void);
uint8_t config_init(void);
uint8_t config_save(void);
uint8_t config_load(void);

/*
 * main.c
 */
extern int debug;

#include "my_thing_template.h"
#include "my_thing.h"
#include "my_game.h"

#endif
