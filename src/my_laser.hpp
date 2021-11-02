//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_LASER_HPP_
#define _MY_LASER_HPP_

#include "my_main.hpp"
#include "my_point.hpp"
#include "my_thing_id.hpp"
#include "my_tile.hpp"

typedef class Laser_
{
public:
  Laser_(Levelp level, ThingId thing_id, point start, point stop, point pixel_map_at, uint32_t ts_start,
         uint32_t ts_stop);

  Levelp  level {};
  ThingId id {};
  point   start;
  point   stop;
  point   pixel_map_at;

  uint32_t ts_start {};
  uint32_t ts_stop {};

  //
  // Animation frames
  //
  std::vector< std::vector< Tilep > > tiles;
  static const auto                   max_frames = 16;
} Laser;

#endif // _MY_LASER_HPP_
