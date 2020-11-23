//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_MAIN_H_
#define _MY_MAIN_H_

#define ENABLE_ASSERT              // DIE on errors, like array bound check
#define ENABLE_CRASH_HANDLER       // Intercept SEGV
#define ENABLE_DEBUG_TRACE         // Function tracing
#define ENABLE_PTRCHECK_HISTORY 2  // Per pointer history
#define ENABLE_TILE_BOUNDS         // Scan tiles for bounds
#undef  ENABLE_DEBUG_AI            // Monster AI decisions
#undef  ENABLE_DEBUG_AI_ASTAR      // Astar AI path costs
#undef  ENABLE_DEBUG_AI_GOALS      // AI goal selection
#undef  ENABLE_DEBUG_AI_WANDER     // AI wander path selection
#undef  ENABLE_DEBUG_GFX_GL_BLEND  // Use to debug specific blends
#undef  ENABLE_DEBUG_IO            // File i/o
#undef  ENABLE_DEBUG_LIGHT         // Lighting algorithm for player
#undef  ENABLE_DEBUG_PTRCHECK      // Debug ptrcheck itself
#undef  ENABLE_DEBUG_PY            // Python debugs
#undef  ENABLE_DEBUG_SAVE_CHECK    // Verify compressed file
#undef  ENABLE_DEBUG_SAVE_LOAD     // Map saving and loading
#undef  ENABLE_DEBUG_SAVE_LOAD_HEX // Hex dump of save files
#undef  ENABLE_DEBUG_TILE          // Astar AI path costs
#undef  ENABLE_DEBUG_UI            // User interface logs
#undef  ENABLE_DEBUG_UI2           // User interface logs with inheritance
#undef  ENABLE_DEBUG_UI_FOCUS      // Which windows we are over
#undef  ENABLE_LOG_TIMESTAMPS      // Full timestamps with date in logs
#undef  ENABLE_PTRCHECK_LEAK
#undef  ENABLE_THING_ID_LOGS       // Thing ID allocations
#undef  ENABLE_UI_ASCII_MOUSE      // Show an in game mouse, not system mouse

