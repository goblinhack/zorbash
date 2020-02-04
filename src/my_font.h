//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//


#ifndef _MY_FONT_H_
#define _MY_FONT_H_

#include <memory>

typedef class Font * Fontp;
extern Fontp fixed_font;

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

typedef struct {
    SDL_Surface *image = {};
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

    Tilep unicode_to_tile (int u)
    {
        if ((u < 0) || (u >= TTF_GLYPH_MAX)) {
            if (u == L'?') {
                ERR("unicode char c 0x%x -> bad index", u);
            } else {
                ERR("unicode char c 0x%x -> bad index", u);
            }
            return (unicode_to_tile(L'?'));
        }

        auto index = get(this->u_to_c, u);

        if ((index < 0) || (index >= TTF_GLYPH_MAX)) {
            if (u == L'?') {
                ERR("unicode char c 0x%x -> bad index %d", u, index);
            } else {
                ERR("unicode char c 0x%x -> bad index %d", u, index);
            }
            return (unicode_to_tile(L'?'));
        }

        auto tile = get(this->cache, index);
        if (tile) {
            return (tile);
        }

        char tile_name[10];
        snprintf(tile_name, sizeof(tile_name), "C%d", index);

        tile = tile_find(tile_name);
        if (!tile) {
            if (u == L'?') {
                ERR("unicode char c 0x%x -> not found as tile %s", u, tile_name);
            } else {
                ERR("unicode char c 0x%x -> not found as tile %s", u, tile_name);
                return (unicode_to_tile(L'?'));
            }
        }

        set(this->cache, index, tile);

        return (tile);
    }
};
#endif
