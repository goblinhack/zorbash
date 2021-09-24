//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_DEPTH_H_
#define _MY_DEPTH_H_

enum {
  MAP_DEPTH_THE_GRID,
  MAP_DEPTH_FLOOR,
  MAP_DEPTH_FLOOR2,
  MAP_DEPTH_WATER,
  MAP_DEPTH_LAVA,
  MAP_DEPTH_CHASM,
#define MAP_DEPTH_LAST_FLOOR_TYPE MAP_DEPTH_CHASM
  //
  // Walls and player need to be the same depth or the player
  // overlaps the wall
  //
  MAP_DEPTH_OBJ,
  MAP_DEPTH_WEAPON,
#define MAP_DEPTH_EXPLOSION_MINOR  MAP_DEPTH_WEAPON
#define MAP_DEPTH_LAST_FG_MAP_TYPE MAP_DEPTH_WEAPON
  MAP_DEPTH_EXPLOSION_MAJOR,
  MAP_DEPTH_MESSAGE,
  MAP_DEPTH,
};

enum {
  MAP_PRIO_ALWAYS_BEHIND,
  MAP_PRIO_BEHIND,
  MAP_PRIO_NORMAL,
  MAP_PRIO_INFRONT,
};

#endif
