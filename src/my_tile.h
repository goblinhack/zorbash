/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_TILE_H_
#define _MY_TILE_H_
#include "./my_sdl.h"
#include "my_tile_private.h"
#include "my_glapi.h"

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
void tile_blit_mask_fat(tilep tile, char *name, fpoint tl, fpoint br);
void blit_quad(point tl, point br);
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

/*
 * Blits a whole tile. Y co-ords are inverted.
 */
static inline
void tile_blit_fat (tpp tp, tilep tile, char *name, fpoint *tl, fpoint *br)
{
    double x1;
    double x2;
    double y1;
    double y2;

    x1 = tile->x1;
    x2 = tile->x2;
    y1 = tile->y1;
    y2 = tile->y2;

    if (unlikely(tp != 0)) {
        double left_off  = (double)tp_get_blit_left_off(tp);
        double right_off = (double)tp_get_blit_right_off(tp);
        double top_off   = (double)tp_get_blit_top_off(tp);
        double bot_off   = (double)tp_get_blit_bot_off(tp);

        double pct_w     = tile->pct_width;
        double pct_h     = tile->pct_height;
        double pix_w     = br->x - tl->x;
        double pix_h     = br->y - tl->y;

        tl->x -= left_off  * pix_w;
        br->x += right_off * pix_w;
        tl->y -= top_off   * pix_h;
        br->y += bot_off   * pix_h;

        x1 -= left_off  * pct_w;
        x2 += right_off * pct_w;
        y1 -= top_off   * pct_h;
        y2 += bot_off   * pct_h;
    }

    blit(tile->gl_surface_binding,
         x1, y2, x2, y1, tl->x, br->y, br->x, tl->y);
}

/*
 * Blits a whole tile. Y co-ords are inverted.
 */
static inline
void tile_blit_fat_with_offset (tpp tp, tilep tile, 
                                char *name, fpoint *tl,
                                fpoint *br,
                                double left_off,
                                double right_off,
                                double top_off,
                                double bot_off)
{
    double x1;
    double x2;
    double y1;
    double y2;

    x1 = tile->x1;
    x2 = tile->x2;
    y1 = tile->y1;
    y2 = tile->y2;

    double pct_w     = tile->pct_width;
    double pct_h     = tile->pct_height;
    double pix_w     = br->x - tl->x;
    double pix_h     = br->y - tl->y;

    tl->x -= left_off  * pix_w;
    br->x += right_off * pix_w;
    tl->y -= top_off   * pix_h;
    br->y += bot_off   * pix_h;

    x1 -= left_off  * pct_w;
    x2 += right_off * pct_w;
    y1 -= top_off   * pct_h;
    y2 += bot_off   * pct_h;

    blit(tile->gl_surface_binding,
         x1, y2, x2, y1, tl->x, br->y, br->x, tl->y);
}

/*
 * Given tile bounds, stretch them to get the full size.
 */
static inline
void tile_get_blit_size (tpp tp, tilep tile, char *name, fpoint *tl, fpoint *br)
{
    if (tp) {
        double left_off  = (double)tp_get_blit_left_off(tp);
        double right_off = (double)tp_get_blit_right_off(tp);
        double top_off   = (double)tp_get_blit_top_off(tp);
        double bot_off   = (double)tp_get_blit_bot_off(tp);

        double pix_w     = br->x - tl->x;
        double pix_h     = br->y - tl->y;

        tl->x -= left_off  * pix_w;
        br->x += right_off * pix_w;
        tl->y -= top_off   * pix_h;
        br->y += bot_off   * pix_h;
    }
}

/*
 * Blits a whole tile.
 */
static inline
void tile_blit_at (tilep tile, char *name, fpoint tl, fpoint br)
{
    blit(tile->gl_surface_binding,
         tile->x1, tile->y2, tile->x2, tile->y1, tl.x, tl.y, br.x, br.y);
}

/*
 * Blits a whole tile.
 */
static inline
void tile_blit (tilep tile, char *name, point at)
{
    fpoint tl, br;

    tl.x = at.x - tile->pix_width/2;
    br.y = at.y - tile->pix_height/2;
    br.x = at.x + tile->pix_width/2;
    tl.y = at.y + tile->pix_height/2;

    tile_blit_at(tile, name, tl, br);
}

/*
 * Blits a whole tile. Y co-ords are inverted.
 */
static inline
void tile_blit_colored_fat (tpp tp,
                            tilep tile,
                            fpoint tl,
                            fpoint br,
                            color color_tl,
                            color color_tr,
                            color color_bl,
                            color color_br)
{
    double x1 = tile->x1;
    double x2 = tile->x2;
    double y1 = tile->y1;
    double y2 = tile->y2;

    if (unlikely(tp != 0)) {
        double left_off  = (double)tp_get_blit_left_off(tp);
        double right_off = (double)tp_get_blit_right_off(tp);
        double top_off   = (double)tp_get_blit_top_off(tp);
        double bot_off   = (double)tp_get_blit_bot_off(tp);

        double pct_w     = tile->pct_width;
        double pct_h     = tile->pct_height;
        double pix_w     = br.x - tl.x;
        double pix_h     = br.y - tl.y;

        tl.x -= left_off  * pix_w;
        br.x += right_off * pix_w;
        tl.y -= top_off   * pix_h;
        br.y += bot_off   * pix_h;

        x1 -= left_off  * pct_w;
        x2 += right_off * pct_w;
        y1 -= top_off   * pct_h;
        y2 += bot_off   * pct_h;
    }

    blit_colored(tile->gl_surface_binding,
                 x1, y2, x2, y1,
                 tl.x, br.y, br.x, tl.y,
                 color_tl,
                 color_tr,
                 color_bl,
                 color_br);
}
#endif
