//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_MAIN_H_
#define _MY_MAIN_H_

#define ENABLE_ASSERT              // DIE on errors, like array bound check
#define ENABLE_CRASH_HANDLER       // Intercept SEGV
#define ENABLE_PTRCHECK_HISTORY 2  // Per pointer history
#define ENABLE_TILE_BOUNDS         // Scan tiles for bounds
#define ENABLE_TRACING             // Function tracing
#undef  ENABLE_DEBUG_AI            // Monster AI decisions
#undef  ENABLE_DEBUG_AI_ASTAR      // Astar AI path costs
#undef  ENABLE_DEBUG_AI_GOALS      // AI goal selection
#undef  ENABLE_DEBUG_AI_WANDER     // AI wander path selection
#undef  ENABLE_DEBUG_GFX_GL_BLEND  // Use to debug specific blends
#undef  ENABLE_DEBUG_LIGHT         // Lighting algorithm for player
#undef  ENABLE_DEBUG_SAVE_CHECK    // Verify compressed file
#undef  ENABLE_DEBUG_SAVE_LOAD     // Map saving and loading
#undef  ENABLE_DEBUG_SAVE_LOAD_HEX // Hex dump of save files
#undef  ENABLE_DEBUG_TILE          // Astar AI path costs
#undef  ENABLE_DEBUG_UI_FOCUS      // Which windows we are over
#undef  ENABLE_LOG_TIMESTAMPS      // Full timestamps with date in logs
#undef  ENABLE_MAP_DEBUG           // Visible map, no lighting
#undef  ENABLE_PTRCHECK_DEBUG      // Debug ptrcheck itself
#undef  ENABLE_PTRCHECK_LEAK
#undef  ENABLE_THING_ID_LOGS       // Thing ID allocations
#undef  ENABLE_UI_ASCII_MOUSE      // Show an in game mouse, not system mouse
#undef  ENABLE_UI_DEBUG            // User interface logs
#undef  ENABLE_UI_DEBUG_EXTRA      // User interface logs with inheritance

