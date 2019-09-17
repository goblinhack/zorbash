/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_ascii.h"
#include "my_font.h"
#include "my_game.h"
#include "my_gl.h"
#include "my_time.h"

struct ascii_ ascii;

int ASCII_WIDTH;
int ASCII_HEIGHT;

typedef struct {
    Tilep fg_tile;
    Tilep bg_tile;
    Tilep bg2_tile;

    Texp tex;

    //
    // For background tex
    //
    float tx;
    float ty;
    float dx;
    float dy;

    //
    // For background tex
    //
    float bg2_tx;
    float bg2_ty;
    float bg2_dx;
    float bg2_dy;

    color fg_color_tl;
    color fg_color_bl;
    color fg_color_tr;
    color fg_color_br;
    color bg_color_tl;
    color bg_color_bl;
    color bg_color_tr;
    color bg_color_br;
    color bg2_color_tl;
    color bg2_color_bl;
    color bg2_color_tr;
    color bg2_color_br;

    /*
     * Is reset each frame, and so although a pointer potentially should be
     * zeroed out on game load once it is used.
     */
    void *context;

} ascii_cell;

static ascii_cell cells[ASCII_WIDTH_MAX][ASCII_HEIGHT_MAX];

/*
 * For drawing the mouse cursor.
 */
static fpoint mouse_tile_tl;
static fpoint mouse_tile_br;
static int mouse_found = false;

static point scissors_tl;
static point scissors_br;
static bool scissors_enabled = false;

void ascii_clear_scissors (void)
{
    scissors_enabled = false;
}

void ascii_set_scissors (point tl, point br)
{
    scissors_enabled = true;
    scissors_tl = tl;
    scissors_br = br;
}

void pixel_to_ascii (int *x, int *y)
{
    *x = (int)(floor((float)(*x) / ((float)game->config.video_pix_width / ASCII_WIDTH)));
    *y = (int)(floor((float)(*y) / ((float)game->config.video_pix_height / ASCII_HEIGHT)));
}

static int ascii_ok_for_scissors (int x, int y)
{
    if (scissors_enabled) {
        if ((x < scissors_tl.x) || (x > scissors_br.x)) {
            return (false);
        }

        if ((y < scissors_tl.y) || (y > scissors_br.y)) {
            return (false);
        }
    }

    return (ascii_ok(x, y));
}

void ascii_set_fg (int x, int y, color c)
{
    if (!ascii_ok_for_scissors(x, y)) {
        return;
    }

    ascii_cell *cell = &cells[x][y];

    cell->fg_color_tl = c;
    cell->fg_color_tr = c;
    cell->fg_color_bl = c;
    cell->fg_color_br = c;
}

void ascii_set_bg (int x, int y, color c)
{
    if (!ascii_ok_for_scissors(x, y)) {
        return;
    }

    ascii_cell *cell = &cells[x][y];

    cell->bg_color_tl = c;
    cell->bg_color_tr = c;
    cell->bg_color_bl = c;
    cell->bg_color_br = c;
}

void ascii_set_bg2 (int x, int y, color c)
{
    if (!ascii_ok_for_scissors(x, y)) {
        return;
    }

    ascii_cell *cell = &cells[x][y];

    cell->bg2_color_tl = c;
    cell->bg2_color_tr = c;
    cell->bg2_color_bl = c;
    cell->bg2_color_br = c;
}

void ascii_set_context (int x, int y, void *context)
{
    if (!context) {
        return;
    }

    if (!ascii_ok_for_scissors(x, y)) {
        return;
    }

    ascii_cell *cell = &cells[x][y];

    cell->context = context;
}

void *ascii_get_context (int x, int y)
{
    if (!ascii_ok(x, y)) {
        return (0);
    }

    ascii_cell *cell = &cells[x][y];

    return (cell->context);
}

void ascii_set_bg (int x, int y, const Texp tex, 
                   float tx, float ty, float dx, float dy)
{
    if (!ascii_ok_for_scissors(x, y)) {
        return;
    }

    ascii_cell *cell = &cells[x][y];

    cell->tex = tex;
    cell->tx = tx;
    cell->ty = ty;
    cell->dx = dx;
    cell->dy = dy;
}

