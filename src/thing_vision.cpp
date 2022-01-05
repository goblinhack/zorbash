//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

bool Level::can_see_obstacle(int x, int y)
{
  if (is_wall(x, y) || is_door(x, y) || is_rock(x, y)) {
    return true;
  }

  return false;
}

bool Level::can_see_(int x0_in, int y0_in, int x1_in, int y1_in, int flag)
{
  float temp;
  float dx;
  float dy;
  float tdy;
  float dydx;
  float p;
  float x;
  float y;
  float i;

  float x0 = x0_in;
  float y0 = y0_in;
  float x1 = x1_in;
  float y1 = y1_in;

  if (x0 > x1) {
    temp = x0;
    x0   = x1;
    x1   = temp;

    temp = y0;
    y0   = y1;
    y1   = temp;
  }

  dx = x1 - x0;
  dy = y1 - y0;

  tdy  = 2.0 * dy;
  dydx = tdy - (2.0 * dx);

  p = tdy - dx;
  x = x0;
  y = y0;

  if (flag == 0) {
    if (can_see_obstacle((int) x, (int) y)) {
      return true;
    }
  } else if (flag == 1) {
    if (can_see_obstacle((int) y, (int) x)) {
      return true;
    }
  } else if (flag == 2) {
    if (can_see_obstacle((int) y, (int) -x)) {
      return true;
    }
  } else if (flag == 3) {
    if (can_see_obstacle((int) x, (int) -y)) {
      return true;
    }
  }

  for (i = 1; i <= dx; i++) {
    x++;

    if (p < 0) {
      p += tdy;
    } else {
      p += dydx;
      y++;
    }

    if (flag == 0) {
      if (can_see_obstacle((int) x, (int) y)) {
        return true;
      }
    } else if (flag == 1) {
      if (can_see_obstacle((int) y, (int) x)) {
        return true;
      }
    } else if (flag == 2) {
      if (can_see_obstacle((int) y, (int) -x)) {
        return true;
      }
    } else if (flag == 3) {
      if (can_see_obstacle((int) x, (int) -y)) {
        return true;
      }
    }
  }

  return false;
}

/*
 * Can A see B unimpeded?
 */
bool Level::can_see_unimpeded(int x0, int y0, int x1, int y1)
{
  float slope = 100.0;

  if (x0 != x1) {
    slope = (y1 - y0) * (1.0 / (x1 - x0));
  }

  int r;

  if ((0 <= slope) && (slope <= 1)) {
    r = can_see_(x0, y0, x1, y1, 0);
  } else if ((-1 <= slope) && (slope <= 0)) {
    r = can_see_(x0, -y0, x1, -y1, 3);
  } else if (slope > 1) {
    r = can_see_(y0, x0, y1, x1, 1);
  } else {
    r = can_see_(-y0, x0, -y1, x1, 2);
  }

  return (! r);
}

point Thing::get_vision_source(void)
{
  if (is_minion() && distance_minion_vision_shared()) {
    auto mob_spawner = get_top_mob_spawner();
    if (mob_spawner) {
      return mob_spawner->curr_at;
    }
  }
  return curr_at;
}
