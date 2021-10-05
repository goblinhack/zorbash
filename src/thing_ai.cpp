//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.h"
#include "my_dmap.h"
#include "my_game.h"
#include "my_globals.h"
#include "my_level.h"
#include "my_math.h"
#include "my_monst.h"
#include "my_player.h"
#include "my_ptrcheck.h"
#include "my_random.h"
#include "my_sprintf.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_thing_ai.h"
#include "my_thing_template.h"
#include "my_vector_bounds_check.h"
#include "my_wid_actionbar.h"
#include "my_wid_inventory.h"
#include "my_wid_popup.h"
#include "my_wid_thing_info.h"
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

#define SCORE_ADD(score, msg)                                                                                          \
  total_score += (score);                                                                                              \
  got_a_goal = true;                                                                                                   \
  if (last_msg.empty()) {                                                                                              \
    last_msg = msg;                                                                                                    \
  } else {                                                                                                             \
    last_msg += ", ";                                                                                                  \
    last_msg += msg;                                                                                                   \
  }                                                                                                                    \
  IF_DEBUG3                                                                                                            \
  {                                                                                                                    \
    auto s = string_sprintf("Add sub-goal score %d @(%d,%d) %s", score, p.x, p.y, msg);                                \
    AI_LOG("", s, it);                                                                                                 \
  }

void Thing::ai_log(const std::string &short_msg, const std::string &long_msg, Thingp it)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    if (! short_msg.empty()) {
      BOTCON("Robot: %s", short_msg.c_str());
    }

    if (it) {
      CON("Robot: @(%s, %d,%d %d/%dh) %s, %s", level->to_string().c_str(), (int) mid_at.x, (int) mid_at.y, get_health(),
          get_health_max(), long_msg.c_str(), it->to_string().c_str());
    } else {
      CON("Robot: @(%s, %d,%d %d/%dh) %s", level->to_string().c_str(), (int) mid_at.x, (int) mid_at.y, get_health(),
          get_health_max(), long_msg.c_str());
    }
  } else {
    if (it) {
      log("%s, %s", long_msg.c_str(), it->to_string().c_str());
    } else {
      log("AI: %s", long_msg.c_str());
    }
  }
}

void Thing::ai_log(const std::string &short_msg, const std::string &long_msg) { ai_log(short_msg, long_msg, nullptr); }

void Thing::ai_log(const std::string &short_msg) { ai_log(short_msg, short_msg, nullptr); }

void Thing::ai_log(const std::string &short_msg, Thingp it) { ai_log(short_msg, short_msg, it); }

