//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once
#ifndef _MY_PARTICLE_H_
#define _MY_PARTICLE_H_

#include "my_main.h"
#include "my_point.h"

typedef struct Particle_ {
public:
    fpoint start;
    fpoint stop;
    uint32_t timestamp_stop;
    uint32_t timestamp_end;
    Tilep tile;
} Particle;

#endif // _MY_PARTICLE_H_
