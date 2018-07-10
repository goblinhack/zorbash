/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_TILE_H_
#define _MY_TILE_H_

typedef std::shared_ptr< class tile > tilep;

#include <map>
#include "my_config.h"
#include "my_point.h"
#include "my_color.h"
#include "my_tex.h"
#include "my_thing_template.h"

class tile {

public:
    tile (void)
    {
    }

    ~tile (void)
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
#ifdef NEED_TILE_BOUNDS
    double px1 {};
    double py1 {};
    double px2 {};
    double py2 {};
#endif

    int32_t gl_surface_binding {};
    texp tex;
    uint8_t pix[MAX_TILE_WIDTH][MAX_TILE_HEIGHT] = {};
};

extern std::map<std::string, std::shared_ptr< class tile > > tiles;
typedef std::shared_ptr< class tile > tilep;

uint8_t tile_init(void);
void tile_fini(void);
void tile_load(std::string file, uint32_t width, uint32_t height,
               uint32_t nargs, ...);
void tile_load_arr(std::string tex,
                   uint32_t width, uint32_t height,
                   uint32_t nargs, const char * arr[]);
tilep tile_find(std::string name);
tilep tile_from_surface(SDL_Surface *surface,
                        std::string optional_file,
                        std::string name);
int32_t tile_get_gl_binding(tilep);
std::string tile_get_name(tilep);
int32_t tile_get_width(tilep);
int32_t tile_get_height(tilep);
texp tile_get_tex(tilep);
uint32_t tile_get_index(tilep);
tilep string2tile(const char **s);
tilep string2tile(std::string &s, int *len);
tilep string2tile(std::wstring &s, int *len);
void tile_get_coords(tilep, float *x1, float *y1, float *x2, float *y2);

void tile_blit_colored_fat(tpp tp,
                           tilep tile,
                           fpoint tl,
                           fpoint br,
                           color color_tl,
                           color color_tr,
                           color color_bl,
                           color color_br);
#endif
