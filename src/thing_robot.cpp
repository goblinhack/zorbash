//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
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
#include "my_wid_actionbar.h"
#include "my_player.h"

#define GOAL_ADD(score, msg)                                               \
        total_score += (score);                                            \
        got_a_goal = true;                                                 \
        dbg2(" add goal (%d,%d) score %d %s, %s",                          \
             p.x + minx, p.y + miny, score, msg, it->to_string().c_str()); \

//
// Look at all the things that are currently visited (read that as light rays
// have touched them) and choose the best goal. Create a path to that goal for
// the thing to walk.
//
bool Thing::robot_ai_create_path_to_goal (int minx, int miny, int maxx, int maxy)
{_
    point start((int)mid_at.x, (int)mid_at.y);

    dbg("Choose goal");
_
    //
    // Find all the possible goals. Higher scores, lower costs are preferred
    //
    std::multiset<Goal> main_goals;
    std::multiset<Goal> search_goals;
    std::multiset<Goal> open_door_goals;
    auto dmap_can_see = get_dmap_can_see();
    auto age_map = get_age_map();

    //
    // Initialize basic visibility and things that are lit and can be seen
    //
    dbg("Choose goals (higher scores, lower costs are preferred):");
    robot_ai_init_can_see_dmap(minx, miny, maxx, maxy);
    robot_ai_choose_initial_goals(main_goals, minx, miny, maxx, maxy);

    std::list<GoalMap> goalmaps;
    goalmaps.push_back(GoalMap{main_goals, dmap_can_see});

    //
    // Even if we found main goals we need to add backup ones in case any
    // of the main ones are not reachable.
    //
    if (is_player()) {
        robot_ai_init_can_see_dmap(minx, miny, maxx, maxy);
        robot_ai_choose_search_goals(search_goals);
        goalmaps.push_back(GoalMap{search_goals, dmap_can_see});

        //
        // Add open door goes in case all of the wander goals are also not
        // reachable.
        //
        robot_ai_choose_search_goals(open_door_goals, true);
        goalmaps.push_back(GoalMap{open_door_goals, dmap_can_see});
    }

    //
    // No goals?
    //
    if (goalmaps.empty()) {
        dbg2("No goals found");
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

        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
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

        dbg4("Sorted goals, %d (best) .. %d (worst)",
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
                score *= DMAP_IS_PASSABLE - 2;
                score++;
            }

            assert(score <= DMAP_IS_PASSABLE);
            uint8_t score8 = (int)score;
            set(g.dmap->val, goal_target.x, goal_target.y, score8);

            dbg2(" scale goal (%d,%d) score %d to dmap score %d",
                (int)minx + goal.at.x, (int)miny + goal.at.y, 
                (int)orig_score, (int)score8);
        }

        //
        // Record we've been here.
        //
        set(age_map->val, start.x, start.y, game->tick_current);

        //
        // Find the best next-hop to the best goal.
        //
#ifdef ENABLE_DEBUG_AI_VERBOSE
        if (unlikely(g_opt_debug3)) {
            dbg("Goals:");
            dmap_print(g.dmap,
                       point(start.x - minx, start.y - miny),
                       point(0, 0),
                       point(maxx - minx, maxy - miny));
        }
#endif

        //
        // Make sure we do not want to stay in the same position by making
        // our current cell passable but the very least preferred it can be.
        //
        if (get(g.dmap->val, start.x - minx, start.y - miny) > 0) {
            set(g.dmap->val, start.x - minx, start.y - miny, DMAP_IS_PASSABLE);
        }

        //
        // Move diagonally if not blocked by walls
        //
        point astar_start(start.x - minx, start.y - miny);

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
            {
                dbg2("ASTAR pre solve:");
                auto start = point(0, 0);
                auto end = point(maxx - minx, maxy - miny);
                astar_dump(g.dmap, goal.at, start, end);
            }
            auto result = astar_solve(path_debug,
                                      astar_start,
                                      astar_end,
                                      g.dmap);
            //
            // Unreachable?
            //
            if (result.cost == std::numeric_limits<int>::max()) {
                dbg2(" goal (%d,%d) score %d -> unreachable", 
                    goal.at.x + minx, goal.at.y + miny,
                    (int)goal.score);
#ifdef ENABLE_DEBUG_AI_ASTAR
                auto start = point(0, 0);
                auto end = point(maxx - minx, maxy - miny);
                astar_dump(g.dmap, goal.at, start, end);
#endif
                continue;
            }

            paths.insert(result);
            dbg2(" goal (%d,%d) score %d -> cost %d", 
                goal.at.x + minx, goal.at.y + miny,
                (int)goal.score, (int)result.cost);

#ifdef ENABLE_DEBUG_AI_ASTAR
            for (auto& p : result.path) {
                set(astar_debug, p.x, p.y, '*');
            }
            auto start = point(0, 0);
            auto end = point(maxx - minx, maxy - miny);
            astar_dump(g.dmap, goal.at, start, end);
#endif
        }

        for (auto& result : paths) {
            std::vector<point> new_move_path;
            for (point p : result.path) {
                p.x += minx;
                p.y += miny;
                if ((p.x == mid_at.x) && (p.y == mid_at.y)) {
                    continue;
                }
                new_move_path.push_back(p);
            }

            if (new_move_path.empty()) {
                continue;
            }

            std::reverse(new_move_path.begin(), new_move_path.end());
            if (is_player()) {
                level->cursor_path_create(new_move_path);
                level->debug_path_create(new_move_path);
                if (cursor_path_pop_first_move()) {
                    return true;
                }
            } else {
                monstp->move_path = new_move_path;
                return true;
            }
        }
    }

    return false;
}

