//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//
#pragma once

#ifndef _MY_MAIN_H_
#define _MY_MAIN_H_

//
// It crashes? Enable this for more info
//
#undef DEBUG_CRASH

//
// Commonly changed settings
//
#ifdef DEBUG_CRASH
#define ENABLE_ASSERT              // DIE on errors
#define ENABLE_CRASH_HANDLER       // Intercept SEGV
#define ENABLE_PTRCHECK            // Check validity of pointers too
#define ENABLE_PTRCHECK_HISTORY 2  // Per pointer history
#define ENABLE_PTRCHECK_LEAK
#define ENABLE_TRACING             // Function tracing
#undef  ENABLE_PTRCHECK_DEBUG      // Debug ptrcheck itself
#undef  ENABLE_THING_ID_LOGS       // Thing ID allocations
#endif

#undef  ENABLE_INVERTED_GFX        // For vision impaired
#undef  ENABLE_FULL_TIMESTAMPS     // Full timestamps with date in logs

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

//
// UI debugging
//
#undef  ENABLE_WID_DEBUG
#undef  DEBUG_WID_FOCUS
#ifdef  ENABLE_WID_DEBUG
#define WID_FULL_LOGNAME
#endif

#undef  ENABLE_ASCII_MOUSE
#define ENABLE_TILE_COLLISION_CHECKING

////////////////////////////////////////////////////////////////////////////
// Map
////////////////////////////////////////////////////////////////////////////

//
// Dungeon size; composed of a grid of rooms
//
#define GRID_WIDTH                  7
#define GRID_HEIGHT                 7
#define ROOM_WIDTH                  13
#define ROOM_HEIGHT                 13

//
// Dungeon has a pad of tiles around the edges
//
#define MAP_BORDER                  20
#define MAP_WIDTH                   ((GRID_WIDTH*ROOM_WIDTH) + (MAP_BORDER*2))
#define MAP_HEIGHT                  ((GRID_HEIGHT*ROOM_HEIGHT) + (MAP_BORDER*2))

////////////////////////////////////////////////////////////////////////////
// Things on map
////////////////////////////////////////////////////////////////////////////

#define MAP_SLOTS                   16
#define MAX_THINGS                  (1 << 15)
#define MAX_THINGS_MASK             (MAX_THINGS - 1)
#define MAX_THING_COLL_DELAY_TENTHS 1

////////////////////////////////////////////////////////////////////////////
// Lights
////////////////////////////////////////////////////////////////////////////

//
// Light sources
//
#define MAX_LIGHT_RAYS              (360)
#define MAX_LIGHT_PLAYER_DISTANCE   (TILES_ACROSS * 5)

////////////////////////////////////////////////////////////////////////////
// Tiles
////////////////////////////////////////////////////////////////////////////

//
// Per screen
//
extern int TILES_ACROSS;
extern int TILES_DOWN;

//
// Tile size of the player
//
#define TILE_WIDTH                  16
#define TILE_HEIGHT                 16

//
// Largest tile for collisions
//
#define MAX_TILE_WIDTH              64
#define MAX_TILE_HEIGHT             64

//
// Dimentions of the fixed text on screen
//
#define ASCII_WIDTH_MAX             120
#define ASCII_HEIGHT_MAX            ASCII_WIDTH_MAX

////////////////////////////////////////////////////////////////////////////
// UI button styles
////////////////////////////////////////////////////////////////////////////

#define WID_STYLE_OUTLINE           0
#define WID_STYLE_GREEN             1
#define WID_STYLE_RED               2
#define WID_STYLE_NORMAL            3
#define WID_STYLE_DARK              4
#define WID_STYLE_NONE              5
#define WID_STYLE_MAX               6

#define WID_POPUP_WIDTH_NORMAL      24
#define WID_POPUP_WIDTH_WIDE        36
#define WID_POPUP_WIDTH_WIDEST      48

////////////////////////////////////////////////////////////////////////////
// UI save slots
////////////////////////////////////////////////////////////////////////////

//
// How many save game slots
//
#define MAX_SAVE_SLOTS              10

////////////////////////////////////////////////////////////////////////////
// UI console
////////////////////////////////////////////////////////////////////////////

#define CONSOLE_CURSOR_COLOR        GRAY
#define CONSOLE_CURSOR_OTHER_COLOR  WHITE
#define CONSOLE_TEXT_COLOR          GRAY
#define CONSOLE_INPUT_COLOR         ORANGE
#define CONSOLE_WIDTH               120
#define CONSOLE_HEIGHT              200
#define CONSOLE_KEY1                '`'
#define CONSOLE_KEY2                '~'
#define CONSOLE_KEY3                '\\'

