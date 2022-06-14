//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

uint32_t Level::get_is_map_changed(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_map_changed, x, y));
}

uint32_t Level::get_is_map_changed_no_check(const int x, const int y)
{
  return (get_no_check(_is_map_changed, x, y));
}

void Level::is_map_changed_no_check_set(const int x, const int y) { set(_is_map_changed, x, y, game->tick_current); }

void Level::is_map_changed_set(const int x, const int y) { set(_is_map_changed, x, y, game->tick_current); }

void Level::is_map_changed_no_check_set(const int x, const int y, uint32_t v)
{
  set_no_check(_is_map_changed, x, y, v);
}

void Level::is_map_changed_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_map_changed, x, y, (uint32_t) 0);
}

void Level::is_map_changed_no_check_unset(const int x, const int y)
{
  set_no_check(_is_map_changed, x, y, (uint32_t) 0);
}
