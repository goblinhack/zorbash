//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_dungeon.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

//
// New or loaded level
//
void Level::update_new_level(void)
{
  TRACE_AND_INDENT();
  map_mini_valid    = false;
  is_heatmap_valid = false;

  scroll_map_to_player_immediately();
  lights_update_new_level();
  dmap_to_player_update();

  //
  // Load what we were able to see previously
  //
  sdl_fbo_load(FBO_FULLMAP_LIGHT, fbo_light);
}

//
// Something changed on the level
//
void Level::update_same_level(void)
{
  TRACE_AND_INDENT();
  map_mini_valid    = false;
  is_heatmap_valid = false;

  lights_update_same_level();
  dmap_to_player_update();
}

//
// For example, a zoom change
//
void Level::update_same_level_immediately(void)
{
  TRACE_AND_INDENT();
  map_mini_valid    = false;
  is_heatmap_valid = false;

  scroll_map_to_player_immediately();
  lights_update_new_level();
  dmap_to_player_update();
}
