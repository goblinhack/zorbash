/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_sdl.h"
#include "my_font.h"
#include "my_ascii.h"

void ascii_put_shaded_box (int x1, int y1, int x2, int y2,
                           color col_border_text, color col_tl, color col_mid, color col_br,
                           void *context)
{_
    int x;
    int y;

    auto c = L'▋';

    if (y1 == y2) {
        y = y1;
        for (x = x1; x <= x2; x++) {
            ascii_set_bg(x, y, c);
            ascii_set_bg(x, y, col_mid);
            ascii_set_fg(x, y, (Tilep)nullptr);
        }
    } else {
        for (y = y1; y <= y2; y++) {
            for (x = x1; x <= x2; x++) {
                ascii_set_bg(x, y, c);
                ascii_set_bg(x, y, col_tl);
                ascii_set_fg(x, y, (Tilep)nullptr);
            }
        }

        for (y = y1 + 1; y <= y2; y++) {
            for (x = x1 + 1; x <= x2; x++) {
                ascii_set_bg(x, y, c);
                ascii_set_bg(x, y, col_br);
                ascii_set_fg(x, y, (Tilep)nullptr);
            }
            ascii_set_bg(x1, y2, c);
            ascii_set_bg(x1, y2, col_br);
        }

        for (y = y1 + 1; y <= y2 - 1; y++) {
            for (x = x1 + 1; x <= x2 - 1; x++) {
                ascii_set_bg(x, y, c);
                ascii_set_bg(x, y, col_mid);
                ascii_set_fg(x, y, (Tilep)nullptr);
            }
        }
    }

    for (x = x1; x <= x2; x++) {
        for (y = y1; y <= y2; y++) {
            ascii_set_context(x, y, context);
            ascii_set_fg(x, y, (Tilep)nullptr);
        }
    }

    if ((y2 - y1) < 2) {
        return;
    }

    if (x1 == x2) {
        return;
    }

    if (col_border_text == COLOR_NONE) {
        return;
    }

    static bool init;
    static Tilep tile_ui_tl = nullptr;
    static Tilep tile_ui_br = nullptr;
    static Tilep tile_ui_tr = nullptr;
    static Tilep tile_ui_bl = nullptr;
    static Tilep tile_ui_left = nullptr;
    static Tilep tile_ui_right = nullptr;
    static Tilep tile_ui_top = nullptr;
    static Tilep tile_ui_bot = nullptr;
    if (!init) {
        init = true;
        tile_ui_tl    = tile_find("ui-tl");
        tile_ui_br    = tile_find("ui-br");
        tile_ui_tr    = tile_find("ui-tr");
        tile_ui_bl    = tile_find("ui-bl");
        tile_ui_left  = tile_find("ui-left");
        tile_ui_right = tile_find("ui-right");
        tile_ui_top   = tile_find("ui-top");
        tile_ui_bot   = tile_find("ui-bot");
    }

    for (x = x1 + 1; x <= x2 - 1; x++) {
        ascii_set_fg(x, y1, tile_ui_top);
        ascii_set_fg(x, y2, tile_ui_bot);
        ascii_set_fg(x, y1, col_border_text);
        ascii_set_fg(x, y2, col_border_text);
    }
    for (y = y1 + 1; y <= y2 - 1; y++) {
        ascii_set_fg(x1, y, tile_ui_left);
        ascii_set_fg(x2, y, tile_ui_right);
        ascii_set_fg(x1, y, col_border_text);
        ascii_set_fg(x2, y, col_border_text);
    }
    ascii_set_fg(x1, y1, tile_ui_tl);
    ascii_set_fg(x2, y2, tile_ui_br);
    ascii_set_fg(x2, y1, tile_ui_tr);
    ascii_set_fg(x1, y2, tile_ui_bl);

    ascii_set_fg(x1, y1, col_border_text);
    ascii_set_fg(x2, y2, col_border_text);
    ascii_set_fg(x2, y1, col_border_text);
    ascii_set_fg(x1, y2, col_border_text);
}

static void ascii_put_box_ (int x,
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

    ascii_put_shaded_box(x, y,
                         x + width - 1, y + height - 1,
                         col_border_text, col_tl, col_mid, col_br,
                         0 /* context */);

    ascii_putf__(x + ((width - len) / 2), y + 1, WHITE, COLOR_NONE, b);
}

void ascii_put_box (box_args b, const wchar_t *fmt, ...)
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

        b.col_border_text = ASCII_UI_BOX_BORDER_ACTIVE;
        b.col_tl = ASCII_UI_BOX_ACTIVE_LEFT_COLOR;
        b.col_mid = ASCII_UI_BOX_ACTIVE_MID_COLOR;
        b.col_br = ASCII_UI_BOX_ACTIVE_RIGHT_COLOR;
    }

    int x = b.x;
    int y = b.y;
    int w = b.width;
    int h = b.height;

    /*
     * Draw the box
     */
    va_start(args, fmt);

    ascii_put_box_(b.x,
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
