//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"

std::string Level::to_string(void)
{
  TRACE_NO_INDENT();

  std::string level_no_str;
  if (dungeon_walk_order_level_no) {
    level_no_str = std::to_string(dungeon_walk_order_level_no);
  } else {
    level_no_str = world_at.to_string();
  }

  //
  // This makes more sense from an end user point of view as it matches the level
  // seen on the rightbar
  //
  level_no_str = std::to_string(num());

  if (biome == BIOME_SEWER) {
    return ("sewer L" + level_no_str);
  }
  if (biome == BIOME_SWAMP) {
    return ("swamp L" + level_no_str);
  }
  if (biome == BIOME_ICE) {
    return ("ice L" + level_no_str);
  }
  if (biome == BIOME_CHASMS) {
    return ("chasms L" + level_no_str);
  }
  if (biome == BIOME_LAVA) {
    return ("lava L" + level_no_str);
  }
  return ("dungeon L" + level_no_str);
}

uint32_t Level::num(void)
{
  TRACE_NO_INDENT();
  return dungeon_walk_order_level_no;
}
