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

int Thing::ai_choose_goal (void)
{_
    dbg("Choose goal");
_
    const float dx = (MAP_WIDTH / 6);
    const float dy = (MAP_HEIGHT / 6);

    const int minx = std::max(0,         (int)(mid_at.x - dx));
    const int maxx = std::min(MAP_WIDTH, (int)(mid_at.x + dx - 1));

    const int miny = std::max(0,          (int)(mid_at.y - dy));
    const int maxy = std::min(MAP_HEIGHT, (int)(mid_at.y + dy - 1));

    point start((int)mid_at.x, (int)mid_at.y);

    auto dmap_can_see = get_dmap_can_see();
    auto age_map = get_age_map();

    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            point p(x, y);
            auto X = x - minx;
            auto Y = y - miny;

            if (ai_obstacle_for_me(p)) {
                set(dmap_can_see->val, X, Y, DMAP_IS_WALL);
            } else {
                set(dmap_can_see->val, X, Y, DMAP_IS_PASSABLE);
            }
        }
    }

    //
    // We want to find how far everything is from us.
    //
    set(dmap_can_see->val, start.x - minx, start.y - miny, DMAP_IS_GOAL);

    dmap_process(dmap_can_see, point(0, 0), point(maxx - minx, maxy - miny));

    //
    // Find all the possible goals we can smell.
    //
    std::multiset<Goal> goals;

    dbg("Choose goals (higher scores, lower costs are preferred):");
_
    auto tpp = tp();
    for (auto y = miny; y < maxy; y++) { for (auto x = minx; x < maxx; x++) {
        point p(x, y);
        auto X = x - minx;
        auto Y = y - miny;

        //
        // Too far away to sense?
        //
        if (get(dmap_can_see->val, X, Y) > tpp->ai_scent_distance()) {
            set(dmap_can_see->val, X, Y, DMAP_IS_WALL);
            continue;
        }

        bool got_a_goal = false;
        bool avoiding = false;
        int terrain_score = get_terrain_cost(p);
        int total_score = -(int)terrain_score;

#define GOAL_ADD(score, msg)                                               \
        total_score += (score);                                            \
        got_a_goal = true;                                                 \
        if (last_msg.empty()) {                                            \
            last_msg = msg;                                                \
        } else {                                                           \
            last_msg += ", ";                                              \
            last_msg += msg;                                               \
        }                                                                  \
        dbg2(" add goal (%d,%d) score %d %s, %s",                          \
             p.x + minx, p.y + miny, score, msg, it->to_string().c_str()); \

        std::string last_msg;

        FOR_ALL_INTERESTING_THINGS(level, it, p.x, p.y) {
            if (it == this) { continue; }

            if (it->is_changing_level ||
                it->is_hidden ||
                it->is_falling ||
                it->is_jumping) {
                if (DEBUG4) {
                    if (it->is_loggable_for_unimportant_stuff()) {
                        dbg2(" ignore %s", it->to_string().c_str());
                    }
                }
                continue;
            }

            if (DEBUG4) {
                if (it->is_loggable_for_unimportant_stuff()) {
                    dbg2(" consider %s", it->to_string().c_str());
                }
            }
            _

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
                    for (auto dx = -d; dx <= d; dx++) {
                        for (auto dy = -d; dy <= d; dy++) {

                            auto dist = distance(mid_at + fpoint(dx, dy), it->mid_at);
                            if (dist < ai_avoid_distance()) {
                                continue;
                            }

                            point p(mid_at.x + dx, mid_at.y + dy);
                            if (ai_obstacle_for_me(p)) {
                                continue;
                            }

                            int terrain_score = get_terrain_cost(p);
                            int total_score = -(int)terrain_score;
                            total_score += dist * dist;
                            goals.insert(Goal(total_score, point(X + dx, Y + dy), last_msg));
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

                                int terrain_score = get_terrain_cost(p);
                                int total_score = -(int)terrain_score;
                                total_score += dist * dist;
                                goals.insert(Goal(total_score, point(X + dx, Y + dy), last_msg));
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
            goals.insert(Goal(total_score, point(X, Y), last_msg));
            set(dmap_can_see->val, X, Y, DMAP_IS_GOAL);
        } else if (terrain_score) {
            set(dmap_can_see->val, X, Y, (uint8_t)terrain_score);
        } else {
            set(dmap_can_see->val, X, Y, DMAP_IS_PASSABLE);
        }
    } }

    //
    // No goals?
    //
    if (goals.empty()) {
        dbg2("No goals found");
        return false;
    }

#ifdef ENABLE_DEBUG_AI_VERBOSE
    dbg2("Initial goal map derived:");
    dmap_print(dmap_can_see,
               point(start.x - minx, start.y - miny),
               point(0, 0),
               point(maxx - minx, maxy - miny));
#endif

    //
    // Find the highest/least preferred score so we can scale all the goals
    // later so they fit in one byte (makes it easier to debug).
    //
    std::array<std::array<float, MAP_HEIGHT>, MAP_WIDTH> cell_totals = {};
    float least_preferred = 0;
    float most_preferred = 0;
    bool least_preferred_set = false;
    bool most_preferred_set = false;

    for (auto& goal : goals) {
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
    for (auto& goal : goals) {
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
        set(dmap_can_see->val, goal_target.x, goal_target.y, score8);

        dbg2(" scale goal (%d,%d) %d to %d",
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
    if (DEBUG4) {
        dbg("Goals:");
        dmap_print(dmap_can_see,
                   point(start.x - minx, start.y - miny),
                   point(0, 0),
                   point(maxx - minx, maxy - miny));
    }

    //
    // Make sure we do not want to stay in the same position by making
    // our current cell passable but the very least preferred it can be.
    //
    if (get(dmap_can_see->val, start.x - minx, start.y - miny) > 0) {
        set(dmap_can_see->val, start.x - minx, start.y - miny, DMAP_IS_PASSABLE);
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

    for (auto& goal : goals) {
#ifdef ENABLE_DEBUG_AI_ASTAR
        astar_debug = {};
#endif
        auto astar_end = goal.at;
        auto result = astar_solve(&goal,
                                  path_debug,
                                  astar_start,
                                  astar_end,
                                  dmap_can_see);
        //
        // Unreachable?
        //
        if (result.cost == std::numeric_limits<int>::max()) {
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
        astar_dump(dmap_can_see, goal.at, start, end);
#endif
    }

    for (auto& result : paths) {
        auto hops = result.path;
        auto hops_len = hops.size();
        point best;

        if (hops_len >= 2) {
            auto hop0 = get(hops, hops_len - 1);
            auto hop1 = get(hops, hops_len - 2);
            if (dmap_can_i_move_diagonally(dmap_can_see, astar_start, hop0, hop1)) {
                best = hop1;
            } else {
                best = hop0;
            }
            dbg2("Best is %d,%d with cost %d, %d hops away",
                 best.x + minx, best.y + miny, result.cost, (int)hops_len);
        } else if (hops_len >= 1) {
            auto hop0 = get(hops, hops_len - 1);
            best = hop0;
            dbg2("Best is %d,%d with cost %d, %d hops away",
                 best.x + minx, best.y + miny, result.cost, (int)hops_len);
        } else {
            dbg2("Best is where we are, cost %d, %d hops away",
                 result.cost, (int)hops_len);
            best = point(mid_at.x - minx, mid_at.y - miny);
        }

        auto nh = point(best.x + minx, best.y + miny);

        if (move_to_or_attack(nh)) {
            dbg2("We can move to or attack or eat this next-hop");
            return true;
        }
    }

    return false;
}
