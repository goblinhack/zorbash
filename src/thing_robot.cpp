//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include <algorithm>
#include <set>
#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_dmap.h"
#include "my_math.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_thing_ai.h"
#include "my_array_bounds_check.h"
#include "my_vector_bounds_check.h"
#include "my_globals.h"
#include "my_ptrcheck.h"
#include "my_monst.h"
#include "my_wid_popup.h"
#include "my_wid_thing_info.h"
#include "my_wid_inventory.h"
#include "my_wid_actionbar.h"
#include "my_player.h"

//
// Search priorities in order
//
#define SEARCH_TYPE_MAX                       6
#define SEARCH_TYPE_LOCAL_NO_JUMP             0
#define SEARCH_TYPE_LOCAL_JUMP_ALLOWED        1
#define SEARCH_TYPE_GLOBAL_NO_JUMP            2
#define SEARCH_TYPE_GLOBAL_JUMP_ALLOWED       3
#define SEARCH_TYPE_LAST_RESORTS_NO_JUMP      4
#define SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED 5

#define SCORE_ADD(score, msg)                         \
    total_score += (score);                           \
    got_a_goal = true;                                \
    if (last_msg.empty()) {                           \
      last_msg = msg;                                 \
    } else {                                          \
      last_msg += ", ";                               \
      last_msg += msg;                                \
    }                                                 \
    dbg("Add sub-goal score %d @(%d,%d) %s, %s",      \
      score, p.x, p.y, msg, it->to_string().c_str()); \

