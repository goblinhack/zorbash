//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#ifndef _MY_PARTICLE_H_
#define _MY_PARTICLE_H_

#include "my_point.h"

typedef struct Particle_* Particlep;

typedef struct Particle_ {
public:
    Particle_ (void) {}
    ~Particle_ (void) {}
    bool    in_use {};
    bool    is_new {};
    fpoint  at;
    fpoint  orig_at;
    fpoint  force;
    fpoint  velocity;
} Particle;

#endif // _MY_PARTICLE_H_
