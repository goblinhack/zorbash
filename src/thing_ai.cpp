//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_player.hpp"
#include "my_ptrcheck.hpp"
#include "my_sprintf.hpp"
#include "my_template.hpp"
#include "my_thing.hpp"
#include <set>

#define GOAL_PRIO_VERY_HIGH 0
#define GOAL_PRIO_HIGH      1
#define GOAL_PRIO_MED       2
#define GOAL_PRIO_LOW       3
#define GOAL_PRIO_VERY_LOW  4

#define GOAL_ADD(prio, score, msg, it)                                                                               \
  IF_DEBUG                                                                                                           \
  {                                                                                                                  \
    auto s = string_sprintf("Add goal prio %d score %d @(%d,%d) %s", prio, score, p.x, p.y, msg);                    \
    AI_LOG(s, it);                                                                                                   \
  }                                                                                                                  \
  goals.insert(Goal(prio, score, p, msg, it));

#define GOAL_AVOID_ADD(prio, score, msg, it)                                                                         \
  IF_DEBUG                                                                                                           \
  {                                                                                                                  \
    auto s = string_sprintf("Add goal (avoid) prio %d score %d @(%d,%d) %s", prio, score, p.x, p.y, msg);            \
    AI_LOG(s, it);                                                                                                   \
  }                                                                                                                  \
  goals.insert(Goal(prio, score, p, msg, it, true /* avoid */));

void Thing::ai_log(const std::string &msg, Thingp it)
{
  TRACE_NO_INDENT();

  if (it) {
    log("AI: %s, %s", msg.c_str(), it->to_short_string().c_str());
  } else {
    log("AI: %s", msg.c_str());
  }
}

void Thing::ai_log(const std::string &msg) { ai_log(msg, nullptr); }

//
// Look at all the things that are currently visited (read that as light rays
// have touched them) and choose the best goal. Create a path to that goal for
// the thing to walk.
//
bool Thing::ai_create_path_to_goal(int minx, int miny, int maxx, int maxy, int search_type)
{
  point start((int) curr_at.x, (int) curr_at.y);

  //
  // Choose goals (higher scores, lower costs are preferred)
  //
  std::string s = "Choose goal";
  IF_DEBUG { s = string_sprintf("Try to find goals, search-type %d", search_type); }
  AI_LOG(s);
  TRACE_AND_INDENT();

  //
  // Find all the possible goals. Higher scores, lower costs are preferred
  //
  auto dmap_can_see = dmap_can_see_get();

  switch (search_type) {
    case MONST_SEARCH_TYPE_CAN_SEE_JUMP_ALLOWED:
    case MONST_SEARCH_TYPE_LOCAL_NO_JUMP:
    case MONST_SEARCH_TYPE_LOCAL_JUMP_ALLOWED: break;
    case MONST_SEARCH_TYPE_GLOBAL_NO_JUMP:
    case MONST_SEARCH_TYPE_GLOBAL_JUMP_ALLOWED:
    case MONST_SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED:
    case MONST_SEARCH_TYPE_LAST_RESORTS_NO_JUMP:
      if (is_player()) {
        minx = 0;
        maxx = MAP_WIDTH - 1;
        miny = 0;
        maxy = MAP_HEIGHT - 1;
      }
      break;
  }

  std::multiset< Goal > goals;
  std::list< GoalMap >  goalmaps;
  ai_dmap_can_see_init(minx, miny, maxx, maxy, search_type, false);

  switch (search_type) {
    case MONST_SEARCH_TYPE_CAN_SEE_JUMP_ALLOWED:
      ai_choose_can_see_goals(goals, minx, miny, maxx, maxy);
      goalmaps.push_back(GoalMap {goals, dmap_can_see});
      break;
    case MONST_SEARCH_TYPE_LOCAL_NO_JUMP:
    case MONST_SEARCH_TYPE_LOCAL_JUMP_ALLOWED:
    case MONST_SEARCH_TYPE_GLOBAL_NO_JUMP:
    case MONST_SEARCH_TYPE_GLOBAL_JUMP_ALLOWED:
    case MONST_SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED:
    case MONST_SEARCH_TYPE_LAST_RESORTS_NO_JUMP:
      ai_choose_search_goals(goals, search_type);
      goalmaps.push_back(GoalMap {goals, dmap_can_see});
      break;
  }

  //
  // No goals?
  //
  if (goalmaps.empty()) {
    AI_LOG("No goals found");
    return false;
  }

  IF_DEBUG2
  {
    AI_LOG("All goals:");
    TRACE_AND_INDENT();
    for (auto &g : goalmaps) {
      AI_LOG("Goalmap:");
      TRACE_AND_INDENT();
      for (const auto &goal : g.goals) {
        auto s = string_sprintf("Goal, prio %d score %d @(%d,%d) %s", (int) goal.prio, (int) goal.score,
                                (int) goal.at.x, (int) goal.at.y, goal.msg.c_str());
        AI_LOG(s);
      }
    }
  }

  AI_LOG("Process goals:");
  TRACE_AND_INDENT();

  for (auto &g : goalmaps) {
    IF_DEBUG2
    {
      if (is_debug_type()) {
        AI_LOG("Pre modify dmap for terrain");
        dmap_print(g.dmap, point(start.x, start.y), point(minx, miny), point(maxx, maxy));

        if (search_type == MONST_SEARCH_TYPE_CAN_SEE_JUMP_ALLOWED) {
          level->heatmap_print(point(start.x, start.y), point(minx, miny), point(maxx, maxy));
        }
      }
    }

    //
    // Modify the dmap for terrain.
    //
    for (int y = miny; y <= maxy; y++) {
      for (int x = minx; x <= maxx; x++) {
        point p(x, y);
        auto  c = getptr(g.dmap->val, x, y);
        if ((*c < DMAP_IS_PASSABLE) && (*c > DMAP_IS_GOAL)) {
          dmap_modify_terrain_cost(p, c);
        }
      }
    }

    IF_DEBUG2
    {
      AI_LOG("Modified dmap for terrain");
      dmap_print(g.dmap, point(start.x, start.y), point(minx, miny), point(maxx, maxy));
    }

    const Dmap saved_dmap = *g.dmap;
    for (const auto &goal : g.goals) {
      if (goal.avoid) {
        AI_LOG("Processing avoid goal");
        TRACE_AND_INDENT();
        std::multiset< Goal > avoid;
        if (ai_choose_avoid_goals(avoid, goal)) {
          for (const auto &inner_goal : avoid) {
            if (ai_create_path_to_single_goal(minx, miny, maxx, maxy, inner_goal, &saved_dmap)) {
              if (goal.what) {
                add_goal_penalty(goal.what);
              }

              if (fire_at(goal.what)) {
                return true;
              }

              IF_DEBUG
              {
                auto s = string_sprintf("Accept avoid goal score %d @(%d,%d) %s", (int) goal.score, (int) goal.at.x,
                                        (int) goal.at.y, goal.msg.c_str());
                AI_LOG(s);
              }
              return true;
            }
          }
        }
        continue;
      }

      if (fire_at(goal.what)) {
        return true;
      }

      if (ai_create_path_to_single_goal(minx, miny, maxx, maxy, goal, &saved_dmap)) {
        if (goal.what) {
          add_goal_penalty(goal.what);
        }

        IF_DEBUG
        {
          auto s = string_sprintf("Accept goal score %d @(%d,%d) %s", (int) goal.score, (int) goal.at.x,
                                  (int) goal.at.y, goal.msg.c_str());
          AI_LOG(s);
        }
        return true;
      }
    }
  }

  return false;
}

