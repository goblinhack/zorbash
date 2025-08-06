//
// Copyright goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

//
// Return the dmap distance. DMAP_IS_WALL if not reachable.
//
int Thing::distance_to_player(void)
{
  TRACE_AND_INDENT();

  if (! game->level) {
    return DMAP_IS_WALL;
  }

  auto player = game->level->player;
  if (! player) {
    return DMAP_IS_WALL;
  }

  //
  // Check we're on the same level
  //
  if (player->level != level) {
    return DMAP_IS_WALL;
  }

  return get(&game->level->dmap_to_player.val, (int) curr_at.x, (int) curr_at.y);
}

int Thing::distance_to_player_on_different_level(void)
{
  TRACE_AND_INDENT();

  if (! game->level) {
    return DMAP_IS_WALL;
  }

  auto player = game->level->player;
  if (! player) {
    return DMAP_IS_WALL;
  }

  return get(&player->level->dmap_to_player.val, (int) curr_at.x, (int) curr_at.y);
}

void Level::dmap_to_player_update(void)
{
  TRACE_AND_INDENT();
  if (! player) {
    return;
  }

#if 0
  //
  // Limit the size of the dmap for performance?
  //
  auto max_dist = 20;
  int minx = player->curr_at.x - max_dist;
  int maxx = player->curr_at.x + max_dist;
  int miny = player->curr_at.y - max_dist;
  int maxy = player->curr_at.y + max_dist;
#endif

  int minx = 0;
  int maxx = MAP_WIDTH;
  int miny = 0;
  int maxy = MAP_HEIGHT;

  //
  // Set up obstacles for the search
  //
  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      if ((x >= minx) && (x <= maxx) && (y >= miny) && (y <= maxy)) {
        if (is_obs_wall_or_door(point(x, y))) {
          set(dmap_to_player.val, x, y, DMAP_IS_WALL);
        } else {
          set(dmap_to_player.val, x, y, DMAP_IS_PASSABLE);
        }
      } else {
        set(dmap_to_player.val, x, y, DMAP_IS_WALL);
      }
    }
  }

  set(dmap_to_player.val, player->curr_at.x, player->curr_at.y, DMAP_IS_GOAL);

  dmap_process_allow_diagonals(&dmap_to_player, point(0, 0), point(MAP_WIDTH - 1, MAP_HEIGHT - 1), true);

  IF_DEBUG3
  {
    LOG("Player dmap:");
    dmap_print(&dmap_to_player);
  }
}
