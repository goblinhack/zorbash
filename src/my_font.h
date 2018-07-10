/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_FONT_H_
#define _MY_FONT_H_

typedef std::shared_ptr< class font > fontp;
extern fontp fixed_font;

#include "SDL_ttf.h"
#include "my_main.h"
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
    texp tex_p = {};
} glyphtex;

void font_fini(void);
uint8_t font_init(void);
fontp font_find(std::string);

class font {

public:
    font (void)
    {
    }

    ~font (void)
    {
    }

    glyph glyphs[TTF_GLYPH_MAX+1] = {};
    glyphtex tex[TTF_GLYPH_MAX+1] = {};
    SDL_Color foreground = {};
    SDL_Color background = {};
    int u_to_c[TTF_GLYPH_MAX+1]= {};
    int valid[TTF_GLYPH_MAX+1]= {};
    tilep cache[TTF_GLYPH_MAX+1] = {};

    tilep unicode_to_tile (int u)
    {
        if ((u < 0) || (u >= TTF_GLYPH_MAX)) {
            if (u == L'?') {
                DIE("unicode char c 0x%x -> bad index", u);
            } else {
                DIE("unicode char c 0x%x -> bad index", u);
            }
            return (unicode_to_tile(L'?'));
        }

        auto index = this->u_to_c[u];

        if ((index < 0) || (index >= TTF_GLYPH_MAX)) {
            if (u == L'?') {
                DIE("unicode char c 0x%x -> bad index %d", u, index);
            } else {
                DIE("unicode char c 0x%x -> bad index %d", u, index);
            }
            return (unicode_to_tile(L'?'));
        }
        
        auto tile = this->cache[index];
        if (tile) {
            return (tile);
        }

        char tile_name[10];
        snprintf(tile_name, sizeof(tile_name), "C%d", index);

        tile = tile_find(tile_name);
        if (!tile) {
            if (u == L'?') {
                DIE("unicode char c 0x%x -> not found as tile %s", u, tile_name);
            } else {
                ERR("unicode char c 0x%x -> not found as tile %s", u, tile_name);
                return (unicode_to_tile(L'?'));
            }
        }

        this->cache[index] = tile;

        return (tile);
    }
};
#endif