bool Thing::ai_create_path_to_single_goal(int minx, int miny, int maxx, int maxy, const Goal &goal,
                                          const Dmap *saved_dmap)
{
  IF_DEBUG
  {
    auto s = string_sprintf("Process goal score %d @(%d,%d) %s", (int) goal.score, (int) goal.at.x, (int) goal.at.y,
                            goal.msg.c_str());
    AI_LOG(s);
  }
  TRACE_AND_INDENT();

  auto ai = aip();

  //
  // Copy the dmap so we start with a fresh map per goal.
  //
  Dmap dmap = *saved_dmap;

  point start((int) curr_at.x, (int) curr_at.y);

  //
  // Check we can get to this goal
  //
  uint8_t *c = getptr(dmap.val, goal.at.x, goal.at.y);
  if (*c == DMAP_MAX_LESS_PREFERRED_TERRAIN) {
    AI_LOG("Goal is on bad terrain");
    return false;
  }

  //
  // Mark the goal in the dmap
  //
  set(dmap.val, goal.at.x, goal.at.y, DMAP_IS_GOAL);

  //
  // Make sure we do not want to stay in the same position by making
  // our current cell passable but the very least preferred it can be.
  //
  if (get(dmap.val, start.x, start.y) > 0) {
    set(dmap.val, start.x, start.y, DMAP_IS_PASSABLE);
  }

  IF_DEBUG2 { dmap_print(&dmap, point(start.x, start.y), point(minx, miny), point(maxx, maxy)); }

  //
  // Record we've been here.
  //
  auto age_map = age_map_get();
  set(age_map->val, start.x, start.y, game->tick_current);

  //
  // Modify the given goals with scores that indicate the cost of the
  // path to that goal. The result should be a sorted set of goals.
  //
  std::multiset< Path > paths;
  char                  path_debug = '\0'; // astart path debug

#ifdef ENABLE_DEBUG_AI_ASTAR
  astar_debug = {};
#endif
  point astar_start(start.x, start.y);
  auto  astar_end           = goal.at;
  auto [ result, fallback ] = astar_solve(&goal, path_debug, astar_start, astar_end, &dmap);

  //
  // Unreachable?
  //
  if (result.cost == std::numeric_limits< int >::max()) {
    //
    // Occasionally try the fallback path for a bit of variety.
    //
    if (d100() < 20) {
      if (fallback.path.size()) {
        //
        // If the fallback path ends in an AI obstacle (like a chasm)
        // then this is sub ideal.
        //
        if (ai_obstacle_for_me(fallback.path[ fallback.path.size() - 1 ])) {
          AI_LOG("Goal (and fallback) is astar unreachable");
          return false;
        }

        IF_DEBUG
        {
          auto s = string_sprintf("Use fallback path as goal at %d,%d is unreachable", goal.at.x, goal.at.y);
          AI_LOG(s);
        }
        result = fallback;
      } else {
#ifdef ENABLE_DEBUG_AI_ASTAR
        auto start = point(minx, miny);
        auto end   = point(maxx, maxy);
        astar_dump(&dmap, goal.at, start, end);
#endif
        AI_LOG("Goal is astar unreachable");
        return false;
      }
    }
  }

  paths.insert(result);

#ifdef ENABLE_DEBUG_AI_ASTAR
  {
    for (auto &p : result.path) {
      set(astar_debug, p.x, p.y, '*');
    }
    auto start = point(minx, miny);
    auto end   = point(maxx, maxy);
    astar_dump(&dmap, goal.at, start, end);
  }
#endif

  for (auto &result : paths) {
    std::vector< point > new_move_path = result.path;

    std::reverse(new_move_path.begin(), new_move_path.end());

    path_shorten(new_move_path);

    if (new_move_path.empty()) {
      if (is_stuck()) {
        stuck("Stuck in something");
        AI_LOG("Stuck in something");
        if (is_player()) {
          game->tick_begin("Try to break free");
        }
        return true;
      }
      AI_LOG("Goal has no path");
      return false;
    }

    std::string goal_path_str = "Goal path:";
    for (auto p1 : new_move_path) {
      goal_path_str += " " + p1.to_string();
    }
    AI_LOG(goal_path_str);

    if (is_player()) {
      level->cursor_path_create(this, new_move_path);
      IF_DEBUG3 { level->debug_path_create(new_move_path); }

      //
      // Try to move. It might not work and we end up attacking.
      //
      if (cursor_path_pop_first_move(THING_MOVE_REASON_AI)) {
        AI_LOG("Successfully popped move");
        return true;
      }

      //
      // Did we try or attempt to try to do something?
      //
      if (! game->tick_requested.empty()) {
        IF_DEBUG
        {
          auto s = string_sprintf("Successfully requested a tick: %s", game->tick_requested.c_str());
          AI_LOG(s);
        }
        return true;
      }
    } else {
      ai->move_path = new_move_path;

      if (teleport_attack(goal.what)) {
        return true;
      }

      if (jump_attack(goal.what)) {
        return true;
      }

      return true;
    }

    AI_LOG("Failed to move to goal");
  }

  AI_LOG("Goal had no reachable paths");
  return false;
}