//
// Initialize basic visibility and things that are lit and can be seen
//
int Thing::robot_ai_init_can_see_dmap (int minx, int miny, int maxx, int maxy)
{_
    std::array< std::array<uint8_t, MAP_WIDTH>, MAP_HEIGHT> can_jump = {};
    point start((int)mid_at.x, (int)mid_at.y);
    auto dmap_can_see = get_dmap_can_see();
    auto seen_map = get_seen_map();

    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            point p(x, y);
            auto X = x - minx;
            auto Y = y - miny;

            if (is_player()) {
                if (!level->is_lit_currently(p)) {
                    set(dmap_can_see->val, X, Y, DMAP_IS_WALL);
                    continue;
                }
            }

            if (!ai_obstacle_for_me(p)) {
                set(dmap_can_see->val, X, Y, DMAP_IS_PASSABLE);
                continue;
            }

            if (is_jumper()) {
                //
                // Trace all possible jump paths to see if we can jump over
                //
                if (is_hazardous_to_me(p)) {
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
                        // No jump begin/end from a chasm for example
                        //
                        if (ai_obstacle_for_me(jump_begin)) {
                            continue;
                        }

                        if (ai_obstacle_for_me(jump_end)) {
                            continue;
                        }

                        //
                        // Must be able to see the begin/end.
                        //
                        if (!level->is_lit_currently(jump_begin)) {
                            continue;
                        }

                        if (!level->is_lit_currently(jump_end)) {
                            continue;
                        }

                        //
                        // Too close?
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
                            if (level->is_movement_blocking_hard(j)) {
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
                                set(can_jump, j.x - minx, j.y - miny, DMAP_IS_PASSABLE);
                            }
                        }
                    }
                }
            }

            set(dmap_can_see->val, X, Y, DMAP_IS_WALL);
            continue;
        }
    }

    int something_changed = 0;

    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            auto X = x - minx;
            auto Y = y - miny;
            if (get(can_jump, X, Y)) {
                set(dmap_can_see->val, X, Y, DMAP_IS_PASSABLE);
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
    set(dmap_can_see->val, start.x - minx, start.y - miny, DMAP_IS_GOAL);
    dmap_print(dmap_can_see);
    dmap_process(dmap_can_see, point(0, 0), point(maxx - minx, maxy - miny));
    dmap_print(dmap_can_see);

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

    for (auto y = miny; y < maxy; y++) { for (auto x = minx; x < maxx; x++) {
        point p(x, y);
        auto X = x - minx;
        auto Y = y - miny;

        if (get(dmap_can_see->val, X, Y) == DMAP_IS_WALL) {
            continue;
        }

        bool got_a_goal = false;
        bool avoiding = false;
        int terrain_score = is_less_preferred_terrain(p);
        int total_score = -(int)terrain_score;

        FOR_ALL_INTERESTING_THINGS(level, it, p.x, p.y) {
            if (it == this) { continue; }

            if (it->is_changing_level ||
                it->is_hidden || 
                it->is_falling || 
                it->is_jumping) { 
                if (unlikely(g_opt_debug4)) {
                    dbg2(" ignore %s", it->to_string().c_str());
                }
                continue; 
            }

            dbg2(" consider %s", it->to_string().c_str());

            //
            // Worse terrain, less preferred. Higher score, more preferred.
            //
            auto my_health = get_health();
            auto it_health = it->get_health();
            auto health_diff = it_health - my_health;
            bool got_one_this_tile = false;

            if (is_starving) {
                if (worth_eating(it)) {
                    //
                    // If starving, prefer the thing with most health
                    //
                    GOAL_ADD(it_health, "eat-it");
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
                        GOAL_ADD(it_health / 2, "eat-player");
                        got_one_this_tile = true;
                    } else if (it->is_alive_monst()) {
                        GOAL_ADD(it_health / 2, "eat-monst");
                        got_one_this_tile = true;
                    } else {
                        GOAL_ADD(it_health / 2, "eat-food");
                        got_one_this_tile = true;
                    }
                }
            }

            if (is_treasure_collector()) {
                if (it->is_treasure() || it->is_food()) {
                    auto score = worth_collecting(it);
                    if (score) {
                        GOAL_ADD(score, "collect-treasure");
                        got_one_this_tile = true;
                    }
                }
            }

            //
            // Need more work before monsts can collect keys
            // as they will be auto collected.
            //
            if (is_key_collector()) {
                if (it->is_key()) {
                    GOAL_ADD(1, "collect-key");
                    got_one_this_tile = true;
                }
            }

            if (!it->is_dead) {
                bool avoid = false;

                //
                // If this is something we really want to avoid, like
                // fire, then stay away from it
                //
                if (will_avoid_threat(it)) {
                    if (distance(mid_at, it->mid_at) < 2) {
                        dbg2("Need to avoid threat %s", it->to_string().c_str());
                        avoid = true;
                    }
                }

                //
                // Monsters we avoid are more serious threats
                //
                if (will_avoid_monst(it)) {
                    if (distance(mid_at, it->mid_at) < ai_avoid_distance()) {
                        dbg2("Need to avoid monst %s", it->to_string().c_str());
                        avoid = true;
                    }
                }

                if (is_enemy(it)) {
                    //
                    // The closer an enemy is (something that attacked us), the
                    // higher the score
                    //
                    float dist = distance(it->mid_at, mid_at);
                    float max_dist = ai_scent_distance();

                    if (dist < max_dist) {
                        GOAL_ADD((int)(max_dist - dist) * 10, "attack-enemy");
                    }
                }

                if (avoid) {
                    dbg2("Need to avoid %s", it->to_string().c_str());

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

                            auto dist = distance(mid_at + fpoint(dx, dy), it->mid_at);
                            if (dist < ai_avoid_distance()) {
                                continue;
                            }

                            point p(mid_at.x + dx, mid_at.y + dy);
                            if (ai_obstacle_for_me(p)) {
                                continue;
                            }

                            int terrain_score = is_less_preferred_terrain(p);
                            int total_score = -(int)terrain_score;
                            total_score += dist * dist;
                            goals.insert(Goal(total_score, point(X + dx, Y + dy)));
                            set(dmap_can_see->val, X + dx, Y + dy, DMAP_IS_GOAL);
                            dbg2("Add avoid location offset %d,%d score %d", dx, dy, total_score);

                            got_avoid = true;
                        }
                    }

                    if (!got_avoid) {
                        for (auto dx = -d; dx <= d; dx++) {
                            for (auto dy = -d; dy <= d; dy++) {

                                auto dist = distance(mid_at + fpoint(dx, dy), it->mid_at);
                                point p(mid_at.x + dx, mid_at.y + dy);
                                if (ai_obstacle_for_me(p)) {
                                    continue;
                                }

                                int terrain_score = is_less_preferred_terrain(p);
                                int total_score = -(int)terrain_score;
                                total_score += dist * dist;
                                goals.insert(Goal(total_score, point(X + dx, Y + dy)));
                                set(dmap_can_see->val, X + dx, Y + dy, DMAP_IS_GOAL);
                                dbg2("Add avoid location offset %d,%d score %d", dx, dy, total_score);

                                got_avoid = true;
                            }
                        }
                    }

                    //
                    // This is an anti goal
                    //
                    if (got_avoid) {
                        avoiding = true;
                        break;
                    } else {
                        dbg2("Could not avoid the monst!");
                    }
                }
            }

            if (!got_one_this_tile) {
                if (possible_to_attack(it)) {
                    GOAL_ADD(- health_diff, "can-attack-monst");
                }
            }

            if (will_prefer_terrain(it)) {
                //
                // Prefer certain terrains over others. i.e. I prefer water.
                //
                auto age = get(age_map->val, p.x, p.y);
                if (age - game->tick_current < 10) {
                    GOAL_ADD(1, "preferred-terrain");
                }
            }
        } FOR_ALL_THINGS_END();

        if (avoiding) {
            set(dmap_can_see->val, X, Y, DMAP_IS_WALL);
        } else if (got_a_goal) {
            goals.insert(Goal(total_score, point(X, Y)));
            set(dmap_can_see->val, X, Y, DMAP_IS_GOAL);
        } else if (terrain_score) {
            set(dmap_can_see->val, X, Y, (uint8_t)terrain_score);
        } else {
            set(dmap_can_see->val, X, Y, DMAP_IS_PASSABLE);
        }
    } }
}

