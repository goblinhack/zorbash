//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_thing.hpp"

bool Level::can_see_obstacle(int x, int y) { return is_obs_wall_or_door(x, y); }

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
  if (distance_minion_vision_shared()) {
    auto mob = top_mob();
    if (mob) {
      return mob->curr_at;
    }
  }
  return curr_at;
}

float Thing::distance_vision_get(void)
{
  TRACE_NO_INDENT();

  //
  // Limit vision by torch light if needed.
  //
  auto v = tp()->distance_vision();

  if (is_able_to_see_in_the_dark()) {
    return v;
  }

  auto l = light_dist_get();

  if (l < v) {
    return l;
  }
  return v;
}
