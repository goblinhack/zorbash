//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_DEPTH_HPP_
#define _MY_DEPTH_HPP_

//
// Map depths are used to group objects together into similar types.
// They are also used as a rough way to sort order for displaying.
// The z-prio below is used for finer granularity sort ordering.
//
enum {
  MAP_DEPTH_FLOOR,
  MAP_DEPTH_FLOOR2,
  MAP_DEPTH_LIQUID,
  MAP_DEPTH_CHASM,
  MAP_DEPTH_OBJ,
  MAP_DEPTH_TOP,
  MAP_DEPTH,
};

#define MAP_DEPTH_ACID MAP_DEPTH_FLOOR2

//
// This is a sub level of sorting in addition to MAP_DEPTH. It allows
// for example OBJs to be sorted. It's really only used for that layer
// but could potentially be used by others.
//
enum {
  MAP_Z_PRIO_ALWAYS_BEHIND, // e.g. Dungeon entrance, walls
  MAP_Z_PRIO_BEHIND,        // e.g. Gargoyle podium
  MAP_Z_PRIO_ITEM,          // Normal items for carrying, like food, weapons
  MAP_Z_PRIO_WEB,           // Should be behind spiders
  MAP_Z_PRIO_FIRE,          // Flames!
  MAP_Z_PRIO_MOB,           // Mobs and dart traps / totems
  MAP_Z_PRIO_MONST,         // Spiders and more! Want monsters in front of fire, so you can see bats for e.g.
  MAP_Z_PRIO_FOLIAGE,       // In front of monsters so they hide
  MAP_Z_PRIO_PLAYER_TORSO,  // In front of foliage else we get lost!
  MAP_Z_PRIO_PLAYER_LEGS,   // Boots in front of torso
  MAP_Z_PRIO_PLAYER_FACE,   // Player's face
  MAP_Z_PRIO_PLAYER_EYES,   // Eyes in front of faces obviously
  MAP_Z_PRIO_PLAYER_HAIR,   // Hair over eyes
  MAP_Z_PRIO_PLAYER_HAT,    // And a hat to top it off
  MAP_Z_PRIO_CARRY,         // e.g. armor, swords
  MAP_Z_PRIO_CLOAK,         // Clock should be over armor?
  MAP_Z_PRIO_RING,          // Carried rings
  MAP_Z_PRIO_BARREL,        // In front of creatures for when they are trapped
  MAP_Z_PRIO_SWING,         // Attack animations
  MAP_Z_PRIO_BIG_MONST,     // Big monsters stand in front
  MAP_Z_PRIO_CONSUMER,      // e.g. a gelatinous cube
  MAP_Z_PRIO_EFFECT,        // Potion effects
  MAP_Z_PRIO_CURSOR,        // Selected path; you want this in front of large monsters so you can target them.
  MAP_Z_PRIO_LAST,
};

#define MAP_Z_PRIO_PLAYER_FIRST MAP_Z_PRIO_PLAYER_TORSO

enum {
  MAP_TICK_PRIO_VERY_HIGH, // e.g. Lasers
  MAP_TICK_PRIO_HIGH,      // Player
  MAP_TICK_PRIO_NORMAL,    // Monsters
  MAP_TICK_PRIO_LOW,       // Sewers, braziers
  MAP_TICK_PRIO,
};

using monst_class_t = enum monst_class {
  MONST_CLASS_ANY,
  MONST_CLASS_A,
  MONST_CLASS_B,
  MONST_CLASS_C,
  MONST_CLASS_D,
  MONST_CLASS_E,
  MONST_CLASS_MAX,
};

using monst_environ_t = enum monst_type {
  MONST_ENVIRON_NORMAL,
  MONST_ENVIRON_SHALLOW_WATER,
  MONST_ENVIRON_DEEP_WATER,
  MONST_ENVIRON_MAX,
};

enum {
  THING_SIZE_NOT_SET,
  THING_SIZE_TINY,
  THING_SIZE_SMALL,
  THING_SIZE_NORMAL,
  THING_SIZE_LARGE,
  THING_SIZE_GIANT,
  THING_SIZE_GARGANTUAN,
};

enum {
  MONST_STATE_IDLE,
  MONST_STATE_MOVING,
  MONST_STATE_SLEEPING,
  MONST_STATE_RESTING,
  MONST_STATE_OPEN_INVENTORY,
  MONST_STATE_USING_ENCHANTSTONE,
  MONST_STATE_USING_SKILLSTONE,
  MONST_STATE_USING_SPELLBOOK,
  MONST_STATE_REPACK_INVENTORY,
};

enum {
  MONST_EQUIP_HELMET,
  MONST_EQUIP_AMULET,
  MONST_EQUIP_GAUNTLET,
  MONST_EQUIP_CLOAK,
  MONST_EQUIP_SHIELD,
  MONST_EQUIP_ARMOR,
  MONST_EQUIP_WEAPON,
  MONST_EQUIP_RING1,
  MONST_EQUIP_BOOTS,
  MONST_EQUIP_RING2,
  MONST_EQUIP_MAX,
};
#define FOR_ALL_EQUIP(_equip_) for (auto _equip_ = 0; _equip_ < MONST_EQUIP_MAX; _equip_++)

enum {
  BODYPART_TORSO, // In front of foliage else we get lost!
  BODYPART_LEGS,  // Boots in front of torso
  BODYPART_FACE,  // Player's face
  BODYPART_EYES,  // Eyes in front of faces obviously
  BODYPART_HAIR,  // Hair over eyes
  BODYPART_HAT,   // And a hat to top it off
  BODYPART_MAX,
};
#define FOR_ALL_BODYPART(_bodypart_) for (auto _bodypart_ = 0; _bodypart_ < BODYPART_MAX; _bodypart_++)

using wid_depth_t = enum {
  TILE_LAYER_BG_0,
  TILE_LAYER_BG_1,
  TILE_LAYER_FG_0,
  TILE_LAYER_FG_1,
  TILE_LAYER_FG_2,
  TILE_LAYER_FG_3,
  TILE_LAYER_FG_4,
  TILE_LAYER_FG_5,
  TILE_LAYER_FG_6,
  TILE_LAYER_FG_7,
  TILE_LAYER_FG_8,
  TILE_LAYER_FG_9,
  TILE_LAYER_MAX,
};

#endif