//
// We get here if there is nothing visible of interest. Look at the edges of
// what is currently visible and find the most interesting point at that edge
// and then create a path to that edge.
//
void Thing::robot_ai_choose_search_goals (std::multiset<Goal> &goals, bool open_doors)
{_  
    point start((int)mid_at.x, (int)mid_at.y);

    std::array< std::array<bool, MAP_WIDTH>, MAP_HEIGHT> walked = {};
    std::array< std::array<bool, MAP_WIDTH>, MAP_HEIGHT> pushed = {};
    std::deque<point> in;
    std::deque<point> can_reach_cands;
    std::deque<Thingp> out;
    in.push_back(start);
    set(pushed, start.x, start.y, true);

    log("Dmap, to player:");
    auto dmap_to_player = &level->dmap_to_player;
    dmap_print(dmap_to_player);

    log("Dmap, can see:");
    auto dmap_can_see = get_dmap_can_see();
    dmap_print(dmap_can_see);

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
        if (p.x <= MAP_BORDER_ROCK) {
            continue;
        }
        if (p.y <= MAP_BORDER_ROCK) {
            continue;
        }

        //
        // If an unvisited tile is next to a visited one, consider that tile.
        //
        if (!level->is_lit_ever(p.x, p.y)) {
            continue;
        }

        if (level->is_movement_blocking_hard(p.x, p.y)) {
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

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (!dx && !dy) {
                    continue;
                }

                point o(p.x + dx, p.y + dy);

                if (get(walked, o.x, o.y)) {
                    continue;
                }

                if (level->is_door(o)) {
                    //
                    // A locked door is worth investigating
                    //
                } else {
                    //
                    // If lit then we can already see it, so not worth
                    // exploring.
                    //
                    if (level->is_lit_ever(o)) {
                        continue;
                    }

                    if (level->is_movement_blocking_hard(o)) {
                        continue;
                    }
                }

                set(walked, o.x, o.y, true);
                can_reach_cands.push_back(o);
            }
        }
    }

