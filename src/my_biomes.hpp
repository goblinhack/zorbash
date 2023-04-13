//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_BIOMES_HPP_
#define _MY_BIOMES_HPP_

#include "my_color.hpp"
#include "my_point3d.hpp"

using biome_t = enum biome_type {
  BIOME_UNKNOWN,
  BIOME_DUNGEON, // A single dungeon
  BIOME_SWAMP,
  BIOME_SEWER,
  BIOME_ICE,
  BIOME_CHASMS,
  BIOME_LAVA,
  BIOME_DUNGEONS, // The grid of dungeons
  BIOME_MAX,
};

#define BIOME_DUNGEON_COLOR GRAY50
#define BIOME_SWAMP_COLOR   OLIVEDRAB
#define BIOME_SEWER_COLOR   GRAY50
#define BIOME_ICE_COLOR     CYAN3
#define BIOME_CHASMS_COLOR  STEELBLUE3
#define BIOME_LAVA_COLOR    LAVA

biome_t     get_biome(point3d world_at, int difficulty_depth);
biome_t     get_biome(int difficulty_depth);
color       get_biome_color(biome_t biome);
color       get_difficulty_depth_color(int difficulty_depth);
std::string biome_to_string(biome_t biome);

#endif /*_MY_BIOMES_HPP_ */
