//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_ASCII_HPP_
#define _MY_ASCII_HPP_

#include "my_enums.hpp"
#include "my_tex.hpp"
#include "my_tile.hpp"

#define TERM_ASCII_WIDTH_DEF  132
#define TERM_ASCII_HEIGHT_DEF 46

#define TERM_GFX_WIDTH_DEF  120
#define TERM_GFX_HEIGHT_DEF 80

#define TERM_WIDTH_MAX  (std::max(TERM_GFX_WIDTH_DEF + 10, TERM_ASCII_WIDTH_DEF))
#define TERM_HEIGHT_MAX (std::max(TERM_GFX_HEIGHT_DEF + 10, TERM_ASCII_HEIGHT_DEF))

using ascii_key_down_callback   = int (*)(int, int, const struct SDL_Keysym *);
using ascii_mouse_down_callback = int (*)(int, int, int);
using ascii_mouse_over_callback = int (*)(int, int);

typedef std::array< Tilep, TILE_LAYER_MAX > TileLayers;

struct ascii_ {
  //
  // In ascii mode, where on the ASCII we are
  //
  point mouse_at;
  //
  // UI triggers for ASCII co-ords.
  //
  std::array< std::array< int, TERM_HEIGHT_MAX >, TERM_WIDTH_MAX > sdl_mod {};
  std::array< std::array< int, TERM_HEIGHT_MAX >, TERM_WIDTH_MAX > sdl_key {};
  std::array< std::array< int, TERM_HEIGHT_MAX >, TERM_WIDTH_MAX > mouse_button {};

  //
  // Callbacks for ASCII co-ords.
  //
  std::array< std::array< ascii_key_down_callback, TERM_HEIGHT_MAX >, TERM_WIDTH_MAX >   key_down {};
  std::array< std::array< ascii_mouse_down_callback, TERM_HEIGHT_MAX >, TERM_WIDTH_MAX > mouse_down {};
  std::array< std::array< ascii_mouse_over_callback, TERM_HEIGHT_MAX >, TERM_WIDTH_MAX > mouse_over {};
};

extern int16_t TERM_WIDTH;
extern int16_t TERM_HEIGHT;

using button_args = struct {
  int x;
  int y;
  int width;
  int over;

  int sdl_mod;
  int sdl_key;
  int mouse_button;

  color col;

  ascii_key_down_callback   key_down;
  ascii_mouse_down_callback mouse_down;
  ascii_mouse_over_callback mouse_over;

  void *context;
};

using box_args = struct box_args_ {
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

  ascii_key_down_callback   key_down;
  ascii_mouse_down_callback mouse_down;
  ascii_mouse_over_callback mouse_over;

  void *context;
};

bool ascii_is_empty(int x, int y);

color ascii_get_color(int x, int y, int z);

int ascii_ok(int x, int y);
int ascii_ok_for_scissors(int x, int y);
int ascii_strlen(std::wstring const &buf, std::wstring *col);
int ascii_strlen(std::wstring const &);
int ascii_tp_br1_tile(int x, int y, fpoint *);
int ascii_tp_tile_mid(int x, int y, fpoint *);
int ascii_tp_tl1_tile(int x, int y, fpoint *);
int ascii_x_ok(int x);
int ascii_y_ok(int y);

std::string ascii_strip(std::string const &text);

void *ascii_get_stat_context(int x, int y);

void ascii_blit_layer(int z, int no_color);
void ascii_clear_display(void);
void ascii_clear_scissors(void);
void ascii_dim(int x, int y, int z, float alpha);
void ascii_display(void);
void ascii_draw_line(int x0, int y0, int x1, int y1, Tilep what, color c);
void ascii_draw_line(int x0, int y0, int x1, int y1, const char *tilename, color c);
void ascii_draw_line(int x0, int y0, int x1, int y1, wchar_t what, color c);
void ascii_draw_line(int depth, int x0, int y0, int x1, int y1, wchar_t ch, color c);
void ascii_init(void);
void ascii_put_bg_square(int tlx, int tly, int brx, int bry, Tilep what, color c);
void ascii_put_bg_square(int tlx, int tly, int brx, int bry, const char *tilename, color c);
void ascii_put_bg_square(int tlx, int tly, int brx, int bry, wchar_t what, color c);
void ascii_put_box(box_args b, int style, const TileLayers, const wchar_t *fmt, ...);
void ascii_putf(int x, int y, color fg, color bg, const std::wstring fmt, ...);
void ascii_putf(int x, int y, color fg, color bg, const wchar_t *fmt, ...);
void ascii_putf(int x, int y, color fg, const std::wstring fmt, ...);
void ascii_putf(int x, int y, color fg, const wchar_t *fmt, ...);
void ascii_putf(int x, int y, const std::wstring fmt, ...);
void ascii_putf(int x, int y, const wchar_t *fmt, ...);
void ascii_putf__(int x, int y, color fg, color bg, const std::wstring text);
void ascii_set_context(int x, int y, void *context);
void ascii_set(int depth, int x, int y, Texp, float tx, float ty, float dx, float dy);
void ascii_set(int depth, int x, int y, Tilep, float tx, float ty, float dx, float dy);
void ascii_set(int depth, int x, int y, Tilep);
void ascii_set(int depth, int x, int y, color c);
void ascii_set(int depth, int x, int y, const char *tilename);
void ascii_set(int depth, int x, int y, const wchar_t c);
void ascii_set_scissors(point tl, point br);
void ascii_shade(void);
void pixel_to_ascii(int *x, int *y);

extern float         tile_pix_w;
extern float         tile_pix_h;
extern int16_t       ascii_mouse_x;
extern int16_t       ascii_mouse_y;
extern struct ascii_ ascii;

#endif
