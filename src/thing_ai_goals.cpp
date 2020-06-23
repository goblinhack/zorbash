//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include <algorithm>
#include <set>
#include "my_main.h"
#include "my_level.h"
#include "my_dmap.h"
#include "my_math.h"
#include "my_thing.h"

int Thing::ai_choose_goal (void)
{_
    log("choose goal");
_
    const float dx = (MAP_WIDTH / 6);
    const float dy = (MAP_HEIGHT / 6);

    const int minx = std::max(0,         (int)(mid_at.x - dx));
    const int maxx = std::min(MAP_WIDTH, (int)(mid_at.x + dx - 1));

    const int miny = std::max(0,          (int)(mid_at.y - dy));
    const int maxy = std::min(MAP_HEIGHT, (int)(mid_at.y + dy - 1));

    point start((int)mid_at.x, (int)mid_at.y);

    auto dmap_scent = get_dmap_scent();
    auto age_map = get_age_map();

    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            point p(x, y);
            auto X = x - minx;
            auto Y = y - miny;

            if (is_obstacle_for_me(p)) {
                set(dmap_scent->val, X, Y, DMAP_IS_WALL);
            } else {
                set(dmap_scent->val, X, Y, DMAP_IS_PASSABLE);
            }
        }
    }

    //
    // We want to find how far everything is from us.
    //
    set(dmap_scent->val, start.x - minx, start.y - miny, DMAP_IS_GOAL);

    dmap_process(dmap_scent, point(0, 0), point(maxx - minx, maxy - miny));

    //
    // Find all the possible goals we can smell.
    //
    std::multiset<Goal> goals;

    log("choose goals (higher scores are preferred):");

    auto tpp = tp();
    for (auto y = miny; y < maxy; y++) { for (auto x = minx; x < maxx; x++) {
        point p(x, y);
        auto X = x - minx;
        auto Y = y - miny;

        //
        // Too far away to sense?
        //
        if (get(dmap_scent->val, X, Y) > tpp->ai_scent_distance()) {
            set(dmap_scent->val, X, Y, DMAP_IS_WALL);
            continue;
        }

        bool got_one = false;
        uint8_t terrain_score = is_less_preferred_terrain(p);
        int total_score = -(int)terrain_score;

#ifdef ENABLE_DEBUG_AI_GOALS
#define GOAL_ADD(score, msg) \
        total_score += (score); \
        got_one = true; \
        log(" goal (%d,%d) score %d %s, %s", \
            p.x, p.y, score, msg, it->to_string().c_str());
#else
#define GOAL_ADD(score, msg) \
        total_score += (score); \
        got_one = true;
#endif
        FOR_ALL_INTERESTING_THINGS(level, it, p.x, p.y) {
            if (it == this) { continue; }
            if (it->is_hidden || it->is_falling || it->is_jumping) { continue; }

            //
            // Worse terrain, less preferred. Higher score, more preferred.
            //
            auto my_health = get_stats_health();
            auto it_stats_health = it->get_stats_health();
            auto health_diff = it_stats_health - my_health;

            if (is_starving) {
                if (will_eat(it)) {
                    //
                    // If starving, prefer the thing with most health
                    //
                    GOAL_ADD(it_stats_health, "eat-player");
                }
            } else if (is_hungry) {
                if (will_eat(it)) {
                    //
                    // Prefer easy food over attacking the player and prefer
                    // the player over a monster. Factor in health so we will
                    // go for the easier kill in preference.
                    //
                    if (it->is_player()) {
                        GOAL_ADD(- health_diff, "eat-player");
                    } else if (it->is_alive_monst()) {
                        GOAL_ADD(- health_diff, "eat-monst");
                    } else {
                        GOAL_ADD(it_stats_health, "eat-food");
                    }
                }
            }

            if (will_prefer_terrain(it)) {
                //
                // Prefer certain terrains over others. i.e. I prefer water.
                //
                GOAL_ADD(1, "preferred-terrain");
            }

            if (is_enemy(it)) {
                //
                // The closer an enemy is (something that attacked us), the
                // higher the scoree
                //
                float dist = distance(it->mid_at, mid_at);
                float max_dist = ai_scent_distance();

                if (dist < max_dist) {
                    GOAL_ADD((int)(max_dist - dist) * 10, "attack-enemy");
                }
            }
        } FOR_ALL_THINGS_END();

        if (got_one) {
            goals.insert(Goal(total_score, point(X, Y)));
            set(dmap_scent->val, X, Y, DMAP_IS_GOAL);
        } else if (terrain_score) {
            set(dmap_scent->val, X, Y, terrain_score);
        } else {
            set(dmap_scent->val, X, Y, DMAP_IS_PASSABLE);
        }
    } }

    //
    // No goals?
    //
    if (goals.empty()) {
        log("no goals found");
        return false;
    }

