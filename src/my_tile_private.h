/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_TILE_PRIVATE_H_
#define _MY_TILE_PRIVATE_H_

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
#endif
