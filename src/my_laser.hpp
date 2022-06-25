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

class LaserInfo
{
public:
  //
  // Map co-ordinates
  //
  point map_start;
  point map_stop;
  //
  // Onscreen pixel co-ordinates
  //
  point pixel_start;
  point pixel_stop;
  point pixel_map_at;
  //
  // Duration
  //
  uint32_t ts_start {};
  uint32_t ts_stop {};
  //
  // Flags
  //
  bool follow_moving_target {};
};

typedef class Laser_
{
public:
  Laser_(Levelp level, ThingId thing_id, ThingId victim_id, LaserInfo info);

  Levelp    level {};
  ThingId   id {};
  ThingId   victim_id {};
  LaserInfo info;

  //
  // Animation frames
  //
  std::vector< std::vector< Tilep > > tiles;
  static const auto                   max_frames = 16;
} Laser;

#endif // _MY_LASER_HPP_
