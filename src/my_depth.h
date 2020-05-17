//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#ifndef _MY_DEPTH_H_
#define _MY_DEPTH_H_

enum {
    MAP_DEPTH_FLOOR,
    MAP_DEPTH_WATER,
    MAP_DEPTH_LAVA,
    MAP_DEPTH_CHASM,
#define MAP_DEPTH_LAST_FLOOR_TYPE MAP_DEPTH_CHASM
    MAP_DEPTH_WALLS,
    MAP_DEPTH_EXIT,
#define MAP_DEPTH_FIRE MAP_DEPTH_EXIT
    MAP_DEPTH_OBJ,
    MAP_DEPTH_MONST,
    MAP_DEPTH_PLAYER,
    MAP_DEPTH_WEAPON,
    MAP_DEPTH,
};

#endif
