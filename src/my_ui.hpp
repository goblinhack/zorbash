//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_UI_HPP_
#define _MY_UI_HPP_

#define UI_ACTIONBAR_BR_Y            (TERM_HEIGHT - 2)
#define UI_ACTIONBAR_ITEM_HEIGHT     3
#define UI_ACTIONBAR_ITEM_WIDTH      3
#define UI_ACTIONBAR_TL_Y            (TERM_HEIGHT - 5)
#define UI_BOTCON_HEIGHT             1 // Scrollbar limit
#define UI_BOTCON_TEXT_COLOR         UI_TEXT_COLOR
#define UI_BOTCON_VIS_HEIGHT         1
#define UI_BOTCON_VIS_WIDTH          UI_BOTCON_WIDTH
#define UI_BOTCON_WIDTH              (TERM_WIDTH)
#define UI_CONSOLE_HEIGHT            (TERM_HEIGHT * 2)
#define UI_CONSOLE_INPUT_COLOR       ORANGE
#define UI_CONSOLE_TEXT_COLOR        GRAY
#define UI_CONSOLE_WIDTH             (TERM_WIDTH - 3)
#define UI_CURSOR_COLOR              GRAY
#define UI_CURSOR_OTHER_COLOR        WHITE
#define UI_FONT_ASCII_HEIGHT         232
#define UI_FONT_ASCII_WIDTH          128
#define UI_FONT_LARGE_HEIGHT         8
#define UI_FONT_LARGE_WIDTH          8
#define UI_FONT_PIXEL_SIZE           6
#define UI_FONT_SMALL_HEIGHT         8
#define UI_FONT_SMALL_WIDTH          6
#define UI_HEALTH_BAR_STEPS          18 // How many graduations on health bar
#define UI_HEALTH_ICON_STEPS         5
#define UI_INVENTORY_QUICK_ITEMS_MAX 10
#define UI_LEFTBAR_WIDTH             UI_HEALTH_BAR_STEPS
#define UI_LOGGING_EMPTY_LINE        "`" // Complete hack, char I use to force space
#define UI_MOUSE_DOUBLE_CLICK        500 // Double click time
#define UI_MOUSE_WHEEL_SCALE         1.0 // How much the wheel mouse moves.
#define UI_MOUSE_WHEEL_SCALE_MAX     10
#define UI_POPUP_TEXT_COLOR          UI_TEXT_COLOR
#define UI_RIGHTBAR_PIXELART_HEIGHT  58
#define UI_RIGHTBAR_WIDTH            18
#define UI_SCROLL_JOY_SCALE          1.0
#define UI_SCROLL_JOY_SCALE_MAX      1.5
#define UI_TEXT_COLOR                GRAY // Default text color
#define UI_TEXT_COLOR_STR            "gray"
#define UI_TEXT_HIGHLIGHT_COLOR_STR  "white"
#define UI_THING_INFO_WIDTH          (g_opt_ascii ? 40 : 30)
#define UI_TILE_PIXELART_HEIGHT      8
#define UI_TILE_PIXELART_WIDTH       8
#define UI_TOPCON_HEIGHT             4 // Scrollbar limit
#define UI_TOPCON_TEXT_COLOR         UI_TEXT_COLOR
#define UI_TOPCON_VIS_HEIGHT         UI_TOPCON_HEIGHT
#define UI_TOPCON_VIS_WIDTH          UI_TOPCON_WIDTH
#define UI_TOPCON_WIDTH              (TERM_WIDTH - UI_RIGHTBAR_WIDTH)
#define UI_TYPE_ASCII                1
#define UI_TYPE_PIXELART             0
#define UI_TYPES_MAX                 2
#define UI_WID_POPUP_WIDTH_NORMAL    24
#define UI_WID_POPUP_WIDTH_WIDE      38
#define UI_WID_SAVE_SLOTS            10 // How many save game slots

//
// Various colors for the level selection
//
#define UI_DUNGEONS_CRYSTAL_COLOR       YELLOW3
#define UI_DUNGEONS_BOSS_COLOR          ORANGE
#define UI_DUNGEONS_FINAL_BOSS_COLOR    RED
#define UI_DUNGEONS_CURRENT_LEVEL_COLOR GREEN
#define UI_DUNGEONS_SEED_COLOR          GREEN2
#define UI_DUNGEONS_PLAYER_COLOR        PINK2
#define UI_DUNGEONS_UNKNOWN_COLOR       GRAY30

//
// Do faster processing of events, like reading the keyboard and updating widgets.
//
#define UI_EVENT_LOOP_FREQ_FAST_MS (g_opt_ascii ? 10 : 5)

//
// Less frequent updates like updating the FPS.
//
#define UI_EVENT_LOOP_FREQ_SLOW_MS (g_opt_ascii ? 20 : 10)

//
// This is for either
// a) level tick when in ascii mode.
// b) waiting for level fade in when in pixel art mode.
//
#define UI_EVENT_LOOP_FREQ_VERY_SLOW_MS (g_opt_ascii ? 40 : 20)

enum {
  UI_WID_STYLE_SPARSE_NONE = -1, // Used for widgets with their own backgrounds
  UI_WID_STYLE_SOLID_NONE,
  UI_WID_STYLE_GREEN,
  UI_WID_STYLE_RED,
  UI_WID_STYLE_NORMAL,
  UI_WID_STYLE_DARK,
  UI_WID_STYLE_SOLID_DEFAULT,
  UI_WID_STYLE_GRAY,
  UI_WID_STYLE_OUTLINE,
  UI_WID_STYLE_VERT_DARK,
  UI_WID_STYLE_VERT_LIGHT,
  UI_WID_STYLE_HORIZ_DARK,
  UI_WID_STYLE_HORIZ_LIGHT,
  UI_WID_STYLE_VERT_SCROLL_DARK,
  UI_WID_STYLE_VERT_SCROLL_LIGHT,
  UI_WID_STYLE_HORIZ_SCROLL_DARK,
  UI_WID_STYLE_HORIZ_SCROLL_LIGHT,
  UI_WID_STYLE_BAG,
  UI_WID_STYLE_MAX,
};

#endif
