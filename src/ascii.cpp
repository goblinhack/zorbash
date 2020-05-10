//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

// REMOVED #include "my_main.h"
#include "my_ascii.h"
#include "my_font.h"
// REMOVED #include "my_time.h"
#include "my_game.h"
#include "my_gl.h"
#include "my_thing_template.h"

struct ascii_ ascii;

int ASCII_WIDTH;
int ASCII_HEIGHT;

class AsciiCell {
public:
    Tilep fg_tile {};
    Tilep fg2_tile {};
    Tilep bg_tile {};
    Tilep bg2_tile {};

    Texp tex {};

    //
    // For background tex
    //
    float tx {};
    float ty {};
    float dx {};
    float dy {};

    //
    // For background tex
    //
    float bg2_tx {};
    float bg2_ty {};
    float bg2_dx {};
    float bg2_dy {};
    float fg2_tx {};
    float fg2_ty {};
    float fg2_dx {};
    float fg2_dy {};

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
    color fg2_color_tl;
    color fg2_color_bl;
    color fg2_color_tr;
    color fg2_color_br;

    //
    // Is reset each frame, and so although a pointer potentially should be
    // zeroed out on game load once it is used.
    //
    void *context {};

    AsciiCell(void) {}
};

static std::vector<std::vector<AsciiCell> > cells;

void ascii_init (void)
{
    cells.resize(ASCII_WIDTH_MAX);
    for (auto x = 0; x < ASCII_WIDTH_MAX; x++) {
        cells[x].resize(ASCII_HEIGHT_MAX);
    }
}

//
// For drawing the mouse cursor.
//
static spoint mouse_tile_tl;
static spoint mouse_tile_br;
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
    *x = (int)(floor((float)(*x) / ((float)game->config.outer_pix_width / ASCII_WIDTH)));
    *y = (int)(floor((float)(*y) / ((float)game->config.outer_pix_height / ASCII_HEIGHT)));
}

static int ascii_ok_for_scissors (int x, int y)
{
    if ((x < 0) || (y < 0) || (x >= ASCII_WIDTH) || (y >= ASCII_HEIGHT)) {
        return (false);
    }

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

    AsciiCell *cell = &getref(cells, x, y);

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

    AsciiCell *cell = &getref(cells, x, y);

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

    AsciiCell *cell = &getref(cells, x, y);

    cell->bg2_color_tl = c;
    cell->bg2_color_tr = c;
    cell->bg2_color_bl = c;
    cell->bg2_color_br = c;
}

void ascii_set_fg2 (int x, int y, color c)
{
    if (!ascii_ok_for_scissors(x, y)) {
        return;
    }

    AsciiCell *cell = &getref(cells, x, y);

    cell->fg2_color_tl = c;
    cell->fg2_color_tr = c;
    cell->fg2_color_bl = c;
    cell->fg2_color_br = c;
}

void ascii_set_context (int x, int y, void *context)
{
    if (!context) {
        return;
    }

    if (!ascii_ok_for_scissors(x, y)) {
        return;
    }

    AsciiCell *cell = &getref(cells, x, y);

    cell->context = context;
}

void *ascii_get_context (int x, int y)
{
    if (!ascii_ok(x, y)) {
        return (0);
    }

    AsciiCell *cell = &getref(cells, x, y);

    return (cell->context);
}

