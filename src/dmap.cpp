//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_dmap.hpp"
#include "my_main.hpp"
#include "my_sdl.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing_defs.hpp"

void dmap_print(const Dmap *D, point at, point tl, point br)
{
  uint8_t x;
  uint8_t y;

  int minx, miny, maxx, maxy;
  if (tl.x < br.x) {
    minx = tl.x;
    maxx = br.x;
  } else {
    minx = br.x;
    maxx = tl.x;
  }
  if (tl.y < br.y) {
    miny = tl.y;
    maxy = br.y;
  } else {
    miny = br.y;
    maxy = tl.y;
  }

  if (minx < 0) {
    minx = 0;
  }
  if (miny < 0) {
    miny = 0;
  }
  if (maxx >= MAP_WIDTH) {
    maxx = MAP_WIDTH - 1;
  }
  if (maxy >= MAP_HEIGHT) {
    maxy = MAP_HEIGHT - 1;
  }

  bool all_walls;

  //
  // Try to minimize the DMAP area if it is mostly walls at the edges, for speed.
  //
  all_walls = true;
  for (x = minx; (x < maxx) && all_walls; x++) {
    for (y = miny; (y < maxy) && all_walls; y++) {
      all_walls = get(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      minx = x;
    }
  }

  all_walls = true;
  for (x = maxx; (x > minx) && all_walls; x--) {
    for (y = miny; (y < maxy) && all_walls; y++) {
      all_walls = get(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      maxx = x;
    }
  }

  all_walls = true;
  for (y = miny; (y < maxy) && all_walls; y++) {
    for (x = minx; (x < maxx) && all_walls; x++) {
      all_walls = get(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      miny = y;
    }
  }

  all_walls = true;
  for (y = maxy; (y > miny) && all_walls; y--) {
    for (x = minx; (x < maxx) && all_walls; x++) {
      all_walls = get(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      maxy = y;
    }
  }

  LOG("DMAP: tl %d,%d br %d %d at %d,%d", minx, miny, maxx, maxy, at.x, at.y);

  for (y = miny; y <= maxy; y++) {
    std::string debug;
    for (x = minx; x <= maxx; x++) {
      uint8_t e = get(D->val, x, y);
      if (point(x, y) == at) {
        debug += ("  @");
        continue;
      }
      if (e == DMAP_IS_WALL) {
        debug += (" ##");
        continue;
      }
      if (e == DMAP_IS_PASSABLE) {
        debug += ("  p");
        continue;
      }

      if (e > 0) {
        debug += string_sprintf("%3X", e);
      } else {
        debug += "  *";
      }
    }
    LOG("DMAP: %s", debug.c_str());
  }
}

void dmap_print(const Dmap *D)
{
  uint8_t x;
  uint8_t y;

  LOG("DMAP:");

  for (y = 0; y < MAP_HEIGHT; y++) {
    std::string debug;
    for (x = 0; x < MAP_WIDTH; x++) {
      uint8_t e = get(D->val, x, y);
      if (e == DMAP_IS_WALL) {
        debug += (" ##");
        continue;
      }
      if (e == DMAP_IS_PASSABLE) {
        debug += ("  .");
        continue;
      }

      if (e > 0) {
        debug += string_sprintf("%3X", e);
      } else {
        debug += "  *";
      }
    }
    LOG("DMAP: %s", debug.c_str());
  }
}

void dmap_process(Dmap *D, point tl, point br)
{
  uint8_t                                                           x;
  uint8_t                                                           y;
  uint8_t                                                           a;
  uint8_t                                                           b;
  uint8_t                                                           c;
  uint8_t                                                           d;
  uint8_t                                                          *e;
  uint8_t                                                           f;
  uint8_t                                                           g;
  uint8_t                                                           h;
  uint8_t                                                           i;
  uint8_t                                                           lowest;
  uint8_t                                                           changed;
  static std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > orig;
  static std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > orig_valid;
  static std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > valid;

  int minx, miny, maxx, maxy;
  if (tl.x < br.x) {
    minx = tl.x;
    maxx = br.x;
  } else {
    minx = br.x;
    maxx = tl.x;
  }
  if (tl.y < br.y) {
    miny = tl.y;
    maxy = br.y;
  } else {
    miny = br.y;
    maxy = tl.y;
  }

  if (minx < 0) {
    minx = 0;
  }
  if (miny < 0) {
    miny = 0;
  }
  if (maxx >= MAP_WIDTH) {
    maxx = MAP_WIDTH - 1;
  }
  if (maxy >= MAP_HEIGHT) {
    maxy = MAP_HEIGHT - 1;
  }

  //
  // Need a wall around the dmap or the search will sort of trickle off the map
  //
  for (y = miny; y < maxy; y++) {
    set(D->val, minx, y, DMAP_IS_WALL);
    set(D->val, maxx - 1, y, DMAP_IS_WALL);
  }
  for (x = minx; x < maxx; x++) {
    set(D->val, x, miny, DMAP_IS_WALL);
    set(D->val, x, maxy - 1, DMAP_IS_WALL);
  }

  bool all_walls;

  //
  // Try to minimize the DMAP area if it is mostly walls at the edges, for speed.
  //
  all_walls = true;
  for (x = minx; (x < maxx) && all_walls; x++) {
    for (y = miny; (y < maxy) && all_walls; y++) {
      all_walls = get(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      minx = x;
    }
  }

  all_walls = true;
  for (x = maxx; (x > minx) && all_walls; x--) {
    for (y = miny; (y < maxy) && all_walls; y++) {
      all_walls = get(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      maxx = x;
    }
  }

  all_walls = true;
  for (y = miny; (y < maxy) && all_walls; y++) {
    for (x = minx; (x < maxx) && all_walls; x++) {
      all_walls = get(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      miny = y;
    }
  }

  all_walls = true;
  for (y = maxy; (y > miny) && all_walls; y--) {
    for (x = minx; (x < maxx) && all_walls; x++) {
      all_walls = get(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      maxy = y;
    }
  }

  for (y = miny + 1; y < maxy - 1; y++) {
    for (x = minx + 1; x < maxx - 1; x++) {
      set(orig, x, y, get(D->val, x, y));

      e = &getref(D->val, x, y);
      if (*e != DMAP_IS_WALL) {
        set(valid, x, y, (uint8_t) 1);
        set(orig_valid, x, y, (uint8_t) 1);
        continue;
      }

      set(valid, x, y, (uint8_t) 0);
      set(orig_valid, x, y, (uint8_t) 0);
    }
  }

  do {
    changed = false;

    for (y = miny + 1; y < maxy - 1; y++) {
      for (x = minx + 1; x < maxx - 1; x++) {
        if (! get(orig_valid, x, y)) {
          continue;
        }

        if (! get(valid, x, y)) {
          continue;
        }

        e = &getref(D->val, x, y);

        //
        // Avoid diagonal moves.
        //
        if ((get(D->val, x - 1, y) == DMAP_IS_WALL) || (get(D->val, x, y - 1) == DMAP_IS_WALL)) {
          a = DMAP_IS_WALL;
        } else {
          a = get(D->val, x - 1, y - 1);
        }

        b = get(D->val, x, y - 1);

        if ((get(D->val, x + 1, y) == DMAP_IS_WALL) || (get(D->val, x, y - 1) == DMAP_IS_WALL)) {
          c = DMAP_IS_WALL;
        } else {
          c = get(D->val, x + 1, y - 1);
        }

        d = get(D->val, x - 1, y);
        f = get(D->val, x + 1, y);

        if ((get(D->val, x - 1, y) == DMAP_IS_WALL) || (get(D->val, x, y + 1) == DMAP_IS_WALL)) {
          g = DMAP_IS_WALL;
        } else {
          g = get(D->val, x - 1, y + 1);
        }

        h = get(D->val, x, y + 1);

        if ((get(D->val, x + 1, y) == DMAP_IS_WALL) || (get(D->val, x, y + 1) == DMAP_IS_WALL)) {
          i = DMAP_IS_WALL;
        } else {
          i = get(D->val, x + 1, y + 1);
        }

        if (a < b) {
          lowest = a;
        } else {
          lowest = b;
        }

        if (c < lowest) {
          lowest = c;
        }
        if (d < lowest) {
          lowest = d;
        }
        if (f < lowest) {
          lowest = f;
        }
        if (g < lowest) {
          lowest = g;
        }
        if (h < lowest) {
          lowest = h;
        }
        if (i < lowest) {
          lowest = i;
        }

        if (*e - lowest >= 2) {
          *e      = lowest + 1;
          changed = true;
        }
      }
    }
  } while (changed);

  //
  // Mix in any original depth stats
  //
  for (y = miny + 1; y < maxy - 1; y++) {
    for (x = minx + 1; x < maxx - 1; x++) {
      uint8_t o = get(orig, x, y);
      if (o != DMAP_IS_WALL) {
        if (o > DMAP_IS_PASSABLE) {
          o         = o - DMAP_IS_PASSABLE;
          uint8_t n = get(D->val, x, y);
          if (o + n < DMAP_IS_PASSABLE) {
            incr(D->val, x, y, o);
          }
        }
      }
    }
  }
}

void dmap_process(Dmap *D)
{
#if 0
  //
  // Sanity check the dmap does not take too much time
  //
  if (unlikely(g_opt_debug1)) {
    auto before = SDL_GetTicks();
    dmap_process(D, point(0, 0), point(MAP_WIDTH, MAP_HEIGHT));
    auto after = SDL_GetTicks();
    if (after - before > 70) {
      ERR("DMAP is taking too long, %d ms", after - before);
      dmap_print(D);
    }
  } else {
    dmap_process(D, point(0, 0), point(MAP_WIDTH, MAP_HEIGHT));
  }
#else
  dmap_process(D, point(0, 0), point(MAP_WIDTH, MAP_HEIGHT));
#endif
}

static bool is_obs_wall_or_door_at(const Dmap *D, int x, int y)
{
  if ((x >= MAP_WIDTH) || (y >= MAP_HEIGHT) || (x < 0) || (y < 0)) {
    return true;
  }

  if (get(D->val, x, y) == DMAP_IS_WALL) {
    return true;
  }

  return false;
}

//
// Given 3 points, can we do a shortcut diagonal move?
//
bool dmap_can_i_move_diagonally(const Dmap *D, point a, point b, point c)
{
  auto px = a.x;
  auto py = a.y;

  auto nx = b.x;
  auto ny = b.y;

  auto mx = c.x;
  auto my = c.y;

  if (px - 1 == mx && py + 1 == my && px == nx && py + 1 == ny && ! is_obs_wall_or_door_at(D, px - 1, py)) {
    return true;
  }

  if (px - 1 == mx && py + 1 == my && px - 1 == nx && py == ny && ! is_obs_wall_or_door_at(D, px, py + 1)) {
    return true;
  }

  if (px + 1 == mx && py + 1 == my && px == nx && py + 1 == ny && ! is_obs_wall_or_door_at(D, px + 1, py)) {
    return true;
  }

  if (px + 1 == mx && py + 1 == my && px + 1 == nx && py == ny && ! is_obs_wall_or_door_at(D, px, py + 1)) {
    return true;
  }

  if (px - 1 == mx && py - 1 == my && px == nx && py - 1 == ny && ! is_obs_wall_or_door_at(D, px - 1, py)) {
    return true;
  }

  if (px - 1 == mx && py - 1 == my && px - 1 == nx && py == ny && ! is_obs_wall_or_door_at(D, px, py - 1)) {
    return true;
  }

  if (px + 1 == mx && py - 1 == my && px == nx && py - 1 == ny && ! is_obs_wall_or_door_at(D, px + 1, py)) {
    return true;
  }

  if (px + 1 == mx && py - 1 == my && px + 1 == nx && py == ny && ! is_obs_wall_or_door_at(D, px, py - 1)) {
    return true;
  }
  return false;
}

static std::vector< point > dmap_solve_(const Dmap *D, const point start, const std::vector< point > &all_deltas,
                                        bool allow_diagonals)
{
  std::array< std::array< bool, MAP_HEIGHT >, MAP_WIDTH > walked = {};
  std::vector< point >                                    out    = {};
  auto                                                    at     = start;

  for (; /*ever*/;) {
    auto x = at.x;
    auto y = at.y;

    if (unlikely((x >= MAP_WIDTH - 1) || (y >= MAP_HEIGHT - 1) || (x < 1) || (y < 1))) {
      return out;
    }

    uint8_t lowest = get(D->val, x, y);
    bool    got    = false;
    point   best;

    if (get(D->val, x, y) == DMAP_IS_WALL) {
      return out;
    }

    for (const auto &d : all_deltas) {
      auto t  = at + d;
      auto tx = t.x;
      auto ty = t.y;

      if (get(walked, tx, ty)) {
        continue;
      }

      if (get(D->val, tx, ty) == DMAP_IS_WALL) {
        continue;
      }

      if (get(D->val, tx, ty) == DMAP_IS_PASSABLE) {
        continue;
      }

      //
      // Don't allow diagonal shortcuts if an obstacle would be crossed in an adjacent tile
      // Yes, this should be a not check to allow the player to move diagonally.
      //
      if (! allow_diagonals) {
        if (d.x < 0) {
          if (d.y < 0) {
            if ((get(D->val, at.x - 1, at.y) == DMAP_IS_WALL) || (get(D->val, at.x, at.y - 1) == DMAP_IS_WALL)) {
              continue;
            }
          } else if (d.y > 0) {
            if ((get(D->val, at.x - 1, at.y) == DMAP_IS_WALL) || (get(D->val, at.x, at.y + 1) == DMAP_IS_WALL)) {
              continue;
            }
          }
        } else if (d.x > 0) {
          if (d.y < 0) {
            if ((get(D->val, at.x + 1, at.y) == DMAP_IS_WALL) || (get(D->val, at.x, at.y - 1) == DMAP_IS_WALL)) {
              continue;
            }
          } else if (d.y > 0) {
            if ((get(D->val, at.x + 1, at.y) == DMAP_IS_WALL) || (get(D->val, at.x, at.y + 1) == DMAP_IS_WALL)) {
              continue;
            }
          }
        }
      }

      int c = get(D->val, tx, ty);
      if (c <= lowest) {
        got    = true;
        best   = t;
        lowest = c;
      }
    }

    if (! got) {
      return (out);
    }

    out.push_back(best);
    at = best;
    set(walked, best.x, best.y, true);
  }
  return (out);
}

std::vector< point > dmap_solve_allow_diagonal(const Dmap *D, const point start)
{
  static const std::vector< point > all_deltas = {
      point(-1, -1), point(1, -1), point(-1, 1), point(1, 1), point(0, -1), point(-1, 0), point(1, 0), point(0, 1),
  };
  return (dmap_solve_(D, start, all_deltas, true));
}

std::vector< point > dmap_solve(const Dmap *D, const point start)
{
  static const std::vector< point > all_deltas = {
      point(0, -1),
      point(-1, 0),
      point(1, 0),
      point(0, 1),
  };
  return (dmap_solve_(D, start, all_deltas, false));
}
