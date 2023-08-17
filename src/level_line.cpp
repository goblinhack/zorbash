//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

/*
 * Find all things on the path.
 */
std::vector< Thingp > Level::line(const point s, const point e, size_t max_elems)
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
    TRACE_NO_INDENT();
    FOR_ALL_THINGS_THAT_INTERACT(this, it, x0, y0)
    {
      out.push_back(it);

      if (max_elems) {
        if (out.size() >= max_elems) {
          return out;
        }
      }
    }
    TRACE_NO_INDENT();
    FOR_ALL_THINGS_END()

    if (x0 == x1 && y0 == y1) {
      break;
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

/*
 * Set everthing that is in the way on fire.
 */
void Level::line_set_all_on_fire(const point s, const point e, size_t max_elems, const std::string &why)
{
  TRACE_NO_INDENT();

  for (auto t : line(s, e, max_elems)) {
    //
    // Spawn scalding steam if the fire effect is over water.
    //
    if (t->is_water()) {
      thing_new(tp_find("steam"), t->curr_at);
      continue;
    }

    //
    // If over water then do not set things on fire.
    //
    if (is_water(t->curr_at)) {
      continue;
    }

    //
    // Don't set fire to the location of the firer.
    //
    if (t->curr_at == s) {
      continue;
    }

    t->on_fire_set(why);
  }
}

/*
 * Set everthing that is in the way on fire.
 */
void Level::line_set_all_undead_on_fire(const point s, const point e, size_t max_elems, const std::string &why)
{
  TRACE_NO_INDENT();

  for (auto t : line(s, e, max_elems)) {
    //
    // Don't set fire to the location of the firer.
    //
    if (t->curr_at == s) {
      continue;
    }

    if (t->is_undead()) {
      t->on_fire_set(why);
    }
  }
}
