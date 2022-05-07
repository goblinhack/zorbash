//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_globals.hpp"
#include "my_laser.hpp"
#include "my_projectile.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_tex.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"

//
// Periodic updates
//
void Level::update(void)
{
  dbg("Update");
  TRACE_AND_INDENT();

  if (is_map_changed) {
    is_map_changed = false;
    update_map();
  }

  if (game->request_reset_state) {
    game->change_state(Game::STATE_NORMAL);
    game->request_reset_state = false;
  }

  if (game->request_update_same_level) {
    game->request_update_same_level = false;
    update_same_level();
  }
}

//
// Get the bounds. Needs to be a bit off-map for reflections.
//
void Level::display_map_set_bounds(void)
{
  TRACE_AND_INDENT();

  int border = MAP_BORDER_ROCK + 2;
  minx       = std::max(0, (int) map_at.x - border);
  maxx       = std::min(MAP_WIDTH, (int) minx + TILES_ACROSS + (border * 2));

  miny = std::max(0, (int) map_at.y - border);
  maxy = std::min(MAP_HEIGHT, (int) miny + TILES_DOWN + (border * 2));

  map_tl = point(minx, miny);
  map_br = point(maxx, maxy);

  scroll_map_set_target();
  scroll_map();
}
