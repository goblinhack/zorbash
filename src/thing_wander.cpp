//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"
#include "my_vector_bounds_check.hpp"
#include <algorithm>

bool Thing::ai_blocked(void)
{
  TRACE_NO_INDENT();
  static const std::vector< point > move_deltas = {
      point(0, -1),
      point(-1, 0),
      point(1, 0),
      point(0, 1),
  };

  auto at    = curr_at;
  auto count = 0;
  for (const auto &d : move_deltas) {
    auto t = at + d;
    auto x = t.x;
    auto y = t.y;
    if (collision_obstacle(point(x, y))) {
      count++;
    }
  }
  return count >= 4;
}

bool Thing::ai_blocked_completely(void)
{
  TRACE_NO_INDENT();
  static const std::vector< point > move_deltas = {
      point(0, -1), point(-1, 0), point(1, 0), point(0, 1), point(0, 0),
  };

  auto at    = curr_at;
  auto count = 0;
  for (const auto &d : move_deltas) {
    auto t = at + d;
    auto x = t.x;
    auto y = t.y;
    if (collision_obstacle(point(x, y))) {
      count++;
    }
  }
  return count >= 5;
}

bool Thing::ai_create_path(point &nh, const point start, const point end)
{
  if (end == point(-1, -1)) {
    return false;
  }

  if (end == point(0, 0)) {
    return false;
  }

  dbg("AI create path from %d,%d to %d,%d", start.x, start.y, end.x, end.y);
  TRACE_AND_INDENT();

  Dmap  dmap {};
  point dmap_start = start;
  point dmap_end   = end;

  int minx, miny, maxx, maxy;
  if (dmap_start.x < dmap_end.x) {
    minx = dmap_start.x;
    maxx = dmap_end.x;
  } else {
    minx = dmap_end.x;
    maxx = dmap_start.x;
  }
  if (dmap_start.y < dmap_end.y) {
    miny = dmap_start.y;
    maxy = dmap_end.y;
  } else {
    miny = dmap_end.y;
    maxy = dmap_start.y;
  }

  auto border = 4;
  minx -= border;
  miny -= border;
  maxx += border;
  maxy += border;

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
  // Set up obstacles for the search
  //
  for (auto y = miny; y < maxy; y++) {
    for (auto x = minx; x < maxx; x++) {
      auto c = terrain_cost_get(point(x, y));
      if (collision_obstacle(point(x, y))) {
        set(dmap.val, x, y, DMAP_IS_WALL);
        continue;
      }
      if (c >= DMAP_LESS_PREFERRED_TERRAIN) {
        set(dmap.val, x, y, c);
      } else {
        set(dmap.val, x, y, DMAP_IS_PASSABLE);
      }
    }
  }

  dmap_start = point(minx, miny);
  dmap_end   = point(maxx, maxy);

  set(dmap.val, end.x, end.y, DMAP_IS_GOAL);

  set(dmap.val, start.x, start.y, DMAP_IS_PASSABLE);

#if 0
  log("before:");
  dmap_print(&dmap, start, dmap_start, dmap_end);
#endif

  dmap_process(&dmap, dmap_start, dmap_end);

#if 0
  log("after:");
  dmap_print(&dmap, start, dmap_start, dmap_end);
#endif

  char path_debug           = '\0'; // astart path debug
  auto [ result, fallback ] = astar_solve(nullptr, path_debug, start, end, &dmap);

  if (result.cost == std::numeric_limits< int >::max()) {
    if (fallback.path.size()) {
      result = fallback;
    }
  }

#if 0
  for (auto i : result.path) {
    set(dmap.val, i.x, i.y, (uint8_t) 0);
  }
  dmap_print(&dmap, start, dmap_start, dmap_end);
#endif
#ifdef ENABLE_DEBUG_AI_WANDER
  for (auto i : result.path) {
    thing_new("ai_path1", fpoint(i.x, i.y));
  }
#endif

  std::string goal_path_str = "Path:";
  for (auto i : result.path) {
    goal_path_str += " " + i.to_string();
  }
  dbg("AI created path %s", goal_path_str.c_str());
  TRACE_AND_INDENT();

  auto hops     = result.path;
  auto hops_len = hops.size();

  if (hops_len >= 2) {
    auto hop0 = get(hops, hops_len - 1);
    auto hop1 = get(hops, hops_len - 2);
    if (dmap_can_i_move_diagonally(&dmap, start, hop0, hop1)) {
      nh = hop1;
      hops.resize(hops.size() - 1);
    } else {
      nh = hop0;
    }

    auto ai = aip();
    std::reverse(hops.begin(), hops.end());
    ai->move_path = hops;
    change_state(MONST_STATE_MOVING, "found a new wander goal");
    return true;
  }

  if (hops_len >= 1) {
    auto hop0 = get(hops, hops_len - 1);
    nh        = hop0;
    auto ai   = aip();

    std::reverse(hops.begin(), hops.end());
    ai->move_path = hops;
    change_state(MONST_STATE_MOVING, "found a new wander goal");
    return true;
  }

  return false;
}