#if 0
    printf("\n");
    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_WIDTH; x++) {
            if ((x == mid_at.x) && (y == mid_at.y)) {
                printf("*");
                continue;
            }
            for (auto p : can_reach_cands) {
                if ((x == p.x) && (y == p.y)) {
                    printf("c");
                    goto next;
                }
            }
            if (get(walked, x, y)) {
                if (level->is_movement_blocking_hard(x, y)) {
                    printf("W");
                } else {
                    printf("w");
                }
            } else {
                if (level->is_movement_blocking_hard(x, y)) {
                    printf("X");
                } else {
                    printf(".");
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
        if (!open_doors) {
            if (level->is_door(p.x, p.y)) {
                continue;
            }
        } else {
            if (!level->is_door(p.x, p.y)) {
                continue;
            }
        }

        //
        // Prefer easier terrain
        //
        int terrain_score = is_less_preferred_terrain(p);
        int total_score = -(int)terrain_score;

        //
        // Prefer closer
        //
        float dist = distance(start, p);
        total_score -= dist * dist;

        //
        // Prefer to look at doors last
        //
        if (level->is_door(p.x, p.y)) {
            total_score -= 1000;
        }

        goals.insert(Goal(total_score, p));
    }
}

void Thing::robot_tick (void)
{_
    static uint32_t last_tick;
    if (!time_have_x_ms_passed_since(game->get_move_speed(), last_tick)) {
        return;
    }

    last_tick = time_get_time_ms_cached();

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
        is_the_grid || 
        is_jumping) { 
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

    switch (monstp->robot_state) {
        case ROBOT_STATE_IDLE:
        {
            //
            // Look for doors or things to collect, if not being attacked.
            //
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    fpoint at(mid_at.x + dx, mid_at.y + dy);

                    FOR_ALL_THINGS(level, it, at.x, at.y) {

                        if (it->is_door() && !it->is_open) {
                            if (get_keys()) {
                                if (open_door(it)) {
                                    game->tick_begin("Robot opened a door");
                                    return;
                                }
                            }

                            //
                            // Try hitting the door
                            //
                            if (!do_something) {
                                do_something = true;
                                attack = true;
                                break;
                            }
                        }

                        auto items = anything_to_carry_at(at);
                        if (items.size() == 1) {
                            for (auto item : items) {
                                if (try_to_carry(item)) {
                                    game->tick_begin("Robot collected an item");
                                    return;
                                }
                            }
                        }

                        if (do_something) {
                            break;
                        }
                    } FOR_ALL_THINGS_END();
                }

                if (do_something) {
                    break;
                }
            }

            if (!do_something) {
                if (robot_ai_create_path_to_goal(minx, miny, maxx, maxy)) {
                    robot_change_state(ROBOT_STATE_MOVING, "found goal");
                    return;
                } else {
                    CON("Robot: nothing to do");
                }
            }
        }
        break;
        case ROBOT_STATE_MOVING:
        {
            //
            // Check for interrupts
            //
            if (robot_ai_init_can_see_dmap(minx, miny, maxx, maxy)) {
                robot_change_state(ROBOT_STATE_IDLE, "move interrupted by a change");
                wid_actionbar_init();
                return;
            }

            if (monstp->move_path.empty()) {
                robot_change_state(ROBOT_STATE_IDLE, "move finished");
                wid_actionbar_init();
                return;
            } else {
                CON("Robot: moving");
                return;
            }
        }
        break;
    }

    log("Robot: do something");
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
    }
    switch (monstp->robot_state) {
        case ROBOT_STATE_IDLE:
            from = "IDLE";
            break;
        case ROBOT_STATE_MOVING:
            from = "MOVING";
            break;
    }

    CON("Robot: %s -> %s: %s", from.c_str(), to.c_str(), why.c_str());
    
    switch (monstp->robot_state) {
        case ROBOT_STATE_IDLE:
            monstp->move_path.clear();
            break;
        case ROBOT_STATE_MOVING:
            break;
    }
    monstp->robot_state = new_state;
}