//
// Initialize basic visibility and things that are lit and can be seen
//
int Thing::ai_dmap_can_see_init(int minx, int miny, int maxx, int maxy, int search_type, bool check_for_interrupts)
{
  AI_LOG("Init dmap can see");
  TRACE_AND_INDENT();

  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > can_jump = {};

  point start((int) curr_at.x, (int) curr_at.y);
  auto  dmap_can_see      = dmap_can_see_get();
  bool  jump_allowed      = false;
  int   something_changed = 0;

  for (int y = miny; y <= maxy; y++) {
    for (int x = minx; x <= maxx; x++) {
      set(dmap_can_see->val, x, y, DMAP_IS_WALL);
    }
  }

  switch (search_type) {
    case MONST_SEARCH_TYPE_CAN_SEE_JUMP_ALLOWED: jump_allowed = true; break;
    case MONST_SEARCH_TYPE_LOCAL_NO_JUMP: jump_allowed = false; break;
    case MONST_SEARCH_TYPE_LOCAL_JUMP_ALLOWED: jump_allowed = true; break;
    case MONST_SEARCH_TYPE_GLOBAL_NO_JUMP: jump_allowed = false; break;
    case MONST_SEARCH_TYPE_GLOBAL_JUMP_ALLOWED: jump_allowed = true; break;
    case MONST_SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED: jump_allowed = true; break;
    case MONST_SEARCH_TYPE_LAST_RESORTS_NO_JUMP: jump_allowed = false; break;
  }

  if (! is_able_to_jump()) {
    jump_allowed = false;
  }

  auto ai = aip();

  std::array< std::array< bool, MAP_HEIGHT >, MAP_WIDTH > walked = {};

  for (int y = miny; y <= maxy; y++) {
    for (int x = minx; x <= maxx; x++) {
      point p(x, y);

      if (! get(ai->can_see_ever.can_see, x, y)) {
        continue;
      }

      if (too_far_from_mob(p)) {
        continue;
      }

      if (too_far_from_leader(p)) {
        if (distance_from_leader() < too_far_from_leader(p)) {
          continue;
        }
      }

      set(walked, x, y, true);

      //
      // NOTE: in robot mode, chasms are an AI obstacle for the player.
      //
      if (is_moveable()) {
        //
        // Normal monsters that can move
        //
        if (! ai_obstacle_for_me(p)) {
          set(dmap_can_see->val, x, y, DMAP_IS_PASSABLE);
          continue;
        }
      } else {
        //
        // Possibly things like carnivorous plants that cannot, but can lunge
        //
        if (attack_lunge()) {
          set(dmap_can_see->val, x, y, DMAP_IS_PASSABLE);
        } else {
          continue;
        }
      }

      //
      // If a member of the same team is in the way, do not try to
      // jump over them. Better to walk around so you can attack
      // from all sides.
      //
      if (is_able_to_follow()) {
        FOR_ALL_THINGS_THAT_INTERACT(level, it, p.x, p.y)
        {
          if (same_leader(it)) {
            break;
          }
        }
        FOR_ALL_THINGS_END();
      }

      //
      // So if we get here this thing is an AI obstacle. Can we jump over it?
      //
      if (! jump_allowed) {
        continue;
      }

      if (is_disliked_by_me(p)) {
        set(dmap_can_see->val, x, y, DMAP_IS_PASSABLE);
      }

      //
      // Can jump but only if not tired.
      //
      if (stamina() > stamina_max() / 2) {
        //
        // Trace all possible jump paths to see if we can jump over
        //
        auto jump_dist = jump_distance_max_get();
        for (const auto &jp : game->jump_paths) {
          point jump_begin(p.x + jp.begin.x, p.y + jp.begin.y);
          point jump_end(p.x + jp.end.x, p.y + jp.end.y);

          if (level->is_oob(jump_begin)) {
            continue;
          }

          if (level->is_oob(jump_end)) {
            continue;
          }

          //
          // No jump begin/end from a chasm or barrel for example
          //
          if (is_disliked_by_me(jump_begin) || ai_obstacle_for_me(jump_begin)) {
            continue;
          }

          if (is_disliked_by_me(jump_end) || ai_obstacle_for_me(jump_end)) {
            continue;
          }

          //
          // Must be able to see the begin/end.
          //
          if (! get(ai->can_see_ever.can_see, jump_begin.x, jump_begin.y)) {
            continue;
          }

          //
          // Too far?
          //
          float dist = DISTANCE(jump_begin.x, jump_begin.y, jump_end.x, jump_end.y);
          if (dist > jump_dist + 1) {
            continue;
          }

          //
          // Check we really need to jump over all things in the path.
          //
          // Also check for walls. Is it fair to jump over walls?
          //
          bool jump = true;
          for (const auto &jump_over : jp.path) {
            auto j = jump_over + p;
            if (j == p) {
              continue;
            }
            if (level->is_obs_wall_or_door(j)) {
              jump = false;
              break;
            }
            if (! ai_obstacle_for_me(j)) {
              jump = false;
              break;
            }
          }

          if (jump) {
            for (const auto &jump_over : jp.path) {
              auto j = jump_over + p;
              set(can_jump, j.x, j.y, DMAP_IS_PASSABLE);
            }
          }
        }
      }
    }
  }

  if (is_debug_type()) {
    con("This is what I can see (prior to growing the search space) and have looked at:");
    con("  @  - you/it");
    con("  L  - walked and can see currently");
    con("  O  - walked and have seen ever");
    con("  l  - can see currently");
    con("  o  - have seen ever");
    for (int y = 0; y < MAP_HEIGHT; y++) {
      for (int x = 0; x < MAP_WIDTH; x++) {
        if ((x == (int) curr_at.x) && (y == (int) curr_at.y)) {
          printf("@");
          continue;
        }
        if (get(walked, x, y)) {
          if (level->is_obs_wall_or_door(x, y)) {
            if (get(ai->can_see_currently.can_see, x, y)) {
              printf("X");
            } else if (get(ai->can_see_ever.can_see, x, y)) {
              printf("X");
            } else {
              printf("x");
            }
          } else if (level->is_floor(x, y)) {
            if (get(ai->can_see_currently.can_see, x, y)) {
              printf("L");
            } else if (get(ai->can_see_ever.can_see, x, y)) {
              printf("O");
            } else {
              printf(".");
            }
          } else {
            printf(" ");
          }
        } else {
          if (level->is_obs_wall_or_door(x, y)) {
            if (get(ai->can_see_currently.can_see, x, y)) {
              printf("x");
            } else if (get(ai->can_see_ever.can_see, x, y)) {
              printf("x");
            } else {
              printf("x");
            }
          } else if (level->is_floor(x, y)) {
            if (get(ai->can_see_currently.can_see, x, y)) {
              printf("l");
            } else if (get(ai->can_see_ever.can_see, x, y)) {
              printf("o");
            } else {
              printf(".");
            }
          } else {
            printf(" ");
          }
        }
        continue;
      }
      printf("\n");
    }
  }

  //
  // Walk tiles on the edge of what we can see i.e. stuff we did not walk
  // above and look for something worth exploring.
  //
  if (is_explorer()) {
    {
      for (int y = miny; y <= maxy; y++) {
        for (int x = minx; x <= maxx; x++) {
          point p(x, y);

          if (p.x >= MAP_WIDTH - MAP_BORDER_ROCK) {
            continue;
          }
          if (p.y >= MAP_HEIGHT - MAP_BORDER_ROCK) {
            continue;
          }
          if (p.x < MAP_BORDER_ROCK) {
            continue;
          }
          if (p.y < MAP_BORDER_ROCK) {
            continue;
          }
          if (get(walked, x, y)) {
            continue;
          }

          //
          // Ignore tiles we have never seen. This check works as we allow the light to grow
          // a bit when calling fov_calculate
          //
          if (! get(ai->can_see_ever.can_see, p.x, p.y)) {
            continue;
          }

          //
          // Can't see past walls. However we can see over chasms to expand the search space
          //
          if (level->is_door(p)) {
            //
            // Allow us to see doors so we can search them
            //
          } else if (level->is_obs_wall_or_door(p)) {
            //
            // But allow chasms and lava so we can see over. Just block on walls and pillars etc...
            //
            continue;
          }

          set(walked, x, y, true);

          for (auto dx = -1; dx <= 1; dx++) {
            for (auto dy = -1; dy <= 1; dy++) {
              point o(p.x + dx, p.y + dy);

              if (level->is_oob(o)) {
                continue;
              }

              if (! dx && ! dy) {
                continue;
              }

              if (level->is_door(o)) {
                //
                // Allow us to see doors so we can search them
                //
              } else if (level->is_obs_wall_or_door(o)) {
                //
                // But allow chasms and lava so we can see over. Just block on walls and pillars etc...
                //
                continue;
              }

              //
              // Check for something we've never seen before
              //
              if (! get(ai->can_see_ever.can_see, o.x, o.y) && ! get(ai->interrupt_map.val, o.x, o.y)) {

                FOR_ALL_THINGS_THAT_INTERACT(level, it, o.x, o.y)
                {
                  if (it == this) {
                    continue;
                  }

                  if (it->is_changing_level || it->is_hidden || it->is_falling || it->is_jumping) {
                    continue;
                  }

                  if (worth_collecting(it) > 0) {
                    set(ai->interrupt_map.val, p.x, p.y, game->tick_current);
                    if (check_for_interrupts) {
                      something_changed++;
                      AI_LOG("Interrupted by thing worth collecting", it);
                    }
                  }
                  if (is_dangerous(it)) {
                    set(ai->interrupt_map.val, p.x, p.y, game->tick_current);
                    if (check_for_interrupts) {
                      something_changed++;
                      AI_LOG("Interrupted by dangerous thing", it);
                    }
                  }

                  if (worth_eating(it)) {
                    set(ai->interrupt_map.val, p.x, p.y, game->tick_current);
                    if (check_for_interrupts) {
                      something_changed++;
                      AI_LOG("Interrupted by edible collecting", it);
                    }
                  }
                }
                FOR_ALL_THINGS_END();
              }

              set(dmap_can_see->val, o.x, o.y, DMAP_IS_PASSABLE);
            }
          }
        }
      }
    }
  }

  if (is_debug_type()) {
    con("This is what I can see and have looked at:");
    con("  @  - you/it");
    con("  L  - walked and can see currently");
    con("  O  - walked and have seen ever");
    con("  l  - can see currently");
    con("  o  - have seen ever");
    for (int y = 0; y < MAP_HEIGHT; y++) {
      for (int x = 0; x < MAP_WIDTH; x++) {
        if ((x == (int) curr_at.x) && (y == (int) curr_at.y)) {
          printf("@");
          continue;
        }
        if (get(walked, x, y)) {
          if (level->is_obs_wall_or_door(x, y)) {
            if (get(ai->can_see_currently.can_see, x, y)) {
              printf("X");
            } else if (get(ai->can_see_ever.can_see, x, y)) {
              printf("X");
            } else {
              printf("x");
            }
          } else if (level->is_floor(x, y)) {
            if (get(ai->can_see_currently.can_see, x, y)) {
              printf("L");
            } else if (get(ai->can_see_ever.can_see, x, y)) {
              printf("O");
            } else {
              printf(".");
            }
          } else {
            printf(" ");
          }
        } else {
          if (level->is_obs_wall_or_door(x, y)) {
            if (get(ai->can_see_currently.can_see, x, y)) {
              printf("x");
            } else if (get(ai->can_see_ever.can_see, x, y)) {
              printf("x");
            } else {
              printf("x");
            }
          } else if (level->is_floor(x, y)) {
            if (get(ai->can_see_currently.can_see, x, y)) {
              printf("l");
            } else if (get(ai->can_see_ever.can_see, x, y)) {
              printf("o");
            } else {
              printf(".");
            }
          } else {
            printf(" ");
          }
        }
        continue;
      }
      printf("\n");
    }
  }

  //
  // Check for changes in the dmap worthy of note
  //
  if (check_for_interrupts) {
    auto seen_map = seen_map_get();
    for (int y = miny; y <= maxy; y++) {
      for (int x = minx; x <= maxx; x++) {

        if (get(can_jump, x, y)) {
          set(dmap_can_see->val, x, y, DMAP_IS_PASSABLE);
          continue;
        }

        //
        // Ignore interruptions too far away
        //
        float dist     = distance(curr_at, point(x, y));
        float max_dist = distance_vision_get() + 1;
        if (dist > max_dist) {
          continue;
        }

        //
        // Did anything of interest change worthy of interrupting a walk?
        //
        auto dmap_score = get(dmap_can_see->val, x, y);
        auto seen_when  = get(seen_map->val, x, y);
        if (dmap_score == DMAP_IS_PASSABLE) {
          //
          // Is now seen; did something open?
          //
          if (! seen_when) {
            something_changed++;
            set(seen_map->val, x, y, game->tick_current);
            // con("INTERRUPT1 %d,%d", x, y);
          }
        } else if (dmap_score == DMAP_IS_WALL) {
          //
          // Was seen but now cannot see; did something close?
          //
          if (seen_when && (seen_when < game->tick_current - 20)) {
            something_changed++;
            // con("INTERRUPT2 %d,%d", x, y);
            set(seen_map->val, x, y, 0U);
          }
        }
      }
    }
  }

  //
  // We want to find how far everything is from us.
  //
  set(dmap_can_see->val, start.x, start.y, DMAP_IS_GOAL);

  IF_DEBUG2
  {
    if (is_debug_type()) {
      dbg("Dmap can see before processing:");
      dmap_print(dmap_can_see, curr_at, point(minx, miny), point(maxx, maxy));
    }
  }

  dmap_process(dmap_can_see, point(minx, miny), point(maxx, maxy));

  IF_DEBUG2
  {
    if (is_debug_type()) {
      dbg("Dmap can see:");
      dmap_print(dmap_can_see, curr_at, point(minx, miny), point(maxx, maxy));
    }
  }

  return something_changed;
}