bool Thing::ai_choose_wander(point &nh)
{
  dbg("AI choose wander dest");
  TRACE_AND_INDENT();

  if (! maybe_aip()) {
    err("No monst aip");
  }

  //
  // Reached the dest? Choose a new one.
  //
  auto dest = aip()->wander_dest;
  if ((curr_at.x == dest.x) && (curr_at.y == dest.y)) {
    dbg("Reached dest");
    dest = point(-1, -1);
  }

  //
  // Try to use the same location.
  //
  if (ai_create_path(nh, curr_at, dest)) {
    return true;
  }

  //
  // Choose a new wander location
  //
  aip()->wander_dest = point(0, 0);
  dest               = dest_random_get();
  dbg("Try wander to %s", dest.to_string().c_str());

  //
  // Minions are constrained but we should stop the movement if it gets too far.
  // There may be nowhere else for it to try to move.
  //
  if (too_far_from_mob(dest)) {
    dbg("Too far off the leash but allow wander anyway to %d,%d", dest.x, dest.y);
  }

  if (too_far_from_leader(dest)) {
    if (distance_from_leader() > too_far_from_leader(dest)) {
      dbg("Wander closer to leader via %d,%d", dest.x, dest.y);
    } else {
      dbg("Too far from leader; but allow wander anyway to %d,%d", dest.x, dest.y);
    }
  }

  if (! ai_create_path(nh, curr_at, dest)) {
    dbg("Could not wander; could not create path to %d,%d", dest.x, dest.y);
    return false;
  }

  if (dest == curr_at) {
    dbg("Could not wander; at dest");
    return false;
  }

  aip()->wander_dest = dest;
#ifdef ENABLE_DEBUG_AI_WANDER
  thing_new("ai_path2", fpoint(dest.x, dest.y));
#endif
  dbg("Wander to %d,%d nh %d,%d", dest.x, dest.y, nh.x, nh.y);

  return true;
}

bool Thing::ai_wander(void)
{
  dbg("AI wander");
  TRACE_AND_INDENT();

  if (! is_moveable()) {
    dbg("No cannot move");
    return false;
  }

  //
  // Need to clear any existing path, so we don't come back to that later and jump around the screen
  //
  clear_move_path("AI wander");

  if (ai_blocked_completely()) {
    dbg("Blocked on all sides, try escape");
    if (ai_escape()) {
      return true;
    }

    if (is_able_to_jump()) {
      dbg("Blocked on all sides, try jumping");
      if (try_harder_to_jump()) {
        return true;
      }
    }
    dbg("AI wander blocked");
    return false;
  }

  if (ai_blocked()) {
    dbg("Blocked on all sides except current pos, try jumping");
    if (is_able_to_jump()) {
      if (try_harder_to_jump()) {
        return true;
      }
    }

    dbg("AI wander blocked");
    return false;
  }

  dbg("AI wander");
  auto tries = THING_AI_WANDER_TRIES;
  if (game->tick_current_is_too_slow || game->prev_tick_was_too_slow) {
    tries = 1;
  }
  while (tries-- > 0) {
    point nh;
    if (ai_choose_wander(nh)) {
      if (terrain_cost_get(nh) < DMAP_LESS_PREFERRED_TERRAIN) {
        return true;
      }

      //
      // Set this so next time we will choose another dest
      //
      aip()->wander_dest = point(0, 0);
    }
  }

  dbg("No wander goal");
  return false;
}
