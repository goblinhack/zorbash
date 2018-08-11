/*
 * Copyright (C) 2017 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#include "my_point.h"

typedef struct dmap_ {
    int16_t val[MAP_WIDTH][MAP_HEIGHT];
} dmap;

extern void dmap_process(dmap *d);
extern void dmap_print(dmap *d);
extern std::vector<point> dmap_solve(const dmap *d, const point end, 
                                     const point start);
extern void dmap_l_shaped_path_to_diag(const dmap *D, 
                                       std::vector<point> &path);

#define DMAP_IS_WALL     MAP_WIDTH
#define DMAP_IS_PASSABLE (MAP_WIDTH - 1)
#define DMAP_IS_GOAL     0
