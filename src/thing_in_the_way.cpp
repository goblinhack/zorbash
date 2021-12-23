//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

Thingp Thing::in_the_way(const point s, const point e, int x, int y)
{
  point p(x, y);
  if (p == s) {
    return nullptr;
  }
  if (p == e) {
    return nullptr;
  }
  FOR_ALL_THINGS_THAT_INTERACT(level, t, x, y)
  {
    //
    // Occassionally allow goblins to fire through comrades
    //
    if (same_leader(t)) {
      if ((int) pcg_random_range(0, 100) > collateral_damage_pct()) {
        return t;
      }
      continue;
    }

    if (t->is_attackable_by_player() || t->is_attackable_by_monst()) {
      log("This is in the way: %s", t->to_short_string().c_str());
      return t;
    }
  }
  FOR_ALL_THINGS_END()

  return nullptr;
}

Thingp Thing::in_the_way_(const point s, const point e, int x0_in, int y0_in, int x1_in, int y1_in, int flag)
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

  Thingp it = nullptr;

  if (flag == 0) {
    it = in_the_way(s, e, (int) x, (int) y);
  } else if (flag == 1) {
    it = in_the_way(s, e, (int) y, (int) x);
  } else if (flag == 2) {
    it = in_the_way(s, e, (int) y, (int) -x);
  } else if (flag == 3) {
    it = in_the_way(s, e, (int) x, (int) -y);
  }

  if (it) {
    return it;
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
      it = in_the_way(s, e, (int) x, (int) y);
    } else if (flag == 1) {
      it = in_the_way(s, e, (int) y, (int) x);
    } else if (flag == 2) {
      it = in_the_way(s, e, (int) y, (int) -x);
    } else if (flag == 3) {
      it = in_the_way(s, e, (int) x, (int) -y);
    }

    if (it) {
      return it;
    }
  }

  return nullptr;
}

/*
 * We're trying to hit a target, but something might be in the way.
 */
Thingp Thing::in_the_way(const point s, const point e)
{
  float slope = 100.0;

  int x0 = s.x;
  int y0 = s.y;
  int x1 = e.x;
  int y1 = e.y;

  if (x0 != x1) {
    slope = (y1 - y0) * (1.0 / (x1 - x0));
  }

  Thingp it;

  if ((0 <= slope) && (slope <= 1)) {
    it = in_the_way_(s, e, x0, y0, x1, y1, 0);
  } else if ((-1 <= slope) && (slope <= 0)) {
    it = in_the_way_(s, e, x0, -y0, x1, -y1, 3);
  } else if (slope > 1) {
    it = in_the_way_(s, e, y0, x0, y1, x1, 1);
  } else {
    it = in_the_way_(s, e, -y0, x0, -y1, x1, 2);
  }

  return it;
}