#define LEVELS_ACROSS              MAP_WIDTH // World size
#define LEVELS_DEEP                32
#define LEVELS_DOWN                MAP_HEIGHT
#define LEVELS_MONST_COUNT         100
#define LEVEL_FADE_IN_MS           800
#define LEVEL_FADE_OUT_MS          500
#define LIGHT_MAX_RAYS             180  // Max light rays cast
#define MAP_BORDER_TOTAL                 10   // Room border padding
#define MAP_GRID_HEIGHT            4
#define MAP_GRID_WIDTH             4 // Rooms across and down
#define MAP_HEIGHT                 ((MAP_GRID_HEIGHT*MAP_ROOM_HEIGHT) + (MAP_BORDER_TOTAL*2))
#define MAP_BORDER_ROCK            1  // Map rock border
#define MAP_ROOM_HEIGHT            13
#define MAP_ROOM_WIDTH             13
#define MAP_SLOTS                  32 // Max things per map slot
#define MAP_WIDTH                  ((MAP_GRID_WIDTH*MAP_ROOM_WIDTH) + (MAP_BORDER_TOTAL*2))
#define PARTICLE_SPEED_MS          400
#define TERM_HEIGHT_DEF            36
#define TERM_HEIGHT_MAX            TERM_HEIGHT_DEF
#define TERM_WIDTH_DEF             100
#define TERM_WIDTH_MAX             TERM_WIDTH_DEF
#define THING_AI_WANDER_FREQ_TENTHS 3   // How often we can wander
#define THING_DAMAGE_SHAKE_ABOVE   10   // Damage above this causes shakes
#define THING_DAMAGE_SHAKE_SCALE   40.0 // Smaller means more shaking
#define THING_HEALTH_BLOODIED_PCT1 35   // Some blood on the screen
#define THING_HEALTH_BLOODIED_PCT2 15   // More...
#define THING_HEALTH_BLOODIED_PCT3 15   // More...
#define THING_HEALTH_BLOODIED_PCT4 5    // Lots of blood on screen
#define THING_TICK_MAX_MOVES_AHEAD 5    // How many moves ahead things get
#define TILE_CURSOR                ((wchar_t)('z' + 6))
#define TILE_CURSOR_NAME           "1.97" // block
#define TILE_HEIGHT                game->config.tile_height
#define TILE_HEIGHT_ASCII          48
#define TILE_HEIGHT_LORES          16
#define TILE_HEIGHT_MAX            64
#define TILE_UNKNOWN_NAME               "1.31" // ?
#define TILE_WIDTH                 game->config.tile_width
#define TILE_WIDTH_ASCII           48   // Tile size of the player
#define TILE_WIDTH_LORES           16   // Tile size of the player
#define TILE_WIDTH_MAX             64   // Largest tile for collisions
#define TTF_GLYPH_MAX              134
#define TTF_GLYPH_MIN              ' '
#define TTF_GLYPH_PER_ROW          60
#define UI_ACTIONBAR_BR_Y          (TERM_HEIGHT - 2)
#define UI_ACTIONBAR_ITEM_HEIGHT   3
#define UI_ACTIONBAR_ITEM_WIDTH    3
#define UI_ACTIONBAR_MAX_ITEMS     10
#define UI_ACTIONBAR_TL_Y          (TERM_HEIGHT - 5)
#define UI_BOTCON_HEIGHT           1 // Scrollbar limit
#define UI_BOTCON_TEXT_COLOR       UI_TEXT_COLOR
#define UI_BOTCON_VIS_HEIGHT       1
#define UI_BOTCON_VIS_WIDTH        UI_BOTCON_WIDTH
#define UI_BOTCON_WIDTH            (TERM_WIDTH)
#define UI_CONSOLE_HEIGHT          200
#define UI_CONSOLE_INPUT_COLOR     ORANGE
#define UI_CONSOLE_TEXT_COLOR      GRAY
#define UI_CONSOLE_WIDTH           (TERM_WIDTH - 3)
#define UI_CURSOR_COLOR            GRAY
#define UI_CURSOR_OTHER_COLOR      WHITE
#define UI_FONT_HEIGHT             26
#define UI_FONT_NAME               "data/ttf/6x6.tga"
#define UI_FONT_PIXEL_SIZE         6
#define UI_FONT_WIDTH              20
#define UI_HEALTH_BAR_STEPS        12 // How many graduations on health bar
#define UI_HEALTH_ICON_STEPS       5
#define UI_MINICON_HEIGHT          6 // Scrollbar limit
#define UI_MINICON_TEXT_COLOR      UI_TEXT_COLOR
#define UI_MINICON_VIS_HEIGHT      5
#define UI_MINICON_VIS_WIDTH       UI_MINICON_WIDTH
#define UI_MINICON_WIDTH           (TERM_WIDTH - UI_SIDEBAR_RIGHT_WIDTH)
#define UI_MINIMAP_SIZE            0.155
#define UI_MONST_HEALTH_BAR_STEPS  16
#define UI_MOUSE_DOUBLE_CLICK      500 // Double click time
#define UI_MOUSE_WHEEL_SCALE       1.0 // How much the wheel mouse moves.
#define UI_MOUSE_WHEEL_SCALE_MAX   10
#define UI_POPUP_TEXT_COLOR        UI_TEXT_COLOR
#define UI_SCROLL_JOY_SCALE        1.0
#define UI_SCROLL_JOY_SCALE_MAX    1.5
#define UI_SIDEBAR_LEFT_WIDTH      16
#define UI_SIDEBAR_RIGHT_WIDTH     16
#define UI_TEXT_COLOR              GRAY // Default text color
#define UI_TEXT_COLOR_STR          "gray"
#define UI_UPDATE_FAST_MS          5
#define UI_UPDATE_SLOW_MS          50 // FPS and game status
#define UI_WID_POPUP_WIDTH_NORMAL  24
#define UI_WID_POPUP_WIDTH_WIDE    38
#define UI_WID_POPUP_WIDTH_WIDEST  48
#define UI_WID_SAVE_SLOTS          25 // How many save game slots
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
