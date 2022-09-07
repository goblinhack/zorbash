//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

Thingp Thing::in_the_way_for_jumping(const point s, const point e, int x, int y)
{
  TRACE_NO_INDENT();

  point p(x, y);

  FOR_ALL_COLLISION_THINGS(level, t, x, y)
  {
    if (t == this) {
      continue;
    }

    //
    // So missiles do not hit blood or maps
    //
    if (t->is_flat()) {
      continue;
    }

    if (t->is_dead) {
      continue;
    }

    if (t->is_open) {
      continue;
    }

    if (t->is_jump_blocker()) {
      dbg("This is in the way: %s", t->to_short_string().c_str());
      return t;
    }
  }
  FOR_ALL_THINGS_END()

  return nullptr;
}

//
// We're trying to jump, but something might be in the way.
//
std::vector< Thingp > Thing::in_the_way_for_jumping(const point s, const point e, size_t max_elems)
{
  TRACE_NO_INDENT();

  std::vector< Thingp > out;

  int x0 = s.x;
  int y0 = s.y;
  int x1 = e.x;
  int y1 = e.y;

  int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy, e2; /* error value e_xy */

  for (;;) { /* loop */
    if (x0 == x1 && y0 == y1) {
      break;
    }

    auto it = in_the_way_for_jumping(s, e, x0, y0);
    if (it) {
      out.push_back(it);
      if (max_elems) {
        if (out.size() >= max_elems) {
          return out;
        }
      }
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
  return out;
}
