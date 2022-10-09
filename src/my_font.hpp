//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_FONT_HPP_
#define _MY_FONT_HPP_

#include <array>

#include "my_fwd.hpp"
#include "my_sdl.hpp"

extern Fontp font_pixelart_small;
extern Fontp font_pixelart_large;
extern Fontp font_ascii;
extern Fontp font_ui;

#include "my_tile.hpp"

#define FONT_MAX_CHAR 223
#define FONT_MIN_CHAR ' '

void    font_fini(void);
uint8_t font_init(void);
Fontp   font_find(std::string);

class Font
{
public:
  Font(void) = default;
  ~Font(void) = default;
  std::array< int, FONT_MAX_CHAR + 1 >   u_to_c {};
  std::array< Tilep, FONT_MAX_CHAR + 1 > cache {};
  int                                    tile_index;
  Tilep                                  unicode_to_tile(int u);
};
#endif
