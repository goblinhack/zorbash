//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once
#ifndef _MY_PARTICLE_H_
#define _MY_PARTICLE_H_

#include "my_main.h"
#include "my_point.h"
#include "my_size.h"

typedef class Particle_ {
public:
    Particle_(point start, point stop, size sz,
              uint32_t timestamp_start, uint32_t timestamp_stop,
              Tilep tile) :
        start(start),
        stop(stop),
        sz(sz),
        timestamp_start(timestamp_start),
        timestamp_stop(timestamp_stop),
        tile(tile) { }

    point start;
    point stop;
    size sz;
    uint32_t timestamp_start {};
    uint32_t timestamp_stop {};
    Tilep tile {};
} Particle;

#endif // _MY_PARTICLE_H_
