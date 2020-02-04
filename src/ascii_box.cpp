//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_sdl.h"
#include "my_font.h"
#include "my_ascii.h"
#include <array>

static void ascii_put_box__ (int style, Tilep bg_tile, Tilep fg_tile,
                             int x1, int y1, int x2, int y2,
                             color col_bg, color col_fg,
                             void *context)
{_
    int x;
    int y;

    static bool init;
    static const int MAX_UI_SIZE = 16;
    static const int MAX_UI_BG_SIZE = MAX_UI_SIZE - 2;
    static std::array<
               std::array<
                   std::array<Tilep, MAX_UI_SIZE>,
                       MAX_UI_SIZE>, WID_STYLE_MAX> tiles = {};

    if (style >= WID_STYLE_MAX) {
        ERR("unimplemented widget style %d", style);
        return;
    }

    if (!init) {
        init = true;
        for (auto styles = 0; styles < 5; styles++) {
            for (auto x = 0; x < MAX_UI_SIZE; x++) {
                for (auto y = 0; y < MAX_UI_SIZE; y++) {
                    std::string name =
                        "ui" + std::to_string(styles) + "," +
                        std::to_string(x) + "," + std::to_string(y);
                    set(tiles, styles, x, y, tile_find_mand(name));
                }
            }
        }
    }

    {
        float dx = 1.0 / ((float)x2 - (float)x1 + 1);
        float dy = 1.0 / ((float)y2 - (float)y1 + 1);

        for (x = x1; x <= x2; x++) {
            for (y = y1; y <= y2; y++) {
                float tx = (float)(x-x1) * dx;
                float ty = (float)(y-y1) * dy;
                if (bg_tile || (col_bg != COLOR_NONE)) {
                    ascii_set_bg2(x, y, bg_tile, tx, ty, dx, dy);
                    ascii_set_bg2(x, y, col_bg);
                }
                if (fg_tile || (col_fg != COLOR_NONE)) {
                    ascii_set_fg2(x, y, fg_tile, tx, ty, dx, dy);
                    ascii_set_fg2(x, y, col_fg);
                }
                ascii_set_fg(x, y, ' ');
            }
        }
    }

    if (unlikely(y1 == y2)) {
        y = y1;
        for (x = x1; x <= x2; x++) {
            ascii_set_bg(x, y, col_bg);
        }
        return;
    } else if (unlikely(x1 == x2)) {
        x = x1;
        for (y = y1; y <= y2; y++) {
            ascii_set_bg(x, y, col_bg);
        }
        return;
    } else {
        for (y = y1; y <= y2; y++) {
            for (x = x1; x <= x2; x++) {
                if (style >= 0) {
                    ascii_set_bg(x, y, tiles[style][(x % MAX_UI_BG_SIZE)+1][(y % MAX_UI_BG_SIZE)+1]);
                }
                ascii_set_bg(x, y, col_bg);
            }
        }

        for (y = y1 + 1; y <= y2; y++) {
            for (x = x1 + 1; x <= x2; x++) {
                if (style >= 0) {
                    ascii_set_bg(x, y, tiles[style][(x % MAX_UI_BG_SIZE)+1][(y % MAX_UI_BG_SIZE)+1]);
                }
                ascii_set_bg(x, y, col_bg);
            }
            if (style >= 0) {
                ascii_set_bg(x1, y2, tiles[style][(x1 % MAX_UI_BG_SIZE)+1][(y2 % MAX_UI_BG_SIZE)+1]);
            }
            ascii_set_bg(x1, y2, col_bg);
        }

        for (y = y1 + 1; y <= y2 - 1; y++) {
            for (x = x1 + 1; x <= x2 - 1; x++) {
                if (style >= 0) {
                    ascii_set_bg(x, y, tiles[style][(x % MAX_UI_BG_SIZE)+1][(y % MAX_UI_BG_SIZE)+1]);
                }
                ascii_set_bg(x, y, col_bg);
            }
        }
    }

    for (x = x1; x <= x2; x++) {
        for (y = y1; y <= y2; y++) {
            ascii_set_context(x, y, context);
            if (style >= 0) {
                ascii_set_bg(x, y, tiles[style][(x % MAX_UI_BG_SIZE)+1][(y % MAX_UI_BG_SIZE)+1]);
            }
            ascii_set_bg(x, y, col_bg);
        }
    }

    for (x = x1 + 1; x <= x2 - 1; x++) {
        if (style >= 0) {
            ascii_set_bg(x, y1, tiles[style][(x % MAX_UI_BG_SIZE)+1][0]);
            ascii_set_bg(x, y2, tiles[style][(x % MAX_UI_BG_SIZE)+1][MAX_UI_SIZE - 1]);
        }
    }

    for (y = y1 + 1; y <= y2 - 1; y++) {
        if (style >= 0) {
            ascii_set_bg(x1, y, tiles[style][0][(y % MAX_UI_BG_SIZE)+1]);
            ascii_set_bg(x2, y, tiles[style][MAX_UI_SIZE - 1][(y % MAX_UI_BG_SIZE)+1]);
        }
    }

    if (style >= 0) {
        ascii_set_bg(x1, y1, tiles[style][0][0]);
        ascii_set_bg(x2, y2, tiles[style][MAX_UI_SIZE - 1][MAX_UI_SIZE - 1]);
        ascii_set_bg(x2, y1, tiles[style][MAX_UI_SIZE - 1][0]);
        ascii_set_bg(x1, y2, tiles[style][0][MAX_UI_SIZE - 1]);
    }
}