void ascii_set_bg (int x, int y, const Tilep tile)
{
    if (!ascii_ok_for_scissors(x, y)) {
        return;
    }

    ascii_cell *cell = &cells[x][y];

    cell->bg_tile = tile;
    cell->tx = 0;
    cell->ty = 0;
    cell->dx = 1;
    cell->dy = 1;
}

void ascii_set_bg2 (int x, int y, const Tilep tile)
{
    if (!ascii_ok_for_scissors(x, y)) {
        return;
    }

    ascii_cell *cell = &cells[x][y];

    cell->bg2_tile = tile;
    cell->bg2_tx = 0;
    cell->bg2_ty = 0;
    cell->bg2_dx = 1;
    cell->bg2_dy = 1;
}

void ascii_set_bg2 (int x, int y, const Tilep tile,
                    float tx, float ty, float dx, float dy)
{
    if (!ascii_ok_for_scissors(x, y)) {
        return;
    }

    ascii_cell *cell = &cells[x][y];

    cell->bg2_tile = tile;
    cell->bg2_tx = tx;
    cell->bg2_ty = ty;
    cell->bg2_dx = dx;
    cell->bg2_dy = dy;
}

void ascii_set_bg (int x, int y, const char *tilename)
{
    ascii_set_bg(x, y, tile_find(tilename));
}

void ascii_set_bg (int x, int y, const wchar_t c)
{
    ascii_set_bg(x, y, fixed_font->unicode_to_tile(c));
}

void ascii_set_bg2 (int x, int y, const char *tilename)
{
    ascii_set_bg2(x, y, tile_find(tilename));
}

void ascii_set_bg2 (int x, int y, const wchar_t c)
{
    ascii_set_bg2(x, y, fixed_font->unicode_to_tile(c));
}

void ascii_set_fg (int x, int y, const Tilep tile)
{
    if (!ascii_ok_for_scissors(x, y)) {
        return;
    }

    ascii_cell *cell = &cells[x][y];

    cell->fg_tile = tile;
}

void ascii_set_fg (int x, int y, const char *tilename)
{
    Tilep tile;

    if (tilename) {
        tile = tile_find(tilename);
        if (!tile) {
            return;
        }
    } else {
        tile = 0;
    }

    ascii_set_fg(x, y, tile);
}

void ascii_set_fg (int x, int y, const wchar_t c)
{
    ascii_set_fg(x, y, fixed_font->unicode_to_tile(c));
}

void ascii_putf__ (int x, int y, color fg, color bg, std::wstring &text)
{_
    Tilep tile;
    int bg_set = false;
    auto text_iter = text.begin();

//printf("ascii_putf__ [%S]/%ld\n", text.c_str(), text.size());
    if (y < 0) {
        return;
    }

    if (y >= ASCII_HEIGHT) {
        return;
    }

    if (bg != COLOR_NONE) {
        bg_set = true;
    }

    while (text_iter != text.end()) {
        auto c = *text_iter;
        text_iter++;

        if (c == L'`') {
            c = L' ';
        }

        if (c == L'%') {
            if (std::string(text_iter, text_iter + 3) == "fg=") {
                text_iter += 3;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                fg = string2color(tmp, &len);
                text_iter += len + 1;
                continue;
            } else if (std::string(text_iter, text_iter + 3) == "bg=") {
                text_iter += 3;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                bg = string2color(tmp, &len);
                text_iter += len + 1;

                bg_set = true;
                continue;
            } else if (std::string(text_iter, text_iter + 3) == "tp=") {
                text_iter += 3;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                auto tp = string2tp(tmp, &len);
                text_iter += len + 1;

                tile = tp_first_tile(tp);
                continue;
            } else if (std::string(text_iter, text_iter + 4) == "tex=") {
                text_iter += 4;
                continue;
            } else if (std::string(text_iter, text_iter + 5) == "tile=") {
                text_iter += 5;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                tile = string2tile(tmp, &len);
                text_iter += len + 1;
                continue;
            }
        }

        if (!ascii_ok_for_scissors(x, y)) {
            x++;
            continue;
        }

        auto is_cursor = (c == ASCII_CURSOR_UCHAR);

        tile = fixed_font->unicode_to_tile(c);
        if (tile == nullptr) {
            tile = fixed_font->unicode_to_tile(L'▋');
            if (tile == nullptr) {
                tile = fixed_font->unicode_to_tile(L'_');
                if (tile == nullptr) {
                    x++;
                    continue;
                }
            }
        }

        auto saved_fg = fg;

        if (is_cursor) {
            static uint32_t last;
            static uint8_t first = true;

            if (first) {
                first = false;
                last = time_get_time_ms_cached();
            }

            if (time_have_x_tenths_passed_since(10, last)) {
                fg = CONSOLE_CURSOR_COLOR;
                last = time_get_time_ms_cached();
            } else if (time_have_x_tenths_passed_since(5, last)) {
                fg = CONSOLE_CURSOR_COLOR;
            } else {
                fg = CONSOLE_CURSOR_OTHER_COLOR;
            }

            tile = fixed_font->unicode_to_tile(L'_');
        }

        ascii_cell *cell = &cells[x++][y];

        cell->fg_tile = tile;

        cell->fg_color_tl = fg;
        cell->fg_color_tr = fg;
        cell->fg_color_bl = fg;
        cell->fg_color_br = fg;

        if (bg_set) {
            if (bg.r || bg.g || bg.b || bg.a) {
                static Tilep tile;
                if (!tile) {
                    tile = tile_find_mand("CSPACE");
                }
                cell->bg_tile = tile;
            } else {
                cell->bg_tile = 0;
            }

            cell->bg_color_tl = bg;
            cell->bg_color_tr = bg;
            cell->bg_color_bl = bg;
            cell->bg_color_br = bg;
        }

        if (is_cursor) {
            fg = saved_fg;
        }
    }
}

