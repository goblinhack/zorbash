//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_FONT_H_
#define _MY_FONT_H_

#include <memory>

typedef class Font * Fontp;

extern Fontp font_small;
extern Fontp font_large;

#include "SDL_ttf.h"
#include "my_tile.h"

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
    Font (void)
    {
    }

    ~Font (void)
    {
    }

    std::array<glyph, TTF_GLYPH_MAX+1> glyphs {};
    std::array<glyphtex, TTF_GLYPH_MAX+1> tex {};
    SDL_Color foreground = {};
    SDL_Color background = {};
    std::array<int, TTF_GLYPH_MAX+1> u_to_c {};
    std::array<int, TTF_GLYPH_MAX+1> valid {};
    std::array<Tilep, TTF_GLYPH_MAX+1> cache {};
    int tile_index;

    Tilep unicode_to_tile (int u)
    {
        if ((u < 0) || (u >= TTF_GLYPH_MAX)) {
            if (u == L'?') {
                DIE("unicode char 0x%x/%d -> bad index", u, u);
            } else {
                DIE("unicode char 0x%x/%d -> bad index", u, u);
            }
            return (unicode_to_tile(L'?'));
        }

        auto index = get(this->u_to_c, u);

        if ((index < 0) || (index >= TTF_GLYPH_MAX)) {
            if (u == L'?') {
                DIE("unicode char 0x%x/%d -> bad index %d", u, u, index);
            } else {
                DIE("unicode char 0x%x/%d -> bad index %d", u, u, index);
            }
            return (unicode_to_tile(L'?'));
        }

        auto tile = get(this->cache, index);
        if (tile) {
            return (tile);
        }

        char tile_name[10];
        snprintf(tile_name, sizeof(tile_name), "%d.%d", tile_index, index);

        tile = tile_find(tile_name);
        if (!tile) {
            if (u == L'?') {
                DIE("unicode char 0x%x/%d -> not found as tile %s", u, u, tile_name);
            } else {
                DIE("unicode char 0x%x/%d -> not found as tile %s", u, u, tile_name);
                return (unicode_to_tile(L'?'));
            }
        }

        set(this->cache, index, tile);

        return (tile);
    }
};
#endif