//
// Look at all the things that are currently visited (read that as light rays
// have touched them) and choose the best goal. Create a path to that goal for
// the thing to walk.
//
void Thing::ai_choose_can_see_goals(std::multiset< Goal > &goals, int minx, int miny, int maxx, int maxy)
{
  AI_LOG("Choose can see goals");
  TRACE_AND_INDENT();

  auto dmap_can_see = dmap_can_see_get();
  auto age_map      = age_map_get();

  auto ai = aip();

  auto l = leader();
  if (l) {
    if (too_far_from_leader()) {
      point p = l->curr_at;
      GOAL_ADD(GOAL_PRIO_HIGH, 100, "follow-leader", l);
    }
  }

  for (int y = miny; y <= maxy; y++) {
    for (int x = minx; x <= maxx; x++) {
      point p(x, y);

      if (! get(ai->can_see_currently.can_see, p.x, p.y)) {
        //        if (is_debug_type()) {
        //          log("%d %d can not see currently", p.x, p.y);
        //        }
        continue;
      }

      if (get(dmap_can_see->val, x, y) == DMAP_IS_WALL) {
        //        if (is_debug_type()) {
        //          log("%d %d can not see due to dmap", p.x, p.y);
        //        }
        continue;
      }

      if (is_debug_type()) {
        log("%d %d walk", p.x, p.y);
      }

      FOR_ALL_THINGS_THAT_INTERACT(level, it, p.x, p.y)
      {
        AI_LOG("Can see cand", it);

        if (it->is_changing_level || it->is_hidden || it->is_falling || it->is_jumping) {
          continue;
        }

        if (it == this) {
          continue;
        }

        if (it->immediate_owner_id().ok()) {
          AI_LOG("Has an ownwer; ignore", it);
          continue;
        }

        //
        // Don't attack your mob
        //
        if (it->is_mob() && (top_mob() == this)) {
          AI_LOG("My mob spawner", it);
          continue;
        }

        //
        // Don't attack your fellow minion
        //
        if (it->is_minion() && it->top_mob() && (it->top_mob() == top_mob())) {
          AI_LOG("Fellow minion", it);
          continue;
        }

        //
        // Don't attack your leader
        //
        auto l = leader();
        if (l == this) {
          AI_LOG("Same leader", it);
          continue;
        }

        //
        // Don't attack your fellow follower
        //
        if (it->is_able_to_follow()) {
          if (l) {
            if (it->leader() == l) {
              AI_LOG("Fellow follower", it);
              continue;
            }
          }
        }

        if (is_friend(it)) {
          AI_LOG("Friend", it);
          continue;
        }

        // AI_LOG("Can see", it);

        auto goal_penalty = goal_penalty_get(it);

        //
        // Worse terrain, less preferred. Higher score, morepreferred.
        //
        auto my_health   = health();
        auto it_health   = it->health();
        auto health_diff = my_health - it_health;

        //
        // Don't allow of attacking monsts from memory if the player or
        // robot
        //
        auto lit_recently = get(ai->can_see_currently.can_see, it->curr_at.x, it->curr_at.y);

        if (hunger_is_insatiable()) {
          if (can_eat(it)) {
            //
            // If instatiable, eat, eat, eat...
            //
            GOAL_ADD(GOAL_PRIO_LOW, it_health - goal_penalty, "eat-it", it);
          }
        } else if (is_starving) {
          if (worth_eating(it)) {
            //
            // If starving, prefer the thing with most health
            //
            GOAL_ADD(GOAL_PRIO_LOW, it_health - goal_penalty, "eat-it", it);
          }
        } else if (is_hungry) {
          if (worth_eating(it) && ! is_dangerous(it)) {
            //
            // Prefer easy food over attacking the player and prefer
            // the player over a monster. Factor in health so we will
            // go for the easier kill in preference.
            //
            if (it->is_player()) {
              GOAL_ADD(GOAL_PRIO_LOW, it_health / 2 - goal_penalty, "eat-player", it);
            } else if (it->is_alive_monst()) {
              GOAL_ADD(GOAL_PRIO_LOW, it_health / 2 - goal_penalty, "eat-monst", it);
            } else {
              GOAL_ADD(GOAL_PRIO_LOW, it_health / 2 - goal_penalty, "eat-food", it);
            }
          }
        }

        if (is_item_collector()) {
          if (it->is_collectable()) {
            auto score = worth_collecting(it);
            if (score > 0) {
              GOAL_ADD(GOAL_PRIO_LOW, score - goal_penalty, "collect", it);
            }
          }
        }

        //
        // Need more work before monsts can collect keys as they will be auto collected.
        //
        if (it->is_key()) {
          if (is_able_to_collect_keys()) {
            GOAL_ADD(GOAL_PRIO_LOW, -goal_penalty, "collect-key", it);
          }
        }

        if (it->is_door() && ! it->is_open) {
          if (is_able_to_open_doors() || is_able_to_break_down_doors()) {
            if (keys()) {
              GOAL_ADD(GOAL_PRIO_LOW, -goal_penalty, "open-door-with-key", it);
            } else {
              GOAL_ADD(GOAL_PRIO_LOW, 100 - goal_penalty, "open-door", it);
            }
          }
        }

        if (! it->is_dead) {
          float dist     = distance(curr_at, it->curr_at);
          float max_dist = distance_vision_get();

          //
          // If we can see an enemy, get them! If the monster is not lit then it's not really fair to use that
          // knowledge.
          //
          if (lit_recently) {
            dbg("AI: Consider (my health %d, its health %d) ? %s%s%s%s", my_health, it_health,
                it->to_short_string().c_str(), is_enemy(it) ? ", is enemy" : "",
                is_dangerous(it) ? ", is dangerous" : "", is_to_be_avoided(it) ? ", is to be avoided" : "");

            if (is_enemy(it) && (dist <= max_dist)) {
              if (! is_fearless() && (is_to_be_avoided(it) || is_dangerous(it)) && (health() < health_max() / 2)) {
                //
                // Low on health. Best to avoid this enemy.
                //
                if (cannot_avoid(it)) {
                  GOAL_ADD(GOAL_PRIO_HIGH, (int) (max_dist - dist) * health_diff - goal_penalty,
                           "attack-enemy-i-cannot-avoid", it);
                  AI_LOG("Cannot avoid enemy", it);
                } else {
                  int avoid_score = ((max_dist - dist) * health_diff) - goal_penalty;
                  GOAL_AVOID_ADD(GOAL_PRIO_VERY_HIGH, avoid_score, "avoid-monst", it);
                }
              } else {
                //
                // The closer an enemy is (something that attacked us), the higher the score
                //
                GOAL_ADD(GOAL_PRIO_VERY_HIGH, (int) (max_dist - dist) * health_diff - goal_penalty, "attack-enemy",
                         it);
              }
            } else if (! is_fearless() && (dist < distance_avoid_get()) && will_avoid_monst(it)) {
              //
              // Things we avoid are more serious threats
              //
              if (cannot_avoid(it)) {
                GOAL_ADD(GOAL_PRIO_HIGH, (int) (max_dist - dist) * health_diff, "attack-monst-i-cannot-avoid", it);
                AI_LOG("Cannot avoid monst", it);
              } else {
                //
                // Higher score the closer you are.
                //
                int avoid_score = ((max_dist - dist) * health_diff);
                GOAL_AVOID_ADD(GOAL_PRIO_VERY_HIGH, avoid_score, "avoid-monst", it);
              }
            } else if (it->is_mob() && is_able_to_attack_mobs()) {
              //
              // Very close, very high priority attack as they can spawn much danger!
              //
              GOAL_ADD(GOAL_PRIO_VERY_HIGH, 200 + (int) (max_dist - dist) * health_diff - goal_penalty,
                       "attack-nearby-mob", it);
            } else if ((it->is_alive_monst() || it->is_player()) && possible_to_attack(it)) {
              //
              // The alive monst check is to avoid attacking pools of blood.
              //
              AI_LOG("Possible to attack alive monst", it);

              if (dist < 2) {
                //
                // Very close, high priority attack
                //
                GOAL_ADD(GOAL_PRIO_HIGH, (int) (max_dist - dist) * health_diff - goal_penalty, "attack-nearby-monst",
                         it);
              } else if (dist <= max_dist) {
                //
                // No hunting monsters we cannot see just because we have visited that area before.
                // How aggressive are we?
                //
                if (d100() < aggression_pct()) {
                  if (possible_to_attack(it)) {
                    GOAL_ADD(GOAL_PRIO_MED, -health_diff - goal_penalty, "can-attack-monst-unprovoked", it);
                    //
                    // Add it as an enemy so we will keep going for it and not cool off due to random aggression
                    //
                    add_enemy(it);
                  }
                } else {
                  AI_LOG("Feeling nice, do not attack", it);
                }
              }
            }
          }

          if (! is_immune_to_spiderwebs()) {
            if (it->is_spiderweb() && ! dist) {
              //
              // Very close, high priority attack
              //
              GOAL_ADD(GOAL_PRIO_VERY_HIGH, 666, "get-out-of-web", it);
            }
          }
        }

        if (will_prefer_terrain(it)) {
          //
          // Prefer certain terrains over others. i.e. I prefer water.
          //
          auto age = get(age_map->val, p.x, p.y);
          if (age - game->tick_current < 10) {
            GOAL_ADD(GOAL_PRIO_LOW, 1, "preferred-terrain", it);
          }
        }
      }
      FOR_ALL_THINGS_END();
    }
  }
}

