//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once
#ifndef _MY_WORLD_H_
#define _MY_WORLD_H_

#include "my_point.h"
#include "my_level.h"

class World {
public:
    std::array<
      std::array<
        std::array<Levelp, LEVELS_DEEP>,
                           LEVELS_DOWN>,
                           LEVELS_ACROSS>
          levels {};
    //
    // Which level in the world
    //
    point3d at;

    void clear(void);
    void fini(void);
    void dump(std::string prefix, std::ostream &out);
    void log(std::string prefix);
    Levelp new_level_at(point3d at, int seed);
    friend std::ostream& operator<<(std::ostream &out, Bits<const World & > const my);
    friend std::istream& operator>>(std::istream &in, Bits<World &> my);
};

#endif
