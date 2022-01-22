//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_dungeon_grid.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_globals_extra.hpp"
#include "my_level.hpp"
#include "my_random.hpp"
#include "my_random_name.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_skillbox.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_topcon.hpp"
#include "my_world.hpp"

bool Game::init_level(point3d world_at, point grid_at, int difficulty_depth, int dungeon_walk_order_level_no)
{
  DBG("Game init level %d,%d,%d", world_at.x, world_at.y, world_at.z);
  TRACE_AND_INDENT();

  if (world_at.z >= LEVELS_DEEP) {
    LOG("Cannot create new level at: %d,%d,%d, too deep", world_at.x, world_at.y, world_at.z);
    return false;
  }

  auto level_seed = seed + world_at.x + world_at.y + world_at.z;
  TRACE_AND_INDENT();
  auto l = get(world.levels, world_at.x, world_at.y, world_at.z);
  TRACE_AND_INDENT();
  if (! l) {
    DBG("Create new level at: %d,%d,%d", world_at.x, world_at.y, world_at.z);
    world.new_level_at(world_at, grid_at, level_seed, difficulty_depth, dungeon_walk_order_level_no);
    l = get(world.levels, world_at.x, world_at.y, world_at.z);
    if (! l) {
      ERR("No level created at: %d,%d,%d", game->current_level.x, game->current_level.y, game->current_level.z);
      return false;
    }
  } else {
    LOG("Level already exists: %d,%d,%d", world_at.x, world_at.y, world_at.z);
  }
  return true;
}
