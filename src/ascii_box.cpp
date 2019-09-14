/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_sdl.h"
#include "my_font.h"
#include "my_ascii.h"
#include <array>

void ascii_put_shaded_box (int style, int x1, int y1, int x2, int y2,
                           color col_border_text, 
                           color col_tl, color col_mid, color col_br,
                           void *context)
{_
    int x;
    int y;

    static bool init;
    static const int MAX_STYLES = 5;
    static const int MAX_UI_SIZE = 16;
    static const int MAX_UI_BG_SIZE = MAX_UI_SIZE - 2;
    static Tilep tiles[MAX_STYLES][MAX_UI_SIZE][MAX_UI_SIZE];

    if (style >= MAX_STYLES) {
        DIE("unimplemented style %d", style);
    }

    if (!init) {
        init = true;
        for (auto styles = 0; styles < 5; styles++) {
            for (auto x = 0; x < MAX_UI_SIZE; x++) {
                for (auto y = 0; y < MAX_UI_SIZE; y++) {
                    std::string name = 
                        "ui" + std::to_string(styles) + "," +
                        std::to_string(x) + "," + std::to_string(y);
                    tiles[styles][x][y] = tile_find_mand(name);
                }
            }
        }
    }

    if (y1 == y2) {
        y = y1;
        for (x = x1; x <= x2; x++) {
            ascii_set_bg(x, y, col_mid);
            ascii_set_bg(x, y, tiles[style][(x % MAX_UI_BG_SIZE)+1][(y % MAX_UI_BG_SIZE)+1]);
        }
    } else {
        for (y = y1; y <= y2; y++) {
            for (x = x1; x <= x2; x++) {
                ascii_set_bg(x, y, tiles[style][(x % MAX_UI_BG_SIZE)+1][(y % MAX_UI_BG_SIZE)+1]);
                ascii_set_bg(x, y, col_tl);
            }
        }

        for (y = y1 + 1; y <= y2; y++) {
            for (x = x1 + 1; x <= x2; x++) {
                ascii_set_bg(x, y, tiles[style][(x % MAX_UI_BG_SIZE)+1][(y % MAX_UI_BG_SIZE)+1]);
                ascii_set_bg(x, y, col_br);
            }
            ascii_set_bg(x1, y2, tiles[style][(x1 % MAX_UI_BG_SIZE)+1][(y2 % MAX_UI_BG_SIZE)+1]);
            ascii_set_bg(x1, y2, col_br);
        }

        for (y = y1 + 1; y <= y2 - 1; y++) {
            for (x = x1 + 1; x <= x2 - 1; x++) {
                ascii_set_bg(x, y, tiles[style][(x % MAX_UI_BG_SIZE)+1][(y % MAX_UI_BG_SIZE)+1]);
                ascii_set_bg(x, y, col_mid);
            }
        }
    }

    for (x = x1; x <= x2; x++) {
        for (y = y1; y <= y2; y++) {
            ascii_set_context(x, y, context);
            ascii_set_bg(x, y, tiles[style][(x % MAX_UI_BG_SIZE)+1][(y % MAX_UI_BG_SIZE)+1]);
            ascii_set_bg(x, y, col_mid);
        }
    }

    if ((y2 - y1) < 2) {
        return;
    }

    if (x1 == x2) {
        return;
    }

    for (x = x1 + 1; x <= x2 - 1; x++) {
        ascii_set_bg(x, y1, tiles[style][(x % MAX_UI_BG_SIZE)+1][0]);
        ascii_set_bg(x, y2, tiles[style][(x % MAX_UI_BG_SIZE)+1][MAX_UI_SIZE - 1]);
        ascii_set_bg(x, y1, col_border_text);
        ascii_set_bg(x, y2, col_border_text);
    }

    for (y = y1 + 1; y <= y2 - 1; y++) {
        ascii_set_bg(x1, y, tiles[style][0][(y % MAX_UI_BG_SIZE)+1]);
        ascii_set_bg(x2, y, tiles[style][MAX_UI_SIZE - 1][(y % MAX_UI_BG_SIZE)+1]);
        ascii_set_bg(x1, y, col_border_text);
        ascii_set_bg(x2, y, col_border_text);
    }

    ascii_set_bg(x1, y1, tiles[style][0][0]);
    ascii_set_bg(x2, y2, tiles[style][MAX_UI_SIZE - 1][MAX_UI_SIZE - 1]);
    ascii_set_bg(x2, y1, tiles[style][MAX_UI_SIZE - 1][0]);
    ascii_set_bg(x1, y2, tiles[style][0][MAX_UI_SIZE - 1]);

    ascii_set_bg(x1, y1, col_border_text);
    ascii_set_bg(x2, y2, col_border_text);
    ascii_set_bg(x2, y1, col_border_text);
    ascii_set_bg(x1, y2, col_border_text);
}

static void ascii_put_box_ (int style,
                            int x,
                            int y,
                            int width,
                            int height,
                            color col_border_text,
                            color col_tl,
                            color col_mid,
                            color col_br,
                            const wchar_t *fmt,
                            va_list args)
{_
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

    ascii_put_shaded_box(style, x, y,
                         x + width - 1, y + height - 1,
                         col_border_text, col_tl, col_mid, col_br,
                         0 /* context */);

    ascii_putf__(x + ((width - len) / 2), y + 1, WHITE, COLOR_NONE, b);
}

void ascii_put_box (box_args b, int style, const wchar_t *fmt, ...)
{_
    va_list args;

    if (!b.width || !b.height) {
        b.x = ASCII_MAP_TL_X;
        b.y = ASCII_MAP_TL_Y;
        b.width = ASCII_MAP_VISIBLE_WIDTH;
        b.height = ASCII_MAP_VISIBLE_HEIGHT;
    }

    if ((b.col_tl == COLOR_NONE) &&
        (b.col_mid == COLOR_NONE) &&
        (b.col_br == COLOR_NONE)) {

        b.col_border_text = WHITE;
        b.col_tl = WHITE;
        b.col_mid = WHITE;
        b.col_br = WHITE;
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
                   b.x,
                   b.y,
                   b.width,
                   b.height,
                   b.col_border_text,
                   b.col_tl,
                   b.col_mid,
                   b.col_br,
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
        for (y = y1; y <= y2; y++) {

            if (!ascii_ok(x, b.y)) {
                continue;
            }

            ascii.sdl_mod[x][y] = b.sdl_mod;
            ascii.sdl_key[x][y] = b.sdl_key;
            ascii.mouse_button[x][y] = b.mouse_button;

            /*
             * Callbacks for ascii co-ords.
             */
            ascii.key_down[x][y] = b.key_down;
            ascii.mouse_down[x][y] = b.mouse_down;
            ascii.mouse_over[x][y] = b.mouse_over;
        }
    }
}