//
// We get here if there is nothing visible of interest. Look at the edges of
// what is currently visible and find the most interesting point at that edge
// and then create a path to that edge.
//
void Thing::ai_choose_search_goals(std::multiset< Goal > &goals, int search_type)
{
  AI_LOG("Choose search goals");
  TRACE_AND_INDENT();

  point start((int) curr_at.x, (int) curr_at.y);

  std::array< std::array< bool, MAP_HEIGHT >, MAP_WIDTH > walked = {};
  std::array< std::array< bool, MAP_HEIGHT >, MAP_WIDTH > pushed = {};
  std::deque< point >                                     in;
  std::deque< point >                                     can_reach_cands;
  std::deque< Thingp >                                    out;
  in.push_back(start);
  set(pushed, start.x, start.y, true);

  if (! is_moveable()) {
    return;
  }

  auto dmap_can_see = dmap_can_see_get();
  while (! in.empty()) {
    auto p = in.front();
    in.pop_front();

    if (get(walked, p.x, p.y)) {
      continue;
    }
    set(walked, p.x, p.y, true);

    if (p.x >= MAP_WIDTH - MAP_BORDER_ROCK) {
      continue;
    }
    if (p.y >= MAP_HEIGHT - MAP_BORDER_ROCK) {
      continue;
    }
    if (p.x < MAP_BORDER_ROCK) {
      continue;
    }
    if (p.y < MAP_BORDER_ROCK) {
      continue;
    }
    if (level->is_obs_wall_or_door(p.x, p.y)) {
      continue;
    }

    //
    // Don't look too far beyond where we can go
    //
    if (too_far_from_mob(p)) {
      continue;
    }

    if (too_far_from_leader(p)) {
      if (distance_from_leader() < too_far_from_leader(p)) {
        continue;
      }
    }

    bool skip_location = false;

    //
    // Don't try and walk through other minions
    //
    if (is_minion()) {
      FOR_ALL_THINGS(level, it, p.x, p.y)
      {
        if (it == this) {
          continue;
        }
        if (it->is_minion()) {
          if (same_mob(it)) {
            skip_location = true;
            break;
          }
        }
      }
    }
    FOR_ALL_THINGS_END();

    //
    // Don't try and walk through other followers
    //
    if (is_able_to_follow()) {
      FOR_ALL_THINGS(level, it, p.x, p.y)
      {
        if (it == this) {
          continue;
        }
        if (it->is_able_to_follow()) {
          if (same_leader(it)) {
            skip_location = true;
            break;
          }
        }
      }
    }
    FOR_ALL_THINGS_END();

    if (skip_location) {
      continue;
    }

    auto ai = aip();

    //
    // If an unvisited tile is next to a visited one, consider that tile.
    //
    if (level->is_descend_dungeon(p) || level->is_ascend_sewer(p)) {
      //
      // Always consider exits so we do not get stuck.
      //
      can_reach_cands.push_back(p);
    } else {
      if (! get(ai->can_see_ever.can_see, p.x, p.y)) {
        can_reach_cands.push_back(p);
        continue;
      }
    }

    if (! get(pushed, p.x + 1, p.y)) {
      set(pushed, p.x + 1, p.y, true);
      in.push_back(point(p.x + 1, p.y));
    }

    if (! get(pushed, p.x - 1, p.y)) {
      set(pushed, p.x - 1, p.y, true);
      in.push_back(point(p.x - 1, p.y));
    }

    if (! get(pushed, p.x, p.y + 1)) {
      set(pushed, p.x, p.y + 1, true);
      in.push_back(point(p.x, p.y + 1));
    }

    if (! get(pushed, p.x, p.y - 1)) {
      set(pushed, p.x, p.y - 1, true);
      in.push_back(point(p.x, p.y - 1));
    }

    int jump_distance;

    switch (search_type) {
      case MONST_SEARCH_TYPE_LOCAL_JUMP_ALLOWED: jump_distance = jump_distance_max_get(); break;
      case MONST_SEARCH_TYPE_LOCAL_NO_JUMP: jump_distance = 0; break;
      case MONST_SEARCH_TYPE_GLOBAL_JUMP_ALLOWED: jump_distance = jump_distance_max_get(); break;
      case MONST_SEARCH_TYPE_GLOBAL_NO_JUMP: jump_distance = 0; break;
      case MONST_SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED: jump_distance = jump_distance_max_get(); break;
      case MONST_SEARCH_TYPE_LAST_RESORTS_NO_JUMP: jump_distance = 0; break;
      default: DIE("unexpected search-type case"); break;
    }

    auto dist = distance(p, curr_at);
    for (int dx = -jump_distance; dx <= jump_distance; dx++) {
      for (int dy = -jump_distance; dy <= jump_distance; dy++) {

        point o(p.x + dx, p.y + dy);
        if (level->is_oob(o)) {
          continue;
        }

        if (! dx && ! dy) {
          continue;
        }

        if (get(dmap_can_see->val, o.x, o.y) > DMAP_IS_PASSABLE) {
          continue;
        }

        if (get(walked, o.x, o.y)) {
          continue;
        }

        if (level->is_door(o)) {
          //
          // A locked door is worth investigating
          //
          if (! is_able_to_open_doors() && ! is_able_to_break_down_doors()) {
            continue;
          }
        } else if (level->is_secret_door(o)) {
          if (! ai_detect_secret_doors()) {
            continue;
          }
          if (dist > THING_AI_CAN_SEE_SECRET_DOOR_DIST) {
            continue;
          }
        } else if (level->is_descend_sewer(o)) {
          //
          // Worth investigating unless over
          //
          if (! is_exit_finder()) {
            continue;
          }
          if ((o.x == curr_at.x) && (o.y == curr_at.y)) {
            continue;
          }
          if (search_type < MONST_SEARCH_TYPE_LAST_RESORTS_NO_JUMP) {
            continue;
          }
          IF_DEBUG
          {
            auto s = string_sprintf("Choose possible descend sewer at @(%d,%d)", o.x, o.y);
            AI_LOG(s);
          }
        } else if (level->is_ascend_sewer(o)) {
          //
          // Worth investigating
          //
          if (! is_exit_finder()) {
            continue;
          }
          if ((o.x == curr_at.x) && (o.y == curr_at.y)) {
            continue;
          }
          if (search_type < MONST_SEARCH_TYPE_LAST_RESORTS_NO_JUMP) {
            continue;
          }
          IF_DEBUG
          {
            auto s = string_sprintf("Choose possible ascend sewer at @(%d,%d)", o.x, o.y);
            AI_LOG(s);
          }
        } else if (level->is_descend_dungeon(o)) {
          //
          // Worth investigating
          //
          if (! is_exit_finder()) {
            continue;
          }
          if ((o.x == curr_at.x) && (o.y == curr_at.y)) {
            continue;
          }
          if (search_type < MONST_SEARCH_TYPE_LAST_RESORTS_NO_JUMP) {
            continue;
          }
          IF_DEBUG
          {
            auto s = string_sprintf("Choose possible descend dungeon at @(%d,%d)", o.x, o.y);
            AI_LOG(s);
          }
        } else if (level->is_ascend_dungeon(o)) {
          //
          // Worth investigating
          //
          if (! is_exit_finder()) {
            continue;
          }
          if ((o.x == curr_at.x) && (o.y == curr_at.y)) {
            continue;
          }
          if (search_type < MONST_SEARCH_TYPE_LAST_RESORTS_NO_JUMP) {
            continue;
          }
          IF_DEBUG
          {
            auto s = string_sprintf("Choose possible ascend dungeon at @(%d,%d)", o.x, o.y);
            AI_LOG(s);
          }
        } else {
          //
          // If lit then we can already see it, so not worth exploring.
          //
          if (get(ai->can_see_ever.can_see, o.x, o.y)) {
            continue;
          }

          if (level->is_obs_wall_or_door(o)) {
            continue;
          }
        }

        set(walked, o.x, o.y, true);
        can_reach_cands.push_back(o);
      }
    }
  }

  if (is_debug_type()) {
    auto ai = aip();

    con("This is what I am searching (type %d):", search_type);
    con("  @  - you/it");
    con("  L  - walked and can see currently");
    con("  O  - walked and have seen ever");
    con("  l  - can see currently");
    con("  o  - have seen ever");

    for (int y = 0; y < MAP_HEIGHT; y++) {
      std::string s;
      for (int x = 0; x < MAP_WIDTH; x++) {
        if ((x == (int) curr_at.x) && (y == (int) curr_at.y)) {
          s += "@";
          s += " ";
          continue;
        }
        if (get(walked, x, y)) {
          if (level->is_obs_wall_or_door(x, y)) {
            if (get(ai->can_see_currently.can_see, x, y)) {
              s += "X";
            } else if (get(ai->can_see_ever.can_see, x, y)) {
              s += "X";
            } else {
              s += "x";
            }
          } else if (level->is_floor(x, y)) {
            if (get(ai->can_see_currently.can_see, x, y)) {
              s += "L";
            } else if (get(ai->can_see_ever.can_see, x, y)) {
              s += "O";
            } else {
              s += ".";
            }
          } else {
            s += " ";
          }
        } else {
          if (level->is_obs_wall_or_door(x, y)) {
            if (get(ai->can_see_currently.can_see, x, y)) {
              s += "x";
            } else if (get(ai->can_see_ever.can_see, x, y)) {
              s += "x";
            } else {
              s += "x";
            }
          } else if (level->is_floor(x, y)) {
            if (get(ai->can_see_currently.can_see, x, y)) {
              s += "l";
            } else if (get(ai->can_see_ever.can_see, x, y)) {
              s += "o";
            } else {
              s += ".";
            }
          } else {
            s += " ";
          }
        }

        bool found = false;
        for (auto p : can_reach_cands) {
          if ((x == p.x) && (y == p.y)) {
            s += "c";
            found = true;
            break;
          }
        }
        if (! found) {
          s += " ";
        }
      }
      con("%s", s.c_str());
    }
  }

  //
  // Choose goals (higher scores, lower costs are preferred)
  //
  for (auto i = 0; i < (int) can_reach_cands.size(); i++) {
    auto p = can_reach_cands[ i ];

    //
    // Avoid sewer descend/ascend loop
    //
    if ((p.x == curr_at.x) && (p.y == curr_at.y)) {
      continue;
    }

    if (too_far_from_mob(p, 1)) {
      continue;
    }

    if (too_far_from_leader(p, 1)) {
      continue;
    }

    //
    // No search destinations that are, for example, a chasm
    //
    if (is_hated_by_me(p)) {
      IF_DEBUG
      {
        auto s = string_sprintf("Search cand is hated @(%d,%d)", p.x, p.y);
        AI_LOG(s);
      }
      continue;
    }

    //
    // Prefer easier terrain
    //
    int terrain_cost = terrain_cost_get(p);
    int total_score  = -(int) terrain_cost;

    //
    // Prefer newer tiles
    //
    auto age_map = age_map_get();
    int  age     = get(age_map->val, p.x, p.y);

    //
    // Prefer the unknown.
    //
    if (age) {
      total_score -= ((int) age) - game->tick_current;
    } else {
      total_score += 100;
    }

    //
    // Prefer closer
    //
    float dist = distance(start, p);
    total_score -= dist;

    //
    // Choose doors etc... as a last resort when nothing else
    //
    if (is_explorer()) {
      if (level->is_door(p)) {
        total_score -= 100;
      }
    }

    if (is_exit_finder()) {
      if (level->is_descend_sewer(p)) {
        total_score -= 5000;
        //
        // Prefer not to walk over if there is a way around
        //
        terrain_cost += 10;
      }

      if (level->is_ascend_sewer(p)) {
        total_score -= 10000;
        terrain_cost += 10;
      }

      if (level->is_descend_dungeon(p)) {
        total_score += 100;
        terrain_cost += 10;
      }

      if (level->is_ascend_dungeon(p)) {
        total_score -= 100000;
        terrain_cost += 10;
      }
    }

    if (is_minion()) {
      auto mob = top_mob();
      if (mob) {
        auto dist = distance(p, mob->curr_at);
        auto msg  = string_sprintf("search cand @(%d,%d) dist-from-owner %f", p.x, p.y, dist);
        GOAL_ADD(GOAL_PRIO_VERY_LOW, total_score, msg.c_str(), nullptr);
      } else {
        auto msg = string_sprintf("search cand @(%d,%d) no-owner", p.x, p.y);
        GOAL_ADD(GOAL_PRIO_VERY_LOW, total_score, msg.c_str(), nullptr);
      }
    } else {
      auto msg = string_sprintf("search cand @(%d,%d)", p.x, p.y);
      GOAL_ADD(GOAL_PRIO_VERY_LOW, total_score, msg.c_str(), nullptr);
      if (is_debug_type()) {
        con("search cand @(%d,%d) score %d", p.x, p.y, total_score);
      }
    }
  }
}

