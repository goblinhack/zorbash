//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_PROJECTILE_HPP_
#define _MY_PROJECTILE_HPP_

#include "my_main.hpp"
#include "my_point.hpp"
#include "my_thing_id.hpp"
#include "my_tile.hpp"

typedef class Projectile_
{
public:
  Projectile_(Levelp level, ThingId thing_id, ThingId target_id, point start, point stop, point pixel_map_at,
              uint32_t ts_start, uint32_t ts_stop, bool follow_moving_target);

  Levelp  level {};
  ThingId id {};
  ThingId target_id {};
  point   start;
  point   stop;
  point   pixel_map_at;

  uint32_t ts_start {};
  uint32_t ts_stop {};
  bool     follow_moving_target {};

  //
  // Animation frames
  //
  std::vector< Tilep > tiles;
  static const auto    max_frames = 16;
} Projectile;

#endif // _MY_LASER_HPP_
