//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once
#ifndef _MY_MAIN_H_
#define _MY_MAIN_H_

#undef  ENABLE_DEBUG_CRASH         // Enable this for lots of sanity checks
#define ENABLE_CRASH_HANDLER       // Intercept SEGV
#define ENABLE_TRACING             // Function tracing

#undef  ENABLE_DEBUG_AI            // Monster AI decisions
#undef  ENABLE_DEBUG_AI_ASTAR      // Astar AI path costs
#undef  ENABLE_DEBUG_AI_GOALS      // AI goal selection
#undef  ENABLE_DEBUG_AI_WANDER     // AI wander path selection
#undef  ENABLE_DEBUG_GFX_GL_BLEND  // Use to debug specific blends
#undef  ENABLE_DEBUG_UI_FOCUS      // Which windows we are over
#undef  ENABLE_GFX_INVERSE_COLORS  // For vision impaired
#undef  ENABLE_GFX_TILE_COLLISIONS // Not needed for roguelike
#undef  ENABLE_LOG_TIMESTAMPS      // Full timestamps with date in logs
#undef  ENABLE_MAP_DEBUG           // Visible map, no lighting
#undef  ENABLE_UI_ASCII_MOUSE      // Show an in game mouse, not system mouse
#undef  ENABLE_UI_DEBUG            // User interface logs
#undef  ENABLE_UI_DEBUG_EXTRA      // User interface logs with inheritance

#ifdef ENABLE_DEBUG_CRASH
#define ENABLE_ASSERT              // DIE on errors, like array bound check
#define ENABLE_PTRCHECK            // Check validity of pointers too
#define ENABLE_PTRCHECK_HISTORY 2  // Per pointer history
#define ENABLE_PTRCHECK_LEAK
#define ENABLE_THING_ID_LOGS       // Thing ID allocations
#undef  ENABLE_PTRCHECK_DEBUG      // Debug ptrcheck itself
#endif

#define GRID_HEIGHT                5
#define GRID_WIDTH                 5  // Rooms across and down
#define LEVELS_ACROSS              MAP_WIDTH // World size
#define LEVELS_DEEP                32
#define LEVELS_DOWN                MAP_HEIGHT
#define LIGHT_RAYS                 180
#define MAP_BORDER                 10 // Room border padding
#define MAP_HEIGHT                 ((GRID_HEIGHT*ROOM_HEIGHT) + (MAP_BORDER*2))
#define MAP_ROCK_BORDER            1  // Map rock border
#define MAP_SLOTS                  32
#define MAP_WIDTH                  ((GRID_WIDTH*ROOM_WIDTH) + (MAP_BORDER*2))
#define PLAYER_MOVE_SPEED_MS       100
#define ROOM_HEIGHT                13
#define ROOM_WIDTH                 13
#define TILE_HEIGHT                16
#define TILE_HEIGHT_MAX            64
#define TILE_WIDTH                 16 // Tile size of the player
#define TILE_WIDTH_MAX             64 // Largest tile for collisions
#define TTF_CURSOR_CHAR            127
#define TTF_GLYPH_MAX              134
#define TTF_GLYPH_MIN              ' '
#define TTF_GLYPH_PER_ROW          60
#define UI_ACTIONBAR_BR_Y          (ASCII_HEIGHT - 1)
#define UI_ACTIONBAR_ITEM_HEIGHT   3
#define UI_ACTIONBAR_ITEM_WIDTH    3
#define UI_ACTIONBAR_MAX_ITEMS     20
#define UI_ACTIONBAR_TL_Y          (ASCII_HEIGHT - 4)
#define UI_CONSOLE_HEIGHT          200
#define UI_CONSOLE_INPUT_COLOR     ORANGE
#define UI_CONSOLE_KEY1            '`'
#define UI_CONSOLE_KEY2            '~'
#define UI_CONSOLE_KEY3            '\\'
#define UI_CONSOLE_TEXT_COLOR      GRAY
#define UI_CONSOLE_WIDTH           ASCII_WIDTH
#define UI_CURSOR_COLOR            GRAY
#define UI_CURSOR_OTHER_COLOR      WHITE
#define UI_FONT_HEIGHT             24
#define UI_FONT_NAME               "data/ttf/6x6.tga"
#define UI_FONT_PIXEL_SIZE         6
#define UI_FONT_WIDTH              20
#define UI_HEALTH_BAR_STEPS        12 // How many graduations on health bar
#define UI_HEALTH_ICON_STEPS       5
#define UI_MINICON_HEIGHT          20 // Scrollbar limit
#define UI_MINICON_TEXT_COLOR      UI_TEXT_COLOR
#define UI_MINICON_VIS_HEIGHT      5
#define UI_MINICON_VIS_WIDTH       UI_MINICON_WIDTH
#define UI_MINICON_WIDTH           (ASCII_WIDTH - UI_SIDEBAR_WIDTH)
#define UI_POLL_EVENTS_MS          10
#define UI_POPUP_TEXT_COLOR        UI_TEXT_COLOR
#define UI_SCROLL_JOY_SCALE        1.0
#define UI_SCROLL_JOY_SCALE_MAX    1.5
#define UI_SCROLL_WHEEL_SCALE      1.0 // How much the wheel mouse moves.
#define UI_SCROLL_WHEEL_SCALE_MAX  10
#define UI_SIDEBAR_WIDTH           12
#define UI_TEXT_COLOR              GRAY // Default text color
#define UI_TEXT_COLOR_STR          "gray"
#define UI_WID_POPUP_WIDTH_NORMAL  24
#define UI_WID_POPUP_WIDTH_WIDE    38
#define UI_WID_POPUP_WIDTH_WIDEST  48
#define UI_WID_SAVE_SLOTS          10 // How many save game slots
#define UI_WID_STYLE_DARK          4
#define UI_WID_STYLE_GREEN         1
#define UI_WID_STYLE_MAX           6
#define UI_WID_STYLE_NONE          5
#define UI_WID_STYLE_NORMAL        3
#define UI_WID_STYLE_OUTLINE       0
#define UI_WID_STYLE_RED           2

#include "my_sys.h"

#endif
