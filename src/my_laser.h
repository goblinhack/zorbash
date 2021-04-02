//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_LASER_H_
#define _MY_LASER_H_

#include "my_main.h"
#include "my_point.h"
#include "my_size.h"
#include "my_thing_id.h"

typedef class Laser_ {
public:
    Laser_(ThingId thing_id,
              point start, point stop,
              point pixel_map_at,
              isize sz,
              uint32_t timestamp_start, uint32_t timestamp_stop,
              class Tile* tile) :
        id(thing_id),
        start(start),
        stop(stop),
        pixel_map_at(pixel_map_at),
        sz(sz),
        timestamp_start(timestamp_start),
        timestamp_stop(timestamp_stop),
        tile(tile) { }

    ThingId id {};
    point start;
    point stop;
    point pixel_map_at;
    isize sz;
    uint32_t timestamp_start {};
    uint32_t timestamp_stop {};
    class Tile* tile {};
    int height {};
} Laser;

#endif // _MY_LASER_H_