#ifdef ENABLE_DEBUG_AI_VERBOSE
    log("initial goal map derived:");
    dmap_print(dmap_scent,
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

#ifdef ENABLE_DEBUG_AI
    log("sorted goals, %d (best) .. %d (worst)",
        (int)most_preferred, (int)least_preferred);
#endif

    //
    // Scale the goals so they will fit in the dmap.
    //
    for (auto& goal : goals) {
        auto goal_target = goal.at;
        float score = get(cell_totals, goal_target.x, goal_target.y);
#ifdef ENABLE_DEBUG_AI
        auto orig_score = score;
#endif
        score /= (most_preferred - least_preferred);
        score *= DMAP_IS_PASSABLE - 2;
        score++;

        assert(score <= DMAP_IS_PASSABLE);
        uint8_t score8 = (int)score;
        set(dmap_scent->val, goal_target.x, goal_target.y, score8);

#ifdef ENABLE_DEBUG_AI
        dbg(" scale goal (%d,%d) %d to %d",
            (int)minx + goal.at.x, (int)miny + goal.at.y, 
            (int)orig_score, (int)score8);
#endif
    }

    //
    // Record we've been here.
    //
    set(age_map->val, start.x, start.y, time_get_time_ms());

    //
    // Find the best next-hop to the best goal.
    //
#ifdef ENABLE_DEBUG_AI_VERBOSE
    log("goals:");
    dmap_print(dmap_scent,
               point(start.x - minx, start.y - miny),
               point(0, 0),
               point(maxx - minx, maxy - miny));
#endif

    //
    // Make sure we do not want to stay in the same position by making
    // our current cell passable but the very least preferred it can be.
    //
    if (get(dmap_scent->val, start.x - minx, start.y - miny) > 0) {
        set(dmap_scent->val, start.x - minx, start.y - miny, DMAP_IS_PASSABLE);
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
        auto result = astar_solve(path_debug, astar_start, astar_end, dmap_scent);
        paths.insert(result);

        log(" goal (%d,%d) score %d -> cost %d", goal.at.x, goal.at.y,
            (int)goal.score, (int)result.cost);

#ifdef ENABLE_DEBUG_AI_ASTAR
        for (auto& p : result.path) {
            set(astar_debug, p.x, p.y, '*');
        }
        auto start = point(0, 0);
        auto end = point(maxx - minx, maxy - miny);
        astar_dump(dmap_scent, goal.at, start, end);
#endif
    }

    for (auto& result : paths) {
        auto hops = result.path;
        auto hops_len = hops.size();
        point best;

        if (hops_len >= 2) {
            auto hop0 = get(hops, hops_len - 1);
            auto hop1 = get(hops, hops_len - 2);
            if (dmap_can_i_move_diagonally(dmap_scent, astar_start, hop0, hop1)) {
                best = hop1;
            } else {
                best = hop0;
            }
        } else if (hops_len >= 1) {
            auto hop0 = get(hops, hops_len - 1);
            best = hop0;
        } else {
            continue;
        }

        auto nh = point(best.x + minx, best.y + miny);

        if (move_to_or_attack(nh)) {
            return true;
        }
    }

    return false;
}
