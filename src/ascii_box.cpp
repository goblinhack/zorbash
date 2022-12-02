//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_ascii.hpp"
#include "my_color_defs.hpp"
#include "my_main.hpp"
#include "my_string.hpp"
#include "my_ui.hpp"

static void ascii_put_box__(int style, Tilep bg_tile, Tilep fg_tile, Tilep fg2_tile, Tilep fg3_tile, int x1, int y1,
                            int x2, int y2, color col_bg, color col_fg, void *context)
{
  TRACE_NO_INDENT();

  int x;
  int y;

  static bool      init;
  static const int MAX_UI_SIZE    = 16;
  static const int MAX_UI_BG_SIZE = MAX_UI_SIZE - 2;
  static std::array< std::array< std::array< std::array< Tilep, MAX_UI_SIZE >, MAX_UI_SIZE >, UI_WID_STYLE_MAX >,
                     UI_TYPES_MAX >
      tiles = {};

  if (style >= UI_WID_STYLE_MAX) {
    ERR("Unimplemented widget style %d", style);
    return;
  }

  if (! init) {
    init = true;
    for (auto type = 0; type < UI_TYPES_MAX; type++) {
      for (auto styles = 0; styles < UI_WID_STYLE_MAX; styles++) {
        for (auto x = 0; x < MAX_UI_SIZE; x++) {
          for (auto y = 0; y < MAX_UI_SIZE; y++) {
            if (type == UI_TYPE_PIXELART) {
              std::string name =
                  "ui.pixelart." + std::to_string(styles) + "," + std::to_string(x) + "," + std::to_string(y);
              set(tiles, type, styles, x, y, tile_find_mand(name));
            } else {
              std::string name =
                  "ui.ascii." + std::to_string(styles) + "," + std::to_string(x) + "," + std::to_string(y);
              set(tiles, type, styles, x, y, tile_find_mand(name));
            }
          }
        }
      }
    }
  }

  int ui_type;

  if (g_opt_ascii) {
    ui_type = UI_TYPE_ASCII;
  } else {
    ui_type = UI_TYPE_PIXELART;
  }

  {
    float dx = 1.0 / (((float) x2) - ((float) x1) + 1);
    float dy = 1.0 / (((float) y2) - ((float) y1) + 1);

    for (x = x1; x <= x2; x++) {
      for (y = y1; y <= y2; y++) {
        float tx = ((float) (x) -x1) * dx;
        float ty = ((float) (y) -y1) * dy;
        if (bg_tile || (col_bg != COLOR_NONE)) {
          ascii_set_bg2(x, y, bg_tile, tx, ty, dx, dy);
          ascii_set_bg2(x, y, col_bg);
        }

        //
        // The numbers for fg are offset here as "fg1" is really the ascii letter tile
        //
        if (fg_tile || (col_fg != COLOR_NONE)) {
          ascii_set_fg2(x, y, fg_tile, tx, ty, dx, dy);
          ascii_set_fg2(x, y, col_fg);
        }
        if (fg2_tile || (col_fg != COLOR_NONE)) {
          ascii_set_fg3(x, y, fg2_tile, tx, ty, dx, dy);
          ascii_set_fg3(x, y, col_fg);
        }
        if (fg3_tile || (col_fg != COLOR_NONE)) {
          ascii_set_fg4(x, y, fg3_tile, tx, ty, dx, dy);
          ascii_set_fg4(x, y, col_fg);
        }
        ascii_set_fg(x, y, ' ');
      }
    }
  }

  if (unlikely(y1 == y2)) {
    //
    // Horizontal
    //
    y = y1;
    for (x = x1; x <= x2; x++) {
      if (style >= 0) {
        ascii_set_bg(x, y, tiles[ ui_type ][ style ][ (x % MAX_UI_BG_SIZE) + 1 ][ 0 ]);
      }
      ascii_set_bg(x, y, col_bg);
    }
    if (style >= 0) {
      ascii_set_bg(x1, y, tiles[ ui_type ][ style ][ 0 ][ 0 ]);
      ascii_set_bg(x2, y, tiles[ ui_type ][ style ][ MAX_UI_SIZE - 1 ][ 0 ]);
    }
    return;
  }
  if (unlikely(x1 == x2)) {
    //
    // Vertical
    //
    x = x1;
    for (y = y1; y <= y2; y++) {
      if (style >= 0) {
        ascii_set_bg(x, y, tiles[ ui_type ][ style ][ 0 ][ (y % MAX_UI_BG_SIZE) + 1 ]);
      }
      ascii_set_bg(x, y, col_bg);
    }
    if (style >= 0) {
      ascii_set_bg(x, y1, tiles[ ui_type ][ style ][ 0 ][ 0 ]);
      ascii_set_bg(x, y2, tiles[ ui_type ][ style ][ 0 ][ MAX_UI_SIZE - 1 ]);
    }
    return;
  }
  for (y = y1; y <= y2; y++) {
    for (x = x1; x <= x2; x++) {
      if (style >= 0) {
        ascii_set_bg(x, y, tiles[ ui_type ][ style ][ (x % MAX_UI_BG_SIZE) + 1 ][ (y % MAX_UI_BG_SIZE) + 1 ]);
      }
      ascii_set_bg(x, y, col_bg);
    }
  }

  for (y = y1 + 1; y <= y2; y++) {
    for (x = x1 + 1; x <= x2; x++) {
      if (style >= 0) {
        ascii_set_bg(x, y, tiles[ ui_type ][ style ][ (x % MAX_UI_BG_SIZE) + 1 ][ (y % MAX_UI_BG_SIZE) + 1 ]);
      }
      ascii_set_bg(x, y, col_bg);
    }
    if (style >= 0) {
      ascii_set_bg(x1, y2, tiles[ ui_type ][ style ][ (x1 % MAX_UI_BG_SIZE) + 1 ][ (y2 % MAX_UI_BG_SIZE) + 1 ]);
    }
    ascii_set_bg(x1, y2, col_bg);
  }

  for (y = y1 + 1; y <= y2 - 1; y++) {
    for (x = x1 + 1; x <= x2 - 1; x++) {
      if (style >= 0) {
        ascii_set_bg(x, y, tiles[ ui_type ][ style ][ (x % MAX_UI_BG_SIZE) + 1 ][ (y % MAX_UI_BG_SIZE) + 1 ]);
      }
      ascii_set_bg(x, y, col_bg);
    }
  }

  for (x = x1; x <= x2; x++) {
    for (y = y1; y <= y2; y++) {
      ascii_set_context(x, y, context);
      if (style >= 0) {
        ascii_set_bg(x, y, tiles[ ui_type ][ style ][ (x % MAX_UI_BG_SIZE) + 1 ][ (y % MAX_UI_BG_SIZE) + 1 ]);
      }
      ascii_set_bg(x, y, col_bg);
    }
  }

  for (x = x1 + 1; x <= x2 - 1; x++) {
    if (style >= 0) {
      ascii_set_bg(x, y1, tiles[ ui_type ][ style ][ (x % MAX_UI_BG_SIZE) + 1 ][ 0 ]);
      ascii_set_bg(x, y2, tiles[ ui_type ][ style ][ (x % MAX_UI_BG_SIZE) + 1 ][ MAX_UI_SIZE - 1 ]);
    }
  }

  for (y = y1 + 1; y <= y2 - 1; y++) {
    if (style >= 0) {
      ascii_set_bg(x1, y, tiles[ ui_type ][ style ][ 0 ][ (y % MAX_UI_BG_SIZE) + 1 ]);
      ascii_set_bg(x2, y, tiles[ ui_type ][ style ][ MAX_UI_SIZE - 1 ][ (y % MAX_UI_BG_SIZE) + 1 ]);
    }
  }

  if (style >= 0) {
    ascii_set_bg(x1, y1, tiles[ ui_type ][ style ][ 0 ][ 0 ]);
    ascii_set_bg(x2, y2, tiles[ ui_type ][ style ][ MAX_UI_SIZE - 1 ][ MAX_UI_SIZE - 1 ]);
    ascii_set_bg(x2, y1, tiles[ ui_type ][ style ][ MAX_UI_SIZE - 1 ][ 0 ]);
    ascii_set_bg(x1, y2, tiles[ ui_type ][ style ][ 0 ][ MAX_UI_SIZE - 1 ]);
  }
}

