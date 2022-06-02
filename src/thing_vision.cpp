//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_thing.hpp"

bool Level::can_see_obstacle(int x, int y)
{
  if (is_wall(x, y) || is_door(x, y) || is_rock(x, y)) {
    return true;
  }

  return false;
}

bool Level::can_see_unimpeded(int x0, int y0, int x1, int y1)
{
  int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy, e2; /* error value e_xy */

  for (;;) { /* loop */
    if (x0 == x1 && y0 == y1) {
      break;
    }
    if (can_see_obstacle(x0, y0)) {
      return false;
    }
    e2 = 2 * err;
    if (e2 >= dy) {
      err += dy;
      x0 += sx;
    } /* e_xy+e_x > 0 */
    if (e2 <= dx) {
      err += dx;
      y0 += sy;
    } /* e_xy+e_y < 0 */
  }
  return true;
}

bool Level::can_see_unimpeded(const point &start, const point &end)
{
  return can_see_unimpeded(start.x, start.y, end.x, end.y);
}

point Thing::vision_source_get(void)
{
  if (is_minion() && distance_minion_vision_shared()) {
    auto mob = top_mob();
    if (mob) {
      return mob->curr_at;
    }
  }
  return curr_at;
}