////////////////////////////////////////////////////////////////////////////
// UI mini console
////////////////////////////////////////////////////////////////////////////

//
// Minicon
//
#define MINICON_TEXT_COLOR          RESET_TEXT_COLOR
#define MINICON_WIDTH               (ASCII_WIDTH - SIDEBAR_WIDTH)
#define MINICON_HEIGHT              20 // scrollbar limit
#define MINICON_VIS_HEIGHT          5
#define MINICON_VIS_WIDTH           MINICON_WIDTH

////////////////////////////////////////////////////////////////////////////
// UI status bar and inventory
////////////////////////////////////////////////////////////////////////////

//
// How many graduations on e.g. the health bar
//
#define STATUSBAR_ICON_STEPS        12
#define HEALTH_ICON_STEPS           5

//
// Sidebar includes all stats e.g. health / attack / defence
//
#define SIDEBAR_WIDTH               14

#define ITEMBAR_HEIGHT              4
#define ITEMBAR_WIDTH               4
#define ITEMBAR_TOT_WIDTH           (10 * ITEMBAR_WIDTH)
#define ITEMBAR_TL_X                (ASCII_WIDTH / 2 - (ITEMBAR_TOT_WIDTH / 2))
#define ITEMBAR_TL_Y                (ASCII_HEIGHT - 4)
#define ITEMBAR_BR_X                ((ASCII_WIDTH / 2 + (ITEMBAR_TOT_WIDTH / 2)) - 1)
#define ITEMBAR_BR_Y                (ASCII_HEIGHT - 1)
#define INVENTORY_ITEM_WIDTH        2
#define INVENTORY_ITEM_HEIGHT       2
#define INVENTORY_DOWN              5
#define INVENTORY_ACROSS            6

////////////////////////////////////////////////////////////////////////////
// UI text
////////////////////////////////////////////////////////////////////////////

//
// Default text color
//
#define RESET_TEXT_COLOR            GRAY
#define RESET_TEXT_COLOR_STR        "gray"

//
// Popups
//
#define POPUP_TEXT_COLOR            RESET_TEXT_COLOR

//
// Fonts
//
//#define ENABLE_GENERATE_TTF
//#define FIXED_FONT                "data/ttf/dejavu-nerd.ttf"
//#define FIXED_FONT                "data/ttf/unscii-16.ttf"
#define FIXED_FONT                  "data/ttf/PressStart2P.ttf"
#define FONT_SIZE                   8

#define TTF_GLYPH_MIN               ' '
#define TTF_GLYPH_MAX               0xffff // SDL can only do 2b fonts
#define TTF_GLYPH_PER_ROW           60
#define TTF_CURSOR_CHAR             127

////////////////////////////////////////////////////////////////////////////
// UI mouse
////////////////////////////////////////////////////////////////////////////

//
// How much the wheel mouse moves.
//
#define ENABLE_WHEEL_SCROLL_SPEED_SCALE         1.0
#define ENABLE_WHEEL_MAX_SCROLL_SPEED_SCALE     10

#define ENABLE_JOY_SCROLL_SPEED_SCALE           1.0
#define ENABLE_JOY_MAX_SCROLL_SPEED_SCALE       1.5

////////////////////////////////////////////////////////////////////////////
// Random numbers
////////////////////////////////////////////////////////////////////////////

//
// Enhanced random number generator.
//
#include "my_pcg_basic.h"

#define myrand()                     pcg32_random()
#define mysrand(a)                   pcg32_srandom(a,a)

#define random_range(a, b)           (pcg32_boundedrand(b - a) + a)
#define random_range_inclusive(a, b) (pcg32_boundedrand(b - a + 1) + a)

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
typedef unsigned long long   uint64_t;
#endif // _UINT64_T 
#endif

//
// msys functions seem to accept either / or \ so we don't need to worry.
//
#define DSEP "/"
#define DCHAR '/'

#define DIE(args...)                                                          \
    _                                                                         \
    DYING("Died at %s:%s():%u", __FILE__, __FUNCTION__, __LINE__);            \
    CROAK(args);                                                              \
    exit(1);

extern uint8_t croaked;

#ifdef ENABLE_ASSERT
#define ASSERT(x)                                                             \
    if (!(x)) {                                                               \
        DIE("Failed assert:" #x);                                             \
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
void MINICON(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

void CON(const wchar_t *fmt, ...);
void MINICON(const wchar_t *fmt, ...);

void con(const wchar_t *fmt);
void minicon(const wchar_t *fmt);

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

void SDL_MSG_BOX(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void MSG_BOX(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void ERR(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void DBG(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

//
// main.c
//
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

//
// dice.cpp
//
int dice_roll(const std::string &s);

#include "my_ptrcheck.h"

#endif