#define ASCII_HEIGHT_MAX           ASCII_WIDTH_MAX
#define ASCII_WIDTH_MAX            256
#define GRID_HEIGHT                5
#define GRID_WIDTH                 5    // Rooms across and down
#define LEVELS_ACROSS              MAP_WIDTH // World size
#define LEVELS_DEEP                32
#define LEVELS_DOWN                MAP_HEIGHT
#define MAP_BORDER                 10   // Room border padding
#define MAP_HEIGHT                 ((GRID_HEIGHT*ROOM_HEIGHT) + (MAP_BORDER*2))
#define MAP_ROCK_BORDER            1    // Map rock border
#define MAP_SLOTS                  32   // Max things per map slot
#define MAP_WIDTH                  ((GRID_WIDTH*ROOM_WIDTH) + (MAP_BORDER*2))
#define MAX_RAY_LIGHTING           180  // Max light rays cast
#define ROOM_HEIGHT                13
#define ROOM_WIDTH                 13
#define THING_AI_WANDER_FREQ_TENTHS 3   // How often we can wander
#define THING_DAMAGE_SHAKE_ABOVE   10   // Damage above this causes shakes
#define THING_DAMAGE_SHAKE_SCALE   20.0 // Smaller means more shaking
#define THING_HEALTH_BLOODIED_PCT1 35   // Some blood on the screen
#define THING_HEALTH_BLOODIED_PCT2 15   // More...
#define THING_HEALTH_BLOODIED_PCT3 15   // More...
#define THING_HEALTH_BLOODIED_PCT4 5    // Lots of blood on screen
#define THING_TICK_MAX_MOVES_AHEAD 10   // How many moves ahead things get
#define TILE_HEIGHT                16
#define TILE_HEIGHT_MAX            64
#define TILE_WIDTH                 16   // Tile size of the player
#define TILE_WIDTH_MAX             64   // Largest tile for collisions
#define TTF_GLYPH_BAR              127  // For status / progress bars
#define TTF_GLYPH_MAX              134
#define TTF_GLYPH_MIN              ' '
#define TTF_GLYPH_PER_ROW          60
#define UI_ACTIONBAR_BR_Y          (ASCII_HEIGHT - 2)
#define UI_ACTIONBAR_ITEM_HEIGHT   3
#define UI_ACTIONBAR_ITEM_WIDTH    3
#define UI_ACTIONBAR_MAX_ITEMS     10
#define UI_ACTIONBAR_TL_Y          (ASCII_HEIGHT - 5)
#define UI_BOTCON_HEIGHT           1 // Scrollbar limit
#define UI_BOTCON_TEXT_COLOR       UI_TEXT_COLOR
#define UI_BOTCON_VIS_HEIGHT       1
#define UI_BOTCON_VIS_WIDTH        UI_BOTCON_WIDTH
#define UI_BOTCON_WIDTH            (ASCII_WIDTH)
#define UI_CONSOLE_HEIGHT          200
#define UI_CONSOLE_INPUT_COLOR     ORANGE
#define UI_CONSOLE_KEY1            '`'
#define UI_CONSOLE_KEY2            '~'
#define UI_CONSOLE_KEY3            '\\'
#define UI_CONSOLE_TEXT_COLOR      GRAY
#define UI_CONSOLE_WIDTH           (ASCII_WIDTH - 3)
#define UI_CURSOR_COLOR            GRAY
#define UI_CURSOR_OTHER_COLOR      WHITE
#define UI_FONT_HEIGHT             24
#define UI_FONT_NAME               "data/ttf/6x6.tga"
#define UI_FONT_PIXEL_SIZE         6
#define UI_FONT_WIDTH              20
#define UI_HEALTH_BAR_STEPS        12 // How many graduations on health bar
#define UI_HEALTH_ICON_STEPS       5
#define UI_MINICON_HEIGHT          6 // Scrollbar limit
#define UI_MINICON_TEXT_COLOR      UI_TEXT_COLOR
#define UI_MINICON_VIS_HEIGHT      5
#define UI_MINICON_VIS_WIDTH       UI_MINICON_WIDTH
#define UI_MINICON_WIDTH           (ASCII_WIDTH - UI_SIDEBAR_RIGHT_WIDTH)
#define UI_MONST_HEALTH_BAR_STEPS  16
#define UI_MOUSE_DOUBLE_CLICK      500 // Double click time
#define UI_MOUSE_WHEEL_SCALE       1.0 // How much the wheel mouse moves.
#define UI_MOUSE_WHEEL_SCALE_MAX   10
#define UI_POLL_EVENTS_MS          5
#define UI_POPUP_TEXT_COLOR        UI_TEXT_COLOR
#define UI_SCROLL_JOY_SCALE        1.0
#define UI_SCROLL_JOY_SCALE_MAX    1.5
#define UI_SIDEBAR_LEFT_WIDTH      20
#define UI_SIDEBAR_RIGHT_WIDTH     14
#define UI_TEXT_COLOR              GRAY // Default text color
#define UI_TEXT_COLOR_STR          "gray"
#define UI_UPDATE_SLOW_MS          500 // FPS and game status
#define UI_WID_POPUP_WIDTH_NORMAL  24
#define UI_WID_POPUP_WIDTH_WIDE    38
#define UI_WID_POPUP_WIDTH_WIDEST  48
#define UI_WID_SAVE_SLOTS          10 // How many save game slots
#define UI_WID_STYLE_DARK          4
#define UI_WID_STYLE_GRAY          6
#define UI_WID_STYLE_GREEN         1
#define UI_WID_STYLE_HORIZ_DARK    10
#define UI_WID_STYLE_HORIZ_LIGHT   11
#define UI_WID_STYLE_MAX           12
#define UI_WID_STYLE_NORMAL        3
#define UI_WID_STYLE_OUTLINE       7
#define UI_WID_STYLE_RED           2
#define UI_WID_STYLE_SOLID_DEFAULT 5
#define UI_WID_STYLE_VERT_DARK     8
#define UI_WID_STYLE_VERT_LIGHT    9

#include "my_sys.h"

#endif
