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
#define MAP_DEPTH_CURSOR MAP_DEPTH_EXPLOSION_MAJOR
  MAP_DEPTH_MESSAGE,
  MAP_DEPTH,
};

enum {
  MAP_PRIO_ALWAYS_BEHIND, // e.g. Dungeon entrance
  MAP_PRIO_BEHIND,        // e.g. Gargoyle podium
  MAP_PRIO_ITEM,          // Normal items for carrying, like food, weapons
  MAP_PRIO_FIRE,          // Flames!
  MAP_PRIO_CURSOR,        // Selected path
  MAP_PRIO_WEB,           // Should be behind spiders
  MAP_PRIO_MONST,         // Spiders and more!
  MAP_PRIO_FOILAGE,       // In front of monsters so they hide
  MAP_PRIO_PLAYER,        // In front of foilage else we get lost!
  MAP_PRIO_CARRY,         // e.g. armor, swords
  MAP_PRIO_CLOAK,         // Clock should be over armor?
  MAP_PRIO_RING,          // Carried rings
  MAP_PRIO_BARREL,        // In front of creatures for when they are trapped
  MAP_PRIO_SWING,         // Attack animations
  MAP_PRIO_CONSUMER,      // e.g. a gelatinous cube
  MAP_PRIO_EFFECT,        // Potion effects
};

#endif