//
// Look at all the things that are currently visited (read that as light rays
// have touched them) and choose the best goal. Create a path to that goal for
// the thing to walk.
//
bool Thing::robot_ai_create_path_to_goal (int minx, int miny,
                                          int maxx, int maxy,
                                          int search_type)
{_
  point start((int)mid_at.x, (int)mid_at.y);

  dbg("Choose goal");
_
  //
  // Find all the possible goals. Higher scores, lower costs are preferred
  //
  auto dmap_can_see = get_dmap_can_see();
  auto age_map = get_age_map();

  //
  // Initialize basic visibility and things that are lit and can be seen
  //
  dbg("Choose goals (higher scores, lower costs are preferred):");

  std::multiset<Goal> goals;
  std::list<GoalMap> goalmaps;
  robot_ai_init_can_see_dmap(minx, miny, maxx, maxy, search_type);

  switch (search_type) {
    case SEARCH_TYPE_LOCAL_JUMP_ALLOWED:
    case SEARCH_TYPE_LOCAL_NO_JUMP:
      robot_ai_choose_initial_goals(goals, minx, miny, maxx, maxy);
      goalmaps.push_back(GoalMap{goals, dmap_can_see});
      break;
    case SEARCH_TYPE_GLOBAL_JUMP_ALLOWED:
    case SEARCH_TYPE_GLOBAL_NO_JUMP:
      robot_ai_choose_search_goals(goals, search_type);
      goalmaps.push_back(GoalMap{goals, dmap_can_see});
      break;
    case SEARCH_TYPE_LAST_RESORTS_NO_JUMP:
    case SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED:
      robot_ai_choose_search_goals(goals, search_type);
      goalmaps.push_back(GoalMap{goals, dmap_can_see});
      break;
  }

  //
  // No goals?
  //
  if (goalmaps.empty()) {
    if (is_player()) {
      CON("Robot: @(%s, %d,%d %d/%dh) No goals found",
        level->to_string().c_str(),
        (int)mid_at.x, (int)mid_at.y,get_health(), get_health_max());
    }
    return false;
  }

  for (auto &g : goalmaps) {
    //
    // Find the highest/least preferred score so we can scale all the goals
    // later so they fit in one byte (makes it easier to debug).
    //
    std::array<std::array<float, MAP_HEIGHT>, MAP_WIDTH> cell_totals = {};
    float least_preferred = 0;
    float most_preferred = 0;
    bool least_preferred_set = false;
    bool most_preferred_set = false;

    for (int y = miny; y < maxy; y++) {
      for (int x = minx; x < maxx; x++) {
        point p(x, y);
        auto c = getptr(g.dmap->val, x, y);
        if ((*c < DMAP_IS_PASSABLE) && (*c > DMAP_IS_GOAL)) {
          dmap_modify_terrain_cost(p, c);
        }
      }
    }

    for (auto& goal : g.goals) {
      auto goal_target = goal.at;
      incr(cell_totals, goal_target.x, goal_target.y, goal.score);
      auto score = get(cell_totals, goal_target.x, goal_target.y);

      if (least_preferred_set) {
        least_preferred = std::min(least_preferred, score);
      } else {
        least_preferred = score;
        least_preferred_set = true;
      }
      if (most_preferred_set) {
        most_preferred = std::max(most_preferred, score);
      } else {
        most_preferred = score;
        most_preferred_set = true;
      }
    }

    dbg2("Sorted goals, %d (best) .. %d (worst)",
      (int)most_preferred, (int)least_preferred);

    //
    // Scale the goals so they will fit in the dmap.
    //
    for (auto& goal : g.goals) {
      auto goal_target = goal.at;
      float score = get(cell_totals, goal_target.x, goal_target.y);
      auto orig_score = score;

      if (most_preferred == least_preferred) {
        score = 1;
      } else {
        if (least_preferred < 0) {
          score /= most_preferred - least_preferred;
        } else {
          score /= most_preferred;
        }
        score *= DMAP_LESS_PREFERRED_TERRAIN - 2;
        score++;
      }

      assert(score <= DMAP_LESS_PREFERRED_TERRAIN);
      uint8_t score8 = DMAP_LESS_PREFERRED_TERRAIN - (int)score;
      set(g.dmap->val, goal_target.x, goal_target.y, score8);

      dbg("Scale goal (score %d -> %d) @(%d,%d) %s",
        (int)orig_score, (int)score8,
        goal.at.x, goal.at.y, goal.msg.c_str());
    }

    //
    // Record we've been here.
    //
    set(age_map->val, start.x, start.y, game->tick_current);

    //
    // Find the best next-hop to the best goal.
    //
#ifdef ENABLE_DEBUG_AI_VERBOSE
    IF_DEBUG4 {
      dbg("Goals:");
      dmap_print(g.dmap,
             point(min.x, min.y),
             point(start.x, start.y),
             point(max.x, max.y));
    }
#endif

    //
    // Make sure we do not want to stay in the same position by making
    // our current cell passable but the very least preferred it can be.
    //
    if (get(g.dmap->val, start.x, start.y) > 0) {
      set(g.dmap->val, start.x, start.y, DMAP_IS_PASSABLE);
    }

    //
    // Move diagonally if not blocked by walls
    //
    point astar_start(start.x, start.y);

    //
    // Modify the given goals with scores that indicate the cost of the
    // path to that goal. The result should be a sorted set of goals.
    //
    std::multiset<Path> paths;
    char path_debug = '\0'; // astart path debug

    for (auto& goal : g.goals) {
#ifdef ENABLE_DEBUG_AI_ASTAR
      astar_debug = {};
#endif
      auto astar_end = goal.at;
      auto result = astar_solve(&goal,
                    path_debug,
                    astar_start,
                    astar_end,
                    g.dmap);
      //
      // Unreachable?
      //
      if (result.cost == std::numeric_limits<int>::max()) {
        dbg("Unreachable goal score %d @(%d,%d) %s",
          (int)goal.score,
          goal.at.x, goal.at.y, goal.msg.c_str());
#ifdef ENABLE_DEBUG_AI_ASTAR
        auto start = point(minx, miny);
        auto end = point(maxx, maxy);
        astar_dump(g.dmap, goal.at, start, end);
#endif
        continue;
      }

      paths.insert(result);
      dbg("Reachable goal (score %d -> cost %d) @(%d,%d) %s",
        (int)goal.score, (int)result.cost,
        goal.at.x, goal.at.y, goal.msg.c_str());

#ifdef ENABLE_DEBUG_AI_ASTAR
      for (auto& p : result.path) {
        set(astar_debug, p.x, p.y, '*');
      }
      auto start = point(minx, miny);
      auto end = point(maxx, maxy);
      astar_dump(g.dmap, goal.at, start, end);
#endif
    }

    for (auto& result : paths) {
      std::vector<point> new_move_path;

      for (point p : result.path) {
        if ((p.x == mid_at.x) && (p.y == mid_at.y)) {
          continue;
        }
        new_move_path.push_back(p);
      }

      if (new_move_path.empty()) {
        if (level->is_sticky(mid_at.x, mid_at.y)) {
          BOTCON("Robot is stuck");
          CON("Robot: @(%s, %d,%d %d/%dh) Try to break free from the sticky stuff",
            level->to_string().c_str(),
            (int)mid_at.x, (int)mid_at.y,get_health(), get_health_max());
          game->tick_begin("Try to break free");
          return true;
        }
        continue;
      }

      std::reverse(new_move_path.begin(), new_move_path.end());

      auto p = new_move_path[new_move_path.size() - 1];

      std::string goal_path_str = "";
      for (auto p1 : new_move_path) {
        goal_path_str += p1.to_string() + " ";
      }

      bool logged_one = false;
      FOR_ALL_THINGS_THAT_INTERACT(level, it, p.x, p.y) {
        if (it->is_changing_level ||
            it->is_hidden ||
            it->is_falling ||
            it->is_jumping) {
          continue;
        }

        if (it == this) { continue; }

        if (it->get_immediate_spawned_owner_id().ok()) {
          continue;
        }

        logged_one = true;

        if (is_player()) {
          CON("Robot: @(%s, %d,%d %d/%dh) Found a goal: %s %s, via %sscore %d",
            level->to_string().c_str(),
            (int)mid_at.x, (int)mid_at.y, get_health(), get_health_max(),
            it->to_string().c_str(), result.goal.msg.c_str(),
            goal_path_str.c_str(),
            (int)result.goal.score);
          BOTCON("Robot: goal %s %s", result.goal.msg.c_str(), it->text_the().c_str());
        } else {
          log("Monst: Found a goal: %s %s, via %sscore %d",
            it->to_string().c_str(), result.goal.msg.c_str(),
            goal_path_str.c_str(),
            (int)result.goal.score);
        }
      } FOR_ALL_THINGS_END();

      if (!logged_one) {
        FOR_ALL_THINGS(level, it, p.x, p.y) {

          if (it->is_changing_level ||
              it->is_hidden ||
              it->is_the_grid ||
              it->is_tmp_thing() ||
              it->is_falling ||
              it->is_jumping) {
            continue;
          }

          if (it == this) { continue; }

          if (it->get_immediate_spawned_owner_id().ok()) {
            continue;
          }

          logged_one = true;

          if (is_player()) {
            CON("Robot: @(%s, %d,%d %d/%dh) Found a non active-thing goal: %s %s, via %sscore %d",
              level->to_string().c_str(),
              (int)mid_at.x, (int)mid_at.y, get_health(), get_health_max(),
              it->to_string().c_str(), result.goal.msg.c_str(),
              goal_path_str.c_str(),
              (int)result.goal.score);
            BOTCON("Robot: goal %s %s", result.goal.msg.c_str(), it->text_the().c_str());
          } else {
            log("Monst: Found a non active-thing goal: %s %s, via %sscore %d",
              it->to_string().c_str(), result.goal.msg.c_str(),
              goal_path_str.c_str(),
              (int)result.goal.score);
          }
        } FOR_ALL_THINGS_END();
      }

      if (!logged_one) {
        if (is_player()) {
          CON("Robot: @(%s, %d,%d %d/%dh) Found a non thing goal: %s, via %sscore %d",
            level->to_string().c_str(),
            (int)mid_at.x, (int)mid_at.y, get_health(), get_health_max(),
            result.goal.msg.c_str(),
            goal_path_str.c_str(),
            (int)result.goal.score);
          BOTCON("Robot: goal %s", result.goal.msg.c_str());
        } else {
          log("Monst: Found a non thing goal: %s, via %sscore %d",
            result.goal.msg.c_str(),
            goal_path_str.c_str(),
            (int)result.goal.score);
        }
      }

      if (is_player()) {
        level->cursor_path_create(new_move_path);
        level->debug_path_create(new_move_path);

        //
        // Try to move. It might not work and we end up attacking.
        //
        if (cursor_path_pop_first_move()) {
          return true;
        }

        //
        // Did we try or attempt to try to do something?
        //
        if (!game->tick_requested.empty()) {
          return true;
        }
      } else {
        monstp->move_path = new_move_path;
        return true;
      }

      if (is_player()) {
        log("Robot: Failed to move to goal");
      }
    }
  }

  return false;
}

