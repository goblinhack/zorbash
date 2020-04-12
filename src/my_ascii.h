//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include <wchar.h>
#include "my_point.h"
#include "my_color.h"

class Tile;
typedef class Tile* Tilep;
class Tex;
typedef class Tex* Texp;

typedef int (*ascii_key_down_callback)(int x, int y, const struct SDL_KEYSYM * key);
typedef int (*ascii_mouse_down_callback)(int x, int y, int button);
typedef int (*ascii_mouse_over_callback)(int x, int y);

struct ascii_ {
    //
    // In ascii mode, where on the ASCII we are
    //
    point mouse_at;
    //
    // UI triggers for ASCII co-ords.
    //
    std::array<std::array<int32_t,
                    ASCII_HEIGHT_MAX>, ASCII_WIDTH_MAX> sdl_mod {};
    std::array<std::array<int32_t,
                    ASCII_HEIGHT_MAX>, ASCII_WIDTH_MAX> sdl_key {};
    std::array<std::array<int32_t,
                    ASCII_HEIGHT_MAX>, ASCII_WIDTH_MAX> mouse_button {};

    //
    // Callbacks for ASCII co-ords.
    //
    std::array<
      std::array<ascii_key_down_callback, ASCII_HEIGHT_MAX>,
                    ASCII_WIDTH_MAX> key_down {};
    std::array<
      std::array<ascii_mouse_down_callback, ASCII_HEIGHT_MAX>,
                    ASCII_WIDTH_MAX> mouse_down {};
    std::array<
      std::array<ascii_mouse_over_callback, ASCII_HEIGHT_MAX>,
                    ASCII_WIDTH_MAX> mouse_over {};
};

extern struct ascii_ ascii;

extern int ASCII_WIDTH;
extern int ASCII_HEIGHT;
extern void ascii_init(void);

void pixel_to_ascii(int *x, int *y);

void ascii_set_bg(int x, int y, Texp, float tx, float ty, float dx, float dy);
void ascii_set_bg(int x, int y, Tilep);
void ascii_set_bg(int x, int y, color c);
void ascii_set_bg(int x, int y, const char *tilename);
void ascii_set_bg(int x, int y, const wchar_t c);
void ascii_set_bg2(int x, int y, Tilep);
void ascii_set_bg2(int x, int y, Tilep, float tx, float ty, float dx, float dy);
void ascii_set_bg2(int x, int y, color c);
void ascii_set_fg(int x, int y, Texp, float tx, float ty, float dx, float dy);
void ascii_set_fg(int x, int y, Tilep);
void ascii_set_fg(int x, int y, color c);
void ascii_set_fg(int x, int y, const char *tilename);
void ascii_set_fg(int x, int y, const wchar_t c);
void ascii_set_fg2(int x, int y, Tilep);
void ascii_set_fg2(int x, int y, Tilep, float tx, float ty, float dx, float dy);
void ascii_set_fg2(int x, int y, color c);

void ascii_dim(int x, int y, int z, float alpha);

void ascii_putf(int x, int y, const wchar_t *fmt, ...);
void ascii_putf(int x, int y, color fg, const wchar_t *fmt, ...);
void ascii_putf(int x, int y, color fg, color bg, const wchar_t *fmt, ...);
void ascii_putf(int x, int y, std::wstring const& fmt, ...);
void ascii_putf(int x, int y, color fg, std::wstring const& fmt, ...);
void ascii_putf(int x, int y, color fg, color bg, std::wstring const& fmt, ...);
void ascii_putf__(int x, int y, color fg, color bg, std::wstring const& text);

void ascii_display(void);

int ascii_tp_tl1_tile(int x, int y, fpoint *);
int ascii_tp_br1_tile(int x, int y, fpoint *);
int ascii_tp_tile_mid(int x, int y, fpoint *);

void ascii_put_bg_square(int tlx, int tly, int brx, int bry,
                         const char *tilename, color c);
void ascii_put_bg_square(int tlx, int tly, int brx, int bry,
                         wchar_t what, color c);
void ascii_put_bg_square(int tlx, int tly, int brx, int bry,
                         Tilep what, color c);

void ascii_draw_line(int x0, int y0, int x1, int y1, const char *tilename,
                     color c);
void ascii_draw_line(int x0, int y0, int x1, int y1, wchar_t what, color c);
void ascii_draw_line(int x0, int y0, int x1, int y1, Tilep what, color c);

int ascii_strlen(std::wstring const&);
int ascii_strlen(std::wstring const& buf, std::wstring *col);

void ascii_clear_scissors(void);
void ascii_set_scissors(point tl, point br);

typedef struct {
    int x;
    int y;
    int width;
    int over;

    int sdl_mod;
    int sdl_key;
    int mouse_button;

    color col;

    ascii_key_down_callback key_down;
    ascii_mouse_down_callback mouse_down;
    ascii_mouse_over_callback mouse_over;

    void *context;
} button_args;

typedef struct {
    int x;
    int y;
    int width;
    int height;
    int over;

    int sdl_mod;
    int sdl_key;
    int mouse_button;

    color col_bg;
    color col_text;

    ascii_key_down_callback key_down;
    ascii_mouse_down_callback mouse_down;
    ascii_mouse_over_callback mouse_over;

    void *context;
} box_args;

color ascii_get_color(int x, int y, int z);
void *ascii_get_context(int x, int y);
void ascii_blit_layer(int z, int no_color);
void ascii_put_box(box_args b, int style, Tilep bg_tile, Tilep fg_tile, const wchar_t *fmt, ...);
void ascii_set_context(int x, int y, void *context);
void ascii_shade(void);
std::string ascii_strip(std::string const& text);

static inline int ascii_ok (int x, int y)
{
    if (unlikely(x < 0)) {
        return (false);
    }

    if (unlikely(x >= ASCII_WIDTH)) {
        return (false);
    }

    if (unlikely(y < 0)) {
        return (false);
    }

    if (unlikely(y >= ASCII_HEIGHT)) {
        return (false);
    }

    return (true);
}

static inline int ascii_x_ok (int x)
{
    if (unlikely(x < 0)) {
        return (false);
    }

    if (unlikely(x >= ASCII_WIDTH)) {
        return (false);
    }

    return (true);
}

static inline int ascii_y_ok (int y)
{
    if (unlikely(y < 0)) {
        return (false);
    }

    if (unlikely(y >= ASCII_HEIGHT)) {
        return (false);
    }

    return (true);
}

extern float tile_pix_w;
extern float tile_pix_h;

#define ASCII_CURSOR_UCHAR ((wchar_t)('z' + 6))
#define ASCII_CURSOR_TILE  "C97" // block
#define ASCII_UNKNOWN_TILE "C31" // ?
