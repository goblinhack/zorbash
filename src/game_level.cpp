//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_dungeon_grid.hpp"
#include "my_game.hpp"
#include "my_game_dungeons.hpp"
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

void Game::init_level(point3d p, int difficulty_depth, int dungeon_depth)
{
  DBG("Game init level %d,%d,%d", p.x, p.y, p.z);
  TRACE_AND_INDENT();

  auto level_seed = seed + p.x + p.y + p.z;
  TRACE_AND_INDENT();
  auto l = get(world.levels, p.x, p.y, p.z);
  TRACE_AND_INDENT();
  if (! l) {
    DBG("Create new level at: %d,%d,%d", p.x, p.y, p.z);
    world.new_level_at(p, level_seed, difficulty_depth, dungeon_depth);
    l = get(world.levels, p.x, p.y, p.z);
    if (! l) {
      ERR("No level created at: %d,%d,%d", game->current_level.x, game->current_level.y, game->current_level.z);
    }
  } else {
    LOG("Level already exists: %d,%d,%d", p.x, p.y, p.z);
  }
}