//
// Initialize basic visibility and things that are lit and can be seen
//
int Thing::robot_ai_init_can_see_dmap (int minx, int miny, int maxx, int maxy,
                                       int search_type)
{_
  std::array< std::array<uint8_t, MAP_WIDTH>, MAP_HEIGHT> can_jump = {};
  point start((int)mid_at.x, (int)mid_at.y);
  auto dmap_can_see = get_dmap_can_see();
  auto seen_map = get_seen_map();
  point at = make_point(mid_at);
  bool jump_allowed = false;
  int something_changed = 0;

  switch (search_type) {
    case SEARCH_TYPE_LOCAL_JUMP_ALLOWED:
      jump_allowed = true;
      break;
    case SEARCH_TYPE_LOCAL_NO_JUMP:
      jump_allowed = false;
      break;
    case SEARCH_TYPE_GLOBAL_JUMP_ALLOWED:
      jump_allowed = true;
      break;
    case SEARCH_TYPE_GLOBAL_NO_JUMP:
      jump_allowed = false;
      break;
    case SEARCH_TYPE_LAST_RESORTS_NO_JUMP:
      jump_allowed = false;
      break;
    case SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED:
      jump_allowed = true;
      break;
  }

  for (int y = miny; y < maxy; y++) {
    for (int x = minx; x < maxx; x++) {
      point p(x, y);
      if (is_player()) {
        if (!level->is_lit_ever(p)) {
          set(dmap_can_see->val, x, y, DMAP_IS_WALL);
          continue;
        }
      }

      //
      // Don't block on things like chasms so we can jump
      //
      if (is_jumper()) {
        if (!ai_obstacle_for_me(p)) {
          set(dmap_can_see->val, x, y, DMAP_IS_PASSABLE);
          continue;
        }
      } else {
        if (ai_obstacle_for_me(p)) {
          set(dmap_can_see->val, x, y, DMAP_IS_WALL);
          continue;
        }
      }

      if (level->is_obs_wall_or_door(p)) {
        set(dmap_can_see->val, x, y, DMAP_IS_WALL);
        continue;
      }

      if (level->is_secret_door(p)) {
        auto dist = distance(p, at);
        if (dist > ROBOT_CAN_SEE_SECRET_DOOR_DISTANCE) {
          set(dmap_can_see->val, x, y, DMAP_IS_WALL);
          continue;
        }
      }

      switch (search_type) {
        case SEARCH_TYPE_LOCAL_NO_JUMP:
        case SEARCH_TYPE_GLOBAL_NO_JUMP:
        case SEARCH_TYPE_LAST_RESORTS_NO_JUMP:
          if (level->is_lava(p) ||
            level->is_chasm(p)) {
            set(dmap_can_see->val, x, y, DMAP_IS_WALL);
            continue;
          }
          break;
        case SEARCH_TYPE_GLOBAL_JUMP_ALLOWED:
        case SEARCH_TYPE_LOCAL_JUMP_ALLOWED:
        case SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED:
          break;
      }

      //
      // Can jump but only if not tired.
      //
      if (jump_allowed &&
          is_jumper() &&
          (get_stamina() > get_stamina_max() / 2)) {
        //
        // Trace all possible jump paths to see if we can jump over
        //
        if (is_hazardous_to_me(p) || ai_obstacle_for_me(p)) {
          auto jump_dist = how_far_i_can_jump();
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
            if (is_hazardous_to_me(jump_begin) ||
              ai_obstacle_for_me(jump_begin)) {
              continue;
            }
            if (is_hazardous_to_me(jump_end) ||
              ai_obstacle_for_me(jump_end)) {
              continue;
            }

            //
            // Must be able to see the begin/end.
            //
            if (!level->is_lit_ever(jump_begin)) {
              continue;
            }

            //
            // Too far?
            //
            float dist = DISTANCE(jump_begin.x, jump_begin.y,
                        jump_end.x, jump_end.y);
            if (dist > jump_dist + 1) {
              continue;
            }

            //
            // Check we really need to jump over all things in
            // the path.
            //
            // Also check for walls. Is it fair to jump over
            // walls?
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
              if (!ai_obstacle_for_me(j)) {
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

      set(dmap_can_see->val, x, y, DMAP_IS_WALL);
      continue;
    }
  }

  //
  // Grow the search space beyond the light
  //
  std::array< std::array<bool, MAP_WIDTH>, MAP_HEIGHT> walked = {};
  if (is_player()) {
    for (int y = miny; y < maxy; y++) {
      for (int x = minx; x < maxx; x++) {
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

        if (!level->is_lit_ever(p)) {
          continue;
        }

        //
        // Can't see past walls. However we can see over chasms
        // to expand the search space
        //
        if (level->is_door(p)) {
          //
          // Allow us to see doors so we can search them
          //
        } else if (level->is_obs_wall_or_door(p)) {
          //
          // But allow chasms and lava so we can see over. Just block
          // on walls and pillars etc...
          //
          continue;
        }

        set(walked, x, y, true);

        for (auto dx = -1; dx <= 1; dx++) {
          for (auto dy = -1; dy <= 1; dy++) {
            point o(p.x + dx, p.y + dy);
            if (!dx && !dy) {
              continue;
            }
            if (level->is_oob(o)) {
              continue;
            }
            if (!level->is_able_to_stand_on(o)) {
              continue;
            }
            if (level->is_door(o)) {
              //
              // Allow us to see doors so we can search them
              //
            } else if (level->is_obs_wall_or_door(o)) {
              //
              // But allow chasms and lava so we can see over. Just block
              // on walls and pillars etc...
              //
              continue;
            }

            if (!level->is_lit_currently(p.x, p.y)) {
              FOR_ALL_THINGS_THAT_INTERACT(level, it, p.x, p.y) {
                if (it->is_changing_level ||
                  it->is_hidden ||
                  it->is_falling ||
                  it->is_jumping) {
                  continue;
                }

                if (worth_collecting(it) || worth_eating(it) || is_dangerous(it)) {
                  something_changed++;
                }
              } FOR_ALL_THINGS_END();
            }

            set(dmap_can_see->val, o.x, o.y, DMAP_IS_PASSABLE);
          }
        }
      }
    }
  }
#if 0
  printf("\nrobot search grown:\n");
  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      if ((x == (int)mid_at.x) && (y == (int)mid_at.y)) {
        if (level->is_lit_ever(x, y)) {
          printf("*");
        } else {
          printf("o");
        }
        continue;
      }
      if (get(walked, x, y)) {
        if (level->is_obs_wall_or_door(x, y)) {
          printf("X");
        } else {
          printf("?");
        }
      } else {
        if (level->is_obs_wall_or_door(x, y)) {
          printf("x");
        } else {
          if (level->is_lit_currently(x, y)) {
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
#endif

  for (int y = miny; y < maxy; y++) {
    for (int x = minx; x < maxx; x++) {

      if (get(can_jump, x, y)) {
        set(dmap_can_see->val, x, y, DMAP_IS_PASSABLE);
      }

      //
      // Did anything of interest change worthy of interrupting
      // a walk?
      //
      auto dmap_score = get(dmap_can_see->val, x, y);
      auto seen_when = get(seen_map->val, x, y);
      if (dmap_score == DMAP_IS_PASSABLE) {
        //
        // Is now seen; did something open?
        //
        if (!seen_when) {
          something_changed++;
        }
        set(seen_map->val, x, y, game->tick_current);
      } else if (dmap_score == DMAP_IS_WALL) {
        //
        // Was seen but now cannot see; did something close?
        //
        if (seen_when) {
          something_changed++;
        }
        set(seen_map->val, x, y, 0U);
      }
    }
  }

  //
  // We want to find how far everything is from us.
  //
  set(dmap_can_see->val, start.x, start.y, DMAP_IS_GOAL);
  IF_DEBUG4 {
    dmap_print(dmap_can_see);
  }

  dmap_process(dmap_can_see, point(minx, miny), point(maxx, maxy));

  auto t = most_dangerous_visible_thing_get();
  if (t) {
    something_changed = true;
  }

  return something_changed;
}

//
// Look at all the things that are currently visited (read that as light rays
// have touched them) and choose the best goal. Create a path to that goal for
// the thing to walk.
//
void Thing::robot_ai_choose_initial_goals (std::multiset<Goal> &goals,
                                           int minx, int miny, int maxx, int maxy)
{_
  auto dmap_can_see = get_dmap_can_see();
  auto age_map = get_age_map();

  for (int y = miny; y < maxy; y++) { for (int x = minx; x < maxx; x++) {
    point p(x, y);

    if (get(dmap_can_see->val, x, y) == DMAP_IS_WALL) {
      continue;
    }

    bool got_a_goal = false;
    bool avoiding = false;
    int terrain_cost = get_terrain_cost(p);
    int total_score = -(int)terrain_cost;

    std::string last_msg;

    FOR_ALL_THINGS_THAT_INTERACT(level, it, p.x, p.y) {
      last_msg = "";

      if (it->is_changing_level ||
        it->is_hidden ||
        it->is_falling ||
        it->is_jumping) {
        continue;
      }

      if (it == this) { continue; }

      if (it->get_immediate_owner_id().ok()) {
        continue;
      }

      //
      // Worse terrain, less preferred. Higher score, more preferred.
      //
      auto my_health = get_health();
      auto it_health = it->get_health();
      auto health_diff = it_health - my_health;
      bool got_one_this_tile = false;

      //
      // Don't allow of attacking monsts from memory if the player or
      // robot
      //
      auto lit_recently = level->is_lit_recently(it->mid_at.x, it->mid_at.y);
      if (is_player()) {
        if (it->is_offscreen) {
          lit_recently = false;
        }
      } else {
        lit_recently = true;
      }

      if (is_starving) {
        if (worth_eating(it)) {
          //
          // If starving, prefer the thing with most health
          //
          SCORE_ADD(it_health, "eat-it");
          got_one_this_tile = true;
        }
      } else if (is_hungry) {
        if (worth_eating(it) && !is_dangerous(it)) {
          //
          // Prefer easy food over attacking the player and prefer
          // the player over a monster. Factor in health so we will
          // go for the easier kill in preference.
          //
          if (it->is_player()) {
            SCORE_ADD(it_health / 2, "eat-player");
            got_one_this_tile = true;
          } else if (it->is_alive_monst()) {
            SCORE_ADD(it_health / 2, "eat-monst");
            got_one_this_tile = true;
          } else {
            SCORE_ADD(it_health / 2, "eat-food");
            got_one_this_tile = true;
          }
        }
      }

      if (is_item_collector()) {
        if (it->is_collectable()) {
          auto score = worth_collecting(it);
          if (score > 0) {
            SCORE_ADD(score, "collect");
            got_one_this_tile = true;
            if (is_player()) {
              CON("Robot: @(%s, %d,%d %d/%dh) Is considering collecting %s",
                level->to_string().c_str(),
                (int)mid_at.x, (int)mid_at.y, get_health(), get_health_max(),
                it->to_string().c_str());
            } else {
              con("Monst: Is considering collecting %s", it->to_string().c_str());
            }
          } else {
            if (is_player()) {
              CON("Robot: @(%s, %d,%d %d/%dh) Is not collecting %s (score %d)",
                level->to_string().c_str(),
                (int)mid_at.x, (int)mid_at.y, get_health(), get_health_max(),
                it->to_string().c_str(),
                score);
            } else {
              con("Monst: Is not collecting %s", it->to_string().c_str());
            }
          }
        }
      }

      //
      // Need more work before monsts can collect keys
      // as they will be auto collected.
      //
      if (is_key_collector()) {
        if (it->is_key()) {
          SCORE_ADD(1000, "collect-key");
          got_one_this_tile = true;
        }
      }

      if (!it->is_dead) {
        bool avoid = false;
        auto dist = distance(mid_at, it->mid_at);
        float max_dist = ai_scent_distance();

        //
        // If this is something we really want to avoid, like
        // fire, then stay away from it
        //
        if (will_avoid_hazard(it)) {
          if (dist == 1) {
            avoid = true;
          }
        }

        //
        // If we can see an enemy, get them! If the monster is not lit
        // then it's not really fair to use that knowledge.
        //
        if (lit_recently) {
          if (is_enemy(it) && (dist < max_dist)) {
            if (is_dangerous(it) && (get_health() < get_health_max() / 2)) {
              //
              // Low on health. Best to avoid this enemy.
              //
              avoid = true;
              SCORE_ADD(-(int)((max_dist - dist) + it_health) * 200, "avoid-enemy");
              got_one_this_tile = true;
            } else {
              //
              // The closer an enemy is (something that attacked us), the
              // higher the score
              //
              avoid = false;
              SCORE_ADD((int)(max_dist - dist) * 200, "attack-enemy");
              got_one_this_tile = true;
            }
          } else if (!avoid && (dist < ai_avoid_distance()) && will_avoid_monst(it)) {
            //
            // Monsters we avoid are more serious threats
            //
            avoid = true;
          } else if (!avoid && it->is_minion_generator()) {
            //
            // Very close, high priority attack
            //
            SCORE_ADD((int)(max_dist - dist) * 1000, "attack-nearby-generator");
            got_one_this_tile = true;
          } else if (!avoid && it->is_monst() && !will_avoid_hazard(it)) {
            //
            // Hazard check above is for cleaners standing on their
            // pool of acid. Do we want to attack that without good
            // reason?
            //
            if (dist < 2) {
              //
              // Very close, high priority attack
              //
              SCORE_ADD((int)(max_dist - dist) * 100, "attack-nearby-monst");
              got_one_this_tile = true;
            } else if (dist < max_dist) {
              //
              // Further away close, lower priority attack
              //
              SCORE_ADD((int)(max_dist - dist) * 10, "attack-maybe-monst");
              got_one_this_tile = true;
            }
          }
        }

        if (!avoid && it->is_spiderweb() && !dist) {
          //
          // Very close, high priority attack
          //
          SCORE_ADD(666, "get-out-of-web");
          got_one_this_tile = true;
        }

        if (avoid) {
          if (is_player()) {
            CON("Robot: @(%s, %d,%d %d/%dh) Needs to avoid %s",
              level->to_string().c_str(),
              (int)mid_at.x, (int)mid_at.y, get_health(), get_health_max(),
              it->to_string().c_str());
          } else {
            log("Monst: Thinks it needs to avoid %s", it->to_string().c_str());
          }

          bool got_avoid = false;
          auto d = ai_avoid_distance();
          if (!d) {
            d = 2;
          }

          for (auto dx = -d; dx <= d; dx++) {
            for (auto dy = -d; dy <= d; dy++) {

              if (!dx && !dy) {
                continue;
              }

              float dist = distance(mid_at + fpoint(dx, dy), it->mid_at);
              if (dist < ai_avoid_distance()) {
                continue;
              }

              point p(mid_at.x + dx, mid_at.y + dy);
              if (ai_obstacle_for_me(p)) {
                continue;
              }

              int terrain_cost = get_terrain_cost(p);
              int total_score = -(int)terrain_cost;
              total_score += dist * 100;
              total_score += 1000;
              goals.insert(Goal(total_score, p, last_msg));
              set(dmap_can_see->val, p.x, p.y, DMAP_IS_GOAL);
              dbg("Avoid goal (score %d) @(%d,%d)", total_score, p.x, p.y);
              got_avoid = true;
            }
          }

          //
          // Try again with more lenient checks
          //
          if (!got_avoid) {
            for (auto dx = -d; dx <= d; dx++) {
              for (auto dy = -d; dy <= d; dy++) {

                float dist = distance(mid_at + fpoint(dx, dy), it->mid_at);
                point p(mid_at.x + dx, mid_at.y + dy);
                if (ai_obstacle_for_me(p)) {
                  continue;
                }

                int terrain_cost = get_terrain_cost(p);
                int total_score = -(int)terrain_cost;
                total_score += dist * 100;
                total_score += 1000;
                goals.insert(Goal(total_score, p, last_msg));
                set(dmap_can_see->val, p.x, p.y, DMAP_IS_GOAL);
                dbg("Avoid goal (2) (score %d) @(%d,%d)", total_score, p.x, p.y);

                got_avoid = true;
              }
            }
          }

          //
          // Try again with even more lenient checks
          //
          if (!got_avoid) {
            for (auto dx = -d; dx <= d; dx++) {
              for (auto dy = -d; dy <= d; dy++) {

                float dist = distance(mid_at + fpoint(dx, dy), it->mid_at);
                point p(mid_at.x + dx, mid_at.y + dy);
                if (level->is_obs_wall_or_door(p)) {
                  continue;
                }

                int terrain_cost = get_terrain_cost(p);
                int total_score = -(int)terrain_cost;
                total_score += dist * 100;
                total_score += 1000;
                goals.insert(Goal(total_score, p, last_msg));
                set(dmap_can_see->val, p.x, p.y, DMAP_IS_GOAL);
                dbg("Avoid goal (3) (score %d) @(%d,%d)", total_score, p.x, p.y);

                got_avoid = true;
              }
            }
          }

          //
          // This is an anti goal
          //
          if (got_avoid) {
            avoiding = true;
            CON("Robot is avoiding");
            break;
          } else {
            CON("Robot could not avoid, so attack %s", it->to_string().c_str());
          }
        }

        if (!got_one_this_tile) {
          //
          // No hunting monsters we cannot see just because we
          // have visited that area before.
          //
          // Well this is true for the player. Monsters, we're
          // lenient.
          //
          if (lit_recently) {
            if (possible_to_attack(it)) {
              SCORE_ADD(- health_diff, "can-attack-monst");
            }
          }
        }
      }

      if (will_prefer_terrain(it)) {
        //
        // Prefer certain terrains over others. i.e. I prefer water.
        //
        auto age = get(age_map->val, p.x, p.y);
        if (age - game->tick_current < 10) {
          SCORE_ADD(1, "preferred-terrain");
        }
      }
    } FOR_ALL_THINGS_END();

    if (avoiding) {
      set(dmap_can_see->val, x, y, DMAP_IS_WALL);
    } else if (got_a_goal) {
      goals.insert(Goal(total_score, p, last_msg));
      dbg("Add goal (score %d) @(%d,%d) %s",
        total_score, p.x, p.y, last_msg.c_str());
      set(dmap_can_see->val, x, y, DMAP_IS_GOAL);
    } else if (terrain_cost) {
      set(dmap_can_see->val, x, y, (uint8_t)terrain_cost);
    } else {
      set(dmap_can_see->val, x, y, DMAP_IS_PASSABLE);
    }
  } }
}

//
// We get here if there is nothing visible of interest. Look at the edges of
// what is currently visible and find the most interesting point at that edge
// and then create a path to that edge.
//
void Thing::robot_ai_choose_search_goals (std::multiset<Goal> &goals,
                                          int search_type)
{_
  point start((int)mid_at.x, (int)mid_at.y);

  std::array< std::array<bool, MAP_WIDTH>, MAP_HEIGHT> walked = {};
  std::array< std::array<bool, MAP_WIDTH>, MAP_HEIGHT> pushed = {};
  std::deque<point> in;
  std::deque<point> can_reach_cands;
  std::deque<Thingp> out;
  in.push_back(start);
  set(pushed, start.x, start.y, true);

  auto dmap_can_see = get_dmap_can_see();
  IF_DEBUG3 {
    log("Dmap, can see:");
    dmap_print(dmap_can_see);
  }

  while (!in.empty()) {
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
    // If an unvisited tile is next to a visited one, consider that tile.
    //
    if (!level->is_lit_ever(p.x, p.y)) {
      continue;
    }

    if (level->is_obs_wall_or_door(p.x, p.y)) {
      continue;
    }

    if (!get(pushed, p.x + 1, p.y)) {
      set(pushed, p.x + 1, p.y, true);
      in.push_back(point(p.x + 1, p.y));
    }

    if (!get(pushed, p.x - 1, p.y)) {
      set(pushed, p.x - 1, p.y, true);
      in.push_back(point(p.x - 1, p.y));
    }

    if (!get(pushed, p.x, p.y + 1)) {
      set(pushed, p.x, p.y + 1, true);
      in.push_back(point(p.x, p.y + 1));
    }

    if (!get(pushed, p.x, p.y - 1)) {
      set(pushed, p.x, p.y - 1, true);
      in.push_back(point(p.x, p.y - 1));
    }

    //
    // Look as far as our memory and lighting permits
    //
    auto dist = distance(make_fpoint(p), mid_at);
    float max_dist = ai_scent_distance();

    int jump_distance;

    switch (search_type) {
      case SEARCH_TYPE_LOCAL_JUMP_ALLOWED:
        if (dist >= max_dist) {
          continue;
        }
        jump_distance = how_far_i_can_jump();
        break;
      case SEARCH_TYPE_LOCAL_NO_JUMP:
        if (dist >= max_dist) {
          continue;
        }
        jump_distance = 0;
        break;
      case SEARCH_TYPE_GLOBAL_JUMP_ALLOWED:
        jump_distance = how_far_i_can_jump();
        break;
      case SEARCH_TYPE_GLOBAL_NO_JUMP:
        jump_distance = 0;
        break;
      case SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED:
        jump_distance = how_far_i_can_jump();
        break;
      case SEARCH_TYPE_LAST_RESORTS_NO_JUMP:
        jump_distance = 0;
        break;
      default:
        DIE("unexpected search-type case");
        break;
    }

    for (int dx = -jump_distance; dx <= jump_distance; dx++) {
      for (int dy = -jump_distance; dy <= jump_distance; dy++) {
        if (!dx && !dy) {
          continue;
        }
        point o(p.x + dx, p.y + dy);
        if (level->is_oob(o)) {
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
        } else if (level->is_secret_door(o)) {
          if (dist > ROBOT_CAN_SEE_SECRET_DOOR_DISTANCE) {
            continue;
          }
        } else if (level->is_descend_sewer(o)) {
          //
          // Worth investigating unless over
          //
          if ((o.x == mid_at.x) && (o.y == mid_at.y)) {
            continue;
          }
          if (search_type < SEARCH_TYPE_LAST_RESORTS_NO_JUMP) {
            continue;
          }
        } else if (level->is_ascend_sewer(o)) {
          //
          // Worth investigating
          //
          if ((o.x == mid_at.x) && (o.y == mid_at.y)) {
            continue;
          }
          if (search_type < SEARCH_TYPE_LAST_RESORTS_NO_JUMP) {
            continue;
          }
        } else if (level->is_descend_dungeon(o)) {
          //
          // Worth investigating
          //
          if ((o.x == mid_at.x) && (o.y == mid_at.y)) {
            continue;
          }
          if (search_type < SEARCH_TYPE_LAST_RESORTS_NO_JUMP) {
            continue;
          }
        } else if (level->is_ascend_dungeon(o)) {
          //
          // Worth investigating
          //
          if ((o.x == mid_at.x) && (o.y == mid_at.y)) {
            continue;
          }
          if (search_type < SEARCH_TYPE_LAST_RESORTS_NO_JUMP) {
            continue;
          }
        } else {
          //
          // If lit then we can already see it, so not worth
          // exploring.
          //
          if (level->is_lit_ever(o)) {
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
  printf("\nrobot search cand\n");
  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      if ((x == (int)mid_at.x) && (y == (int)mid_at.y)) {
        if (level->is_lit_ever(x, y)) {
          printf("*");
        } else {
          printf("o");
        }
        continue;
      }
      for (auto p : can_reach_cands) {
        if ((x == p.x) && (y == p.y)) {
          printf("c");
          goto next;
        }
      }
      if (get(walked, x, y)) {
        if (level->is_obs_wall_or_door(x, y)) {
          printf("X");
        } else {
          printf("?");
        }
      } else {
        if (level->is_obs_wall_or_door(x, y)) {
          printf("x");
        } else {
          if (level->is_lit_currently(x, y)) {
            printf("l");
          } else {
            printf(" ");
          }
        }
      }
next:
      continue;
    }
    printf("\n");
  }
#endif

  //
  // Choose goals (higher scores, lower costs are preferred)
  //
  for (auto p : can_reach_cands) {
    //
    // Avoid sewer descend/ascend loop
    //
    if ((p.x == mid_at.x) && (p.y == mid_at.y)) {
      continue;
    }

    //
    // Prefer easier terrain
    //
    int terrain_cost = get_terrain_cost(p);
    int total_score = -(int)terrain_cost;

    //
    // Prefer closer
    //
    float dist = distance(start, p);
    total_score -= dist * dist;

    //
    // Choose doors etc... as a last resort when nothing else
    //
    if (level->is_door(p.x, p.y)) {
      total_score -= 1000;
    }

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

    dbg("Add search cand (score %d) @(%d,%d)", total_score, p.x, p.y);
    goals.insert(Goal(total_score, p, "search cand"));
  }
}

bool Thing::robot_ai_choose_nearby_goal (void)
{_
  bool left;
  bool right;
  bool up;
  bool down;
  bool wait = false;
  bool jump = false;
  bool attack = false;

  for (int dx = -1; dx <= 1; dx++) {
    for (int dy = -1; dy <= 1; dy++) {
      fpoint at(mid_at.x + dx, mid_at.y + dy);

      FOR_ALL_THINGS(level, it, at.x, at.y) {
        if (it->is_door() && !it->is_open) {
          if (get_keys()) {
            if (open_door(it)) {
              BOTCON("Robot opened a door");
              game->tick_begin("Robot opened a door");
              return true;
            }
          }

          //
          // Try hitting the door
          //
          left = dx < 0;
          right = dx > 0;
          up = dy < 0;
          down = dy > 0;
          attack = true;
          CON("Robot: @(%s, %d,%d %d/%dh) Try hitting the door",
            level->to_string().c_str(),
            (int)mid_at.x, (int)mid_at.y,get_health(), get_health_max());
          BOTCON("Robot is trying to break the door down");
          player_tick(left, right, up, down, attack, wait, jump);
          return true;
        }

        if (it->is_spiderweb() && (it->mid_at == mid_at)) {
          //
          // Try hitting the web
          //
          left = dx < 0;
          right = dx > 0;
          up = dy < 0;
          down = dy > 0;
          attack = true;
          CON("Robot: @(%s, %d,%d %d/%dh) Try hitting the web",
            level->to_string().c_str(),
            (int)mid_at.x, (int)mid_at.y,get_health(), get_health_max());
          BOTCON("Robot is trying to escape the web");
          player_tick(left, right, up, down, attack, wait, jump);
          return true;
        }
      } FOR_ALL_THINGS_END();

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
  return false;
}

void Thing::robot_tick (void)
{_
  //
  // For game smoothness we allow the player to run a bit ahead of the
  // monsters.
  //
  // Do not let the robot do this.
  //
  if (game->things_are_moving) {
    return;
  }

  if (game->tick_completed != game->tick_current) {
    return;
  }

  if (is_dead) {
    return;
  }

  if (is_changing_level ||
    is_falling ||
    is_waiting_to_ascend_dungeon ||
    is_waiting_to_descend_sewer ||
    is_waiting_to_descend_dungeon ||
    is_waiting_to_ascend_sewer ||
    is_waiting_to_fall ||
    is_jumping) {
    return;
  }

  if (level->ts_fade_in_begin) {
    return;
  }

  if (level->cursor) {
    level->cursor->hide();
  }

  //
  // Set up the extent of the AI, choosing smaller areas for monsters for
  // speed.
  //
  const float dx = (MAP_WIDTH / 6);
  const float dy = (MAP_HEIGHT / 6);

  int minx = std::max(0,          (int)(mid_at.x - dx));
  int maxx = std::min(MAP_WIDTH,  (int)(mid_at.x + dx - 1));
  int miny = std::max(0,          (int)(mid_at.y - dy));
  int maxy = std::min(MAP_HEIGHT, (int)(mid_at.y + dy - 1));

  if (is_player()) {
    minx = 0;
    maxx = MAP_WIDTH;
    miny = 0;
    maxy = MAP_HEIGHT;
  }

  bool left = false;
  bool right = false;
  bool up = false;
  bool down = false;
  bool attack = false;
  bool wait = false;
  bool jump = false;
  bool do_something = false;

  //
  // See if anything dangerous is close
  //
  auto threat = most_dangerous_visible_thing_get();

  switch (monstp->robot_state) {
    case ROBOT_STATE_IDLE:
    {
      //
      // If we're absolutely exhausted, we must rest, threat or no threat
      //
      if (!get_stamina()) {
        CON("Robot: @(%s, %d,%d %d/%dh) Is forced to rest, very low on stamina",
          level->to_string().c_str(),
          (int)mid_at.x, (int)mid_at.y,get_health(), get_health_max());
        BOTCON("Robot is forced to rest, very low on stamina");
        game->tick_begin("Robot is forced to rest, very low on stamina");
        robot_change_state(ROBOT_STATE_RESTING, "need to rest, very low on stamina");
        return;
      }

      //
      // If really low on health and we have something we can eat, try
      // that.
      //
      if (get_health() < get_health_max() / 3) {
        if (can_eat_something()) {
          CON("Robot: @(%s, %d,%d %d/%dh) Robot needs to rest, very low on health",
            level->to_string().c_str(),
            (int)mid_at.x, (int)mid_at.y,get_health(), get_health_max());
          BOTCON("Robot needs to rest, very low on health");
          game->tick_begin("Robot needs to rest, very low on health");
          robot_change_state(ROBOT_STATE_RESTING, "need to rest, very low on health");
          return;
        }
      }

      //
      // Look for doors or things to collect, if not being attacked.
      //
      if (threat && (is_dangerous(threat) || is_enemy(threat))) {
        //
        // No resting when in danger
        //
        CON("Robot: @(%s, %d,%d %d/%dh) A threat is nearby: %s",
          level->to_string().c_str(),
          (int)mid_at.x, (int)mid_at.y, get_health(), get_health_max(),
          threat->to_string().c_str());
        BOTCON("Robot is facing a threat");
      } else {
        CON("Robot: @(%s, %d,%d %d/%dh) Is idle, look for something to do",
          level->to_string().c_str(),
          (int)mid_at.x, (int)mid_at.y,get_health(), get_health_max());

        if (get_health() < get_health_max() / 2) {
          if (can_eat_something()) {
            CON("Robot: @(%s, %d,%d %d/%dh) Robot needs to rest, low on health",
              level->to_string().c_str(),
              (int)mid_at.x, (int)mid_at.y,get_health(), get_health_max());
            BOTCON("Robot needs to rest, low on health");
            game->tick_begin("Robot needs to rest, low on health");
            robot_change_state(ROBOT_STATE_RESTING, "need to rest, low on health");
            return;
          }
        }

        if (get_stamina() < get_stamina_max() / 3) {
          CON("Robot: @(%s, %d,%d %d/%dh) Robot needs to rest, low on stamina",
            level->to_string().c_str(),
            (int)mid_at.x, (int)mid_at.y,get_health(), get_health_max());
          BOTCON("Robot needs to rest, low on stamina");
          game->tick_begin("Robot needs to rest, low on stamina");
          robot_change_state(ROBOT_STATE_RESTING, "need to rest, low on stamina");
          return;
        }

        Thingp best_weapon;
        get_carried_weapon_highest_value(&best_weapon);
        if (best_weapon && (best_weapon != weapon_get())) {
          if (wield(best_weapon)) {
            CON("Robot: @(%s, %d,%d %d/%dh) Robot is changing weapon to %s",
              level->to_string().c_str(),
              (int)mid_at.x, (int)mid_at.y, get_health(), get_health_max(),
              best_weapon->to_string().c_str());
            BOTCON("Robot is changing weapon");
            game->tick_begin("Robot is changing weapon");
            return;
          }
          CON("Robot: @(%s, %d,%d %d/%dh) Robot failed to change weapon to %s",
            level->to_string().c_str(),
            (int)mid_at.x, (int)mid_at.y, get_health(), get_health_max(),
            best_weapon->to_string().c_str());
        }

        CON("Robot: @(%s, %d,%d %d/%dh) Is idle, look for nearby goal",
          level->to_string().c_str(),
          (int)mid_at.x, (int)mid_at.y,get_health(), get_health_max());

        if (robot_ai_choose_nearby_goal()) {
          return;
        }
      }

      for (int search_type = 0; search_type < SEARCH_TYPE_MAX; search_type++) {
        if (search_type > 0) {
          CON("Robot: @(%s, %d,%d %d/%dh) Try to find goals, search-type %d",
            level->to_string().c_str(),
            (int)mid_at.x, (int)mid_at.y, get_health(), get_health_max(),
            search_type);
        }
        if (robot_ai_create_path_to_goal(minx, miny, maxx, maxy, search_type)) {
          if (monstp->move_path.size()) {
            robot_change_state(ROBOT_STATE_MOVING, "found a new goal");
          } else {
            CON("Robot: @(%s, %d,%d %d/%dh) Robot did not move, but did something else",
              level->to_string().c_str(),
              (int)mid_at.x, (int)mid_at.y,get_health(), get_health_max());
          }
          return;
        }
      }

      if ((get_health() >= (get_health_max() / 4) * 3) &&
          (get_stamina() >= (get_stamina_max() / 4) * 3)) {
        BOTCON("Robot has nothing to do at all");
        wid_actionbar_robot_mode_off();
      } else {
        BOTCON("Robot has nothing to do, rest");
        game->tick_begin("nothing to do, rest");
        robot_change_state(ROBOT_STATE_RESTING, "nothing to do, rest");
      }
    }
    break;

    case ROBOT_STATE_MOVING:
    {
      CON("Robot: @(%s, %d,%d %d/%dh) Continue moving",
        level->to_string().c_str(),
        (int)mid_at.x, (int)mid_at.y,get_health(), get_health_max());

      //
      // Check for interrupts
      //
      if (robot_ai_init_can_see_dmap(minx, miny, maxx, maxy,
                       SEARCH_TYPE_LOCAL_JUMP_ALLOWED)) {
        CON("Robot: @(%s, %d,%d %d/%dh) Something interrupted me",
          level->to_string().c_str(),
          (int)mid_at.x, (int)mid_at.y,get_health(), get_health_max());
        game->tick_begin("Robot move interrupted by something");
        robot_change_state(ROBOT_STATE_IDLE, "move interrupted by a change");
        wid_actionbar_init();
        return;
      }

      if (monstp->move_path.empty()) {
        CON("Robot: @(%s, %d,%d %d/%dh) Robot: Move finished",
          level->to_string().c_str(),
          (int)mid_at.x, (int)mid_at.y,get_health(), get_health_max());
        BOTCON("Robot move finished");
        game->tick_begin("Robot move finished");
        robot_change_state(ROBOT_STATE_IDLE, "move finished");
        wid_actionbar_init();
        return;
      } else {
        CON("Robot: @(%s, %d,%d %d/%dh) Moving",
          level->to_string().c_str(),
          (int)mid_at.x, (int)mid_at.y,get_health(), get_health_max());
        game->tick_begin("Robot move");
        return;
      }
    }
    break;
    case ROBOT_STATE_RESTING:
    {
      if ((get_health() >= (get_health_max() / 4) * 3) &&
          (get_stamina() >= (get_stamina_max() / 4) * 3)) {

        BOTCON("Robot has rested enough");
        game->tick_begin("Robot has rested enough");
        robot_change_state(ROBOT_STATE_IDLE, "rested enough");
        return;
      }

      //
      // Check for food first, before abandoning resting
      //
      if (eat_something()) {
        BOTCON("Robot needs to eat");
        game->tick_begin("Robot ate an item");
        robot_change_state(ROBOT_STATE_OPEN_INVENTORY, "eat something");
        return;
      }

      if (get_stamina()) {
        if (threat && (is_dangerous(threat) || is_enemy(threat))) {
          BOTCON("Robot sees a nearby threat, stop resting");
          game->tick_begin("Robot sees a nearby threat, stop resting");
          robot_change_state(ROBOT_STATE_IDLE, "threat nearby, stop resting");
          return;
        }
      }

      if (get_stamina() >= (get_stamina_max() / 4) * 3) {
        BOTCON("Robot has recovered stamina");
        game->tick_begin("Robot has recovered stamina");
        robot_change_state(ROBOT_STATE_IDLE, "threat nearby, stop resting");
        return;
      }

      CON("Robot: @(%s, %d,%d %d/%dh) Wait and rest",
        level->to_string().c_str(),
        (int)mid_at.x, (int)mid_at.y,get_health(), get_health_max());
      do_something = true;
      wait = true;
      break;
    }
    break;

    case ROBOT_STATE_OPEN_INVENTORY:
    {
      //
      // Wait for the inventory to be remade
      //
      if (game->request_remake_inventory) {
        return;
      }

      //
      // Then close it. This is really just visual feedback.
      //
      robot_change_state(ROBOT_STATE_IDLE, "close inventory");
      game->tick_begin("Robot finished collecting");
    }
  }

  log("Robot: Do something");
  if (do_something) {
    player_tick(left, right, up, down, attack, wait, jump);
  }
}

void Thing::robot_change_state (int new_state, const std::string &why)
{_
  if (monstp->robot_state == new_state) {
    return;
  }

  std::string to;
  std::string from;
  switch (new_state) {
    case ROBOT_STATE_IDLE:
      to = "IDLE";
      break;
    case ROBOT_STATE_MOVING:
      to = "MOVING";
      break;
    case ROBOT_STATE_RESTING:
      to = "RESTING";
      break;
    case ROBOT_STATE_OPEN_INVENTORY:
      to = "OPEN-INVENTORY";
      break;
  }
  switch (monstp->robot_state) {
    case ROBOT_STATE_IDLE:
      from = "IDLE";
      break;
    case ROBOT_STATE_MOVING:
      from = "MOVING";
      break;
    case ROBOT_STATE_RESTING:
      from = "RESTING";
      break;
    case ROBOT_STATE_OPEN_INVENTORY:
      from = "OPEN-INVENTORY";
      wid_thing_info_fini();
      wid_inventory_init();
      break;
  }

  CON("Robot: @(%s, %d,%d %d/%dh) %s -> %s: %s",
    level->to_string().c_str(),
    (int)mid_at.x, (int)mid_at.y,get_health(), get_health_max(),
    from.c_str(), to.c_str(), why.c_str());

  monstp->robot_state = new_state;
  switch (new_state) {
    case ROBOT_STATE_IDLE:
      clear_move_path("Robot is idle");
      BOTCON("Robot is idle");
      break;
    case ROBOT_STATE_MOVING:
      BOTCON("Robot is moving");
      break;
    case ROBOT_STATE_RESTING:
      BOTCON("Robot is resting");
      break;
    case ROBOT_STATE_OPEN_INVENTORY:
      game->change_state(Game::STATE_MOVING_ITEMS);
      game->request_remake_inventory = true;
      game->wid_thing_info_create(game->level->player, false);
      BOTCON("Robot is looking in its inventory");
      break;
  }
}
