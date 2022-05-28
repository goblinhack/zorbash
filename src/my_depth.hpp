//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_DEPTH_HPP_
#define _MY_DEPTH_HPP_

//
// Map depths are used to group objects together into similar types.
// They are also used as a rough way to sort order for displaying.
// The z-prio below is used for finer granularity sort ordering.
enum {
  MAP_DEPTH_FLOOR,
  MAP_DEPTH_FLOOR2,
  MAP_DEPTH_LIQUID,
  MAP_DEPTH_CHASM,
  MAP_DEPTH_OBJ,
  MAP_DEPTH_TOP,
  MAP_DEPTH,
};

enum {
  MAP_Z_PRIO_ALWAYS_BEHIND, // e.g. Dungeon entrance, walls
  MAP_Z_PRIO_BEHIND,        // e.g. Gargoyle podium
  MAP_Z_PRIO_ITEM,          // Normal items for carrying, like food, weapons
  MAP_Z_PRIO_FIRE,          // Flames!
  MAP_Z_PRIO_CURSOR,        // Selected path
  MAP_Z_PRIO_WEB,           // Should be behind spiders
  MAP_Z_PRIO_MONST,         // Spiders and more!
  MAP_Z_PRIO_FOILAGE,       // In front of monsters so they hide
  MAP_Z_PRIO_PLAYER,        // In front of foilage else we get lost!
  MAP_Z_PRIO_CARRY,         // e.g. armor, swords
  MAP_Z_PRIO_CLOAK,         // Clock should be over armor?
  MAP_Z_PRIO_RING,          // Carried rings
  MAP_Z_PRIO_BARREL,        // In front of creatures for when they are trapped
  MAP_Z_PRIO_SWING,         // Attack animations
  MAP_Z_PRIO_CONSUMER,      // e.g. a gelatinous cube
  MAP_Z_PRIO_EFFECT,        // Potion effects
};

#endif
