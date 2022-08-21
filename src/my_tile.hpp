//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_TILE_HPP_
#define _MY_TILE_HPP_

#include "my_color.hpp"
#include "my_fwd.hpp"
#include "my_gl.hpp"
#include "my_point.hpp"
#include <array>

using Tilemap = std::vector< class Tile * >;

#define TILE_HEIGHT       game->config.tile_height
#define TILE_HEIGHT_LORES 16
#define TILE_HEIGHT_MAX   64
#define TILE_WIDTH        game->config.tile_width
#define TILE_WIDTH_LORES  16 // Tile size of the player
#define TILE_WIDTH_MAX    32 // Largest tile for collisions

class Tile
{
public:
  Tile(void);
  ~Tile(void);
  Tile(const class Tile *tile);

  std::string name;
  wchar_t     ascii_fg_char {};
  wchar_t     ascii_bg_char {};
  uint8_t     ascii_bg_alpha {255};
  uint8_t     ascii_fg_alpha {255};
  std::string ascii_fg_col_name;
  std::string ascii_bg_col_name;
  color       ascii_fg_col_value;
  color       ascii_bg_col_value;
  bool        ascii_set {};

  //
  // Grabbed by a template
  //
  uint8_t  in_use {};
  uint16_t global_index;

  //
  // Index within the overall texture, left to right, top to bottom.
  //
  uint16_t index {};

  uint16_t pix_width {};
  uint16_t pix_height {};

  float pct_width {};
  float pct_height {};

  //
  // Texture co-ordinates within the image.
  //
  float x1 {};
  float y1 {};
  float x2 {};
  float y2 {};

  //
  // As above but not clipped 0.5 pixels. Actually we do not clip anymore,
  // it didn't help. Best to choose a resolution that works.
  //
  float ox1 {};
  float oy1 {};
  float ox2 {};
  float oy2 {};

  //
  // Percentage points that indicate the start of the pixels within the tile
  // texture for use in collisions.
  //
  float px1 {};
  float py1 {};
  float px2 {};
  float py2 {};

  class Tex *tex {};
  class Tex *tex_black_and_white {};
  class Tex *tex_mask {};

  std::array< std::array< uint8_t, TILE_HEIGHT_MAX >, TILE_WIDTH_MAX > pix {};

  //
  // Delay in ms between frames.
  //
  uint32_t delay_ms {};

  uint8_t frame {};
  uint8_t dir {};

  bool internal_has_dir_anim         : 1 {};
  bool is_alive_on_end_of_anim       : 1 {};
  bool is_alive_on_end_of_ascii_anim : 1 {};
  bool is_dead                       : 1 {};
  bool is_dead_on_end_of_anim        : 1 {};
  bool is_dead_on_end_of_ascii_anim  : 1 {};
  bool is_end_of_anim                : 1 {};
  bool is_end_of_ascii_anim          : 1 {};
  bool is_hp_100_percent             : 1 {};
  bool is_hp_25_percent              : 1 {};
  bool is_hp_50_percent              : 1 {};
  bool is_hp_75_percent              : 1 {};
  bool is_invisible                  : 1 {};
  bool is_join_bot                   : 1 {};
  bool is_join_horiz                 : 1 {};
  bool is_join_l                     : 1 {};
  bool is_join_l180                  : 1 {};
  bool is_join_l270                  : 1 {};
  bool is_join_l90                   : 1 {};
  bool is_join_left                  : 1 {};
  bool is_join_node                  : 1 {};
  bool is_join_right                 : 1 {};
  bool is_join_t                     : 1 {};
  bool is_join_t180                  : 1 {};
  bool is_join_t270                  : 1 {};
  bool is_join_t90                   : 1 {};
  bool is_join_top                   : 1 {};
  bool is_join_vert                  : 1 {};
  bool is_join_x                     : 1 {};
  bool is_moving                     : 1 {};
  bool is_open                       : 1 {};
  bool is_outline                    : 1 {};
  bool is_resurrecting               : 1 {};
  bool is_sleeping                   : 1 {};
  bool is_yyy5                       : 1 {};
  bool is_yyy6                       : 1 {};
  bool is_yyy7                       : 1 {};
  bool is_yyy8                       : 1 {};
  bool is_yyy9                       : 1 {};

private:
  int _gl_binding {};
  int _gl_binding_black_and_white {};
  int _gl_binding_mask {};

public:
  int  gl_binding(void) const;
  int  gl_binding_black_and_white(void) const;
  int  gl_binding_mask(void) const;
  void set_gl_binding(int v);
  void set_gl_binding_black_and_white(int v);
  void set_gl_binding_mask(int v);
};

