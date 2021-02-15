//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_UI_H_
#define _MY_UI_H_

#define ENABLE_ASSERT              // Abort on errors
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
#define UI_FONT_LARGE_WIDTH        8
#define UI_FONT_LARGE_HEIGHT       8
#define UI_TILE_LARGE_WIDTH        8
#define UI_TILE_LARGE_HEIGHT       8
#define UI_FONT_SMALL_WIDTH        6
#define UI_FONT_SMALL_HEIGHT       8
#define UI_FONT_NAME               "data/fonts/6x6.tga"
#define UI_FONT_PIXEL_SIZE         6
#define UI_HEALTH_BAR_STEPS        17 // How many graduations on health bar
#define UI_HEALTH_ICON_STEPS       5
#define UI_TOPCON_HEIGHT           5 // Scrollbar limit
#define UI_TOPCON_TEXT_COLOR       UI_TEXT_COLOR
#define UI_TOPCON_VIS_HEIGHT       5
#define UI_TOPCON_VIS_WIDTH        UI_TOPCON_WIDTH
#define UI_TOPCON_WIDTH            (TERM_WIDTH - UI_SIDEBAR_RIGHT_WIDTH)
#define UI_MINIMAP_SIZE            0.155
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
#define UI_WID_STYLE_SPARSE_NONE   -1
#define UI_WID_STYLE_SOLID_NONE    0
#define UI_WID_STYLE_GRAY          6
#define UI_WID_STYLE_GREEN         1
#define UI_WID_STYLE_NORMAL        3
#define UI_WID_STYLE_OUTLINE       7
#define UI_WID_STYLE_RED           2
#define UI_WID_STYLE_SOLID_DEFAULT 5
#define UI_WID_STYLE_VERT_DARK     8
#define UI_WID_STYLE_VERT_LIGHT    9
#define UI_WID_STYLE_HORIZ_DARK    10
#define UI_WID_STYLE_HORIZ_LIGHT   11
#define UI_WID_STYLE_BAG           12
#define UI_WID_STYLE_MAX           13
#endif