static void ascii_put_box_ (int style,
                            Tilep bg_tile,
                            Tilep fg_tile,
                            int x,
                            int y,
                            int width,
                            int height,
                            color col_bg,
                            color col_text,
                            const wchar_t *fmt,
                            va_list args)
{_
    if (!*fmt) {
        ascii_put_box__(style, bg_tile, fg_tile, x, y,
                        x + width - 1, y + height - 1,
                        col_bg, col_text, 0 /* context */);
    } else {
        wchar_t buf[MAXSHORTSTR];
        auto wrote = vswprintf(buf, MAXSHORTSTR, fmt, args);

        /*
         * Only a single nul is written, but as we read 2 at a time...
         */
        if (wrote && (wrote < MAXSHORTSTR - 1)) {
            buf[wrote+1] = '\0';
        }

        auto b = std::wstring(buf);
        int len = ascii_strlen(b);

        ascii_put_box__(style, bg_tile, fg_tile, x, y,
                        x + width - 1, y + height - 1,
                        col_bg, col_text, 0 /* context */);

        ascii_putf__(x + ((width - len) / 2), y + 1, col_text, COLOR_NONE, b);
    }
}

void ascii_put_box (box_args b, int style, Tilep bg_tile, Tilep fg_tile, const wchar_t *fmt, ...)
{_
    va_list args;

    if (!b.width || !b.height) {
        b.x = 0;
        b.y = 0;
        b.width = ASCII_WIDTH;
        b.height = ASCII_HEIGHT;
    }

    int x = b.x;
    int y = b.y;
    int w = b.width;
    int h = b.height;

    /*
     * Draw the box
     */
    va_start(args, fmt);

    ascii_put_box_(style,
                   bg_tile,
                   fg_tile,
                   b.x,
                   b.y,
                   b.width,
                   b.height,
                   b.col_bg,
                   b.col_text,
                   fmt,
                   args);

    va_end(args);

    /*
     * Populate the ascii callbacks for this box.
     */
    int x1, x2, y1, y2;

    x1 = x;
    y1 = y;
    x2 = x + w;
    y2 = y + h;

    for (x = x1; x <= x2; x++) {
        if (unlikely(!ascii_x_ok(x))) {
            continue;
        }
        for (y = y1; y <= y2; y++) {
            if (unlikely(!ascii_y_ok(y))) {
                continue;
            }

            set(ascii.sdl_mod, x, y, b.sdl_mod);
            set(ascii.sdl_key, x, y, b.sdl_key);
            set(ascii.mouse_button, x, y, b.mouse_button);

            /*
             * Callbacks for ascii co-ords.
             */
            set(ascii.key_down, x, y, b.key_down);
            set(ascii.mouse_down, x, y, b.mouse_down);
            set(ascii.mouse_over, x, y, b.mouse_over);
        }
    }
}