typedef class Tile *Tilep;

class Tex *tile_get_tex(Tilep);

int tile_get_height(Tilep);
int tile_get_width(Tilep);
int tile_get_n(Tilemap *tmap, Tile *p);

std::string tile_get_name(Tilep);
std::string tile_name(Tilep);

Tilep string2tile(const char **s);
Tilep string2tile(std::string &s, int *len);
Tilep string2tile(std::wstring &s, int *len);
Tilep tile_find_mand(std::string name);
Tilep tile_first(Tilemap *root);
Tilep tile_from_surface(struct SDL_Surface *surface, std::string optional_file, std::string name);
Tilep tile_index_to_tile(uint16_t i);
Tilep tile_next(Tilemap *root, Tilep in);
Tilep tile_n(Tilemap *root, int n);
Tilep tile_random(Tilemap *root);
Tilep tile_find(std::string name);
Tilep tile_get_frame(Tilemap *tmap, uint32_t frame);

uint32_t tile_delay_ms(Tilep);
uint32_t tile_frame(Tilep);
uint32_t tile_get_index(Tilep);
uint32_t tile_move(Tilep);

uint8_t gfx_outline_index_offset(Tilep);
uint8_t tile_init(void);
uint8_t tile_is_alive_on_end_of_anim(Tilep);
uint8_t tile_is_alive_on_end_of_ascii_anim(Tilep);
uint8_t tile_is_dead_on_end_of_anim(Tilep);
uint8_t tile_is_dead_on_end_of_ascii_anim(Tilep);
uint8_t tile_is_dead(Tilep);
uint8_t tile_is_dir_bl(Tilep);
uint8_t tile_is_dir_br(Tilep);
uint8_t tile_is_dir_down(Tilep);
uint8_t tile_is_dir_left(Tilep);
uint8_t tile_is_dir_none(Tilep);
uint8_t tile_is_dir_right(Tilep);
uint8_t tile_is_dir_tl(Tilep);
uint8_t tile_is_dir_tr(Tilep);
uint8_t tile_is_dir_up(Tilep);
uint8_t tile_is_end_of_anim(Tilep);
uint8_t tile_is_end_of_ascii_anim(Tilep);
uint8_t tile_is_hp_100_percent(Tilep);
uint8_t tile_is_hp_25_percent(Tilep);
uint8_t tile_is_hp_50_percent(Tilep);
uint8_t tile_is_hp_75_percent(Tilep);
uint8_t tile_is_invisible(Tilep);
uint8_t tile_is_moving(Tilep);
uint8_t tile_is_open(Tilep);
uint8_t tile_is_resurrecting(Tilep);
uint8_t tile_is_sleeping(Tilep);
uint8_t tile_is_yyy5(Tilep);
uint8_t tile_is_yyy6(Tilep);
uint8_t tile_is_yyy7(Tilep);
uint8_t tile_is_yyy8(Tilep);
uint8_t tile_is_yyy9(Tilep);

