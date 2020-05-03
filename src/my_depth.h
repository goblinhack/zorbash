//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#ifndef _MY_DEPTH_H_
#define _MY_DEPTH_H_

enum {
    MAP_DEPTH_FLOOR,
    MAP_DEPTH_HAZARD,
#define MAP_DEPTH_LAST_FLOOR_TYPE MAP_DEPTH_HAZARD
    MAP_DEPTH_WALLS,
    MAP_DEPTH_WALLS_DECO,
    MAP_DEPTH_FLOOR_DECO,
    MAP_DEPTH_EXIT,
#define MAP_DEPTH_FIRE MAP_DEPTH_EXIT
    MAP_DEPTH_ITEM,
    MAP_DEPTH_MONST,
    MAP_DEPTH_PLAYER,
    MAP_DEPTH_WEAPON,
    MAP_DEPTH_CURSOR,
    MAP_DEPTH,
};

#endif
