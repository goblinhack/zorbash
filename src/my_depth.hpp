//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_DEPTH_HPP_
#define _MY_DEPTH_HPP_

enum {
  MAP_DEPTH_THE_GRID,
  //
  // NOTE: adding more depths does have a performance hit.
  //
  MAP_DEPTH_FLOOR,
  MAP_DEPTH_FLOOR2,
  MAP_DEPTH_LIQUID,
  MAP_DEPTH_CHASM,
  //
  // Walls and player need to be the same depth or the player overlaps the wall
  //
  MAP_DEPTH_OBJ,
#define MAP_DEPTH_EXPLOSION_MINOR MAP_DEPTH_OBJ
  MAP_DEPTH_EXPLOSION_MAJOR,
  MAP_DEPTH_MESSAGE,
  MAP_DEPTH,
};

enum {
  MAP_PRIO_ALWAYS_BEHIND,
  MAP_PRIO_BEHIND,
  MAP_PRIO_NORMAL,
  MAP_PRIO_IN_FRONT,
  MAP_PRIO_IN_FRONT2, // weapons
  MAP_PRIO_IN_FRONT3, // rings
};

#endif
