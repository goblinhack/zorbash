//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_dungeon.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_sdl_proto.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

//
// New or loaded level
//
void Level::update_new_level(void)
{
  TRACE_AND_INDENT();
  is_map_mini_valid = false;
  is_heatmap_valid  = false;

  if (game->level == this) {
    log("Updating current level");
  }

  if (player) {
    dbg("Update new level with player present");
    if (game->level != this) {
      dbg("Game level is not set yet.");
    }
  } else {
    dbg("Update new level with no player present");
  }

  scroll_map_to_player_immediately();
  lights_update_new_level();
  dmap_to_player_update();

  //
  // Load what we were able to see previously
  //
  sdl_fbo_load(FBO_PIXELART_FULLMAP_LIGHT, fbo_light);
}

//
// Something changed on the level
//
void Level::update_same_level(void)
{
  TRACE_AND_INDENT();
  is_map_mini_valid = false;
  is_heatmap_valid  = false;

  lights_update_same_level();
  dmap_to_player_update();
}

//
// For example, a zoom change
//
void Level::update_same_level_immediately(void)
{
  TRACE_AND_INDENT();
  is_map_mini_valid = false;
  is_heatmap_valid  = false;

  scroll_map_to_player_immediately();
  lights_update_new_level();
  dmap_to_player_update();
}
