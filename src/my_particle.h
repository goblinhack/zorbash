//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_PARTICLE_H_
#define _MY_PARTICLE_H_

#include "my_main.h"
#include "my_point.h"
#include "my_size.h"
#include "my_thing_id.h"

typedef class Particle_ {
public:
    Particle_(ThingId thing_id,
              point start, point stop,
              point pixel_map_at,
              size sz,
              uint32_t timestamp_start, uint32_t timestamp_stop,
              Tilep tile,
              bool hflip) :
        id(thing_id),
        start(start),
        stop(stop),
        pixel_map_at(pixel_map_at),
        sz(sz),
        timestamp_start(timestamp_start),
        timestamp_stop(timestamp_stop),
        tile(tile),
        hflip(hflip) { }

    Particle_(point start, point stop,
              point pixel_map_at,
              size sz,
              uint32_t timestamp_start, uint32_t timestamp_stop,
              Tilep tile,
              bool hflip) :
        start(start),
        stop(stop),
        pixel_map_at(pixel_map_at),
        sz(sz),
        timestamp_start(timestamp_start),
        timestamp_stop(timestamp_stop),
        tile(tile),
        hflip(hflip) { }

    ThingId id {};
    point start;
    point stop;
    point pixel_map_at;
    size sz;
    uint32_t timestamp_start {};
    uint32_t timestamp_stop {};
    Tilep tile {};
    bool hflip {};
} Particle;

#endif // _MY_PARTICLE_H_
