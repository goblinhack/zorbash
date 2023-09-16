//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_dmap.hpp"
#include "my_main.hpp"
#include "my_sdl_event.hpp"
#include "my_sprintf.hpp"
#include "my_vector_bounds_check.hpp"

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
  for (x = minx; (x <= maxx) && all_walls; x++) {
    for (y = miny; (y <= maxy) && all_walls; y++) {
      all_walls = get_no_check(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      minx = x;
    }
  }

  all_walls = true;
  for (x = maxx; (x > minx) && all_walls; x--) {
    for (y = miny; (y <= maxy) && all_walls; y++) {
      all_walls = get_no_check(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      maxx = x;
    }
  }

  all_walls = true;
  for (y = miny; (y <= maxy) && all_walls; y++) {
    for (x = minx; (x <= maxx) && all_walls; x++) {
      all_walls = get_no_check(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      miny = y;
    }
  }

  all_walls = true;
  for (y = maxy; (y > miny) && all_walls; y--) {
    for (x = minx; (x <= maxx) && all_walls; x++) {
      all_walls = get_no_check(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      maxy = y;
    }
  }

  LOG("DMAP: tl %d,%d br %d %d at %d,%d", minx, miny, maxx, maxy, at.x, at.y);

  for (y = miny; y <= maxy; y++) {
    std::string debug;
    for (x = minx; x <= maxx; x++) {
      uint8_t e = get_no_check(D->val, x, y);
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
      uint8_t e = get_no_check(D->val, x, y);
      if (e == DMAP_IS_WALL) {
        debug += ("##");
        continue;
      }
      if (e == DMAP_IS_PASSABLE) {
        debug += (" .");
        continue;
      }

      if (e > 0) {
        debug += string_sprintf("%2X", e);
      } else {
        debug += " *";
      }
    }
    LOG("DMAP: %s", debug.c_str());
  }
}

void dmap_process_no_diagonals(Dmap *D, point tl, point br, bool place_border)
{
  auto                                                                      before = SDL_GetTicks();
  uint8_t                                                                   x;
  uint8_t                                                                   y;
  uint8_t                                                                   a;
  uint8_t                                                                   b;
  uint8_t                                                                   c;
  uint8_t                                                                   d;
  uint8_t                                                                  *e;
  uint8_t                                                                   f;
  uint8_t                                                                   g;
  uint8_t                                                                   h;
  uint8_t                                                                   i;
  uint8_t                                                                   lowest;
  uint8_t                                                                   changed;
  static std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > orig;
  static std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > orig_valid;
  static std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > valid;

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

  //
  // We always place a border around the dmap so the search doesn't trickly off the map.
  // So grow the search space slightly so that creatures that can only see one tile, do
  // not lose out and have nothing to look at.
  //
  if (place_border) {
    minx--;
    miny--;
    maxx++;
    maxy++;
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
  for (y = miny; y <= maxy; y++) {
    set_no_check(D->val, minx, y, DMAP_IS_WALL);
    set_no_check(D->val, maxx, y, DMAP_IS_WALL);
  }
  for (x = minx; x <= maxx; x++) {
    set_no_check(D->val, x, miny, DMAP_IS_WALL);
    set_no_check(D->val, x, maxy, DMAP_IS_WALL);
  }

  bool all_walls;

  //
  // Try to minimize the DMAP area if it is mostly walls at the edges, for speed.
  //
  all_walls = true;
  for (x = minx; (x <= maxx) && all_walls; x++) {
    for (y = miny; (y <= maxy) && all_walls; y++) {
      all_walls = get_no_check(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      minx = x;
    }
  }

  all_walls = true;
  for (x = maxx; (x > minx) && all_walls; x--) {
    for (y = miny; (y <= maxy) && all_walls; y++) {
      all_walls = get_no_check(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      maxx = x;
    }
  }

  all_walls = true;
  for (y = miny; (y <= maxy) && all_walls; y++) {
    for (x = minx; (x <= maxx) && all_walls; x++) {
      all_walls = get_no_check(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      miny = y;
    }
  }

  all_walls = true;
  for (y = maxy; (y > miny) && all_walls; y--) {
    for (x = minx; (x <= maxx) && all_walls; x++) {
      all_walls = get_no_check(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      maxy = y;
    }
  }

  for (y = miny + 1; y <= maxy - 1; y++) {
    for (x = minx + 1; x <= maxx - 1; x++) {
      set_no_check(orig, x, y, get_no_check(D->val, x, y));

      e = &getref(D->val, x, y);
      if (*e != DMAP_IS_WALL) {
        set_no_check(valid, x, y, (uint8_t) 1);
        set_no_check(orig_valid, x, y, (uint8_t) 1);
        continue;
      }

      set_no_check(valid, x, y, (uint8_t) 0);
      set_no_check(orig_valid, x, y, (uint8_t) 0);
    }
  }

  do {
    changed = false;

    for (y = miny + 1; y <= maxy - 1; y++) {
      for (x = minx + 1; x <= maxx - 1; x++) {
        if (! get_no_check(orig_valid, x, y)) {
          continue;
        }

        if (! get_no_check(valid, x, y)) {
          continue;
        }

        e = &getref(D->val, x, y);

        //
        // Avoid diagonal moves.
        //
        if (((get_no_check(D->val, x - 1, y) == DMAP_IS_WALL) || (get_no_check(D->val, x, y - 1) == DMAP_IS_WALL))) {
          a = DMAP_IS_WALL;
        } else {
          a = get_no_check(D->val, x - 1, y - 1);
        }

        b = get_no_check(D->val, x, y - 1);

        if (((get_no_check(D->val, x + 1, y) == DMAP_IS_WALL) || (get_no_check(D->val, x, y - 1) == DMAP_IS_WALL))) {
          c = DMAP_IS_WALL;
        } else {
          c = get_no_check(D->val, x + 1, y - 1);
        }

        d = get_no_check(D->val, x - 1, y);
        f = get_no_check(D->val, x + 1, y);

        if (((get_no_check(D->val, x - 1, y) == DMAP_IS_WALL) || (get_no_check(D->val, x, y + 1) == DMAP_IS_WALL))) {
          g = DMAP_IS_WALL;
        } else {
          g = get_no_check(D->val, x - 1, y + 1);
        }

        h = get_no_check(D->val, x, y + 1);

        if (((get_no_check(D->val, x + 1, y) == DMAP_IS_WALL) || (get_no_check(D->val, x, y + 1) == DMAP_IS_WALL))) {
          i = DMAP_IS_WALL;
        } else {
          i = get_no_check(D->val, x + 1, y + 1);
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
  for (y = miny + 1; y <= maxy - 1; y++) {
    for (x = minx + 1; x <= maxx - 1; x++) {
      uint8_t o = get_no_check(orig, x, y);
      if (o != DMAP_IS_WALL) {
        if (o > DMAP_IS_PASSABLE) {
          o         = o - DMAP_IS_PASSABLE;
          uint8_t n = get_no_check(D->val, x, y);
          if (o + n < DMAP_IS_PASSABLE) {
            incr(D->val, x, y, o);
          }
        }
      }
    }
  }

  //
  // Sanity check the dmap does not take too much time
  //
  if (unlikely(g_opt_debug1)) {
    auto after = SDL_GetTicks();
    if (after - before > 70) {
      ERR("DMAP is taking too long, %d ms", after - before);
      dmap_print(D);
    }
    if (after - before > 0) {
      if (! g_opt_test_dungeon_gen) {
        LOG("DMAP took %u ms: tl %d,%d br %d %d", after - before, tl.x, tl.y, br.x, br.y);
      }
    }
  }
}

//
// Pre:
//
// 9 9 9 9 9
// 9 9 9 9 9
// 9 9 9 9 9
// 9 9 0 9 9
// 9 9 9 9 9
// 9 9 9 9 9
// 9 9 9 9 9
//
// Post:
//
// 3 3 3 3 3
// 2 2 2 2 2
// 2 1 1 1 2
// 3 1 0 1 2
// 2 1 1 1 2
// 2 2 2 2 2
// 3 3 3 3 3
//
void dmap_process_allow_diagonals(Dmap *D, point tl, point br, bool place_border)
{
  auto                                                                      before = SDL_GetTicks();
  uint8_t                                                                   x;
  uint8_t                                                                   y;
  uint8_t                                                                   a;
  uint8_t                                                                   b;
  uint8_t                                                                   c;
  uint8_t                                                                   d;
  uint8_t                                                                  *e;
  uint8_t                                                                   f;
  uint8_t                                                                   g;
  uint8_t                                                                   h;
  uint8_t                                                                   i;
  uint8_t                                                                   lowest;
  uint8_t                                                                   changed;
  static std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > orig;
  static std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > orig_valid;
  static std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > valid;

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

  //
  // We always place a border around the dmap so the search doesn't trickly off the map.
  // So grow the search space slightly so that creatures that can only see one tile, do
  // not lose out and have nothing to look at.
  //
  if (place_border) {
    minx--;
    miny--;
    maxx++;
    maxy++;
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
  for (y = miny; y <= maxy; y++) {
    set_no_check(D->val, minx, y, DMAP_IS_WALL);
    set_no_check(D->val, maxx, y, DMAP_IS_WALL);
  }
  for (x = minx; x <= maxx; x++) {
    set_no_check(D->val, x, miny, DMAP_IS_WALL);
    set_no_check(D->val, x, maxy, DMAP_IS_WALL);
  }

  bool all_walls;

  //
  // Try to minimize the DMAP area if it is mostly walls at the edges, for speed.
  //
  all_walls = true;
  for (x = minx; (x <= maxx) && all_walls; x++) {
    for (y = miny; (y <= maxy) && all_walls; y++) {
      all_walls = get_no_check(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      minx = x;
    }
  }

  all_walls = true;
  for (x = maxx; (x > minx) && all_walls; x--) {
    for (y = miny; (y <= maxy) && all_walls; y++) {
      all_walls = get_no_check(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      maxx = x;
    }
  }

  all_walls = true;
  for (y = miny; (y <= maxy) && all_walls; y++) {
    for (x = minx; (x <= maxx) && all_walls; x++) {
      all_walls = get_no_check(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      miny = y;
    }
  }

  all_walls = true;
  for (y = maxy; (y > miny) && all_walls; y--) {
    for (x = minx; (x <= maxx) && all_walls; x++) {
      all_walls = get_no_check(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      maxy = y;
    }
  }

  for (y = miny + 1; y <= maxy - 1; y++) {
    for (x = minx + 1; x <= maxx - 1; x++) {
      set_no_check(orig, x, y, get_no_check(D->val, x, y));

      e = &getref(D->val, x, y);
      if (*e != DMAP_IS_WALL) {
        set_no_check(valid, x, y, (uint8_t) 1);
        set_no_check(orig_valid, x, y, (uint8_t) 1);
        continue;
      }

      set_no_check(valid, x, y, (uint8_t) 0);
      set_no_check(orig_valid, x, y, (uint8_t) 0);
    }
  }

  do {
    changed = false;

    for (y = miny + 1; y <= maxy - 1; y++) {
      for (x = minx + 1; x <= maxx - 1; x++) {
        if (! get_no_check(orig_valid, x, y)) {
          continue;
        }

        if (! get_no_check(valid, x, y)) {
          continue;
        }

        e = &getref(D->val, x, y);

        a = get_no_check(D->val, x - 1, y - 1);
        b = get_no_check(D->val, x, y - 1);
        c = get_no_check(D->val, x + 1, y - 1);
        d = get_no_check(D->val, x - 1, y);
        f = get_no_check(D->val, x + 1, y);
        g = get_no_check(D->val, x - 1, y + 1);
        h = get_no_check(D->val, x, y + 1);
        i = get_no_check(D->val, x + 1, y + 1);

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
  for (y = miny + 1; y <= maxy - 1; y++) {
    for (x = minx + 1; x <= maxx - 1; x++) {
      uint8_t o = get_no_check(orig, x, y);
      if (o != DMAP_IS_WALL) {
        if (o > DMAP_IS_PASSABLE) {
          o         = o - DMAP_IS_PASSABLE;
          uint8_t n = get_no_check(D->val, x, y);
          if (o + n < DMAP_IS_PASSABLE) {
            incr(D->val, x, y, o);
          }
        }
      }
    }
  }

  //
  // Sanity check the dmap does not take too much time
  //
  if (unlikely(g_opt_debug1)) {
    auto after = SDL_GetTicks();
    if (after - before > 70) {
      ERR("DMAP is taking too long, %d ms", after - before);
      dmap_print(D);
    }
    if (after - before > 0) {
      if (! g_opt_test_dungeon_gen) {
        LOG("DMAP took %u ms: tl %d,%d br %d %d", after - before, tl.x, tl.y, br.x, br.y);
      }
    }
  }
}

//
// Pre:
//
// 0 0 0 0 0
// 0 0 0 0 0
// 0 0 0 0 0
// 0 0 3 0 0
// 0 0 0 0 0
// 0 0 0 0 0
// 0 0 0 0 0
//
// Post:
//
// 0 0 0 0 0
// 0 1 1 1 0
// 1 2 2 2 1
// 1 2 3 2 1
// 1 2 2 2 1
// 0 1 1 1 0
// 0 0 0 0 0
//
void dmap_process_reverse_allow_diagonals(Dmap *D, point tl, point br, bool place_border)
{
  auto                                                                      before = SDL_GetTicks();
  uint8_t                                                                   x;
  uint8_t                                                                   y;
  uint8_t                                                                   a;
  uint8_t                                                                   b;
  uint8_t                                                                   c;
  uint8_t                                                                   d;
  uint8_t                                                                  *e;
  uint8_t                                                                   f;
  uint8_t                                                                   g;
  uint8_t                                                                   h;
  uint8_t                                                                   i;
  uint8_t                                                                   highest;
  uint8_t                                                                   changed;
  static std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > orig;
  static std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > orig_valid;
  static std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > valid;

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

  //
  // We always place a border around the dmap so the search doesn't trickly off the map.
  // So grow the search space slightly so that creatures that can only see one tile, do
  // not lose out and have nothing to look at.
  //
  if (place_border) {
    minx--;
    miny--;
    maxx++;
    maxy++;
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
  for (y = miny; y <= maxy; y++) {
    set_no_check(D->val, minx, y, DMAP_IS_WALL);
    set_no_check(D->val, maxx, y, DMAP_IS_WALL);
  }
  for (x = minx; x <= maxx; x++) {
    set_no_check(D->val, x, miny, DMAP_IS_WALL);
    set_no_check(D->val, x, maxy, DMAP_IS_WALL);
  }

  bool all_walls;

  //
  // Try to minimize the DMAP area if it is mostly walls at the edges, for speed.
  //
  all_walls = true;
  for (x = minx; (x <= maxx) && all_walls; x++) {
    for (y = miny; (y <= maxy) && all_walls; y++) {
      all_walls = get_no_check(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      minx = x;
    }
  }

  all_walls = true;
  for (x = maxx; (x > minx) && all_walls; x--) {
    for (y = miny; (y <= maxy) && all_walls; y++) {
      all_walls = get_no_check(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      maxx = x;
    }
  }

  all_walls = true;
  for (y = miny; (y <= maxy) && all_walls; y++) {
    for (x = minx; (x <= maxx) && all_walls; x++) {
      all_walls = get_no_check(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      miny = y;
    }
  }

  all_walls = true;
  for (y = maxy; (y > miny) && all_walls; y--) {
    for (x = minx; (x <= maxx) && all_walls; x++) {
      all_walls = get_no_check(D->val, x, y) == DMAP_IS_WALL;
    }
    if (all_walls) {
      maxy = y;
    }
  }

  for (y = miny + 1; y <= maxy - 1; y++) {
    for (x = minx + 1; x <= maxx - 1; x++) {
      set_no_check(orig, x, y, get_no_check(D->val, x, y));

      e = &getref(D->val, x, y);
      if (*e != DMAP_IS_WALL) {
        set_no_check(valid, x, y, (uint8_t) 1);
        set_no_check(orig_valid, x, y, (uint8_t) 1);
        continue;
      }

      set_no_check(valid, x, y, (uint8_t) 0);
      set_no_check(orig_valid, x, y, (uint8_t) 0);
    }
  }

  do {
    changed = false;

    for (y = miny + 1; y <= maxy - 1; y++) {
      for (x = minx + 1; x <= maxx - 1; x++) {
        if (! get_no_check(orig_valid, x, y)) {
          continue;
        }

        if (! get_no_check(valid, x, y)) {
          continue;
        }

        e = &getref(D->val, x, y);

        a = get_no_check(D->val, x - 1, y - 1);
        b = get_no_check(D->val, x, y - 1);
        c = get_no_check(D->val, x + 1, y - 1);
        d = get_no_check(D->val, x - 1, y);
        f = get_no_check(D->val, x + 1, y);
        g = get_no_check(D->val, x - 1, y + 1);
        h = get_no_check(D->val, x, y + 1);
        i = get_no_check(D->val, x + 1, y + 1);

        if (a >= DMAP_IS_PASSABLE) {
          a = 0;
        }
        if (b >= DMAP_IS_PASSABLE) {
          b = 0;
        }
        if (c >= DMAP_IS_PASSABLE) {
          c = 0;
        }
        if (d >= DMAP_IS_PASSABLE) {
          d = 0;
        }
        if (f >= DMAP_IS_PASSABLE) {
          f = 0;
        }
        if (g >= DMAP_IS_PASSABLE) {
          g = 0;
        }
        if (h >= DMAP_IS_PASSABLE) {
          h = 0;
        }
        if (i >= DMAP_IS_PASSABLE) {
          i = 0;
        }

        if (a > b) {
          highest = a;
        } else {
          highest = b;
        }

        if (c > highest) {
          highest = c;
        }
        if (d > highest) {
          highest = d;
        }
        if (f > highest) {
          highest = f;
        }
        if (g > highest) {
          highest = g;
        }
        if (h > highest) {
          highest = h;
        }
        if (i > highest) {
          highest = i;
        }

        if (highest - *e >= 2) {
          *e      = highest - 1;
          changed = true;
        }
      }
    }
  } while (changed);

  //
  // Mix in any original depth stats
  //
  for (y = miny + 1; y <= maxy - 1; y++) {
    for (x = minx + 1; x <= maxx - 1; x++) {
      uint8_t o = get_no_check(orig, x, y);
      if (o != DMAP_IS_WALL) {
        if (o > DMAP_IS_PASSABLE) {
          o         = o - DMAP_IS_PASSABLE;
          uint8_t n = get_no_check(D->val, x, y);
          if (o + n < DMAP_IS_PASSABLE) {
            incr(D->val, x, y, o);
          }
        }
      }
    }
  }

  //
  // Sanity check the dmap does not take too much time
  //
  if (unlikely(g_opt_debug1)) {
    auto after = SDL_GetTicks();
    if (after - before > 70) {
      ERR("DMAP is taking too long, %d ms", after - before);
      dmap_print(D);
    }
    if (after - before > 0) {
      if (! g_opt_test_dungeon_gen) {
        LOG("DMAP took %u ms: tl %d,%d br %d %d", after - before, tl.x, tl.y, br.x, br.y);
      }
    }
  }
}

static bool is_obs_wall_or_door_at(const Dmap *D, int x, int y)
{
  if ((x >= MAP_WIDTH) || (y >= MAP_HEIGHT) || (x < 0) || (y < 0)) {
    return true;
  }

  if (get_no_check(D->val, x, y) == DMAP_IS_WALL) {
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
  std::array< std::array< bool, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > walked = {};
  std::vector< point >                                            out    = {};
  auto                                                            at     = start;

  for (; /*ever*/;) {
    auto x = at.x;
    auto y = at.y;

    if (unlikely((x >= MAP_WIDTH - 1) || (y >= MAP_HEIGHT - 1) || (x < 1) || (y < 1))) {
      return out;
    }

    uint8_t lowest = get_no_check(D->val, x, y);
    bool    got    = false;
    point   best;

    if (get_no_check(D->val, x, y) == DMAP_IS_WALL) {
      return out;
    }

    for (const auto &d : all_deltas) {
      auto t  = at + d;
      auto tx = t.x;
      auto ty = t.y;

      if (get_no_check(walked, tx, ty)) {
        continue;
      }

      if (get_no_check(D->val, tx, ty) == DMAP_IS_WALL) {
        continue;
      }

      if (get_no_check(D->val, tx, ty) == DMAP_IS_PASSABLE) {
        continue;
      }

      //
      // Don't allow diagonal shortcuts if an obstacle would be crossed in an adjacent tile
      // Yes, this should be a not check to allow the player to move diagonally.
      //
      if (! allow_diagonals) {
        if (d.x < 0) {
          if (d.y < 0) {
            if ((get_no_check(D->val, at.x - 1, at.y) == DMAP_IS_WALL)
                || (get_no_check(D->val, at.x, at.y - 1) == DMAP_IS_WALL)) {
              continue;
            }
          } else if (d.y > 0) {
            if ((get_no_check(D->val, at.x - 1, at.y) == DMAP_IS_WALL)
                || (get_no_check(D->val, at.x, at.y + 1) == DMAP_IS_WALL)) {
              continue;
            }
          }
        } else if (d.x > 0) {
          if (d.y < 0) {
            if ((get_no_check(D->val, at.x + 1, at.y) == DMAP_IS_WALL)
                || (get_no_check(D->val, at.x, at.y - 1) == DMAP_IS_WALL)) {
              continue;
            }
          } else if (d.y > 0) {
            if ((get_no_check(D->val, at.x + 1, at.y) == DMAP_IS_WALL)
                || (get_no_check(D->val, at.x, at.y + 1) == DMAP_IS_WALL)) {
              continue;
            }
          }
        }
      }

      int c = get_no_check(D->val, tx, ty);
      if (c <= lowest) {
        got    = true;
        best   = t;
        lowest = c;
      }
    }

    if (! got) {
      return out;
    }

    out.push_back(best);
    at = best;
    set_no_check(walked, best.x, best.y, true);
  }
  return out;
}

std::vector< point > dmap_solve_allow_diagonal(const Dmap *D, const point start)
{
  static const std::vector< point > all_deltas = {
      point(-1, -1), point(1, -1), point(-1, 1), point(1, 1), point(0, -1), point(-1, 0), point(1, 0), point(0, 1),
  };
  return (dmap_solve_(D, start, all_deltas, true));
}

std::vector< point > dmap_solve_manhattan(const Dmap *D, const point start)
{
  static const std::vector< point > all_deltas = {
      point(0, -1),
      point(-1, 0),
      point(1, 0),
      point(0, 1),
  };
  return (dmap_solve_(D, start, all_deltas, false));
}

//
// Try to solve diagonally first. Then fallback to manhattan if we cannot.
//
std::vector< point > dmap_solve(const Dmap *D, const point start)
{
  //
  // No path? Intentionally not allowing diagonal moves here as that allows the
  // player to take a shortcut around walls. e.g.
  //
  // ..###    ..###
  // ..#$#    ..#$#
  // .@### -> ..###
  // .....    ..@..
  //
  // if we allow the diagonal move then the hidden treasure in the middle of the
  // wall gets exposed.
  //
  auto p         = dmap_solve_allow_diagonal(D, start);
  auto path_size = p.size();
  if (! path_size) {
    std::vector< point > empty_path;
    return empty_path;
  }

  //
  // Take a path like the following
  //
  // ...........
  // .@.........
  // ..*........
  // ...*.#.....
  // ....*###...
  // .....*.#...
  // ......*#...
  // .......*...
  //
  // and convert it to avoid cutting across walls diagonally
  //
  // ...........
  // .@.........
  // ..*........
  // ...*.#.....
  // ....*###...
  // ....**.#...
  // ......*#...
  // ......**...
  //
  p.insert(p.begin(), start);
  std::vector< point > out;
  path_size = p.size();

  for (int i = 0; i < (int) path_size; i++) {
    auto hop0 = get_no_check(p, i);

    if (i == (int) path_size - 1) {
      out.push_back(hop0);
      break;
    }

    auto hop1 = get_no_check(p, i + 1);

    // s.
    // .e
    if (((hop0.x + 1) == hop1.x) && ((hop0.y + 1) == hop1.y)) {
      if (is_obs_wall_or_door_at(D, hop0.x + 1, hop0.y) && is_obs_wall_or_door_at(D, hop0.x, hop0.y + 1)) {
        //
        // Allow fully diagonal moves between walls?
        //
      } else if (is_obs_wall_or_door_at(D, hop0.x + 1, hop0.y)) {
        //
        // Try to make a path around the obstacle
        //
        out.push_back(hop0);
        out.push_back(point(hop0.x, hop0.y + 1));
        continue;
      } else if (is_obs_wall_or_door_at(D, hop0.x, hop0.y + 1)) {
        //
        // Try to make a path around the obstacle
        //
        out.push_back(hop0);
        out.push_back(point(hop0.x + 1, hop0.y));
        continue;
      }
    }

    // .s
    // e.
    if (((hop0.x - 1) == hop1.x) && ((hop0.y + 1) == hop1.y)) {
      if (is_obs_wall_or_door_at(D, hop0.x - 1, hop0.y) && is_obs_wall_or_door_at(D, hop0.x, hop0.y + 1)) {
        //
        // Allow fully diagonal moves between walls?
        //
      } else if (is_obs_wall_or_door_at(D, hop0.x - 1, hop0.y)) {
        //
        // Try to make a path around the obstacle
        //
        out.push_back(hop0);
        out.push_back(point(hop0.x, hop0.y + 1));
        continue;
      } else if (is_obs_wall_or_door_at(D, hop0.x, hop0.y + 1)) {
        //
        // Try to make a path around the obstacle
        //
        out.push_back(hop0);
        out.push_back(point(hop0.x - 1, hop0.y));
        continue;
      }
    }

    // .e
    // s.
    if (((hop0.x + 1) == hop1.x) && ((hop0.y - 1) == hop1.y)) {
      if (is_obs_wall_or_door_at(D, hop0.x + 1, hop0.y) && is_obs_wall_or_door_at(D, hop0.x, hop0.y - 1)) {
        //
        // Allow fully diagonal moves between walls?
        //
      } else if (is_obs_wall_or_door_at(D, hop0.x + 1, hop0.y)) {
        //
        // Try to make a path around the obstacle
        //
        out.push_back(hop0);
        out.push_back(point(hop0.x, hop0.y - 1));
        continue;
      } else if (is_obs_wall_or_door_at(D, hop0.x, hop0.y - 1)) {
        //
        // Try to make a path around the obstacle
        //
        out.push_back(hop0);
        out.push_back(point(hop0.x + 1, hop0.y));
        continue;
      }
    }

    // e.
    // .s
    if (((hop0.x - 1) == hop1.x) && ((hop0.y - 1) == hop1.y)) {
      if (is_obs_wall_or_door_at(D, hop0.x - 1, hop0.y) && is_obs_wall_or_door_at(D, hop0.x, hop0.y - 1)) {
        //
        // Allow fully diagonal moves between walls?
        //
      } else if (is_obs_wall_or_door_at(D, hop0.x - 1, hop0.y)) {
        //
        // Try to make a path around the obstacle
        //
        out.push_back(hop0);
        out.push_back(point(hop0.x, hop0.y - 1));
        continue;
      } else if (is_obs_wall_or_door_at(D, hop0.x, hop0.y - 1)) {
        //
        // Try to make a path around the obstacle
        //
        out.push_back(hop0);
        out.push_back(point(hop0.x - 1, hop0.y));
        continue;
      }
    }

    out.push_back(hop0);
  }

  out.erase(out.begin());
  path_size = out.size();
  if (! path_size) {
    return out;
  }

  return out;
}