int ascii_strlen (std::wstring &text)
{_
    auto text_iter = text.begin();
    int x = 0;

    while (text_iter != text.end()) {
        auto c = *text_iter;
        text_iter++;

        if (c == L'`') {
            c = L' ';
        }

        if (c == L'%') {
            if (text_iter != text.end()) {
                if (*text_iter == L'%') {
                    text_iter++;
                }
            }

            if (std::string(text_iter, text_iter + 3) == "fg=") {
                text_iter += 3;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                (void) string2color(tmp, &len);
                text_iter += len + 1;
                continue;
            } else if (std::string(text_iter, text_iter + 3) == "bg=") {
                text_iter += 3;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                (void) string2color(tmp, &len);
                text_iter += len + 1;

                continue;
            } else if (std::string(text_iter, text_iter + 3) == "tp=") {
                text_iter += 3;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                (void) string2tp(tmp, &len);
                text_iter += len + 1;

                continue;
            } else if (std::string(text_iter, text_iter + 4) == "tex=") {
                text_iter += 4;
                continue;
            } else if (std::string(text_iter, text_iter + 5) == "tile=") {
                text_iter += 5;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                (void) string2tile(tmp, &len);
                text_iter += len + 1;
                continue;
            }
        }

        x++;
    }

    return (x);
}

int ascii_strlen (std::wstring &text, std::wstring *col)
{_
    auto text_iter = text.begin();
    int x = 0;

    for (;;) {
        auto c = *text_iter;
        text_iter++;

        if (c == L'\0') {
            break;
        }

        if (c == L'`') {
            c = L' ';
        }

        if (c == L'%') {
            if (text_iter != text.end()) {
                if (*text_iter == L'%') {
                    text_iter++;
                }
            }

            if (std::string(text_iter, text_iter + 3) == "fg=") {
                text_iter += 3;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                (void) string2color(tmp, &len);
                text_iter += len + 1;
                continue;
            } else if (std::string(text_iter, text_iter + 3) == "bg=") {
                text_iter += 3;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                (void) string2color(tmp, &len);
                text_iter += len + 1;

                continue;
            } else if (std::string(text_iter, text_iter + 3) == "tp=") {
                text_iter += 3;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                (void) string2tp(tmp, &len);
                text_iter += len + 1;

                continue;
            } else if (std::string(text_iter, text_iter + 4) == "tex=") {
                text_iter += 4;
                continue;
            } else if (std::string(text_iter, text_iter + 5) == "tile=") {
                text_iter += 5;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                (void) string2tile(tmp, &len);
                text_iter += len + 1;
                continue;
            }
        }

        x++;
    }

    return (x);
}

static void ascii_putf_ (int x, int y,
                         color fg,
                         color bg,
                         std::wstring fmt, va_list args)
{_
    wchar_t buf[MAXSHORTSTR];

    auto wrote = vswprintf(buf, MAXSHORTSTR, fmt.c_str(), args);

    /*
     * Only a single nul is written, but as we read 2 at a time...
     */
    if (wrote && (wrote < MAXSHORTSTR - 1)) {
        buf[wrote+1] = '\0';
    }

    auto b = std::wstring(buf);

    ascii_putf__(x, y, fg, bg, b);
}

