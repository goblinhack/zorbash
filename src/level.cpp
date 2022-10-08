//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

std::string Level::to_string(void)
{
  TRACE_NO_INDENT();

  std::string level_no_str;
  if (dungeon_walk_order_level_no) {
    level_no_str = std::to_string(dungeon_walk_order_level_no);
  } else {
    level_no_str = world_at.to_string();
  }

  if (biome == BIOME_SEWER) {
    return ("sewer L" + level_no_str);
  } else if (biome == BIOME_SWAMP) {
    return ("swamp L" + level_no_str);
  } else if (biome == BIOME_WATER) {
    return ("water L" + level_no_str);
  } else {
    return ("dungeon L" + level_no_str);
  }
}

uint32_t Level::num(void)
{
  TRACE_NO_INDENT();
  return dungeon_walk_order_level_no;
}
