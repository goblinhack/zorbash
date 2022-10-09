//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_PROJECTILE_HPP_
#define _MY_PROJECTILE_HPP_

#include "my_main.hpp"
#include "my_point.hpp"
#include "my_thing_id.hpp"
#include "my_tile.hpp"

class ProjectileInfo
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
  //
  // Map scroll offset
  //
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

using Projectile = class Projectile_
{
public:
  Projectile_(Levelp level, ThingId thing_id, ThingId victim_id, ProjectileInfo info);

  Levelp         level {};
  ThingId        id {};
  ThingId        victim_id {};
  ProjectileInfo info {};

  //
  // Animation frames
  //
  std::vector< Tilep > tiles;
  static const auto    max_frames = 16;
};

#endif // _MY_LASER_HPP_