static void ascii_putf_ (int x, int y,
                         color fg,
                         color bg,
                         const wchar_t *fmt, va_list args)
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

    ascii_putf__(x, y, fg, bg, b);
}

void ascii_putf (int x, int y, const wchar_t *fmt, ...)
{_
    va_list args;

    va_start(args, fmt);
    ascii_putf_(x, y, WHITE, COLOR_NONE, fmt, args);
    va_end(args);
}

void ascii_putf (int x, int y, color fg, const wchar_t *fmt, ...)
{_
    va_list args;

    va_start(args, fmt);
    ascii_putf_(x, y, fg, COLOR_NONE, fmt, args);
    va_end(args);
}

void ascii_putf (int x, int y, color fg, color bg, const wchar_t *fmt, ...)
{_
    va_list args;

    va_start(args, fmt);
    ascii_putf_(x, y, fg, bg, fmt, args);
    va_end(args);
}

void ascii_putf (int x, int y, std::wstring fmt, ...)
{_
    va_list args;

    va_start(args, fmt);
    ascii_putf_(x, y, WHITE, COLOR_NONE, fmt, args);
    va_end(args);
}

void ascii_putf (int x, int y, color fg, std::wstring fmt, ...)
{_
    va_list args;

    va_start(args, fmt);
    ascii_putf_(x, y, fg, COLOR_NONE, fmt, args);
    va_end(args);
}

void ascii_putf (int x, int y, color fg, color bg, std::wstring fmt, ...)
{_
    va_list args;

    va_start(args, fmt);
    ascii_putf_(x, y, fg, bg, fmt, args);
    va_end(args);
}

#ifdef ENABLE_ASCII_MOUSE
static void ascii_display_mouse (fpoint mouse_tile_tl,
                                 fpoint mouse_tile_br,
                                 point mouse_at)
{_
    static uint32_t ts;
    static int alpha = 100;

    if (time_have_x_hundredths_passed_since(5, ts)) {
        static int alpha_mod = 1;

        alpha += alpha_mod;

        if (alpha > 255) {
            alpha = 255;
            alpha_mod = -1;
        }

        if (alpha < 150) {
            alpha = 150;
            alpha_mod = 1;
        }
    }

    color c = CONSOLE_CURSOR_OTHER_COLOR;
    c.a = alpha;
    glcolor(c);

    glBindTexture(GL_TEXTURE_2D, 0);

    gl_blitsquare(mouse_tile_tl.x, mouse_tile_tl.y,
                  mouse_tile_br.x, mouse_tile_br.y);

    /*
     * Save where we are at
     */
    ascii.mouse_at = mouse_at;
}
#endif

void ascii_put_bg_square (int tlx, int tly, int brx, int bry,
                          Tilep tile, color c)
{_
    int x;
    int y;

    for (x = tlx; x <= brx; x++) {
        for (y = tly; y <= bry; y++) {
            ascii_set_bg(x, y, tile);
            ascii_set_bg(x, y, c);
        }
    }
}

void ascii_put_bg_square (int tlx, int tly, int brx, int bry,
                          const char *tilename, color c)
{_
    ascii_put_bg_square (tlx, tly, brx, bry, tile_find(tilename), c);
}

void ascii_put_bg_square (int tlx, int tly, int brx, int bry,
                          wchar_t what, color c)
{_
    ascii_put_bg_square (tlx, tly, brx, bry,
                         fixed_font->unicode_to_tile(what), c);
}

void ascii_put_shaded_line (int x1, int x2, int y,
                            Tilep tile,
                            color col_tl, color col_mid, color col_br,
                            void *context)
{_
    int x;
    int w = 5;

    for (x = x1; x <= x2; x++) {
        ascii_set_bg(x, y, tile);
        ascii_set_bg(x, y, col_mid);
    }

    color c;
    auto put_on_lhs = 0;
    float d = 0.0;
    float d_scale = 2;
    float e_min = 0.25;

    for (x = x1, d = 1.0; x < x1 + w; d /= d_scale, x++) {
        float e = 1.0 - d;
        e = fmax(e_min, e);
        c = col_tl;
        c.a = 255.0 * e;
        ascii_set_bg(x, y, c);
        put_on_lhs++;
    }

    for (x = x2 - 1, d = 1.0; put_on_lhs > 0; d /= d_scale, x--, put_on_lhs--) {
        float e = 1.0 - d;
        e = fmax(e_min, e);
        c = col_br;
        c.a = 255.0 * e;
        ascii_set_bg(x, y, c);
    }

    for (x = x1; x <= x2; x++) {
        ascii_set_context(x, y, context);
    }
}