void tile_blit(const Tilep &tile, const point tl, const point br);
void tile_blit(const Tilep &tile, const point tl, const point br, const color &c);
void tile_blit(const Tilep &tile, const point tl, const point tr, const point bl, const point br);
void tile_blit(const Tilep &tile, const point at);
void tile_blit(const class Tp *&tp, const Tilep &tile, const point tl, const point br);
void tile_blit(const class Tp *&tp, uint16_t index, const point tl, const point br);
void tile_blit(uint16_t index, const point tl, const point br);
void tile_blit(uint16_t index, const point at);
void tile_blit_at(const Tilep &tile, const point tl, const point br);
void tile_blit_at(uint16_t index, const point tl, const point br);
void tile_blit_colored(Tilep tile, point tl, point br, color color_tl, color color_tr, color color_bl,
                       color color_br);
void tile_blit_colored_fat(class Tp *tp, Tilep tile, point tl, point br, color color_tl, color color_tr,
                           color color_bl, color color_br);
void tile_blit_outline(const Tilep &tile, const point tl, const point br, const color &c);
void tile_blit_outline(const Tilep &tile, const point tl, const point br, const color &c, const color &o);
void tile_blit_outline(uint16_t index, const point tl, const point br, const color &c);
void tile_blit_outline_section(const Tilep &tile, const point tile_tl, const point tile_br, const point tl,
                               const point br);
void tile_blit_outline_section(uint16_t index, const point tile_tl, const point tile_br, const point tl,
                               const point br);
void tile_blit_outline_section_colored(const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br,
                                       const point tl, const point br, color color_bl, color color_br, color color_tl,
                                       color color_tr);
void tile_blit_outline_section_colored(const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br,
                                       const point tl, const point br, color color_bl, color color_br, color color_tl,
                                       color color_tr, float scale);
void tile_blit_outline_section_colored(uint16_t index, const fpoint &tile_tl, const fpoint &tile_br, const point tl,
                                       const point br, color color_bl, color color_br, color color_tl,
                                       color color_tr);
void tile_blit_outline_section_colored(uint16_t index, const fpoint &tile_tl, const fpoint &tile_br, const point tl,
                                       const point br, color color_bl, color color_br, color color_tl, color color_tr,
                                       float scale);
void tile_blit_section(const Tilep &tile, const point tile_tl, const point tile_br, const point tl, const point br);
void tile_blit_section(uint16_t index, const point tile_tl, const point tile_br, const point tl, const point br);
void tile_blit_section_colored(const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br, const point tl,
                               const point br, color color_bl, color color_br, color color_tl, color color_tr);
void tile_blit_section_colored(uint16_t index, const fpoint &tile_tl, const fpoint &tile_br, const point tl,
                               const point br, color color_bl, color color_br, color color_tl, color color_tr);
void tile_blit_shadow(const class Tp *&tp, const Tilep &tile, const point tl, const point br);
void tile_blit_shadow(const class Tp *&tp, uint16_t index, const point tl, const point br);
void tile_blit_shadow_section(const class Tp *&tp, const Tilep &tile, const point tile_tl, const point tile_br,
                              const point tl, const point br);
void tile_blit_shadow_section(const class Tp *&tp, uint16_t index, const point tile_tl, const point tile_br,
                              const point tl, const point br);
void tile_fini(void);
void tile_free(Tilep);
void tile_get_coords(Tilep, float *x1, float *y1, float *x2, float *y2);
void tile_load(std::string file, uint32_t width, uint32_t height, uint32_t nargs, ...);
void tile_load_arr(std::string file, std::string tex_name, uint32_t width, uint32_t height,
                   const std::vector< std::string > &arr);
void tile_load_arr(std::string file, std::string tex_name, uint32_t width, uint32_t height, uint32_t nargs,
                   const char *arr[]);
void tile_load_arr_sprites(std::string file, std::string name, uint32_t width, uint32_t height,
                           const std::vector< std::string > &arr, int gl_mode = GL_NEAREST);
void tile_load_arr_sprites(std::string file, std::string tex_name, uint32_t width, uint32_t height, uint32_t nargs,
                           const char *arr[], int gl_mode = GL_NEAREST);
void tile_blit_frozen(const Tilep &tile, const point tl, const point br);

#endif
