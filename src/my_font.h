//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_FONT_H_
#define _MY_FONT_H_

#include "my_fwd.h"

extern Fontp font_small;
extern Fontp font_large;

#include "SDL_ttf.h"
#include "my_tile.h"

#define TTF_GLYPH_MAX              134
#define TTF_GLYPH_MIN              ' '
#define TTF_GLYPH_PER_ROW          60

typedef struct {
    double width;
    double height;
    double minx;
    double maxx;
    double miny;
    double maxy;
    double advance;
    double texMinX;
    double texMaxX;
    double texMinY;
    double texMaxY;
} glyph;

typedef struct glyphtex_ {
    SDL_Surface *image {};
    uint32_t tex;
    Texp tex_p = {};
} glyphtex;

void font_fini(void);
uint8_t font_init(void);
Fontp font_find(std::string);

class Font {

public:
    Font (void) { }
    ~Font (void) { }
    std::array<glyph, TTF_GLYPH_MAX+1> glyphs {};
    std::array<glyphtex, TTF_GLYPH_MAX+1> tex {};
    SDL_Color foreground = {};
    SDL_Color background = {};
    std::array<int, TTF_GLYPH_MAX+1> u_to_c {};
    std::array<int, TTF_GLYPH_MAX+1> valid {};
    std::array<Tilep, TTF_GLYPH_MAX+1> cache {};
    int tile_index;
    Tilep unicode_to_tile(int u);
};
#endif