void ascii_put_shaded_line (int x1, int x2, int y, const char *tilename,
                            color col_tl, color col_mid, color col_br,
                            void *context)
{_
    ascii_put_shaded_line(x1, x2, y, tile_find(tilename), col_tl, col_mid, col_br,
                          context);
}

void ascii_put_shaded_line (int x1, int x2, int y, wchar_t c,
                            color col_tl, color col_mid, color col_br,
                            void *context)
{_
    ascii_put_shaded_line(x1, x2, y, fixed_font->unicode_to_tile(c),
                          col_tl, col_mid, col_br, context);
}

void ascii_put_solid_line (int x1, int x2, int y, Tilep tile, color col,
                           void *context)
{_
    for (auto x = x1; x <= x2; x++) {
        ascii_set_bg(x, y, tile);
        ascii_set_bg(x, y, col);
    }
}

void ascii_put_solid_line (int x1, int x2, int y, const char *tilename,
                            color col, void *context)
{_
    ascii_put_solid_line(x1, x2, y, tile_find(tilename), col, context);
}

void ascii_put_solid_line (int x1, int x2, int y, wchar_t c, color col,
                           void *context)
{_
    ascii_put_solid_line(x1, x2, y, fixed_font->unicode_to_tile(c), col,
                         context);
}

static void ascii_map_thing_replace (int x, int y, Tilep tile, color c)
{_
    ascii_set_bg(x, y, tile);
    ascii_set_bg(x, y, c);
}

static void do_ascii_line (int x0_in, int y0_in, int x1_in, int y1_in,
                           int flag, Tilep tile, color c)
{_
    float temp;
    float dx;
    float dy;
    float tdy;
    float dydx;
    float p;
    float x;
    float y;
    float i;

    float x0 = x0_in;
    float y0 = y0_in;
    float x1 = x1_in;
    float y1 = y1_in;

    if (x0 > x1) {
        temp = x0;
        x0 = x1;
        x1 = temp;

        temp = y0;
        y0 = y1;
        y1 = temp;
    }

    dx = x1 - x0;
    dy = y1 - y0;

    tdy = 2.0 * dy;
    dydx = tdy - (2.0 * dx);

    p = tdy - dx;
    x = x0;
    y = y0;

    if (flag == 0) {
        ascii_map_thing_replace((int)x, (int)y, tile, c);
    } else if (flag == 1) {
        ascii_map_thing_replace((int)y, (int)x, tile, c);
    } else if (flag == 2) {
        ascii_map_thing_replace((int)y, (int)-x, tile, c);
    } else if (flag == 3) {
        ascii_map_thing_replace((int)x, (int)-y, tile, c);
    }

    for (i = 1; i <= dx; i++){
        x++;

        if (p < 0) {
            p += tdy;
        } else {
            p += dydx;
            y++;
        }

        if (flag == 0) {
            ascii_map_thing_replace((int)x, (int)y, tile, c);
        } else if (flag == 1) {
            ascii_map_thing_replace((int)y, (int)x, tile, c);
        } else if (flag == 2) {
            ascii_map_thing_replace((int)y, (int)-x, tile, c);
        } else if (flag == 3) {
            ascii_map_thing_replace((int)x, (int)-y, tile, c);
        }
    }
}

void ascii_draw_line (int x0, int y0, int x1, int y1, Tilep tile, color c)
{_
    float slope = 100.0;

    if (x0 != x1) {
        slope = (y1 - y0) * (1.0 / (x1 - x0));
    }

    if ((0 <= slope) && (slope <= 1)) {
        do_ascii_line(x0, y0, x1, y1, 0, tile, c);
    } else if ((-1 <= slope) && (slope <= 0)) {
        do_ascii_line(x0, -y0, x1, -y1, 3, tile, c);
    } else if (slope > 1) {
        do_ascii_line(y0, x0, y1, x1, 1, tile, c);
    } else {
        do_ascii_line(-y0, x0, -y1, x1, 2, tile, c);
    }
}

