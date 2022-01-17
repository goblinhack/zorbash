//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_player.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_template.hpp"
#include "my_thing.hpp"
#include "my_thing_ai.hpp"
#include "my_thing_template.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_thing_info.hpp"
#include <algorithm>
#include <set>

//
// Search priorities in order
//
#define SEARCH_TYPE_MAX                       7
#define SEARCH_TYPE_CAN_SEE_JUMP_ALLOWED      0
#define SEARCH_TYPE_LOCAL_NO_JUMP             1
#define SEARCH_TYPE_LOCAL_JUMP_ALLOWED        2
#define SEARCH_TYPE_GLOBAL_NO_JUMP            3
#define SEARCH_TYPE_GLOBAL_JUMP_ALLOWED       4
#define SEARCH_TYPE_LAST_RESORTS_NO_JUMP      5
#define SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED 6

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
  auto dmap_can_see = get_dmap_can_see();

  switch (search_type) {
    case SEARCH_TYPE_CAN_SEE_JUMP_ALLOWED :
    case SEARCH_TYPE_LOCAL_NO_JUMP :
    case SEARCH_TYPE_LOCAL_JUMP_ALLOWED : break;
    case SEARCH_TYPE_GLOBAL_NO_JUMP :
    case SEARCH_TYPE_GLOBAL_JUMP_ALLOWED :
    case SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED :
    case SEARCH_TYPE_LAST_RESORTS_NO_JUMP :
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
    case SEARCH_TYPE_CAN_SEE_JUMP_ALLOWED :
      ai_choose_can_see_goals(goals, minx, miny, maxx, maxy);
      goalmaps.push_back(GoalMap {goals, dmap_can_see});
      break;
    case SEARCH_TYPE_LOCAL_NO_JUMP :
    case SEARCH_TYPE_LOCAL_JUMP_ALLOWED :
    case SEARCH_TYPE_GLOBAL_NO_JUMP :
    case SEARCH_TYPE_GLOBAL_JUMP_ALLOWED :
    case SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED :
    case SEARCH_TYPE_LAST_RESORTS_NO_JUMP :
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

  for (auto &g : goalmaps) {
    IF_DEBUG2
    {
      if (is_debug_type()) {
        AI_LOG("Pre modify dmap for terrain");
        dmap_print(g.dmap, point(start.x, start.y), point(minx, miny), point(maxx, maxy));

        if (search_type == SEARCH_TYPE_CAN_SEE_JUMP_ALLOWED) {
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
                auto s = string_sprintf("Accept goal score %d @(%d,%d) %s", (int) goal.score, (int) goal.at.x,
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

  auto aip = get_aip();

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
  auto age_map = get_age_map();
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
      level->cursor_path_create(new_move_path);
      IF_DEBUG2 { level->debug_path_create(new_move_path); }

      //
      // Try to move. It might not work and we end up attacking.
      //
      if (cursor_path_pop_first_move()) {
        return true;
      }

      //
      // Did we try or attempt to try to do something?
      //
      if (is_player()) {
        if (! game->tick_requested.empty()) {
          return true;
        }
      } else {
        return true;
      }
    } else {
      aip->move_path = new_move_path;

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

  std::array< std::array< uint8_t, MAP_WIDTH >, MAP_HEIGHT > can_jump = {};

  point start((int) curr_at.x, (int) curr_at.y);
  auto  dmap_can_see      = get_dmap_can_see();
  bool  jump_allowed      = false;
  int   something_changed = 0;

  for (int y = miny; y <= maxy; y++) {
    for (int x = minx; x <= maxx; x++) {
      set(dmap_can_see->val, x, y, DMAP_IS_WALL);
    }
  }

  switch (search_type) {
    case SEARCH_TYPE_CAN_SEE_JUMP_ALLOWED : jump_allowed = true; break;
    case SEARCH_TYPE_LOCAL_NO_JUMP : jump_allowed = false; break;
    case SEARCH_TYPE_LOCAL_JUMP_ALLOWED : jump_allowed = true; break;
    case SEARCH_TYPE_GLOBAL_NO_JUMP : jump_allowed = false; break;
    case SEARCH_TYPE_GLOBAL_JUMP_ALLOWED : jump_allowed = true; break;
    case SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED : jump_allowed = true; break;
    case SEARCH_TYPE_LAST_RESORTS_NO_JUMP : jump_allowed = false; break;
  }

  if (! is_able_to_jump()) {
    jump_allowed = false;
  }

  auto aip = get_aip();

  std::array< std::array< bool, MAP_WIDTH >, MAP_HEIGHT > walked = {};

  for (int y = miny; y <= maxy; y++) {
    for (int x = minx; x <= maxx; x++) {
      point p(x, y);
      if (! get(aip->can_see_ever.can_see, x, y)) {
        continue;
      }

      if (too_far_from_mob_spawner(p)) {
        continue;
      }

      if (too_far_from_leader(p)) {
        if (get_distance_from_leader() < too_far_from_leader(p)) {
          continue;
        }
      }

      set(walked, x, y, true);

      if (! ai_obstacle_for_me(p)) {
        set(dmap_can_see->val, x, y, DMAP_IS_PASSABLE);
        continue;
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
      if (get_stamina() > get_stamina_max() / 2) {
        //
        // Trace all possible jump paths to see if we can jump over
        //
        auto jump_dist = how_far_i_can_jump_max();
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
          if (! get(aip->can_see_ever.can_see, jump_begin.x, jump_begin.y)) {
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
          // a bit when calling fov_calculete
          //
          if (! get(aip->can_see_ever.can_see, p.x, p.y)) {
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
              if (! get(aip->can_see_ever.can_see, o.x, o.y) && ! get(aip->interrupt_map.val, o.x, o.y)) {

                FOR_ALL_THINGS_THAT_INTERACT(level, it, o.x, o.y)
                {
                  if (it == this) {
                    continue;
                  }

                  if (it->is_changing_level || it->is_hidden || it->is_falling || it->is_jumping) {
                    continue;
                  }

                  if (worth_collecting(it) > 0) {
                    set(aip->interrupt_map.val, p.x, p.y, game->tick_current);
                    if (check_for_interrupts) {
                      something_changed++;
                      AI_LOG("Interrupted by thing worth collecting", it);
                    }
                  }
                  if (is_dangerous(it)) {
                    set(aip->interrupt_map.val, p.x, p.y, game->tick_current);
                    if (check_for_interrupts) {
                      something_changed++;
                      AI_LOG("Interrupted by dangerous thing", it);
                    }
                  }

                  if (worth_eating(it)) {
                    set(aip->interrupt_map.val, p.x, p.y, game->tick_current);
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

#if 0
  if (is_debug_type()) {
    con("This is what I can see:");
    for (int y = 0; y < MAP_HEIGHT; y++) {
      for (int x = 0; x < MAP_WIDTH; x++) {
        if ((x == (int) curr_at.x) && (y == (int) curr_at.y)) {
          if (get(aip->can_see_ever.can_see, x, y)) {
            printf("*");
          } else {
            printf("o");
          }
          continue;
        }
        if (get(walked, x, y)) {
          if (level->is_obs_wall_or_door(x, y)) {
            if (get(aip->can_see_ever.can_see, x, y)) {
              printf("X");
            } else {
              printf("x");
            }
          } else {
            if (get(aip->can_see_ever.can_see, x, y)) {
              printf("?");
            } else {
              printf(",");
            }
          }
        } else {
          if (level->is_obs_wall_or_door(x, y)) {
            printf("+");
          } else {
            if (get(aip->can_see_currently.can_see, x, y)) {
              printf("l");
            } else {
              printf(" ");
            }
          }
        }
        continue;
      }
      printf("\n");
    }
  }
#endif

  //
  // Check for changes in the dmap worthy of note
  //
  if (check_for_interrupts) {
    auto seen_map = get_seen_map();
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
        float max_dist = get_distance_vision() + 1;
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

  auto dmap_can_see = get_dmap_can_see();
  auto age_map      = get_age_map();

  auto aip = get_aip();

  auto leader = get_leader();
  if (leader) {
    if (too_far_from_leader()) {
      point p = leader->curr_at;
      GOAL_ADD(GOAL_PRIO_HIGH, 100, "follow-leader", leader);
    }
  }

  if (is_debug_type()) {
    log("Choose can see goals %d,%d to %d,%d", minx, miny, maxx, maxy);
  }

  for (int y = miny; y <= maxy; y++) {
    for (int x = minx; x <= maxx; x++) {
      point p(x, y);

      if (! get(aip->can_see_currently.can_see, p.x, p.y)) {
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

      //      if (is_debug_type()) {
      //        log("%d %d walk", p.x, p.y);
      //      }

      FOR_ALL_THINGS_THAT_INTERACT(level, it, p.x, p.y)
      {
        AI_LOG("Can see cand", it);

        if (it->is_changing_level || it->is_hidden || it->is_falling || it->is_jumping) {
          continue;
        }

        if (it == this) {
          continue;
        }

        if (it->get_immediate_owner_id().ok()) {
          AI_LOG("Has an ownwer; ignore", it);
          continue;
        }

        //
        // Don't attack your mob_spawner
        //
        if (it->is_mob_spawner() && (get_top_mob_spawner() == this)) {
          AI_LOG("My mob spawner", it);
          continue;
        }

        //
        // Don't attack your fellow minion
        //
        if (it->is_minion() && (it->get_top_mob_spawner() == get_top_mob_spawner())) {
          AI_LOG("Fellow minion", it);
          continue;
        }

        //
        // Don't attack your leader
        //
        auto leader = get_leader();
        if (leader == this) {
          AI_LOG("Same leader", it);
          continue;
        }

        //
        // Don't attack your fellow follower
        //
        if (it->is_able_to_follow()) {
          if (leader) {
            if (it->get_leader() == leader) {
              AI_LOG("Fellow follower", it);
              continue;
            }
          }
        }

        AI_LOG("Can see", it);

        auto goal_penalty = get_goal_penalty(it);

        //
        // Worse terrain, less preferred. Higher score, morepreferred.
        //
        auto my_health   = get_health();
        auto it_health   = it->get_health();
        auto health_diff = my_health - it_health;

        //
        // Don't allow of attacking monsts from memory if the player or
        // robot
        //
        auto lit_recently = get(aip->can_see_currently.can_see, it->curr_at.x, it->curr_at.y);

        if (is_starving) {
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
            if (get_keys()) {
              GOAL_ADD(GOAL_PRIO_LOW, -goal_penalty, "open-door-with-key", it);
            } else {
              GOAL_ADD(GOAL_PRIO_LOW, 100 - goal_penalty, "open-door", it);
            }
          }
        }

        if (! it->is_dead) {
          float dist     = distance(curr_at, it->curr_at);
          float max_dist = get_distance_vision();

          //
          // If we can see an enemy, get them! If the monster is not lit
          // then it's not really fair to use that knowledge.
          //
          if (lit_recently) {
            dbg("AI: Consider attacking? %s%s%s%s", it->to_short_string().c_str(), is_enemy(it) ? ", is enemy" : "",
                is_dangerous(it) ? ", is dangerous" : "", is_to_be_avoided(it) ? ", is to be avoided" : "");

            if (is_enemy(it) && (dist <= max_dist)) {
              if (! is_fearless() && (is_to_be_avoided(it) || is_dangerous(it)) &&
                  (get_health() < get_health_max() / 2)) {
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
            } else if (! is_fearless() && (dist < get_distance_avoid()) && will_avoid_monst(it)) {
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
            } else if (it->is_mob_spawner() && is_able_to_attack_mobs()) {
              //
              // Very close, high priority attack
              //
              GOAL_ADD(GOAL_PRIO_HIGH, (int) (max_dist - dist) * health_diff - goal_penalty, "attack-nearby-mob", it);
            } else if (possible_to_attack(it)) {
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
                if (d100() < aggression_level_pct()) {
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

          if (! environ_prefers_spiderwebs()) {
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

  std::array< std::array< bool, MAP_WIDTH >, MAP_HEIGHT > walked = {};
  std::array< std::array< bool, MAP_WIDTH >, MAP_HEIGHT > pushed = {};
  std::deque< point >                                     in;
  std::deque< point >                                     can_reach_cands;
  std::deque< Thingp >                                    out;
  in.push_back(start);
  set(pushed, start.x, start.y, true);

  auto dmap_can_see = get_dmap_can_see();
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

    //
    // Don't look too far beyond where we can go
    //
    if (too_far_from_mob_spawner(p)) {
      continue;
    }

    if (too_far_from_leader(p)) {
      if (get_distance_from_leader() < too_far_from_leader(p)) {
        continue;
      }
    }

    if (level->is_obs_wall_or_door(p.x, p.y)) {
      continue;
    }

    auto aip = get_aip();

    //
    // If an unvisited tile is next to a visited one, consider that tile.
    //
    if (! get(aip->can_see_ever.can_see, p.x, p.y)) {
      can_reach_cands.push_back(p);
      continue;
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
      case SEARCH_TYPE_LOCAL_JUMP_ALLOWED : jump_distance = how_far_i_can_jump_max(); break;
      case SEARCH_TYPE_LOCAL_NO_JUMP : jump_distance = 0; break;
      case SEARCH_TYPE_GLOBAL_JUMP_ALLOWED : jump_distance = how_far_i_can_jump_max(); break;
      case SEARCH_TYPE_GLOBAL_NO_JUMP : jump_distance = 0; break;
      case SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED : jump_distance = how_far_i_can_jump_max(); break;
      case SEARCH_TYPE_LAST_RESORTS_NO_JUMP : jump_distance = 0; break;
      default : DIE("unexpected search-type case"); break;
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
          if (search_type < SEARCH_TYPE_LAST_RESORTS_NO_JUMP) {
            continue;
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
          if ((o.x == curr_at.x) && (o.y == curr_at.y)) {
            continue;
          }
          if (search_type < SEARCH_TYPE_LAST_RESORTS_NO_JUMP) {
            continue;
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
          if (search_type < SEARCH_TYPE_LAST_RESORTS_NO_JUMP) {
            continue;
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
          if (search_type < SEARCH_TYPE_LAST_RESORTS_NO_JUMP) {
            continue;
          }
        } else {
          //
          // If lit then we can already see it, so not worth exploring.
          //
          if (get(aip->can_see_ever.can_see, o.x, o.y)) {
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

#if 0
  if (is_debug_type()) {
    con("This is what I am searching (type %d):", search_type);
    for (int y = 0; y < MAP_HEIGHT; y++) {
      std::string s;
      for (int x = 0; x < MAP_WIDTH; x++) {
        if ((x == (int) curr_at.x) && (y == (int) curr_at.y)) {
          if (get(get_aip()->can_see_ever.can_see, x, y)) {
            s += "* ";
          } else {
            s += "o ";
          }
          continue;
        }
        for (auto p : can_reach_cands) {
          if ((x == p.x) && (y == p.y)) {
            s += "c ";
            goto next;
          }
        }
        if (get(walked, x, y)) {
          if (level->is_obs_wall_or_door(x, y)) {
            if (level->is_door(x, y)) {
              s += "D";
            } else {
              s += "X";
            }
          } else {
            s += "_";
          }
        } else {
          if (level->is_obs_wall_or_door(x, y)) {
            if (level->is_door(x, y)) {
              s += "d";
            } else {
              s += "x";
            }
          } else {
            s += " ";
          }
        }
        if (get(get_aip()->can_see_currently.can_see, x, y)) {
          s += ".";
        } else if (get(get_aip()->can_see_ever.can_see, x, y)) {
          s += ",";
        } else {
          s += " ";
        }
      next:
        continue;
      }
      log("%s", s.c_str());
    }
  }
#endif

  //
  // Choose goals (higher scores, lower costs are preferred)
  //
  for (auto i = 0; i < can_reach_cands.size(); i++) {
    auto p = pcg_one_of(can_reach_cands);

    //
    // Avoid sewer descend/ascend loop
    //
    if ((p.x == curr_at.x) && (p.y == curr_at.y)) {
      continue;
    }

    if (too_far_from_mob_spawner(p, 1)) {
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
    int terrain_cost = get_terrain_cost(p);
    int total_score  = -(int) terrain_cost;

    //
    // Prefer newer tiles
    //
    auto age_map = get_age_map();
    total_score -= get(age_map->val, p.x, p.y);

    //
    // Prefer closer
    //
    float dist = distance(start, p);
    total_score -= dist * dist;

    //
    // Choose doors etc... as a last resort when nothing else
    //
    if (is_explorer()) {
      if (level->is_door(p.x, p.y)) {
        total_score -= 100;
      }
    }

    if (is_exit_finder()) {
      if (level->is_descend_sewer(p.x, p.y)) {
        total_score -= 5000;
        //
        // Prefer not to walk over if there is a way around
        //
        terrain_cost += 10;
      }

      if (level->is_ascend_sewer(p.x, p.y)) {
        total_score -= 10000;
        terrain_cost += 10;
      }

      if (level->is_descend_dungeon(p.x, p.y)) {
        total_score -= 50000;
        terrain_cost += 10;
      }

      if (level->is_ascend_dungeon(p.x, p.y)) {
        total_score -= 100000;
        terrain_cost += 10;
      }
    }

    if (is_minion()) {
      auto mob_spawner = get_top_mob_spawner();
      if (mob_spawner) {
        auto dist = distance(p, mob_spawner->curr_at);
        auto msg  = string_sprintf("search cand @(%d,%d) dist-from-owner %f", p.x, p.y, dist);
        GOAL_ADD(GOAL_PRIO_VERY_LOW, total_score, msg.c_str(), nullptr);
      } else {
        auto msg = string_sprintf("search cand @(%d,%d) no-owner", p.x, p.y);
        GOAL_ADD(GOAL_PRIO_VERY_LOW, total_score, msg.c_str(), nullptr);
      }
    } else {
      auto msg = string_sprintf("search cand @(%d,%d)", p.x, p.y);
      GOAL_ADD(GOAL_PRIO_VERY_LOW, total_score, msg.c_str(), nullptr);
    }
  }
}

bool Thing::ai_choose_immediately_adjacent_goal(void)
{
  AI_LOG("Choose immediately adjacent goals");
  TRACE_AND_INDENT();

  bool left;
  bool right;
  bool up;
  bool down;
  bool wait           = false;
  bool jump           = false;
  bool attack         = false;
  bool shove_allowed  = false;
  bool attack_allowed = true;

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
            if (get_keys()) {
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
            left           = dx < 0;
            right          = dx > 0;
            up             = dy < 0;
            down           = dy > 0;
            attack         = true;
            attack_allowed = true;

            AI_LOG("Trying to break down a door", it);
            if (is_player()) {
              player_tick(left, right, up, down, attack, wait, jump);
            } else {
              move(curr_at, up, down, left, right, attack, wait, shove_allowed, attack_allowed);
            }
            return true;
          }
        }

        if (is_able_to_break_out_of_webs()) {
          if (it->is_spiderweb() && (it->curr_at == curr_at)) {
            //
            // Try hitting the web
            //
            left           = dx < 0;
            right          = dx > 0;
            up             = dy < 0;
            down           = dy > 0;
            attack         = true;
            attack_allowed = true;

            AI_LOG("Trying to break out of a web", it);
            if (is_player()) {
              player_tick(left, right, up, down, attack, wait, jump);
            } else {
              move(curr_at, up, down, left, right, attack, wait, shove_allowed, attack_allowed);
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

//
// Return true on having done something
//
bool Thing::ai_tick(bool recursing)
{
  dbg("AI tick");
  TRACE_AND_INDENT();

  auto aip = get_aip();

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

  if (level->ts_fade_in_begin) {
    return false;
  }

  if (level->cursor) {
    level->cursor->hide();
  }

  //
  // Set up the extent of the AI, choosing smaller areas for monsters for
  // speed.
  //
  const float dx = get_distance_vision();
  const float dy = dx;

  auto vision_source = get_vision_source();

  int minx = std::max(0, (int) (vision_source.x - dx));
  int maxx = std::min(MAP_WIDTH - 1, (int) (vision_source.x + dx));
  int miny = std::max(0, (int) (vision_source.y - dy));
  int maxy = std::min(MAP_HEIGHT - 1, (int) (vision_source.y + dy));

  bool left         = false;
  bool right        = false;
  bool up           = false;
  bool down         = false;
  bool attack       = false;
  bool wait         = false;
  bool jump         = false;
  bool do_something = false;

  //
  // See if anything dangerous is close
  //
  auto threat = get_most_dangerous_visible_thing();
  if (threat) {
    AI_LOG("Threat", threat);
  }

  //
  // A threat can be a few tiles away; but if one is standing literally
  // next to us! then it takes priority.
  //
  auto adjacent_threat = get_most_dangerous_adjacent_thing();
  if (adjacent_threat) {
    AI_LOG("Adjacent threat", adjacent_threat);
    if (is_dangerous(adjacent_threat)) {
      threat = adjacent_threat;
    } else {
      AI_LOG("Adjacent threat (not dangerous)", adjacent_threat);
      threat = nullptr;
    }
  }

  //
  // Update what we can see - which if a minion is from the perspective of the mob_spawner.
  //
  auto vision_souce = get_vision_source();

  //
  // We need to grow the light a bit for level explorers
  //
  if (is_explorer()) {
    level->fov_calculete(&aip->can_see_currently, vision_souce.x, vision_souce.y, get_distance_vision() + 1);
  } else {
    level->fov_calculete(&aip->can_see_currently, vision_souce.x, vision_souce.y, get_distance_vision());
  }

  //
  // If we have a treasure map then we know this level
  //
  if (map_treasure_available()) {
    for (int y = miny; y <= maxy; y++) {
      for (int x = minx; x <= maxx; x++) {
        set(aip->can_see_ever.can_see, x, y, true);
      }
    }
  }

  //
  // Anything we can see currently, set into the "have ever seen" array
  //
  for (int y = miny; y <= maxy; y++) {
    for (int x = minx; x <= maxx; x++) {
      if (aip->can_see_currently.can_see[ x ][ y ]) {
        IF_DEBUG3 { (void) level->thing_new("ai_path2", point(x, y)); }
        set(aip->can_see_ever.can_see, x, y, true);
      }
    }
  }

  if (get_infop()->monst_state != MONST_STATE_IDLE) {
    if (! recursing) {
      //
      // Check for serious interrupts
      //
      if (is_on_fire() && environ_avoids_fire()) {
        AI_LOG("I am on fire!");
        return ai_tick(true);
      }

      if (get_terrain_cost(curr_at) >= DMAP_LESS_PREFERRED_TERRAIN) {
        AI_LOG("I am on some bad terrain!");
        return ai_tick(true);
      }

      //
      // Check for less interrupts; like a monster being seen
      //
      AI_LOG("Check for interruptions");
      if (ai_dmap_can_see_init(minx, miny, maxx, maxy, SEARCH_TYPE_CAN_SEE_JUMP_ALLOWED, true)) {
        AI_LOG("Something interrupted me");
        if (is_player()) {
          game->tick_begin("Robot move interrupted by something");
        }

        ai_change_state(MONST_STATE_IDLE, "move interrupted by a change");
        if (is_player()) {
          game->request_remake_actionbar = true;
        }

        //
        // Allow another go; this stops monster's moves stuttering
        //
        return ai_tick(true);
      }
    }
  }

#if 0
  if (is_debug_type()) {
    con("This is my field of view:");
    con("  .  - can see currently");
    con("  ,  - have seen ever");
    for (int y = 0; y < MAP_HEIGHT; y++) {
      for (int x = 0; x < MAP_WIDTH; x++) {
        if ((x == (int) curr_at.x) && (y == (int) curr_at.y)) {
          printf("*");
        } else {
          if (get(aip->can_see_currently.can_see, x, y)) {
            if (level->is_door(x, y)) {
              printf("D");
            } else if (level->is_obs_wall_or_door(x, y)) {
              printf("X");
            } else {
              printf(".");
            }
          } else if (get(aip->can_see_ever.can_see, x, y)) {
            if (level->is_door(x, y)) {
              printf("D");
            } else if (level->is_obs_wall_or_door(x, y)) {
              printf("X");
            } else {
              printf(",");
            }
          } else {
            if (level->is_door(x, y)) {
              printf("d");
            } else if (level->is_obs_wall_or_door(x, y)) {
              printf("x");
            } else {
              printf(" ");
            }
          }
        }
      }
      printf("\n");
    }
  }
#endif
  switch (get_infop()->monst_state) {
    case MONST_STATE_IDLE :
      {
        //
        // If on fire, try and put it out!
        //
        if (is_on_fire() && environ_avoids_fire()) {
          AI_LOG("I am on fire!");
          TRACE_AND_INDENT();
          if (is_intelligent()) {
            if (ai_on_fire()) {
              return true;
            }
          }
        }

        //
        // If somewhere bad, escape
        //
        if (get_terrain_cost(curr_at) >= DMAP_LESS_PREFERRED_TERRAIN) {
          AI_LOG("on bad terrain, escape");
          TRACE_AND_INDENT();
          if (ai_escape()) {
            return true;
          }

          aip->wander_dest = point(0, 0);
          AI_LOG("cannot escape, try to wander");
          TRACE_AND_INDENT();
          if (ai_wander()) {
            return true;
          }
        }

        if (threat) {
          if (is_dangerous(threat)) {
            AI_LOG("A dangerous threat is near", threat);
          } else if (is_enemy(threat)) {
            AI_LOG("An enemy threat is near", threat);
          } else if (is_to_be_avoided(threat)) {
            AI_LOG("An avoid threat is near", threat);
          } else {
            AI_LOG("A threat is near", threat);
          }
        }

        //
        // Look for doors or things to collect, if not being attacked.
        //
        if (threat && (is_dangerous(threat) || is_enemy(threat) || is_to_be_avoided(threat))) {
          //
          // If not too close to the thread we can try and do something else like pick up a weapon.
          //
          if (game->tick_current - get_tick_last_i_was_attacked() < 2) {
            //
            // Don't relax. You're being attacked.
            //
          } else if (distance(curr_at, threat->curr_at) > 2) {
            //
            // Look around for something nearby to do; like collect an item.
            //
            AI_LOG("Look around for some immediately adjacent goal as threat is not too close");
            if (ai_choose_immediately_adjacent_goal()) {
              return true;
            }
          }

          //
          // No resting when in danger unless in dire straits
          //
          // If we're absolutely exhausted, we must rest, threat or no threat
          //
          if (is_able_to_tire() && (get_stamina() < get_stamina_max() / 10)) {
            AI_LOG("Very low on stamina, forced to rest");
            if (is_player()) {
              game->tick_begin("Robot is forced to rest, very low on stamina");
            }
            ai_change_state(MONST_STATE_RESTING, "need to rest, very low on stamina");
            return true;
          }

          //
          // If really low on health and we have something we can eat, try
          // that.
          //
          if (get_health() < get_health_max() / 10) {
            if (can_eat_something()) {
              AI_LOG("Very low on health, forced to rest");
              if (is_player()) {
                game->tick_begin("Robot needs to rest, very low on health");
              }
              ai_change_state(MONST_STATE_RESTING, "need to rest, very low on health");
              return true;
            }
          }
        } else {
          //
          // Not under threat, so we can think about doing some other house cleaning tasks.
          //
          AI_LOG("Idle, look for something to do");

          //
          // If we're absolutely exhausted, we must rest, threat or no threat
          //
          AI_LOG("Idle, rest check");
          if (is_able_to_tire() && (get_stamina() < get_stamina_max() / 3)) {
            AI_LOG("Low on stamina, rest");
            if (is_player()) {
              game->tick_begin("Robot is low on stamina");
            }
            ai_change_state(MONST_STATE_RESTING, "need to rest, low on stamina");
            return true;
          }

          //
          // If really low on health and we have something we can eat, try
          // that.
          //
          AI_LOG("Idle, health check");
          if (get_health() < get_health_max() / 3) {
            AI_LOG("Idle, eat check as a bit hungry");
            if (can_eat_something()) {
              AI_LOG("Low on health, rest");
              if (is_player()) {
                game->tick_begin("Robot is low on health");
              }
              ai_change_state(MONST_STATE_RESTING, "need to rest, low on health");
              return true;
            }
          }

          //
          // Be a bit more careful if there is somethjing that might want to
          // attack us, even if it is not a threat. i.e. a harmless goblin
          // could push us off of a cliff while we're doing other stuff.
          //
          if (is_able_to_enchant_items() || is_able_to_learn_skills()) {
            AI_LOG("Idle, unfriendly monst check");
            if (! any_unfriendly_monst_visible()) {
              //
              // Can we enchant something?
              //
              AI_LOG("Idle, enchant check");
              if (is_able_to_enchant_items()) {
                if (get_enchantstone_count() && can_enchant_something()) {
                  AI_LOG("Try to enchant something");
                  if (is_player()) {
                    game->tick_begin("Robot can enchant something");
                  }
                  ai_change_state(MONST_STATE_USING_ENCHANTSTONE, "can enchant something");
                  return true;
                }
              }

              //
              // Can we learn some skills?
              //
              AI_LOG("Idle, enchant check");
              if (is_able_to_learn_skills()) {
                if (get_skillstone_count() && can_learn_something()) {
                  AI_LOG("Try to use a skillstone");
                  if (is_player()) {
                    game->tick_begin("Robot can learn something");
                  }
                  ai_change_state(MONST_STATE_USING_SKILLSTONE, "can learn something");
                  return true;
                }
              }
            } else {
              AI_LOG("Idle, unfriendlies are near");
            }
          }

          //
          // Can we switch to a better weapon? Only if we can use weapons. We don't
          // wand jellys wandering around with swords!
          //
          if (is_able_to_use_weapons()) {
            AI_LOG("Idle, weapon check");
            Thingp curr_weapon = get_equip(MONST_EQUIP_WEAPON);
            Thingp best_weapon = nullptr;
            get_carried_weapon_highest_value(&best_weapon);
            if (best_weapon) {
              auto curr_weapon_val = curr_weapon ? get_value(curr_weapon) : 0;
              auto best_weapon_val = get_value(best_weapon);

              if (! curr_weapon) {
                if (use(best_weapon, MONST_EQUIP_WEAPON)) {
                  AI_LOG("Change weapon", best_weapon);
                  if (is_player()) {
                    game->tick_begin("Robot, has equipped weapon");
                  }
                  return true;
                }
              } else if (best_weapon_val > curr_weapon_val) {
                if (use(best_weapon, MONST_EQUIP_WEAPON)) {
                  AI_LOG("Change weapon", best_weapon);
                  if (is_player()) {
                    game->tick_begin("Robot, has changed weapon");
                  }
                  return true;
                }
              }
            }
          }

          if (is_able_to_use_armor()) {
            AI_LOG("Idle, armor check");
            Thingp curr_armor = get_equip(MONST_EQUIP_ARMOR);
            Thingp best_armor = nullptr;
            get_carried_armor_highest_value(&best_armor);
            if (best_armor) {
              auto curr_armor_val = curr_armor ? get_value(curr_armor) : 0;
              auto best_armor_val = get_value(best_armor);

              if (! curr_armor) {
                if (use(best_armor, MONST_EQUIP_ARMOR)) {
                  AI_LOG("Change armor", best_armor);
                  if (is_player()) {
                    game->tick_begin("Robot, has equipped armor");
                  }
                  return true;
                }
              } else if (best_armor_val > curr_armor_val) {
                if (use(best_armor, MONST_EQUIP_ARMOR)) {
                  AI_LOG("Change armor", best_armor);
                  if (is_player()) {
                    game->tick_begin("Robot, has changed armor");
                  }
                  return true;
                }
              }
            }
          }

          if (is_able_to_use_helmet()) {
            AI_LOG("Idle, helmet check");
            Thingp curr_helmet = get_equip(MONST_EQUIP_HELMET);
            Thingp best_helmet = nullptr;
            get_carried_helmet_highest_value(&best_helmet);
            if (best_helmet) {
              auto curr_helmet_val = curr_helmet ? get_value(curr_helmet) : 0;
              auto best_helmet_val = get_value(best_helmet);

              if (! curr_helmet) {
                if (use(best_helmet, MONST_EQUIP_HELMET)) {
                  AI_LOG("Change helmet", best_helmet);
                  if (is_player()) {
                    game->tick_begin("Robot, has equipped helmet");
                  }
                  return true;
                }
              } else if (best_helmet_val > curr_helmet_val) {
                if (use(best_helmet, MONST_EQUIP_HELMET)) {
                  AI_LOG("Change helmet", best_helmet);
                  if (is_player()) {
                    game->tick_begin("Robot, has changed helmet");
                  }
                  return true;
                }
              }
            }
          }

          if (is_able_to_use_amulet()) {
            AI_LOG("Idle, amulet check");
            Thingp curr_amulet = get_equip(MONST_EQUIP_AMULET);
            Thingp best_amulet = nullptr;
            get_carried_amulet_highest_value(&best_amulet);
            if (best_amulet) {
              auto curr_amulet_val = curr_amulet ? get_value(curr_amulet) : 0;
              auto best_amulet_val = get_value(best_amulet);

              if (! curr_amulet) {
                if (use(best_amulet, MONST_EQUIP_AMULET)) {
                  AI_LOG("Change amulet", best_amulet);
                  if (is_player()) {
                    game->tick_begin("Robot, has equipped amulet");
                  }
                  return true;
                }
              } else if (best_amulet_val > curr_amulet_val) {
                if (use(best_amulet, MONST_EQUIP_AMULET)) {
                  AI_LOG("Change amulet", best_amulet);
                  if (is_player()) {
                    game->tick_begin("Robot, has changed amulet");
                  }
                  return true;
                }
              }
            }
          }

          if (is_able_to_use_boots()) {
            AI_LOG("Idle, boots check");
            Thingp curr_boots = get_equip(MONST_EQUIP_BOOTS);
            Thingp best_boots = nullptr;
            get_carried_boots_highest_value(&best_boots);
            if (best_boots) {
              auto curr_boots_val = curr_boots ? get_value(curr_boots) : 0;
              auto best_boots_val = get_value(best_boots);

              if (! curr_boots) {
                if (use(best_boots, MONST_EQUIP_BOOTS)) {
                  AI_LOG("Change boots", best_boots);
                  if (is_player()) {
                    game->tick_begin("Robot, has equipped boots");
                  }
                  return true;
                }
              } else if (best_boots_val > curr_boots_val) {
                if (use(best_boots, MONST_EQUIP_BOOTS)) {
                  AI_LOG("Change boots", best_boots);
                  if (is_player()) {
                    game->tick_begin("Robot, has changed boots");
                  }
                  return true;
                }
              }
            }
          }

          if (is_able_to_use_gauntlet()) {
            AI_LOG("Idle, gauntlet check");
            Thingp curr_gauntlet = get_equip(MONST_EQUIP_GAUNTLET);
            Thingp best_gauntlet = nullptr;
            get_carried_gauntlet_highest_value(&best_gauntlet);
            if (best_gauntlet) {
              auto curr_gauntlet_val = curr_gauntlet ? get_value(curr_gauntlet) : 0;
              auto best_gauntlet_val = get_value(best_gauntlet);

              if (! curr_gauntlet) {
                if (use(best_gauntlet, MONST_EQUIP_GAUNTLET)) {
                  AI_LOG("Change gauntlet", best_gauntlet);
                  if (is_player()) {
                    game->tick_begin("Robot, has equipped gauntlet");
                  }
                  return true;
                }
              } else if (best_gauntlet_val > curr_gauntlet_val) {
                if (use(best_gauntlet, MONST_EQUIP_GAUNTLET)) {
                  AI_LOG("Change gauntlet", best_gauntlet);
                  if (is_player()) {
                    game->tick_begin("Robot, has changed gauntlet");
                  }
                  return true;
                }
              }
            }
          }

          if (is_able_to_use_shield()) {
            AI_LOG("Idle, shield check");
            Thingp curr_shield = get_equip(MONST_EQUIP_SHIELD);
            Thingp best_shield = nullptr;
            get_carried_shield_highest_value(&best_shield);
            if (best_shield) {
              auto curr_shield_val = curr_shield ? get_value(curr_shield) : 0;
              auto best_shield_val = get_value(best_shield);

              if (! curr_shield) {
                if (use(best_shield, MONST_EQUIP_SHIELD)) {
                  AI_LOG("Change shield", best_shield);
                  if (is_player()) {
                    game->tick_begin("Robot, has equipped shield");
                  }
                  return true;
                }
              } else if (best_shield_val > curr_shield_val) {
                if (use(best_shield, MONST_EQUIP_SHIELD)) {
                  AI_LOG("Change shield", best_shield);
                  if (is_player()) {
                    game->tick_begin("Robot, has changed shield");
                  }
                  return true;
                }
              }
            }
          }

          if (is_able_to_use_cloak()) {
            AI_LOG("Idle, cloak check");
            Thingp curr_cloak = get_equip(MONST_EQUIP_CLOAK);
            Thingp best_cloak = nullptr;
            get_carried_cloak_highest_value(&best_cloak);
            if (best_cloak) {
              auto curr_cloak_val = curr_cloak ? get_value(curr_cloak) : 0;
              auto best_cloak_val = get_value(best_cloak);

              if (! curr_cloak) {
                if (use(best_cloak, MONST_EQUIP_CLOAK)) {
                  AI_LOG("Change cloak", best_cloak);
                  if (is_player()) {
                    game->tick_begin("Robot, has equipped cloak");
                  }
                  return true;
                }
              } else if (best_cloak_val > curr_cloak_val) {
                if (use(best_cloak, MONST_EQUIP_CLOAK)) {
                  AI_LOG("Change cloak", best_cloak);
                  if (is_player()) {
                    game->tick_begin("Robot, has changed cloak");
                  }
                  return true;
                }
              }
            }
          }

          if (is_able_to_use_rings()) {
            AI_LOG("Idle, ring check");
            //
            // Can we switch to a better ring?
            //
            Thingp curr_ring1 = get_equip(MONST_EQUIP_RING1);
            Thingp curr_ring2 = get_equip(MONST_EQUIP_RING2);
            Thingp best_ring  = nullptr;
            get_carried_ring_highest_value(&best_ring);
            if (best_ring) {
              auto curr_ring1_val = curr_ring1 ? get_value(curr_ring1) : 0;
              auto curr_ring2_val = curr_ring2 ? get_value(curr_ring2) : 0;
              auto best_ring_val  = get_value(best_ring);

              if (! curr_ring1) {
                if (use(best_ring, MONST_EQUIP_RING1)) {
                  AI_LOG("Change ring", best_ring);
                  if (is_player()) {
                    game->tick_begin("Robot, has equipped ring1");
                  }
                  return true;
                }
              } else if (! curr_ring2) {
                if (use(best_ring, MONST_EQUIP_RING2)) {
                  AI_LOG("Change ring", best_ring);
                  if (is_player()) {
                    game->tick_begin("Robot, has equipped ring2");
                  }
                  return true;
                }
              } else if (best_ring_val > curr_ring1_val) {
                if (use(best_ring, MONST_EQUIP_RING1)) {
                  AI_LOG("Change ring", best_ring);
                  if (is_player()) {
                    game->tick_begin("Robot, has changed ring1");
                  }
                  return true;
                }
              } else if (best_ring_val > curr_ring2_val) {
                if (use(best_ring, MONST_EQUIP_RING2)) {
                  AI_LOG("Change ring", best_ring);
                  if (is_player()) {
                    game->tick_begin("Robot, has changed ring2");
                  }
                  return true;
                }
              }
            }
          }

          //
          // Look around for something nearby to do; like collect an item.
          //
          AI_LOG("Look around for some immediately adjacent goal");
          if (ai_choose_immediately_adjacent_goal()) {
            return true;
          }
        }

        //
        // Look for goals. Each search type expands the scope of what we look at
        // until at the end, we end up looking for the exit.
        //
        AI_LOG("Idle, look for goals");
        int search_type_max;
        if (is_able_to_jump()) {
          if (is_explorer()) {
            if (is_exit_finder()) {
              search_type_max = SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED + 1;
            } else {
              search_type_max = SEARCH_TYPE_GLOBAL_JUMP_ALLOWED + 1;
            }
          } else {
            search_type_max = SEARCH_TYPE_LOCAL_JUMP_ALLOWED + 1;
          }
        } else {
          if (is_explorer()) {
            if (is_exit_finder()) {
              search_type_max = SEARCH_TYPE_LAST_RESORTS_NO_JUMP + 1;
            } else {
              search_type_max = SEARCH_TYPE_GLOBAL_NO_JUMP + 1;
            }
          } else {
            search_type_max = SEARCH_TYPE_LOCAL_NO_JUMP + 1;
          }
        }

        for (int search_type = 0; search_type < search_type_max; search_type++) {
          if (ai_create_path_to_goal(minx, miny, maxx, maxy, search_type)) {
            if (aip->move_path.size()) {
              ai_change_state(MONST_STATE_MOVING, "found a new goal");
            }
            return true;
          }
        }

        //
        // If going somewhere, continue
        //
        if (aip->wander_dest != point(0, 0)) {
          if (pcg_random_range(0, 100) < 50) {
            dbg("Try to continue wander");
            if (ai_wander()) {
              return true;
            }
          }
        }

        //
        // If nothing to do, might as well rest. If there is a point.
        //
        auto rest = true;
        if ((get_health() >= (get_health_max() / 4) * 3)) {
          if (is_able_to_tire()) {
            if (get_stamina() >= (get_stamina_max() / 4) * 3) {
              rest = false;
            }
          } else {
            rest = false;
          }
        }

        if (rest) {
          AI_LOG("Nothing to do. Rest.");
          if (is_player()) {
            game->tick_begin("nothing to do, rest");
          }
          ai_change_state(MONST_STATE_RESTING, "nothing to do, rest");
          return true;
        }

        //
        // Compress the bag?
        //
        if (is_player()) {
          if (bag_compress()) {
            while (bag_compress()) {
            }
            AI_LOG("Repack inventory.");
            if (is_player()) {
              game->tick_begin("repacked bag");
              return true;
            }
          }
        }

        //
        // What is the point of it all?
        //
        AI_LOG("Nothing to do at all.");
        if (is_player()) {
          msg("Robot has ran out of things to do.");
          wid_actionbar_robot_mode_off();
        }

        return ai_wander();
      }
      break;

    case MONST_STATE_MOVING :
      {
        //
        // Finished the move?
        //
        if (aip->move_path.empty()) {
          AI_LOG("Move finished.");
          if (is_player()) {
            game->tick_begin("Robot move finished");
          }
          ai_change_state(MONST_STATE_IDLE, "move finished");
          if (is_player()) {
            game->request_remake_actionbar = true;
          }
          return true;
        }

        //
        // Keep on moving.
        //
        AI_LOG("Keep on moving");
        if (is_player()) {
          game->tick_begin("Robot move");
        }
        path_pop_next_move();
        return true;
      }
      break;
    case MONST_STATE_RESTING :
      {
        //
        // If attacked, we should be kicked out of resting
        //
        // If resting, check if we are rested enough.
        //
        if ((get_health() >= (get_health_max() / 4) * 3) && (get_stamina() >= (get_stamina_max() / 4) * 3)) {
          AI_LOG("Rested enough. Back to work.");
          if (is_player()) {
            game->tick_begin("Robot has rested enough");
          }
          ai_change_state(MONST_STATE_IDLE, "rested enough");
          get_infop()->last_failed_jump_at = point(0, 0);
          return true;
        }

        //
        // Check for food first, before abandoning resting
        //
        if (eat_something()) {
          AI_LOG("Ate an item.");
          if (is_player()) {
            game->tick_begin("Robot ate an item");
          }
          ai_change_state(MONST_STATE_OPEN_INVENTORY, "eat something");
          return true;
        }

        AI_LOG("Wait and rest.");
        do_something = true;
        wait         = true;
        break;
      }
      break;

    case MONST_STATE_OPEN_INVENTORY :
      {
        //
        // Wait for the inventory to be remade
        //
        if (is_player()) {
          if (game->request_remake_rightbar) {
            return true;
          }
        }

        //
        // Then close it. This is really just visual feedback.
        //
        if (is_player()) {
          ai_change_state(MONST_STATE_REPACK_INVENTORY, "repack inventory");
          game->tick_begin("Robot finished collecting");
        } else {
          ai_change_state(MONST_STATE_IDLE, "close inventory");
        }
      }
      break;

    case MONST_STATE_USING_ENCHANTSTONE :
      {
        //
        // Enchant a random item.
        //
        enchant_random_item_with_stone();
        if (is_player()) {
          ai_change_state(MONST_STATE_REPACK_INVENTORY, "enchanted");
          game->tick_begin("Robot finished enchanting");
        } else {
          ai_change_state(MONST_STATE_IDLE, "enchanted");
        }
      }
      break;

    case MONST_STATE_USING_SKILLSTONE :
      {
        //
        // Choose a skill
        //
        learn_random_skill();
        if (is_player()) {
          ai_change_state(MONST_STATE_REPACK_INVENTORY, "added skill");
          game->tick_begin("Robot finished adding skills");
        } else {
          ai_change_state(MONST_STATE_IDLE, "added skill");
        }
      }
      break;

    case MONST_STATE_REPACK_INVENTORY :
      {
        //
        // Compress the bag?
        //
        if (bag_compress()) {
          while (bag_compress()) {
          }
          AI_LOG("Repacked inventory.");
        }
        if (is_player()) {
          game->tick_begin("repacked bag");
        }

        //
        // Need to go back to reseting, as this resets failed jumps once fully rested
        // and we may have came here due to eating food when resting.
        //
        ai_change_state(MONST_STATE_RESTING, "finished repacking");
        return true;
      }
      break;
  }

  if (do_something) {
    if (is_player()) {
      player_tick(left, right, up, down, attack, wait, jump);
    } else {
      move(curr_at, up, down, left, right, attack, wait, false, false);
    }
  }

  return true;
}

void Thing::ai_change_state(int new_state, const std::string &why)
{
  TRACE_NO_INDENT();

  if (get_infop()->monst_state == new_state) {
    return;
  }

  dbg("AI change state: %s", why.c_str());
  TRACE_AND_INDENT();

  std::string to;
  std::string from;
  switch (new_state) {
    case MONST_STATE_IDLE : to = "IDLE"; break;
    case MONST_STATE_MOVING : to = "MOVING"; break;
    case MONST_STATE_RESTING : to = "RESTING"; break;
    case MONST_STATE_OPEN_INVENTORY : to = "OPEN-INVENTORY"; break;
    case MONST_STATE_USING_ENCHANTSTONE : to = "USING-ENCHANTSTONE"; break;
    case MONST_STATE_USING_SKILLSTONE : to = "USING-SKILLSTONE"; break;
    case MONST_STATE_REPACK_INVENTORY : to = "REPACK"; break;
  }

  if (is_player()) {
    wid_inventory_fini();
  }

  //
  // Current state
  //
  switch (get_infop()->monst_state) {
    case MONST_STATE_IDLE : from = "IDLE"; break;
    case MONST_STATE_MOVING : from = "MOVING"; break;
    case MONST_STATE_RESTING : from = "RESTING"; break;
    case MONST_STATE_REPACK_INVENTORY : from = "REPACK"; break;
    case MONST_STATE_OPEN_INVENTORY : from = "OPEN-INVENTORY"; break;
    case MONST_STATE_USING_ENCHANTSTONE :
      from = "USING-ENCHANTSTONE";
      if (is_player()) {
        wid_enchant_destroy();
      }
      break;
    case MONST_STATE_USING_SKILLSTONE :
      from = "USING-SKILLSTONE";
      if (is_player()) {
        wid_skill_choose_destroy();
      }
      break;
  }

  IF_DEBUG
  {
    auto s = string_sprintf("State change %s -> %s, reason: %s", from.c_str(), to.c_str(), why.c_str());
    AI_LOG(s);
  }

  get_infop()->monst_state = new_state;
  switch (new_state) {
    case MONST_STATE_IDLE : clear_move_path("State is now idle"); break;
    case MONST_STATE_MOVING : break;
    case MONST_STATE_RESTING : break;
    case MONST_STATE_REPACK_INVENTORY : break;
    case MONST_STATE_OPEN_INVENTORY :
      if (is_player()) {
        wid_inventory_init();
        game->request_remake_rightbar = true;
      }
      break;
    case MONST_STATE_USING_ENCHANTSTONE :
      if (is_player()) {
        game->wid_enchant_an_item();
      }
      break;
    case MONST_STATE_USING_SKILLSTONE :
      if (is_player()) {
        game->wid_skill_choose();
      }
      break;
  }
}

void Thing::ai_get_next_hop(void)
{
  TRACE_NO_INDENT();

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

  auto d = get_distance_vision();
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
      if (dist < get_distance_avoid()) {
        continue;
      }

      if (ai_obstacle_for_me(p)) {
        continue;
      }

      int terrain_cost = get_terrain_cost(p);
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
      int   terrain_cost = get_terrain_cost(p);
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
      int   terrain_cost = get_terrain_cost(p);
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
