//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_dungeon.h"
#include "my_thing.h"
#include "my_sdl.h"
#include "my_gl.h"

//
// New or loaded level
//
void Level::update_new_level(void)
{
  TRACE_AND_INDENT();
  minimap_valid    = false;
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
  minimap_valid    = false;
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
  minimap_valid    = false;
  is_heatmap_valid = false;

  scroll_map_to_player_immediately();
  lights_update_new_level();
  dmap_to_player_update();
}
