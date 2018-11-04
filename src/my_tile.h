/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_TILE_H_
#define _MY_TILE_H_

#include <memory>
typedef class Tile*  Tilep;

#include <map>
#include "my_main.h"
#include "my_point.h"
#include "my_color.h"
#include "my_tex.h"
#include "my_thing_template.h"
#include "my_glapi.h"

class Tile {

public:
    Tile (void)
    {
    }

    ~Tile (void)
    {
    }

    std::string name;

    /*
     * Index within the overall texture, left to right, top to bottom.
     */
    uint32_t index {};
    uint32_t pix_width {};
    uint32_t pix_height {};
    /*
     * Texture co-ordinates within the image.
     */
    double x1 {};
    double y1 {};
    double x2 {};
    double y2 {};
    /*
     * As above but not clipped 0.5 pixels.
     */
    double ox1 {};
    double oy1 {};
    double ox2 {};
    double oy2 {};

    double pct_width {};
    double pct_height {};

    /*
     * Percentage points that indicate the start of the pixels within the tile
     * texture for use in collisions.
     */
    double px1 {};
    double py1 {};
    double px2 {};
    double py2 {};

    int32_t gl_surface_binding {};
    Texp tex;
    uint8_t pix[MAX_TILE_WIDTH][MAX_TILE_HEIGHT] = {};
};

extern std::map<std::string, class Tile* > all_tiles;
typedef class Tile* Tilep;

uint8_t tile_init(void);
void tile_fini(void);
void tile_load(std::string file, uint32_t width, uint32_t height,
               uint32_t nargs, ...);
void tile_load_arr(std::string tex,
                   uint32_t width, uint32_t height,
                   uint32_t nargs, const char * arr[]);
Tilep tile_find(std::string name);
Tilep tile_from_surface(SDL_Surface *surface,
                        std::string optional_file,
                        std::string name);
int32_t tile_get_gl_binding(Tilep);
std::string tile_get_name(Tilep);
int32_t tile_get_width(Tilep);
int32_t tile_get_height(Tilep);
Texp tile_get_tex(Tilep);
uint32_t tile_get_index(Tilep);
Tilep string2tile(const char **s);
Tilep string2tile(std::string &s, int *len);
Tilep string2tile(std::wstring &s, int *len);
void tile_get_coords(Tilep, float *x1, float *y1, float *x2, float *y2);
void tile_blit_colored_fat(Tpp tp,
                           Tilep tile,
                           fpoint tl,
                           fpoint br,
                           color color_tl,
                           color color_tr,
                           color color_bl,
                           color color_br);

/*
 * Blits a whole tile. Y co-ords are inverted.
 */
static inline void tile_blit_fat (const Tpp &tp, const Tilep &tile, 
                                  const fpoint &tl, const fpoint &br)
{
    double x1;
    double x2;
    double y1;
    double y2;

    x1 = tile->x1;
    x2 = tile->x2;
    y1 = tile->y1;
    y2 = tile->y2;

    blit(tile->gl_surface_binding, x1, y2, x2, y1, tl.x, br.y, br.x, tl.y);
}

void tile_blit_fat_outline(const Tpp &tp, const Tilep &tile, 
                           const fpoint &tl, const fpoint &br);
void tile_blit_fat_with_offset(const Tpp &tp, Tilep &tile, 
                               const fpoint &tl, const fpoint &br);
void tile_get_blit_size(const Tpp &tp, const Tilep tile, char *name, 
                        fpoint *tl, fpoint *br);
void tile_blit_at(const Tilep &tile, const char *name, 
                  const fpoint tl, const fpoint br);
void tile_blit(const Tilep &tile, const char *name, const point at);
#endif
