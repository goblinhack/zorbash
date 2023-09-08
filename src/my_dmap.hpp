//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_DMAP_HPP_
#define _MY_DMAP_HPP_

#include "my_game_defs.hpp"
#include "my_point.hpp"

#include <array>

using Dmap = struct Dmap_ {
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > val {};
};

extern void dmap_process_no_diagonals(Dmap *D, point tl, point br, bool place_border);
extern void dmap_process_allow_diagonals(Dmap *D, point tl, point br, bool place_border);
extern void dmap_process_reverse_allow_diagonals(Dmap *D, point tl, point br, bool place_border);
extern void dmap_print(const Dmap *d, point at, point start, point end);
extern void dmap_print(const Dmap *d);
extern void dmap_l_shaped_path_to_diag(const Dmap *D, std::vector< point > &path);
extern bool dmap_can_i_move_diagonally(const Dmap *D, const point p, const point n, const point m);

extern std::vector< point > dmap_solve(const Dmap *d, const point start);
extern std::vector< point > dmap_solve_manhattan(const Dmap *d, const point start);
extern std::vector< point > dmap_solve_allow_diagonal(const Dmap *d, const point start);

#define DMAP_IS_WALL                    ((uint8_t) 255)
#define DMAP_IS_PASSABLE                ((uint8_t) 254)
#define DMAP_LESS_PREFERRED_TERRAIN     ((uint8_t) 100)
#define DMAP_MAX_LESS_PREFERRED_TERRAIN ((uint8_t) 253)
#define DMAP_IS_GOAL                    ((uint8_t) 0)

#endif
