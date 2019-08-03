//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once

#include "my_point.h"
#include "my_main.h"

typedef struct dmap_ {
    uint16_t val[CHUNK_WIDTH][CHUNK_HEIGHT];
} Dmap;

extern void dmap_process(Dmap *D, point tl, point br);
extern void dmap_print(Dmap *d, point start);
extern void dmap_print_walls(Dmap *d);
extern std::vector<point> dmap_solve(const Dmap *d, const point start);
extern void dmap_l_shaped_path_to_diag(const Dmap *D,
                                       std::vector<point> &path);
extern bool dmap_can_i_move_diagonally(const Dmap *D,
                                       const point p,
                                       const point n,
                                       const point m);
extern void dmap_scale_and_recenter(Dmap *D,
                                    const fpoint p,
                                    const int scale);
extern uint64_t dmap_hash(Dmap *d);

#define DMAP_IS_WALL     65535
#define DMAP_IS_PASSABLE 1000
#define DMAP_IS_GOAL     0
