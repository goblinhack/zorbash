//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_DEPTH_HPP_
#define _MY_DEPTH_HPP_

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
  MAP_DEPTH_EQUIP,
#define MAP_DEPTH_EXPLOSION_MINOR  MAP_DEPTH_EQUIP
#define MAP_DEPTH_LAST_FG_MAP_TYPE MAP_DEPTH_EQUIP
  MAP_DEPTH_EXPLOSION_MAJOR,
  MAP_DEPTH_MESSAGE,
  MAP_DEPTH,
};

enum {
  MAP_PRIO_ALWAYS_BEHIND,
  MAP_PRIO_BEHIND,
  MAP_PRIO_NORMAL,
  MAP_PRIO_IN_FRONT,
};

#endif