void ascii_set_bg (int x, int y, const Texp tex,
                   float tx, float ty, float dx, float dy)
{
    if (!ascii_ok_for_scissors(x, y)) {
        return;
    }

    AsciiCell *cell = &getref(cells, x, y);

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

    AsciiCell *cell = &getref(cells, x, y);

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

    AsciiCell *cell = &getref(cells, x, y);

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

    AsciiCell *cell = &getref(cells, x, y);

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

void ascii_set_fg (int x, int y, const Texp tex,
                   float tx, float ty, float dx, float dy)
{
    if (!ascii_ok_for_scissors(x, y)) {
        return;
    }

    AsciiCell *cell = &getref(cells, x, y);

    cell->tex = tex;
    cell->tx = tx;
    cell->ty = ty;
    cell->dx = dx;
    cell->dy = dy;
}

void ascii_set_fg (int x, int y, const Tilep tile)
{
    if (!ascii_ok_for_scissors(x, y)) {
        return;
    }

    AsciiCell *cell = &getref(cells, x, y);

    cell->fg_tile = tile;
    cell->tx = 0;
    cell->ty = 0;
    cell->dx = 1;
    cell->dy = 1;
}

void ascii_set_fg2 (int x, int y, const Tilep tile)
{
    if (!ascii_ok_for_scissors(x, y)) {
        return;
    }

    AsciiCell *cell = &getref(cells, x, y);

    cell->fg2_tile = tile;
    cell->fg2_tx = 0;
    cell->fg2_ty = 0;
    cell->fg2_dx = 1;
    cell->fg2_dy = 1;
}

void ascii_set_fg2 (int x, int y, const Tilep tile,
                    float tx, float ty, float dx, float dy)
{
    if (!ascii_ok_for_scissors(x, y)) {
        return;
    }

    AsciiCell *cell = &getref(cells, x, y);

    cell->fg2_tile = tile;
    cell->fg2_tx = tx;
    cell->fg2_ty = ty;
    cell->fg2_dx = dx;
    cell->fg2_dy = dy;
}

void ascii_set_fg (int x, int y, const char *tilename)
{
    ascii_set_fg(x, y, tile_find(tilename));
}

void ascii_set_fg (int x, int y, const wchar_t c)
{
    ascii_set_fg(x, y, fixed_font->unicode_to_tile(c));
}

void ascii_set_fg2 (int x, int y, const char *tilename)
{
    ascii_set_fg2(x, y, tile_find(tilename));
}

void ascii_set_fg2 (int x, int y, const wchar_t c)
{
    ascii_set_fg2(x, y, fixed_font->unicode_to_tile(c));
}

void ascii_putf__ (int x, int y, color fg, color bg, std::wstring const& text)
{_
    Tilep tile;
    int bg_set = false;
    auto text_iter = text.begin();

// printf("ascii_putf__ [%S]/%ld scissors x %d y %d scissors %d %d %d %d %d\n", text.c_str(), text.size(), x, y, scissors_tl.x, scissors_tl.y, scissors_br.x, scissors_br.y, scissors_enabled);
    if (unlikely(y < 0)) {
        return;
    }

    if (unlikely(y >= ASCII_HEIGHT)) {
        return;
    }

    if (bg != COLOR_NONE) {
        bg_set = true;
    }

    tile = nullptr;

    while (text_iter != text.end()) {
        auto c = *text_iter;
        text_iter++;

        if (unlikely(c == L'%')) {
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
                text_iter += len;

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
                text_iter += len;
                continue;
            }
            continue;
        }

        if (unlikely(!ascii_ok_for_scissors(x, y))) {
            x++;
            continue;
        }

        if (!tile) {
            tile = fixed_font->unicode_to_tile(c);
            if (tile == nullptr) {
                tile = tile_find_mand(ASCII_UNKNOWN_TILE);
            }
        }

        auto saved_fg = fg;

        auto is_cursor = (c == ASCII_CURSOR_UCHAR);
        if (unlikely(is_cursor)) {
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
        }

        AsciiCell *cell = &getref(cells, x++, y);

        cell->fg_tile = tile;

        cell->fg_color_tl = fg;
        cell->fg_color_tr = fg;
        cell->fg_color_bl = fg;
        cell->fg_color_br = fg;

        if (bg_set) {
            if (bg.r || bg.g || bg.b || bg.a) {
                static Tilep tile;
                if (!tile) {
                    tile = tile_find_mand(ASCII_CURSOR_TILE);
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

        if (unlikely(is_cursor)) {
            fg = saved_fg;
        }

        tile = nullptr;
    }
}

int ascii_strlen (std::wstring const& text)
{_
    auto text_iter = text.begin();
    int x = 0;

    while (text_iter != text.end()) {
        auto c = *text_iter;
        text_iter++;

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

int ascii_strlen (std::wstring const& text, std::wstring *col)
{_
    auto text_iter = text.begin();
    int x = 0;

    for (;;) {
        auto c = *text_iter;
        text_iter++;

        if (c == L'\0') {
            break;
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

std::string ascii_strip (std::string const& text)
{_
    auto text_iter = text.begin();
    int x = 0;
    std::string out;

    for (;;) {
        auto c = *text_iter;
        text_iter++;

        if (c == '\0') {
            break;
        }

        if (c == '%') {
            if (text_iter != text.end()) {
                if (*text_iter == '%') {
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
                text_iter += len;
                continue;
            } else if (std::string(text_iter, text_iter + 4) == "tex=") {
                text_iter += 4;
                continue;
            } else if (std::string(text_iter, text_iter + 5) == "tile=") {
                text_iter += 5;
                auto tmp = std::string(text_iter, text.end());
                int len = 0;
                (void) string2tile(tmp, &len);
                text_iter += len;
                continue;
            }
        }
        out += c;
        x++;
    }
    return (out);
}

static void ascii_putf_ (int x, int y,
                         color fg,
                         color bg,
                         std::wstring const& fmt, va_list args)
{_
    wchar_t buf[MAXSHORTSTR];

    auto wrote = vswprintf(buf, MAXSHORTSTR, fmt.c_str(), args);

    //
    // Only a single nul is written, but as we read 2 at a time...
    //
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

    //
    // Only a single nul is written, but as we read 2 at a time...
    //
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
static void ascii_display_mouse (spoint mouse_tile_tl,
                                 spoint mouse_tile_br,
                                 point mouse_at)
{_
    glcolor(GREEN);

    blit_init();
    tile_blit(tile_find_mand("C97"),
              spoint(mouse_tile_tl.x, mouse_tile_tl.y),
              spoint(mouse_tile_br.x, mouse_tile_br.y));
    blit_flush();
    //
    // Save where we are at
    //
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
    ascii_put_bg_square(tlx, tly, brx, bry, tile_find(tilename), c);
}

void ascii_put_bg_square (int tlx, int tly, int brx, int bry,
                          wchar_t what, color c)
{_
    ascii_put_bg_square(tlx, tly, brx, bry,
                        fixed_font->unicode_to_tile(what), c);
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

//
// Display one z layer of the ascii.
//
static void ascii_blit (void)
{_
    //
    // Get the mouse position to use. We use this to find the mouse tile that
    // we are over.
    //
    int x;
    int y;
    float tile_x;
    float tile_y;

    glcolor(WHITE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float mx = mouse_x;
    float my = mouse_y;

    tile_y = 0;
    for (y = 0; y < ASCII_HEIGHT; y++) {

        tile_x = 0;
        for (x = 0; x < ASCII_WIDTH; x++) {

            const AsciiCell *cell = &getref(cells, x, y);

            spoint tile_tl;
            spoint tile_br;

            tile_tl.x = tile_x;
            tile_tl.y = tile_y;
            tile_br.x = tile_x + game->config.ascii_gl_width;
            tile_br.y = tile_y + game->config.ascii_gl_height;

            if (!mouse_found) {
                if ((mx < tile_br.x) &&
                    (my < tile_br.y) &&
                    (mx >= tile_tl.x) &&
                    (my >= tile_tl.y)) {
                    mouse_found = true;

                    mouse_tile_tl = tile_tl;
                    mouse_tile_br = tile_br;

                    ascii.mouse_at = point(x, y);
                }
            }

            //
            // Background
            //
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
#if 0
    tile_y = 0;
    for (y = 0; y < ASCII_HEIGHT; y++) {

        tile_x = 0;
        for (x = 0; x < ASCII_WIDTH; x++) {

            const AsciiCell *cell = &getref(cells, x, y);

            spoint tile_tl;
            spoint tile_br;

            tile_tl.x = tile_x;
            tile_tl.y = tile_y;
            tile_br.x = tile_x + game->config.ascii_gl_width;
            tile_br.y = tile_y + game->config.ascii_gl_height;

            if (cell->bg2_tile) {
                color bg2_color_tl = cell->bg2_color_tl;
                color bg2_color_tr = cell->bg2_color_tr;
                color bg2_color_bl = cell->bg2_color_bl;
                color bg2_color_br = cell->bg2_color_br;

                tile_blit_outline_section_colored(
                   cell->bg2_tile,
                   spoint(cell->bg2_tx, cell->bg2_ty),
                   spoint(cell->bg2_tx + cell->bg2_dx,
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
#endif

    //
    // Tiles
    //
    tile_y = 0;
    for (y = 0; y < ASCII_HEIGHT; y++) {

        tile_x = 0;
        for (x = 0; x < ASCII_WIDTH; x++) {

            const AsciiCell *cell = &getref(cells, x, y);

            spoint tile_tl;
            spoint tile_br;

            tile_tl.x = tile_x;
            tile_tl.y = tile_y;
            tile_br.x = tile_x + game->config.ascii_gl_width;
            tile_br.y = tile_y + game->config.ascii_gl_height;

            if (cell->bg2_tile) {
                color bg2_color_tl = cell->bg2_color_tl;
                color bg2_color_tr = cell->bg2_color_tr;
                color bg2_color_bl = cell->bg2_color_bl;
                color bg2_color_br = cell->bg2_color_br;

                tile_blit_section_colored(
                   cell->bg2_tile,
                   spoint(cell->bg2_tx, cell->bg2_ty),
                   spoint(cell->bg2_tx + cell->bg2_dx,
                          cell->bg2_ty + cell->bg2_dy),
                   tile_tl, tile_br,
                   bg2_color_tl,
                   bg2_color_tr,
                   bg2_color_bl,
                   bg2_color_br);
            }

            if (cell->fg2_tile) {
                color fg2_color_tl = cell->fg2_color_tl;
                color fg2_color_tr = cell->fg2_color_tr;
                color fg2_color_bl = cell->fg2_color_bl;
                color fg2_color_br = cell->fg2_color_br;

                tile_blit_section_colored(
                   cell->fg2_tile,
                   spoint(cell->fg2_tx, cell->fg2_ty),
                   spoint(cell->fg2_tx + cell->fg2_dx,
                          cell->fg2_ty + cell->fg2_dy),
                   tile_tl, tile_br,
                   fg2_color_tl,
                   fg2_color_tr,
                   fg2_color_bl,
                   fg2_color_br);
            }

            tile_x += game->config.ascii_gl_width;
        }

        tile_y += game->config.ascii_gl_height;
    }

    tile_y = 0;
    for (y = 0; y < ASCII_HEIGHT; y++) {

        tile_x = 0;
        for (x = 0; x < ASCII_WIDTH; x++) {
            const AsciiCell *cell = &getref(cells, x, y);

            spoint tile_tl;
            spoint tile_br;

            tile_tl.x = tile_x;
            tile_tl.y = tile_y;
            tile_br.x = tile_x + game->config.ascii_gl_width;
            tile_br.y = tile_y + game->config.ascii_gl_height;

            //
            // Foreground
            //
            {
                tile_br.x = tile_x + game->config.ascii_gl_width;
                Tilep tile = cell->fg_tile;

                if (tile) {
                    color fg_color_tl = cell->fg_color_tl;
                    color fg_color_tr = cell->fg_color_tr;
                    color fg_color_bl = cell->fg_color_bl;
                    color fg_color_br = cell->fg_color_br;

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

//
// The big ascii renderer
//
void ascii_display (void)
{_
    mouse_found = false;

    blit_init();
    ascii_blit();
    blit_flush();

#ifdef ENABLE_ASCII_MOUSE
    if (mouse_found) {
        ascii_display_mouse(mouse_tile_tl, mouse_tile_br, ascii.mouse_at);
    }
#endif

    for (auto y = 0; y < ASCII_HEIGHT; y++) {
        for (auto x = 0; x < ASCII_WIDTH; x++) {
            AsciiCell *cell = &getref(cells, x, y);
            *cell = {};
        }
    }
}
