//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_PROJECTILE_H_
#define _MY_PROJECTILE_H_

#include "my_main.h"
#include "my_point.h"
#include "my_thing_id.h"
#include "my_tile.h"

typedef class Projectile_ {
public:
    Projectile_(
           Levelp level,
           ThingId thing_id,
           point start, point stop,
           point pixel_map_at,
           uint32_t timestamp_start, uint32_t timestamp_stop);

    Levelp level {};
    ThingId id {};
    point start;
    point stop;
    point pixel_map_at;

    uint32_t timestamp_start {};
    uint32_t timestamp_stop {};

    //
    // Animation frames
    //
    std::vector< Tilep > tiles;
    static const auto max_frames = 16;
} Projectile;

#endif // _MY_LASER_H_