//
// Look at all the things that are currently visited (read that as light rays
// have touched them) and choose the best goal. Create a path to that goal for
// the thing to walk.
//
bool Thing::ai_create_path_to_goal(int minx, int miny, int maxx, int maxy, int search_type)
{
  TRACE_AND_INDENT();
  point start((int) mid_at.x, (int) mid_at.y);

  //
  // Choose goals (higher scores, lower costs are preferred)
  //
  std::string s = "Choose goal";
  IF_DEBUG3 { s = string_sprintf("Try to find goals, search-type %d", search_type); }

  AI_LOG("", s);
  TRACE_AND_INDENT();

  //
  // Find all the possible goals. Higher scores, lower costs are preferred
  //
  auto dmap_can_see = get_dmap_can_see();
  auto age_map      = get_age_map();

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
    AI_LOG("", "No goals found");
    return false;
  }

  AI_LOG("", "Found some goals. Choose the best.");
  for (auto &g : goalmaps) {
    //
    // Find the highest/least preferred score so we can scale all the goals
    // later so they fit in one byte (makes it easier to debug).
    //
    std::array< std::array< float, MAP_HEIGHT >, MAP_WIDTH > cell_totals         = {};
    float                                                    least_preferred     = 0;
    float                                                    most_preferred      = 0;
    bool                                                     least_preferred_set = false;
    bool                                                     most_preferred_set  = false;

    for (int y = miny; y < maxy; y++) {
      for (int x = minx; x < maxx; x++) {
        point p(x, y);
        auto  c = getptr(g.dmap->val, x, y);
        if ((*c < DMAP_IS_PASSABLE) && (*c > DMAP_IS_GOAL)) {
          dmap_modify_terrain_cost(p, c);
        }
      }
    }

    for (auto &goal : g.goals) {
      auto goal_target = goal.at;
      incr(cell_totals, goal_target.x, goal_target.y, goal.score);
      auto score = get(cell_totals, goal_target.x, goal_target.y);

      if (least_preferred_set) {
        least_preferred = std::min(least_preferred, score);
      } else {
        least_preferred     = score;
        least_preferred_set = true;
      }
      if (most_preferred_set) {
        most_preferred = std::max(most_preferred, score);
      } else {
        most_preferred     = score;
        most_preferred_set = true;
      }
    }

    IF_DEBUG3
    {
      auto s = string_sprintf("Sorted goals, %d (best) .. %d (worst)", (int) most_preferred, (int) least_preferred);
      AI_LOG("", s);
    }

    //
    // Scale the goals so they will fit in the dmap.
    //
    for (auto &goal : g.goals) {
      auto  goal_target = goal.at;
      float score       = get(cell_totals, goal_target.x, goal_target.y);

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
      uint8_t score8 = DMAP_LESS_PREFERRED_TERRAIN - (int) score;
      set(g.dmap->val, goal_target.x, goal_target.y, score8);
    }

    //
    // Record we've been here.
    //
    set(age_map->val, start.x, start.y, game->tick_current);

    //
    // Find the best next-hop to the best goal.
    //
#ifdef ENABLE_DEBUG_AI_VERBOSE
    IF_DEBUG3
    {
      AI_LOG("", "Goals:");
      dmap_print(g.dmap, point(min.x, min.y), point(start.x, start.y), point(max.x, max.y));
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
    std::multiset< Path > paths;
    char                  path_debug = '\0'; // astart path debug

    for (auto &goal : g.goals) {
#ifdef ENABLE_DEBUG_AI_ASTAR
      astar_debug = {};
#endif
      auto astar_end = goal.at;
      auto result    = astar_solve(&goal, path_debug, astar_start, astar_end, g.dmap);

      //
      // Unreachable?
      //
      if (result.cost == std::numeric_limits< int >::max()) {
#ifdef ENABLE_DEBUG_AI_ASTAR
        auto start = point(minx, miny);
        auto end   = point(maxx, maxy);
        astar_dump(g.dmap, goal.at, start, end);
#endif
        continue;
      }

      paths.insert(result);

#ifdef ENABLE_DEBUG_AI_ASTAR
      for (auto &p : result.path) {
        set(astar_debug, p.x, p.y, '*');
      }
      auto start = point(minx, miny);
      auto end   = point(maxx, maxy);
      astar_dump(g.dmap, goal.at, start, end);
#endif
    }

    for (auto &result : paths) {
      std::vector< point > new_move_path;

      for (point p : result.path) {
        if ((p.x == mid_at.x) && (p.y == mid_at.y)) {
          continue;
        }
        new_move_path.push_back(p);
      }

      if (new_move_path.empty()) {
        if (level->is_sticky(mid_at.x, mid_at.y)) {
          AI_LOG("Stuck in something");
          if (is_player()) {
            game->tick_begin("Try to break free");
          }
          return true;
        }
        continue;
      }

      std::reverse(new_move_path.begin(), new_move_path.end());

      auto p = new_move_path[ new_move_path.size() - 1 ];

      std::string goal_path_str = "";
      for (auto p1 : new_move_path) {
        goal_path_str += p1.to_string() + " ";
      }

      bool logged_one = false;
      FOR_ALL_THINGS_THAT_INTERACT(level, it, p.x, p.y)
      {
        if (it->is_changing_level || it->is_hidden || it->is_falling || it->is_jumping) {
          continue;
        }

        if (it == this) {
          continue;
        }

        if (it->get_immediate_spawned_owner_id().ok()) {
          continue;
        }

        logged_one = true;
        AI_LOG("", "Found a goal", it);
      }
      FOR_ALL_THINGS_END();

      if (! logged_one) {
        FOR_ALL_THINGS(level, it, p.x, p.y)
        {
          if (it->is_changing_level || it->is_hidden || it->is_the_grid || it->is_tmp_thing() || it->is_falling ||
              it->is_jumping) {
            continue;
          }

          if (it == this) {
            continue;
          }

          if (it->get_immediate_spawned_owner_id().ok()) {
            continue;
          }

          logged_one = true;
          AI_LOG("", "Found a non active-thing goal", it);
        }
        FOR_ALL_THINGS_END();
      }

      if (! logged_one) {
        AI_LOG("", "Found a non-thing goal");
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
        if (is_player()) {
          if (! game->tick_requested.empty()) {
            return true;
          }
        } else {
          return true;
        }
      } else {
        monst_aip->move_path = new_move_path;
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
int Thing::ai_dmap_can_see_init(int minx, int miny, int maxx, int maxy, int search_type, bool check_for_interrupts)
{
  TRACE_AND_INDENT();
  std::array< std::array< uint8_t, MAP_WIDTH >, MAP_HEIGHT > can_jump = {};
  point                                                      start((int) mid_at.x, (int) mid_at.y);
  auto                                                       dmap_can_see      = get_dmap_can_see();
  bool                                                       jump_allowed      = false;
  int                                                        something_changed = 0;

  AI_LOG("", "Init dmap");

  for (int y = miny; y < maxy; y++) {
    for (int x = minx; x < maxx; x++) {
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

  if (! ai_is_able_to_jump()) {
    jump_allowed = false;
  }

  for (int y = miny; y < maxy; y++) {
    for (int x = minx; x < maxx; x++) {
      point p(x, y);
      if (! get(monst_aip->can_see_ever.can_see, x, y)) {
        continue;
      }

      if (! ai_obstacle_for_me(p)) {
        set(dmap_can_see->val, x, y, DMAP_IS_PASSABLE);
        continue;
      }

      if (jump_allowed) {
        if (is_hazardous_to_me(p)) {
          set(dmap_can_see->val, x, y, DMAP_IS_PASSABLE);
        }
      }

      //
      // Can jump but only if not tired.
      //
      if (jump_allowed && (get_stamina() > get_stamina_max() / 2)) {
        //
        // Trace all possible jump paths to see if we can jump over
        //
        if (is_hazardous_to_me(p) || ai_obstacle_for_me(p)) {
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
            if (is_hazardous_to_me(jump_begin) || ai_obstacle_for_me(jump_begin)) {
              continue;
            }

            if (is_hazardous_to_me(jump_end) || ai_obstacle_for_me(jump_end)) {
              continue;
            }

            //
            // Must be able to see the begin/end.
            //
            if (! get(monst_aip->can_see_ever.can_see, jump_begin.x, jump_begin.y)) {
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

      continue;
    }
  }

  //
  // Grow the search space beyond the light
  //
  std::array< std::array< bool, MAP_WIDTH >, MAP_HEIGHT > walked = {};
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

        if (! get(monst_aip->can_see_ever.can_see, p.x, p.y)) {
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

            if (! get(monst_aip->can_see_ever.can_see, o.x, o.y) && ! get(monst_aip->interrupt_map.val, o.x, o.y)) {

              FOR_ALL_THINGS_THAT_INTERACT(level, it, o.x, o.y)
              {
                if (it->is_changing_level || it->is_hidden || it->is_falling || it->is_jumping) {
                  continue;
                }

                if (worth_collecting(it) || worth_eating(it) || is_dangerous(it)) {
                  set(monst_aip->interrupt_map.val, o.x, o.y, game->tick_current);
                  if (check_for_interrupts) {
                    something_changed++;
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

  //
  // Not sure what this really does
  //
  if (check_for_interrupts) {
    auto seen_map = get_seen_map();
    for (int y = miny; y < maxy; y++) {
      for (int x = minx; x < maxx; x++) {

        if (get(can_jump, x, y)) {
          set(dmap_can_see->val, x, y, DMAP_IS_PASSABLE);
          continue;
        }

        //
        // Ignore interruptions too far away
        //
        auto  dist     = distance(mid_at, fpoint(x, y));
        float max_dist = ai_scent_distance();
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
          }
        } else if (dmap_score == DMAP_IS_WALL) {
          //
          // Was seen but now cannot see; did something close?
          //
          if (seen_when) {
            something_changed++;
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

  auto threat = most_dangerous_visible_thing_get();
  if (threat) {
    if (threat && (is_dangerous(threat) || is_enemy(threat) || is_to_be_avoided(threat))) {
      something_changed = true;
    }
  }

  IF_DEBUG3
  {
    if (is_player()) {
      log("Dmap can see:");
      dmap_print(dmap_can_see);
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
  TRACE_AND_INDENT();
  auto dmap_can_see = get_dmap_can_see();
  auto age_map      = get_age_map();

  for (int y = miny; y < maxy; y++) {
    for (int x = minx; x < maxx; x++) {
      point p(x, y);

      if (! get(monst_aip->can_see_currently.can_see, p.x, p.y)) {
        continue;
      }

      if (get(dmap_can_see->val, x, y) == DMAP_IS_WALL) {
        continue;
      }

      bool got_a_goal   = false;
      bool avoiding     = false;
      int  terrain_cost = get_terrain_cost(p);
      int  total_score  = -(int) terrain_cost;

      std::string last_msg;

      FOR_ALL_THINGS_THAT_INTERACT(level, it, p.x, p.y)
      {
        last_msg = "";

        if (it->is_changing_level || it->is_hidden || it->is_falling || it->is_jumping) {
          continue;
        }

        if (it == this) {
          continue;
        }

        if (it->get_immediate_owner_id().ok()) {
          continue;
        }

        //
        // Don't attack your master
        //
        if (it->is_minion_generator() && (get_top_minion_owner() == this)) {
          continue;
        }

        //
        // Don't attack your fellow minion
        //
        if (it->is_minion() && (it->get_top_minion_owner() == get_top_minion_owner())) {
          continue;
        }

        auto goal_penalty = get_goal_penalty(it);

        if (is_player()) {
          it->con("seen");
        }

        //
        // Worse terrain, less preferred. Higher score, more preferred.
        //
        auto my_health         = get_health();
        auto it_health         = it->get_health();
        auto health_diff       = it_health - my_health;
        bool got_one_this_tile = false;

        //
        // Don't allow of attacking monsts from memory if the player or
        // robot
        //
        auto lit_recently = get(monst_aip->can_see_currently.can_see, it->mid_at.x, it->mid_at.y);

        if (is_starving) {
          if (worth_eating(it)) {
            //
            // If starving, prefer the thing with most health
            //
            SCORE_ADD(it_health - goal_penalty, "eat-it");
            add_goal_penalty(it);
            got_one_this_tile = true;
          }
        } else if (is_hungry) {
          if (worth_eating(it) && ! is_dangerous(it)) {
            //
            // Prefer easy food over attacking the player and prefer
            // the player over a monster. Factor in health so we will
            // go for the easier kill in preference.
            //
            if (it->is_player()) {
              SCORE_ADD(it_health / 2 - goal_penalty, "eat-player");
              add_goal_penalty(it);
              got_one_this_tile = true;
            } else if (it->is_alive_monst()) {
              SCORE_ADD(it_health / 2 - goal_penalty, "eat-monst");
              add_goal_penalty(it);
              got_one_this_tile = true;
            } else {
              SCORE_ADD(it_health / 2 - goal_penalty, "eat-food");
              add_goal_penalty(it);
              got_one_this_tile = true;
            }
          }
        }

        if (ai_is_item_collector()) {
          if (it->is_collectable()) {
            auto score = worth_collecting(it);
            if (score > 0) {
              SCORE_ADD(score - goal_penalty, "collect");
              add_goal_penalty(it);
              got_one_this_tile = true;
              AI_LOG("", "Is considering collecting", it);
            } else {
              AI_LOG("", "Is not considering collecting", it);
            }
          }
        }

        //
        // Need more work before monsts can collect keys as they will be auto collected.
        //
        if (it->is_key()) {
          if (ai_is_able_to_collect_keys()) {
            SCORE_ADD(1000 - goal_penalty, "collect-key");
            add_goal_penalty(it);
            got_one_this_tile = true;
          }
        }

        if (it->is_door() && ! it->is_open) {
          if (ai_is_able_to_open_doors() || ai_is_able_to_break_down_doors()) {
            if (get_keys()) {
              SCORE_ADD(1000 - goal_penalty, "open-door-with-key");
              add_goal_penalty(it);
            } else {
              SCORE_ADD(100 - goal_penalty, "open-door");
              add_goal_penalty(it);
            }
            got_one_this_tile = true;
          }
        }

        if (! it->is_dead) {
          bool  avoid    = false;
          auto  dist     = distance(mid_at, it->mid_at);
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
              if ((is_to_be_avoided(it) || is_dangerous(it)) && (get_health() < get_health_max() / 2)) {
                //
                // Low on health. Best to avoid this enemy.
                //
                if (cannot_avoid(it)) {
                  SCORE_ADD((int) (max_dist - dist) * 200 - goal_penalty, "attack-enemy-i-cannot-avoid");
                  add_goal_penalty(it);
                  AI_LOG("Cannot avoid enemy", it);
                } else {
                  avoid = true;
                  SCORE_ADD(-(int) ((max_dist - dist) + it_health) * 200 - goal_penalty, "avoid-enemy");
                  add_goal_penalty(it);
                }
                got_one_this_tile = true;
              } else {
                //
                // The closer an enemy is (something that attacked us), the
                // higher the score
                //
                avoid = false;
                SCORE_ADD((int) (max_dist - dist) * 200 - goal_penalty, "attack-enemy");
                add_goal_penalty(it);
                got_one_this_tile = true;
              }
            } else if (! avoid && (dist < ai_avoid_distance()) && will_avoid_monst(it)) {
              //
              // Monsts we avoid are more serious threats
              //
              if (cannot_avoid(it)) {
                SCORE_ADD((int) (max_dist - dist) * 100 - goal_penalty, "attack-monst-i-cannot-avoid");
                add_goal_penalty(it);
                AI_LOG("Cannot avoid monst", it);
              } else {
                avoid = true;
                SCORE_ADD(-(int) ((max_dist - dist) + it_health) * 200 - goal_penalty, "avoid-monst");
                add_goal_penalty(it);
              }
            } else if (! avoid && ai_is_able_to_attack_generators() && it->is_minion_generator()) {
              //
              // Very close, high priority attack
              //
              SCORE_ADD((int) (max_dist - dist) * 1000 - goal_penalty, "attack-nearby-generator");
              add_goal_penalty(it);
              got_one_this_tile = true;
            } else if (! avoid && possible_to_attack(it) && ! will_avoid_hazard(it)) {
              //
              // Hazard check above is for cleaners standing on their
              // pool of acid. Do we want to attack that without good
              // reason?
              //
              if (dist < 2) {
                //
                // Very close, high priority attack
                //
                SCORE_ADD((int) (max_dist - dist) * 100 - goal_penalty, "attack-nearby-monst");
                add_goal_penalty(it);
                got_one_this_tile = true;
              } else if (dist < max_dist) {
                //
                // Further away close, lower priority attack
                //
                if (will_avoid_monst(it)) {
                  //
                  // Nope
                  //
                } else {
                  SCORE_ADD((int) (max_dist - dist) * 10 - goal_penalty, "attack-maybe-monst");
                  add_goal_penalty(it);
                  got_one_this_tile = true;
                }
              }
            }
          }

          if (! avoid && it->is_spiderweb() && ! dist) {
            //
            // Very close, high priority attack
            //
            SCORE_ADD(666, "get-out-of-web");
            add_goal_penalty(it);
            got_one_this_tile = true;
          }

          if (avoid) {
            AI_LOG("Needs to avoid", it);
            add_avoid(it);

            bool got_avoid = false;
            auto d         = ai_avoid_distance();
            if (! d) {
              d = 2;
            }

            for (auto dx = -d; dx <= d; dx++) {
              for (auto dy = -d; dy <= d; dy++) {

                point p(mid_at.x + dx, mid_at.y + dy);
                if (level->is_oob(p)) {
                  continue;
                }

                if (! dx && ! dy) {
                  continue;
                }

                float dist = distance(mid_at + fpoint(dx, dy), it->mid_at);
                if (dist < ai_avoid_distance()) {
                  continue;
                }

                if (ai_obstacle_for_me(p)) {
                  continue;
                }

                int terrain_cost = get_terrain_cost(p);
                int total_score  = -(int) terrain_cost;
                total_score += dist * 100;
                total_score += 1000;
                goals.insert(Goal(total_score, p, last_msg));
                set(dmap_can_see->val, p.x, p.y, DMAP_IS_GOAL);
                IF_DEBUG3
                {
                  auto s = string_sprintf("Avoid goal (score %d) @(%d,%d)", total_score, p.x, p.y);
                  AI_LOG("", s);
                }
                got_avoid = true;
              }
            }

            //
            // Try again with more lenient checks
            //
            if (! got_avoid) {
              for (auto dx = -d; dx <= d; dx++) {
                for (auto dy = -d; dy <= d; dy++) {

                  point p(mid_at.x + dx, mid_at.y + dy);
                  if (level->is_oob(p)) {
                    continue;
                  }

                  if (ai_obstacle_for_me(p)) {
                    continue;
                  }

                  float dist         = distance(mid_at + fpoint(dx, dy), it->mid_at);
                  int   terrain_cost = get_terrain_cost(p);
                  int   total_score  = -(int) terrain_cost;
                  total_score += dist * 100;
                  total_score += 1000;
                  goals.insert(Goal(total_score, p, last_msg));
                  set(dmap_can_see->val, p.x, p.y, DMAP_IS_GOAL);
                  IF_DEBUG3
                  {
                    auto s = string_sprintf("Avoid goal (2) (score %d) @(%d,%d)", total_score, p.x, p.y);
                    AI_LOG("", s);
                  }

                  got_avoid = true;
                }
              }
            }

            //
            // Try again with even more lenient checks
            //
            if (! got_avoid) {
              for (auto dx = -d; dx <= d; dx++) {
                for (auto dy = -d; dy <= d; dy++) {

                  point p(mid_at.x + dx, mid_at.y + dy);
                  if (level->is_oob(p)) {
                    continue;
                  }

                  if (level->is_obs_wall_or_door(p)) {
                    continue;
                  }

                  float dist         = distance(mid_at + fpoint(dx, dy), it->mid_at);
                  int   terrain_cost = get_terrain_cost(p);
                  int   total_score  = -(int) terrain_cost;
                  total_score += dist * 100;
                  total_score += 1000;
                  goals.insert(Goal(total_score, p, last_msg));
                  set(dmap_can_see->val, p.x, p.y, DMAP_IS_GOAL);
                  IF_DEBUG3
                  {
                    auto s = string_sprintf("Avoid goal (3) (score %d) @(%d,%d)", total_score, p.x, p.y);
                    AI_LOG("", s);
                  }

                  got_avoid = true;
                }
              }
            }

            //
            // This is an anti goal
            //
            if (got_avoid) {
              avoiding = true;
              AI_LOG("", "Is avoiding");
              break;
            } else {
              AI_LOG("Could not avoid, so attack", it);
            }
          }

          if (! got_one_this_tile) {
            //
            // No hunting monsters we cannot see just because we have visited that area before.
            //
            // Well this is true for the player. Monsters, we're lenient.
            //
            if (lit_recently) {
              //
              // How aggressive are we?
              //
              if ((int) pcg_random_range(0, 1000) < tp()->ai_unprovoked_attack_chance_d1000()) {
                if (possible_to_attack(it)) {
                  SCORE_ADD(-health_diff - goal_penalty, "can-attack-monst");
                  add_goal_penalty(it);
                }
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
      }
      FOR_ALL_THINGS_END();

      if (avoiding) {
        set(dmap_can_see->val, x, y, DMAP_IS_WALL);
      } else if (got_a_goal) {
        goals.insert(Goal(total_score, p, last_msg));
        IF_DEBUG3
        {
          auto s = string_sprintf("Add goal (score %d) @(%d,%d) %s", total_score, p.x, p.y, last_msg.c_str());
          AI_LOG("", s);
        }
        set(dmap_can_see->val, x, y, DMAP_IS_GOAL);
      } else if (terrain_cost) {
        set(dmap_can_see->val, x, y, (uint8_t) terrain_cost);
      } else {
        set(dmap_can_see->val, x, y, DMAP_IS_PASSABLE);
      }
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
  TRACE_AND_INDENT();
  point start((int) mid_at.x, (int) mid_at.y);

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

    auto  dist     = distance(make_fpoint(p), mid_at);
    float max_dist = ai_scent_distance();

    //
    // Look as far as our memory and lighting permits
    //
    if (! is_player()) {
      if (dist >= max_dist) {
        continue;
      }
    }

    if (level->is_obs_wall_or_door(p.x, p.y)) {
      continue;
    }

    //
    // If an unvisited tile is next to a visited one, consider that tile.
    //
    if (! get(monst_aip->can_see_ever.can_see, p.x, p.y)) {
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
          if (! ai_is_able_to_open_doors() && ! ai_is_able_to_break_down_doors()) {
            continue;
          }
        } else if (level->is_secret_door(o)) {
          if (! ai_is_able_to_detect_secret_doors_when_close()) {
            continue;
          }
          if (dist > ROBOT_CAN_SEE_SECRET_DOOR_DISTANCE) {
            continue;
          }
        } else if (level->is_descend_sewer(o)) {
          //
          // Worth investigating unless over
          //
          if (! ai_is_exit_finder()) {
            continue;
          }
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
          if (! ai_is_exit_finder()) {
            continue;
          }
          if ((o.x == mid_at.x) && (o.y == mid_at.y)) {
            continue;
          }
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
          if (! ai_is_exit_finder()) {
            continue;
          }
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
          if (! ai_is_exit_finder()) {
            continue;
          }
          if ((o.x == mid_at.x) && (o.y == mid_at.y)) {
            continue;
          }
          if (search_type < SEARCH_TYPE_LAST_RESORTS_NO_JUMP) {
            continue;
          }
        } else {
          //
          // If lit then we can already see it, so not worth exploring.
          //
          if (get(monst_aip->can_see_ever.can_see, o.x, o.y)) {
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

#if 1
  if (is_player()) {
    con("Search type %d", search_type);
    for (int y = 0; y < MAP_HEIGHT; y++) {
      for (int x = 0; x < MAP_WIDTH; x++) {
        if ((x == (int) mid_at.x) && (y == (int) mid_at.y)) {
          if (level->is_lit_ever(x, y)) {
            printf("* ");
          } else {
            printf("o ");
          }
          continue;
        }
        for (auto p : can_reach_cands) {
          if ((x == p.x) && (y == p.y)) {
            printf("c ");
            goto next;
          }
        }
        if (get(walked, x, y)) {
          if (level->is_obs_wall_or_door(x, y)) {
            if (level->is_door(x, y)) {
              printf("D");
            } else {
              printf("X");
            }
          } else {
            printf("_");
          }
        } else {
          if (level->is_obs_wall_or_door(x, y)) {
            if (level->is_door(x, y)) {
              printf("d");
            } else {
              printf("x");
            }
          } else {
            printf(" ");
          }
        }
        if (get(monst_aip->can_see_currently.can_see, x, y)) {
          printf(".");
        } else if (get(monst_aip->can_see_ever.can_see, x, y)) {
          printf(",");
        } else {
          printf(" ");
        }
      next:
        continue;
      }
      printf("\n");
    }
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
    // No search destinations that are, for example, a chasm
    //
    if (is_hazardous_to_me(p)) {
      continue;
    }

    //
    // Prefer easier terrain
    //
    int terrain_cost = get_terrain_cost(p);
    int total_score  = -(int) terrain_cost;

    //
    // Prefer closer
    //
    float dist = distance(start, p);
    total_score -= dist * dist;

    //
    // Choose doors etc... as a last resort when nothing else
    //
    if (ai_is_level_explorer()) {
      if (level->is_door(p.x, p.y)) {
        total_score -= 100;
      }
    }

    if (ai_is_exit_finder()) {
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

    IF_DEBUG3
    {
      auto s = string_sprintf("Add search cand (score %d) @(%d,%d)", total_score, p.x, p.y);
      AI_LOG("", s);
    }
    goals.insert(Goal(total_score, p, "search cand"));
  }
}

bool Thing::ai_choose_immediately_adjacent_goal(void)
{
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

      fpoint at(mid_at.x + dx, mid_at.y + dy);
      if (level->is_oob(at)) {
        continue;
      }

      FOR_ALL_THINGS(level, it, at.x, at.y)
      /* { */
      if (it->is_door() && ! it->is_open) {
        if (ai_is_able_to_open_doors()) {
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

        if (ai_is_able_to_break_down_doors()) {
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
            move(mid_at, up, down, left, right, attack, wait, shove_allowed, attack_allowed);
          }
          return true;
        }
      }

      if (ai_is_able_to_break_out_of_webs()) {
        if (it->is_spiderweb() && (it->mid_at == mid_at)) {
          //
          // Try hitting the web
          //
          left           = dx < 0;
          right          = dx > 0;
          up             = dy < 0;
          down           = dy > 0;
          attack         = true;
          attack_allowed = true;
          AI_LOG("Trying to break out of a web", "Trying to break out of a web", it);
          if (is_player()) {
            player_tick(left, right, up, down, attack, wait, jump);
          } else {
            move(mid_at, up, down, left, right, attack, wait, shove_allowed, attack_allowed);
          }
          return true;
        }
      }
      /* } */
      FOR_ALL_THINGS_END();

      if (ai_is_item_collector()) {
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

bool Thing::ai_tick(bool recursing)
{
  TRACE_AND_INDENT();
  dbg3("AI tick");
  TRACE_AND_INDENT();

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
  const float dx = ai_scent_distance();
  const float dy = dx;

  int minx = std::max(0, (int) (mid_at.x - dx));
  int maxx = std::min(MAP_WIDTH, (int) (mid_at.x + dx));
  int miny = std::max(0, (int) (mid_at.y - dy));
  int maxy = std::min(MAP_HEIGHT, (int) (mid_at.y + dy));

  if (is_player()) {
    minx = 0;
    maxx = MAP_WIDTH;
    miny = 0;
    maxy = MAP_HEIGHT;
  }

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
  auto threat = most_dangerous_visible_thing_get();

  //
  // Update what we can see
  //
  bool light_walls = true;
  level->fov_calculete(&monst_aip->can_see_currently, mid_at.x, mid_at.y, ai_vision_distance(), light_walls);

  //  if (! recursing) {
  for (int y = miny; y < maxy; y++) {
    for (int x = minx; x < maxx; x++) {
      if (monst_aip->can_see_currently.can_see[ x ][ y ]) {
        // IF_DEBUG3 { (void) level->thing_new("ai_path2", fpoint(x, y)); }
        set(monst_aip->can_see_ever.can_see, x, y, true);
      }
    }
  }
  //  }

#if 1
  if (is_player()) {
    con("Can see fov:");
    for (int y = 0; y < MAP_HEIGHT; y++) {
      for (int x = 0; x < MAP_WIDTH; x++) {
        if ((x == (int) mid_at.x) && (y == (int) mid_at.y)) {
          printf("*");
        } else {
          if (get(monst_aip->can_see_currently.can_see, x, y)) {
            if (level->is_door(x, y)) {
              printf("D");
            } else if (level->is_obs_wall_or_door(x, y)) {
              printf("X");
            } else {
              printf(".");
            }
          } else if (get(monst_aip->can_see_ever.can_see, x, y)) {
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
  switch (monst_infop->monst_state) {
    case MONST_STATE_IDLE :
      {
        //
        // If we're absolutely exhausted, we must rest, threat or no threat
        //
        if (is_able_to_tire() && ! get_stamina()) {
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
        if (get_health() < get_health_max() / 3) {
          if (can_eat_something()) {
            AI_LOG("Very low on health, forced to rest");
            if (is_player()) {
              game->tick_begin("Robot needs to rest, very low on health");
            }
            ai_change_state(MONST_STATE_RESTING, "need to rest, very low on health");
            return true;
          }
        }

        //
        // Look for doors or things to collect, if not being attacked.
        //
        if (threat && (is_dangerous(threat) || is_enemy(threat) || is_to_be_avoided(threat))) {
          //
          // No resting when in danger
          //
          if (is_player()) {
            AI_LOG("A threat is near", threat);
          }
        } else {
          //
          // Not under threat, so we can think about doing some other
          // housecleaning tasks.
          //
          AI_LOG("Idle, look for something to do");

          //
          // Be a bit more careful if there is somethjing that might want to
          // attack us, even if it is not a threat. i.e. a harmless goblin
          // could push us off of a cliff while we're doing other stuff.
          //
          if (! any_unfriendly_monst_visible()) {
            //
            // Can we enchant something?
            //
            if (ai_is_able_to_enchant_weapons()) {
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
            if (ai_is_able_to_learn_skills()) {
              if (get_skillstone_count() && can_learn_something()) {
                AI_LOG("Try to use a skillstone");
                if (is_player()) {
                  game->tick_begin("Robot can learn something");
                }
                ai_change_state(MONST_STATE_USING_SKILLSTONE, "can learn something");
                return true;
              }
            }
          }

          //
          // Are we tired and need to rest?
          //
          if (is_able_to_tire() && (get_stamina() < get_stamina_max() / 10)) {
            AI_LOG("Needs to rest, low on stamina");
            if (is_player()) {
              game->tick_begin("Robot needs to rest, low on stamina");
            }
            ai_change_state(MONST_STATE_RESTING, "need to rest, low on stamina");
            return true;
          }

          //
          // Can we switch to a better weapon?
          //
          Thingp best_weapon;
          get_carried_weapon_highest_value(&best_weapon);
          if (best_weapon && (best_weapon != weapon_get())) {
            if (wield(best_weapon)) {
              AI_LOG("Change weapon", best_weapon);
              if (is_player()) {
                game->tick_begin("Robot is changing weapon");
              }
              return true;
            }

            AI_LOG("Failed to change weapon", best_weapon);
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
        int search_type_max;
        if (ai_is_able_to_jump()) {
          if (ai_is_level_explorer()) {
            if (ai_is_exit_finder()) {
              search_type_max = SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED + 1;
            } else {
              search_type_max = SEARCH_TYPE_GLOBAL_JUMP_ALLOWED + 1;
            }
          } else {
            search_type_max = SEARCH_TYPE_LOCAL_JUMP_ALLOWED + 1;
          }
        } else {
          if (ai_is_level_explorer()) {
            if (ai_is_exit_finder()) {
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
            if (monst_aip->move_path.size()) {
              ai_change_state(MONST_STATE_MOVING, "found a new goal");
            }
            return true;
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
        // What is the point of it all?
        //
        AI_LOG("Nothing to do at all.");
        if (is_player()) {
          wid_actionbar_robot_mode_off();
        }
        return false;
      }
      break;

    case MONST_STATE_MOVING :
      {
        //
        // Check for interrupts
        //
        AI_LOG("", "Check for interruptions");
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

        //
        // Finished the move?
        //
        if (monst_aip->move_path.empty()) {
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
          path_pop_next_move();
        }
        return true;
      }
      break;
    case MONST_STATE_RESTING :
      {
        //
        // If resting, check if we are rested enough.
        //
        if ((get_health() >= (get_health_max() / 4) * 3) && (get_stamina() >= (get_stamina_max() / 4) * 3)) {
          AI_LOG("Rested enough. Back to work.");
          if (is_player()) {
            game->tick_begin("Robot has rested enough");
          }
          ai_change_state(MONST_STATE_IDLE, "rested enough");
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

        //
        // If we are able to lift a sword and can see a threat, go back to
        // fighting.
        //
        if (get_stamina()) {
          if (threat && (is_dangerous(threat) || is_enemy(threat) || is_to_be_avoided(threat))) {
            AI_LOG("Seen a threat. Stop resting.");
            if (is_player()) {
              game->tick_begin("Robot sees a nearby threat, stop resting");
            }
            ai_change_state(MONST_STATE_IDLE, "threat nearby, stop resting");
            return true;
          }
        }

        if (get_stamina() >= (get_stamina_max() / 4) * 3) {
          AI_LOG("Seen a threat. Stop resting.");
          if (is_player()) {
            game->tick_begin("Robot has recovered stamina");
          }
          ai_change_state(MONST_STATE_IDLE, "threat nearby, stop resting");
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
          if (game->request_remake_inventory) {
            return true;
          }
        }

        //
        // Then close it. This is really just visual feedback.
        //
        ai_change_state(MONST_STATE_IDLE, "close inventory");
        if (is_player()) {
          game->tick_begin("Robot finished collecting");
        }
      }
      break;

    case MONST_STATE_USING_ENCHANTSTONE :
      {
        //
        // Enchant a random item.
        //
        enchant_random_item();
        ai_change_state(MONST_STATE_IDLE, "enchanted");
        if (is_player()) {
          game->tick_begin("Robot finished enchanting");
        }
      }
      break;

    case MONST_STATE_USING_SKILLSTONE :
      {
        //
        // Choose a skill
        //
        learn_random_skill();
        ai_change_state(MONST_STATE_IDLE, "added skill");
        if (is_player()) {
          game->tick_begin("Robot finished adding skills");
        }
      }
      break;
  }

  if (do_something) {
    if (is_player()) {
      player_tick(left, right, up, down, attack, wait, jump);
    } else {
      move(mid_at, up, down, left, right, attack, wait, false, false);
    }
  }

  return true;
}

void Thing::ai_change_state(int new_state, const std::string &why)
{
  TRACE_AND_INDENT();
  if (monst_infop->monst_state == new_state) {
    return;
  }

  std::string to;
  std::string from;
  switch (new_state) {
    case MONST_STATE_IDLE : to = "IDLE"; break;
    case MONST_STATE_MOVING : to = "MOVING"; break;
    case MONST_STATE_RESTING : to = "RESTING"; break;
    case MONST_STATE_OPEN_INVENTORY : to = "OPEN-INVENTORY"; break;
    case MONST_STATE_USING_ENCHANTSTONE : to = "USING-ENCHANTSTONE"; break;
    case MONST_STATE_USING_SKILLSTONE : to = "USING-SKILLSTONE"; break;
  }

  switch (monst_infop->monst_state) {
    case MONST_STATE_IDLE : from = "IDLE"; break;
    case MONST_STATE_MOVING : from = "MOVING"; break;
    case MONST_STATE_RESTING : from = "RESTING"; break;
    case MONST_STATE_OPEN_INVENTORY :
      from = "OPEN-INVENTORY";
      if (is_player()) {
        wid_thing_info_fini();
        wid_inventory_init();
      }
      break;
    case MONST_STATE_USING_ENCHANTSTONE :
      from = "USING-ENCHANTSTONE";
      if (is_player()) {
        wid_enchant_destroy();
        wid_thing_info_fini();
        wid_inventory_init();
      }
      break;
    case MONST_STATE_USING_SKILLSTONE :
      from = "USING-SKILLSTONE";
      if (is_player()) {
        wid_skill_choose_destroy();
        wid_thing_info_fini();
        wid_inventory_init();
      }
      break;
  }

  IF_DEBUG3
  {
    auto s = string_sprintf("State change %s -> %s, reason: %s", from.c_str(), to.c_str(), why.c_str());
    AI_LOG("", s);
  }

  monst_infop->monst_state = new_state;
  switch (new_state) {
    case MONST_STATE_IDLE : clear_move_path("State is now idle"); break;
    case MONST_STATE_MOVING : break;
    case MONST_STATE_RESTING : break;
    case MONST_STATE_OPEN_INVENTORY :
      if (is_player()) {
        game->change_state(Game::STATE_MOVING_ITEMS);
        game->request_remake_inventory = true;
        game->wid_thing_info_create(game->level->player, false);
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
  TRACE_AND_INDENT();
  dbg("AI");
  TRACE_AND_INDENT();
  point start((int) mid_at.x, (int) mid_at.y);

  //
  // If on fire, try and put it out!
  //
  if (is_on_fire() && hates_fire()) {
    if (is_intelligent()) {
      if (ai_on_fire()) {
        return;
      }
    }
  }

  //
  // If somewhere bad, escape
  //
  if (get_terrain_cost(start) >= DMAP_LESS_PREFERRED_TERRAIN) {
    dbg("On bad terrain, escape");
    if (ai_escape()) {
      return;
    }

    monst_infop->wander_target = point(0, 0);
    dbg("Cannot escape, try to wander");
    if (ai_wander()) {
      return;
    }
  }

  //
  // If going somewhere, continue
  //
  if (monst_infop->wander_target != point(0, 0)) {
    if (pcg_random_range(0, 100) < 50) {
      dbg("Try to continue wander");
      if (ai_wander()) {
        return;
      }
    }
  }

  //
  // Find the best goal to go to
  //
  if (ai_choose_goal()) {
    monst_infop->wander_target = point(0, 0);
    return;
  }

  //
  // If we get here we found no goal. Try to wander.
  //
  if (ai_wander()) {
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

int Thing::ai_choose_goal(void) { return ai_tick(); }
