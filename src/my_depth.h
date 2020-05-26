//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#ifndef _MY_DEPTH_H_
#define _MY_DEPTH_H_

enum {
    MAP_DEPTH_FLOOR,
    MAP_DEPTH_FLOOR2,
    MAP_DEPTH_WATER,
    MAP_DEPTH_LAVA,
    MAP_DEPTH_CHASM,
#define MAP_DEPTH_LAST_FLOOR_TYPE MAP_DEPTH_CHASM
    MAP_DEPTH_WALL,
    MAP_DEPTH_OBJ,
    MAP_DEPTH_OBJ2,
    MAP_DEPTH_WEAPON,
    MAP_DEPTH,
};

#endif