static void ascii_put_box_(int style, Tilep bg_tile, Tilep fg_tile, Tilep fg2_tile, Tilep fg3_tile, int x, int y,
                           int width, int height, color col_bg, color col_text, const wchar_t *fmt, va_list args)
{
  TRACE_NO_INDENT();

  if (! *fmt) {
    ascii_put_box__(style, bg_tile, fg_tile, fg2_tile, fg3_tile, x, y, x + width - 1, y + height - 1, col_bg,
                    col_text, nullptr /* context */);
  } else {
    wchar_t buf[ MAXLONGSTR ];
    auto    wrote = vswprintf(buf, MAXLONGSTR, fmt, args);

    //
    // Only a single nul is written, but as we read 2 at a time...
    //
    if (wrote && (wrote < MAXLONGSTR - 1)) {
      buf[ wrote + 1 ] = '\0';
    }

    auto b   = std::wstring(buf);
    int  len = ascii_strlen(b);

    ascii_put_box__(style, bg_tile, fg_tile, fg2_tile, fg3_tile, x, y, x + width - 1, y + height - 1, col_bg,
                    col_text, nullptr /* context */);

    ascii_putf__(x + ((width - len) / 2), y + 1, col_text, COLOR_NONE, b);
  }
}

void ascii_put_box(box_args b, int style, Tilep bg_tile, Tilep fg_tile, Tilep fg2_tile, Tilep fg3_tile,
                   const wchar_t *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  if (! b.width || ! b.height) {
    b.x      = 0;
    b.y      = 0;
    b.width  = TERM_WIDTH;
    b.height = TERM_HEIGHT;
  }

  int x = b.x;
  int y = b.y;
  int w = b.width;
  int h = b.height;

  //
  // Draw the box
  //
  va_start(args, fmt);

  ascii_put_box_(style, bg_tile, fg_tile, fg2_tile, fg3_tile, b.x, b.y, b.width, b.height, b.col_bg, b.col_text, fmt,
                 args);

  va_end(args);

  //
  // Populate the ascii callbacks for this box.
  //
  int x1, x2, y1, y2;

  x1 = x;
  y1 = y;
  x2 = x + w;
  y2 = y + h;

  for (x = x1; x <= x2; x++) {
    if (unlikely(! ascii_x_ok(x))) {
      continue;
    }
    for (y = y1; y <= y2; y++) {
      if (unlikely(! ascii_y_ok(y))) {
        continue;
      }

      set(ascii.sdl_mod, x, y, b.sdl_mod);
      set(ascii.sdl_key, x, y, b.sdl_key);
      set(ascii.mouse_button, x, y, b.mouse_button);

      //
      // Callbacks for ascii co-ords.
      //
      set(ascii.key_down, x, y, b.key_down);
      set(ascii.mouse_down, x, y, b.mouse_down);
      set(ascii.mouse_over, x, y, b.mouse_over);
    }
  }
}
