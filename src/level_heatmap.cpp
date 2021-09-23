//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_level.h"
#include "my_array_bounds_check.h"

uint8_t Level::heatmap(const point &p)
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_heatmap, p.x, p.y));
}

uint8_t Level::heatmap_no_check(const point &p) { return (get_no_check(_heatmap, p.x, p.y)); }

uint8_t Level::heatmap(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_heatmap, x, y));
}

uint8_t Level::heatmap_no_check(const int x, const int y) { return (get_no_check(_heatmap, x, y)); }

void Level::incr_heatmap(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  uint8_t v = get(_heatmap, x, y);
  if (v < 255) {
    set(_heatmap, x, y, (uint8_t) (v + 1));
  }
}

void Level::incr_heatmap_no_check(const int x, const int y, int dv)
{
  uint8_t v = get_no_check(_heatmap, x, y);
  if (v < 255) {
    set_no_check(_heatmap, x, y, (uint8_t) (v + dv));
  }
}

void Level::incr_heatmap_no_check(const int x, const int y)
{
  uint8_t v = get_no_check(_heatmap, x, y);
  if (v < 255) {
    set_no_check(_heatmap, x, y, (uint8_t) (v + 1));
  }
}

void Level::unset_heatmap(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_heatmap, x, y, (uint8_t) 0);
}

void Level::unset_heatmap_no_check(const int x, const int y) { set_no_check(_heatmap, x, y, (uint8_t) 0); }

void Level::update_heatmap(void)
{
  _heatmap = {};

  for (auto y = MAP_BORDER_ROOM; y < MAP_HEIGHT - MAP_BORDER_ROOM; y++) {
    for (auto x = MAP_BORDER_ROOM; x < MAP_WIDTH - MAP_BORDER_ROOM; x++) {
      if (is_lava(x, y) || is_fire(x, y)) {
        incr_heatmap_no_check(x + 1, y + 1);
        incr_heatmap_no_check(x, y + 1);
        incr_heatmap_no_check(x - 1, y + 1);
        incr_heatmap_no_check(x + 1, y);
        incr_heatmap_no_check(x, y, 10);
        incr_heatmap_no_check(x - 1, y);
        incr_heatmap_no_check(x + 1, y - 1);
        incr_heatmap_no_check(x, y - 1);
        incr_heatmap_no_check(x - 1, y - 1);
      }
    }
  }

  is_heatmap_valid = true;

#if 0
  printf("\n");
  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      if (is_obs_wall_or_door(x, y)) {
        printf("X");
        continue;
      }
      if (get(_heatmap, x, y)) {
        if (get(_heatmap, x, y) < 10) {
          printf("_");
          continue;
        }
        printf("%c", '1' + get(_heatmap, x, y));
        continue;
      }
      printf(".");
    }
    printf("\n");
  }
#endif
}
