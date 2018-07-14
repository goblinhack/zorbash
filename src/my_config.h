/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#define ENABLE_ASSERT              // DIE on errors
#undef  ENABLE_PTRCHECK            // Check validity of pointers too
#undef  ENABLE_CRASH_HANDLER       // Intercept SEGV
#undef  ENABLE_GENERATE_TTF        // Edit .RUNME, look for ENABLE_GENERATE_TTF
#define ENABLE_INVERTED_GFX        // For vision impaired
#define ENABLE_THING_SANITY        // Checks on thing insert

/*
 * How much the wheel mouse moves.
 */
#define ENABLE_WHEEL_SCROLL_SPEED_SCALE         1.0
#define ENABLE_WHEEL_MAX_SCROLL_SPEED_SCALE     10

#define ENABLE_JOY_SCROLL_SPEED_SCALE           1.0
#define ENABLE_JOY_MAX_SCROLL_SPEED_SCALE       1.5

/*
 * Dungeon size
 */
#define MAP_WIDTH                   256
#define MAP_HEIGHT                  256
#define MAP_DEPTH                   1

#define TILES_ACROSS                40 // per screen
#define TILES_DOWN                  24

#define MAX_TILE_WIDTH              64
#define MAX_TILE_HEIGHT             64

#define TILE_WIDTH                  32
#define TILE_HEIGHT                 32

/*
 * Console
 */
#define CONSOLE_CURSOR_COLOR        GRAY
#define CONSOLE_CURSOR_OTHER_COLOR  WHITE
#define CONSOLE_TEXT_COLOR          GRAY
#define CONSOLE_WIDTH               200
#define CONSOLE_HEIGHT              300

/*
 * Fonts
 */
#define FIXED_FONT                  "data/ttf/dejavu-nerd.ttf"
#define FONT_SIZE                   80

#define TTF_GLYPH_MIN               ' '
#define TTF_GLYPH_MAX               0xffff // SDL can only do 2b fonts
#define TTF_GLYPH_PER_ROW           60
#define TTF_CURSOR_CHAR             127

/*
 * Maximum number of thing types. This cannot be exceeded without changing
 * the message format in tx updates.
 */
#define TP_MAX                      10000