bool Thing::ai_choose_immediately_adjacent_goal(void)
{
  AI_LOG("Choose immediately adjacent goals");
  TRACE_AND_INDENT();

  bool left   = false;
  bool right  = false;
  bool up     = false;
  bool down   = false;
  bool wait   = false;
  bool jump   = false;
  bool attack = false;

  AttackOptions attack_options {};

  attack_options.shove_allowed  = false;
  attack_options.attack_allowed = true;

  for (int dx = -1; dx <= 1; dx++) {
    for (int dy = -1; dy <= 1; dy++) {

      point at(curr_at.x + dx, curr_at.y + dy);
      if (level->is_oob(at)) {
        continue;
      }

      FOR_ALL_THINGS(level, it, at.x, at.y)
      {
        if (it->is_hidden) {
          continue;
        }

        if (it->is_door() && ! it->is_open) {
          if (is_able_to_open_doors()) {
            if (keys()) {
              if (open_door(it)) {
                AI_LOG("Opened a door", it);
                if (is_player()) {
                  game->tick_begin("Robot opened a door");
                }
                return true;
              }
            }
          }

          if (is_able_to_break_down_doors()) {
            //
            // Try hitting the door
            //
            left   = dx < 0;
            right  = dx > 0;
            up     = dy < 0;
            down   = dy > 0;
            attack = true;

            attack_options.attack_allowed = true;
            if (up || down || left || right) {
              attack_options.attack_at     = at;
              attack_options.attack_at_set = true;
            }

            AI_LOG("Trying to break down a door", it);
            if (is_player()) {
              player_tick(left, right, up, down, attack, wait, jump);
            } else if (is_moveable()) {
              move(curr_at, up, down, left, right, attack, wait, &attack_options);
            }
            return true;
          }
        }

        if (is_able_to_break_out_of_webs()) {
          if (it->is_spiderweb() && (it->curr_at == curr_at)) {
            //
            // Try hitting the web
            //
            left   = dx < 0;
            right  = dx > 0;
            up     = dy < 0;
            down   = dy > 0;
            attack = true;

            attack_options.attack_allowed = true;
            if (up || down || left || right) {
              attack_options.attack_at     = at;
              attack_options.attack_at_set = true;
            }

            AI_LOG("Trying to break out of a web", it);
            if (is_player()) {
              player_tick(left, right, up, down, attack, wait, jump);
            } else if (is_moveable()) {
              move(curr_at, up, down, left, right, attack, wait, &attack_options);
            }
            return true;
          }
        }

        if (is_able_to_break_out_of_ice()) {
          if (it->is_icecube() && (it->curr_at == curr_at)) {
            //
            // Try hitting the ice
            //
            left   = dx < 0;
            right  = dx > 0;
            up     = dy < 0;
            down   = dy > 0;
            attack = true;

            attack_options.attack_allowed = true;
            if (up || down || left || right) {
              attack_options.attack_at     = at;
              attack_options.attack_at_set = true;
            }

            AI_LOG("Trying to break out of ice", it);
            if (is_player()) {
              player_tick(left, right, up, down, attack, wait, jump);
            } else if (is_moveable()) {
              move(curr_at, up, down, left, right, attack, wait, &attack_options);
            }
            return true;
          }
        }
      }
      FOR_ALL_THINGS_END();

      if (is_item_collector()) {
        auto items = anything_to_carry_at(at);
        if (items.size() >= 1) {
          for (auto item : items) {
            if (try_to_carry_if_worthwhile_dropping_items_if_needed(item)) {
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}

void Thing::ai_get_next_hop(void)
{
  dbg2("AI get nexthop");
  TRACE_AND_INDENT();

  //
  // Find the best goal to go to
  //
  if (ai_tick()) {
    return;
  }

  //
  // Ok our attempted move is done. We failed.
  //
  move_finish();

  //
  // If cannot move (maybe over a chasm that spawned) then fall
  //
  location_check();
}

bool Thing::ai_choose_avoid_goals(std::multiset< Goal > &goals, const Goal &goal)
{
  TRACE_NO_INDENT();

  Thingp it    = goal.what;
  int    score = goal.score;
  int    max_avoid;

  if (is_player()) {
    max_avoid = -1;
  } else {
    max_avoid = THING_AI_MAX_AVOID_ATTEMPT_LOC;
  }

  AI_LOG("Needs to avoid", it);
  TRACE_AND_INDENT();

  auto d = distance_vision_get();
  if (! d) {
    d = 2;
  }

  std::vector< std::pair< Thingp, int > > possible;

  for (auto dx = -d; dx <= d; dx++) {
    for (auto dy = -d; dy <= d; dy++) {

      point p(curr_at.x + dx, curr_at.y + dy);
      if (level->is_oob(p)) {
        continue;
      }

      if (! dx && ! dy) {
        continue;
      }

      float dist = distance(curr_at + point(dx, dy), it->curr_at);
      if (dist < distance_avoid_get()) {
        continue;
      }

      if (ai_obstacle_for_me(p)) {
        continue;
      }

      int terrain_cost = terrain_cost_get(p);
      score -= (int) terrain_cost;
      score += dist * 10;
      GOAL_ADD(GOAL_PRIO_HIGH, score, "avoid-location-1", it);
    }
  }

  if (goals.size()) {
    if (max_avoid > -1) {
      if ((int) goals.size() > max_avoid) {
        auto b = goals.begin();
        auto e = goals.end();
        std::advance(b, max_avoid - 1);
        goals.erase(b, e);
      }
    }
    return true;
  }

  //
  // Try again with more lenient checks
  //
  for (auto dx = -d; dx <= d; dx++) {
    for (auto dy = -d; dy <= d; dy++) {

      point p(curr_at.x + dx, curr_at.y + dy);
      if (level->is_oob(p)) {
        continue;
      }

      if (ai_obstacle_for_me(p)) {
        continue;
      }

      float dist         = distance(curr_at + point(dx, dy), it->curr_at);
      int   terrain_cost = terrain_cost_get(p);
      int   score        = -(int) terrain_cost;
      score += dist * 100;
      score += 1000;
      GOAL_ADD(GOAL_PRIO_HIGH, score, "avoid-location-2", it);
      return true;
    }
  }

  if (goals.size()) {
    if (max_avoid > -1) {
      if ((int) goals.size() > max_avoid) {
        auto b = goals.begin();
        auto e = goals.end();
        std::advance(b, max_avoid - 1);
        goals.erase(b, e);
      }
    }
    return true;
  }

  //
  // Try again with even more lenient checks
  //
  for (auto dx = -d; dx <= d; dx++) {
    for (auto dy = -d; dy <= d; dy++) {

      point p(curr_at.x + dx, curr_at.y + dy);
      if (level->is_oob(p)) {
        continue;
      }

      if (level->is_obs_wall_or_door(p)) {
        continue;
      }

      float dist         = distance(curr_at + point(dx, dy), it->curr_at);
      int   terrain_cost = terrain_cost_get(p);
      int   score        = -(int) terrain_cost;
      score += dist * 100;
      score += 1000;
      GOAL_ADD(GOAL_PRIO_HIGH, score, "avoid-location-3", it);
      return true;
    }
  }

  if (goals.size()) {
    if (max_avoid > -1) {
      if ((int) goals.size() > max_avoid) {
        auto b = goals.begin();
        auto e = goals.end();
        std::advance(b, max_avoid - 1);
        goals.erase(b, e);
      }
    }
    return true;
  }

  AI_LOG("Did not find any location to avoid to");
  TRACE_AND_INDENT();

  //
  // Last resorts
  //
  if (is_monst()) {
    if (ai_escape()) {
      return true;
    }
  }

  AI_LOG("Could not avoid", it);
  return false;
}

//
// Return true on having done something
//
bool Thing::ai_tick(bool recursing)
{
  dbg("AI tick");
  TRACE_AND_INDENT();

  auto ai = aip();

  if (is_player()) {
    if (game->things_are_moving) {
      return false;
    }

    if (game->tick_completed != game->tick_current) {
      return false;
    }
  }

  if (is_dead) {
    return false;
  }

  if (is_changing_level || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall ||
      is_jumping) {
    return false;
  }

  if (! g_opt_ascii && level->ts_fade_in_begin) {
    return false;
  }

  if (level->cursor) {
    level->cursor->hide();
  }

  //
  // Set up the extent of the AI, choosing smaller areas for monsters for speed.
  //
  const float dx = distance_vision_get();
  const float dy = dx;

  auto vision_source = vision_source_get();

  int minx = std::max(0, (int) (vision_source.x - dx));
  int maxx = std::min(MAP_WIDTH - 1, (int) (vision_source.x + dx));
  int miny = std::max(0, (int) (vision_source.y - dy));
  int maxy = std::min(MAP_HEIGHT - 1, (int) (vision_source.y + dy));

  bool   left         = false;
  bool   right        = false;
  bool   up           = false;
  bool   down         = false;
  bool   attack       = false;
  bool   wait         = false;
  bool   jump         = false;
  bool   do_something = false;
  Thingp threat       = nullptr;

  //
  // Wake on noise?
  //
  is_sleeping = infop()->monst_state == MONST_STATE_SLEEPING;
  if (is_sleeping) {
    if (LEVEL_LOUDEST_SOUND - level->noisemap(curr_at) > noise_decibels_hearing()) {
      if (! wake("heard something")) {
        return false;
      }
    }
  }

  //
  // If we have a treasure map then we know this level
  //
  if (map_treasure_available()) {
    for (int y = miny; y <= maxy; y++) {
      for (int x = minx; x <= maxx; x++) {
        set(ai->can_see_ever.can_see, x, y, true);
      }
    }
  }

  //
  // Update what we can see - which if a minion is from the perspective of the mob.
  // We need to grow the light a bit for level explorers and things that can see diagonally.
  //
  level->fov_calculate(this, &ai->can_see_currently, &ai->can_see_ever, vision_source.x, vision_source.y,
                       distance_vision_get() + 1);

  //
  // check for anything dangerous we need to consider and maybe stop what we're doing.
  //
  switch (infop()->monst_state) {
    case MONST_STATE_IDLE:
      //
      // if we are called 2nd time around, then we left some kind of other state and want to try moving.
      //
      if (recursing) {
        break;
      }
    case MONST_STATE_MOVING:
    case MONST_STATE_RESTING:
    case MONST_STATE_SLEEPING:
      {
        //
        // see if anything dangerous is close
        //
        threat = most_dangerous_visible_thing();
        if (threat) {
          ai_log("threat", threat);
        }

        //
        // A threat can be a few tiles away; but if one is standing literally next to us! then it takes priority.
        //
        auto adjacent_threat = most_dangerous_adjacent_thing();
        if (adjacent_threat) {
          AI_LOG("Adjacent threat", adjacent_threat);
          TRACE_AND_INDENT();

          if (is_dangerous(adjacent_threat)) {
            threat = adjacent_threat;
          } else {
            AI_LOG("Adjacent threat (not dangerous)", adjacent_threat);
            threat = nullptr;
          }
        }

        //
        // Prevent loops; should never hit this
        //
        if (recursing) {
          return true;
        }

        //
        // If on fire terrain, change to idle state and try again to move
        //
        if (is_on_fire() && environ_avoids_fire()) {
          AI_LOG("I am on fire!");
          TRACE_AND_INDENT();

          if (is_player()) {
            game->tick_begin("Robot move interrupted by being on fire");
          }
          change_state(MONST_STATE_IDLE, "move interrupted by being on fire!");
          return ai_tick(true); /* try again to move now we are no longer resting or asleep */
        }

        //
        // If on bad terrain, change to idle state and try again to move
        //
        if (terrain_cost_get(curr_at) >= DMAP_LESS_PREFERRED_TERRAIN) {
          AI_LOG("I am on some bad terrain!");
          TRACE_AND_INDENT();

          if (is_player()) {
            game->tick_begin("Robot move interrupted by bad terrain");
          }
          change_state(MONST_STATE_IDLE, "move interrupted by being on bad terrain");
          return ai_tick(true); /* try again to move now we are no longer resting or asleep */
        }
      }
      break;
    case MONST_STATE_REPACK_INVENTORY:
    case MONST_STATE_OPEN_INVENTORY:
    case MONST_STATE_USING_ENCHANTSTONE:
    case MONST_STATE_USING_SKILLSTONE: break;
  }

  switch (infop()->monst_state) {
    case MONST_STATE_IDLE:
      //
      // if we are called 2nd time around, then we left some kind of other state and want to try moving.
      //
      if (recursing) {
        break;
      }
    case MONST_STATE_MOVING:
    case MONST_STATE_RESTING:
      {
        //
        // Check for lesser interrupts; like a monster being seen
        //
        AI_LOG("Check for interruptions");
        TRACE_AND_INDENT();

        if (ai_dmap_can_see_init(minx, miny, maxx, maxy, MONST_SEARCH_TYPE_CAN_SEE_JUMP_ALLOWED, true)) {
          AI_LOG("Something interrupted me");
          TRACE_AND_INDENT();

          if (is_player()) {
            game->tick_begin("Robot move interrupted by something");
          }
          change_state(MONST_STATE_IDLE, "move interrupted by a change");
          return ai_tick(true); /* try again to move now we are no longer resting or asleep */
        }
      }
      break;
    case MONST_STATE_SLEEPING:
    case MONST_STATE_REPACK_INVENTORY:
    case MONST_STATE_OPEN_INVENTORY:
    case MONST_STATE_USING_ENCHANTSTONE:
    case MONST_STATE_USING_SKILLSTONE: break;
  }

  if (is_debug_type()) {
    con("This is my field of view:");
    con("  @  - you/it");
    con("  l  - can see currently");
    con("  o  - have seen ever");
    for (int y = 0; y < MAP_HEIGHT; y++) {
      for (int x = 0; x < MAP_WIDTH; x++) {
        if ((x == (int) curr_at.x) && (y == (int) curr_at.y)) {
          printf("@");
        } else {
          if (get(ai->can_see_currently.can_see, x, y)) {
            if (level->is_door(x, y)) {
              printf("D");
            } else if (level->is_obs_wall_or_door(x, y)) {
              printf("X");
            } else {
              printf("l");
            }
          } else if (get(ai->can_see_ever.can_see, x, y)) {
            if (level->is_door(x, y)) {
              printf("D");
            } else if (level->is_obs_wall_or_door(x, y)) {
              printf("X");
            } else {
              printf("o");
            }
          } else {
            if (level->is_door(x, y)) {
              printf("d");
            } else if (level->is_obs_wall_or_door(x, y)) {
              printf("x");
            } else if (level->is_floor(x, y)) {
              printf(".");
            } else {
              printf(" ");
            }
          }
        }
      }
      printf("\n");
    }
  }

  switch (infop()->monst_state) {
    case MONST_STATE_IDLE:
      if (state_idle(threat, minx, miny, maxx, maxy)) {
        return true;
      }
      break;
    case MONST_STATE_MOVING:
      if (state_moving()) {
        return true;
      }
      break;
    case MONST_STATE_SLEEPING:
      if (state_sleeping(do_something, wait)) {
        return true;
      }
      break;
    case MONST_STATE_RESTING:
      if (state_resting(do_something, wait)) {
        return true;
      }
      break;

    case MONST_STATE_OPEN_INVENTORY:
      if (state_open_inventory()) {
        return true;
      }
      break;

    case MONST_STATE_USING_ENCHANTSTONE:
      if (state_using_enchantstone()) {
        return true;
      }
      break;

    case MONST_STATE_USING_SKILLSTONE:
      if (state_using_skillstone()) {
        return true;
      }
      break;

    case MONST_STATE_REPACK_INVENTORY:
      if (state_repack_inventory()) {
        return true;
      }
      break;
  }

  if (do_something) {
    if (is_player()) {
      player_tick(left, right, up, down, attack, wait, jump);
    } else if (is_moveable()) {
      AttackOptions attack_options {};
      move(curr_at, up, down, left, right, attack, wait, &attack_options);
    }
  }

  return true;
}
