//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_DMAP_HPP_
#define _MY_DMAP_HPP_

#include "my_game_defs.hpp"
#include "my_point.hpp"
#include <array>

typedef struct Dmap_ {
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > val {};
} Dmap;

#include <type_traits>

template < typename T > size_t len(const T &a)
{
  return sizeof(T) / sizeof(typename std::remove_all_extents< T >::type);
}

// https://stackoverflow.com/questions/26948099/stdcopy-for-multidimensional-arrays
template < typename T > typename std::remove_all_extents< T >::type *mbegin(T &arr)
{
  return reinterpret_cast< typename std::remove_all_extents< T >::type * >(&arr);
}
template < typename T > typename std::remove_all_extents< T >::type *mend(T &arr)
{
  return reinterpret_cast< typename std::remove_all_extents< T >::type * >(&arr) + len(arr);
}

extern void                 dmap_process(Dmap *D, point tl, point br);
extern void                 dmap_process(Dmap *D);
extern void                 dmap_print(const Dmap *d, point at, point start, point end);
extern void                 dmap_print(const Dmap *d);
extern std::vector< point > dmap_solve(const Dmap *d, const point start);
extern std::vector< point > dmap_solve_allow_diagonal(const Dmap *d, const point start);
extern void                 dmap_l_shaped_path_to_diag(const Dmap *D, std::vector< point > &path);
extern bool                 dmap_can_i_move_diagonally(const Dmap *D, const point p, const point n, const point m);

#define DMAP_IS_WALL                    ((uint8_t) 255)
#define DMAP_IS_PASSABLE                ((uint8_t) 254)
#define DMAP_LESS_PREFERRED_TERRAIN     ((uint8_t) 100)
#define DMAP_MAX_LESS_PREFERRED_TERRAIN ((uint8_t) 253)
#define DMAP_IS_GOAL                    ((uint8_t) 0)

#endif