void ascii_draw_line (int x0, int y0, int x1, int y1, wchar_t what, color c)
{_
    ascii_draw_line (x0, y0, x1, y1, fixed_font->unicode_to_tile(what), c);
}

void ascii_draw_line (int x0, int y0, int x1, int y1,
                      const char *tilename, color c)
{_
    ascii_draw_line (x0, y0, x1, y1, tile_find(tilename), c);
}

/*
 * Display one z layer of the ascii.
 */
static void ascii_blit (int no_color)
{_
    /*
     * Get the mouse position to use. We use this to find the mouse tile that
     * we are over.
     */
    int x;
    int y;
    float tile_x;
    float tile_y;

    glcolor(WHITE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    tile_y = 0;
    for (y = 0; y < ASCII_HEIGHT; y++) {

        tile_x = 0;
        for (x = 0; x < ASCII_WIDTH; x++) {

            const ascii_cell *cell = &cells[x][y];

            fpoint tile_tl;
            fpoint tile_br;

            tile_tl.x = tile_x;
            tile_tl.y = tile_y;
            tile_br.x = tile_x + game->config.ascii_gl_width;
            tile_br.y = tile_y + game->config.ascii_gl_height;

            int mx1 = tile_tl.x * game->config.video_pix_width;
            int my1 = tile_tl.y * game->config.video_pix_height;
            int mx2 = tile_br.x * game->config.video_pix_width;
            int my2 = tile_br.y * game->config.video_pix_height;

            if (!mouse_found) {
                if ((mx1 < mouse_x) &&
                    (my1 < mouse_y) &&
                    (mx2 >= mouse_x) &&
                    (my2 >= mouse_y)) {
                    mouse_found = true;

                    mouse_tile_tl = tile_tl;
                    mouse_tile_br = tile_br;

                    ascii.mouse_at = point(x, y);
                }
            }

            /*
             * Background
             */
            if (cell->tex) {
		Texp tex = cell->tex;

		blit(tex_get_gl_binding(tex),
                     cell->tx,
                     cell->ty,
                     cell->tx + cell->dx,
                     cell->ty + cell->dy,
                     tile_tl.x,
                     tile_tl.y,
                     tile_br.x,
                     tile_br.y);
            } else if (cell->bg_tile) {
                color bg_color_tl = cell->bg_color_tl;
                color bg_color_tr = cell->bg_color_tr;
                color bg_color_bl = cell->bg_color_bl;
                color bg_color_br = cell->bg_color_br;

                if (no_color) {
                    bg_color_tl = color_to_mono(bg_color_tl);
                    bg_color_tr = color_to_mono(bg_color_tr);
                    bg_color_bl = color_to_mono(bg_color_bl);
                    bg_color_br = color_to_mono(bg_color_br);
                }

                tile_blit_colored_fat(0,
                                      cell->bg_tile,
                                      tile_tl,
                                      tile_br,
                                      bg_color_tl,
                                      bg_color_tr,
                                      bg_color_bl,
                                      bg_color_br);
            }

            tile_x += game->config.ascii_gl_width;
        }

        tile_y += game->config.ascii_gl_height;
    }

    //
    // Tiles outline
    // 
    tile_y = 0;
    for (y = 0; y < ASCII_HEIGHT; y++) {

        tile_x = 0;
        for (x = 0; x < ASCII_WIDTH; x++) {

            const ascii_cell *cell = &cells[x][y];

            fpoint tile_tl;
            fpoint tile_br;

            tile_tl.x = tile_x;
            tile_tl.y = tile_y;
            tile_br.x = tile_x + game->config.ascii_gl_width;
            tile_br.y = tile_y + game->config.ascii_gl_height;

            if (cell->bg2_tile) {
                color bg2_color_tl = cell->bg2_color_tl;
                color bg2_color_tr = cell->bg2_color_tr;
                color bg2_color_bl = cell->bg2_color_bl;
                color bg2_color_br = cell->bg2_color_br;

                if (no_color) {
                    bg2_color_tl = color_to_mono(bg2_color_tl);
                    bg2_color_tr = color_to_mono(bg2_color_tr);
                    bg2_color_bl = color_to_mono(bg2_color_bl);
                    bg2_color_br = color_to_mono(bg2_color_br);
                }

                tile_blit_outline_section_colored(
                   nullptr, 
                   cell->bg2_tile,
                   fpoint(cell->bg2_tx, cell->bg2_ty),
                   fpoint(cell->bg2_tx + cell->bg2_dx, 
                          cell->bg2_ty + cell->bg2_dy),
                   tile_tl, tile_br,
                   bg2_color_tl,
                   bg2_color_tr,
                   bg2_color_bl,
                   bg2_color_br,
                   0.05 / cell->bg2_dx);
            }

            tile_x += game->config.ascii_gl_width;
        }

        tile_y += game->config.ascii_gl_height;
    }

    //
    // Tiles
    // 
    tile_y = 0;
    for (y = 0; y < ASCII_HEIGHT; y++) {

        tile_x = 0;
        for (x = 0; x < ASCII_WIDTH; x++) {

            const ascii_cell *cell = &cells[x][y];

            fpoint tile_tl;
            fpoint tile_br;

            tile_tl.x = tile_x;
            tile_tl.y = tile_y;
            tile_br.x = tile_x + game->config.ascii_gl_width;
            tile_br.y = tile_y + game->config.ascii_gl_height;

            if (cell->bg2_tile) {
                color bg2_color_tl = cell->bg2_color_tl;
                color bg2_color_tr = cell->bg2_color_tr;
                color bg2_color_bl = cell->bg2_color_bl;
                color bg2_color_br = cell->bg2_color_br;

                if (no_color) {
                    bg2_color_tl = color_to_mono(bg2_color_tl);
                    bg2_color_tr = color_to_mono(bg2_color_tr);
                    bg2_color_bl = color_to_mono(bg2_color_bl);
                    bg2_color_br = color_to_mono(bg2_color_br);
                }

                tile_blit_section_colored(
                   nullptr, 
                   cell->bg2_tile,
                   fpoint(cell->bg2_tx, cell->bg2_ty),
                   fpoint(cell->bg2_tx + cell->bg2_dx, 
                          cell->bg2_ty + cell->bg2_dy),
                   tile_tl, tile_br,
                   bg2_color_tl,
                   bg2_color_tr,
                   bg2_color_bl,
                   bg2_color_br);
            }

            tile_x += game->config.ascii_gl_width;
        }

        tile_y += game->config.ascii_gl_height;
    }

    tile_y = 0;
    for (y = 0; y < ASCII_HEIGHT; y++) {

        tile_x = 0;
        for (x = 0; x < ASCII_WIDTH; x++) {

            const ascii_cell *cell = &cells[x][y];

            fpoint tile_tl;
            fpoint tile_br;

            tile_tl.x = tile_x;
            tile_tl.y = tile_y;
            tile_br.x = tile_x + game->config.ascii_gl_width;
            tile_br.y = tile_y + game->config.ascii_gl_height;

            /*
             * Foreground
             */
            {
                tile_br.x = tile_x + game->config.ascii_gl_width;
                Tilep tile = cell->fg_tile;

                if (tile) {
                    color fg_color_tl = cell->fg_color_tl;
                    color fg_color_tr = cell->fg_color_tr;
                    color fg_color_bl = cell->fg_color_bl;
                    color fg_color_br = cell->fg_color_br;

                    if (no_color) {
                        fg_color_tl = color_to_mono(fg_color_tl);
                        fg_color_tr = color_to_mono(fg_color_tr);
                        fg_color_bl = color_to_mono(fg_color_bl);
                        fg_color_br = color_to_mono(fg_color_br);
                    }

                    tile_blit_colored_fat(0,
                                          tile,
                                          tile_tl,
                                          tile_br,
                                          fg_color_tl,
                                          fg_color_tr,
                                          fg_color_bl,
                                          fg_color_br);
                }
            }

            tile_x += game->config.ascii_gl_width;
        }

        tile_y += game->config.ascii_gl_height;
    }
}

/*
 * The big ascii renderer
 */
void ascii_display (void)
{_
    mouse_found = false;

    blit_init();
    ascii_blit(false /* no color */);
    blit_flush();

#ifdef ENABLE_ASCII_MOUSE
    if (mouse_found) {
        ascii_display_mouse(mouse_tile_tl, mouse_tile_br, ascii.mouse_at);
    }
#endif

    memset(cells, 0, sizeof(cells));
}
