/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#pragma once

#include "my_point.h"

typedef struct dmap_ {
    uint8_t val[MAP_WIDTH][MAP_HEIGHT];
} Dmap;

extern void dmap_process(Dmap *d);
extern void dmap_process(Dmap *D, point tl, point br);
extern void dmap_print(Dmap *d, point start);
extern void dmap_print_walls(Dmap *d);
extern std::vector<point> dmap_solve(const Dmap *d, const point start);
extern void dmap_l_shaped_path_to_diag(const Dmap *D, std::vector<point> &path);
extern uint64_t dmap_hash(Dmap *d);

#define DMAP_IS_WALL     255
#define DMAP_IS_PASSABLE 254
#define DMAP_IS_GOAL     0
