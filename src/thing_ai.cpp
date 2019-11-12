//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include <algorithm>
#include "my_main.h"
#include "my_game.h"
#include "my_dmap.h"
#include "my_math.h"
#include <vector>

#define DEBUG_AI

bool Thing::will_attack (const Thingp itp)
{
    auto me = tp();
    auto it = itp->tp();

    if (!tp_is_attackable(it)) {
        return (false);
    }

    if (tp_is_meat_eater(me)) {
        if (tp_is_made_of_meat(it) || tp_is_blood(it)) {
            return (true);
        }
    }
    return (false);
}

bool Thing::will_avoid (const Thingp itp)
{
    auto me = tp();
    auto it = itp->tp();

    if (tp_is_made_of_meat(me)) {
        if (tp_is_meat_eater(it)) {
            return (true);
        }
    }
    return (false);
}

bool Thing::will_eat (const Thingp itp)
{
    auto me = tp();
    auto it = itp->tp();

    if (tp_is_meat_eater(me)) {
        if (tp_is_made_of_meat(it) || tp_is_blood(it)) {
            return (true);
        }
    }
    return (false);
}

bool Thing::will_prefer (const Thingp itp)
{
    auto me = tp();
    auto it = itp->tp();

    if (tp_is_water_dweller(me)) {
        if (tp_is_water(it) || tp_is_deep_water(it)) {
            return (true);
        }
    }
    return (false);
}

bool Thing::ai_is_obstacle_for_me (point p)
{
    //
    // Avoid threats and treat them as obstacles
    //
    for (auto t : get(world->all_thing_ptrs_at, p.x, p.y)) {
        if (!t) {
            continue;
        }
        if (t->is_wall()) {
            return (true);
        }
        if (t->is_rock()) {
            return (true);
        }
        if (t->is_door()) {
            return (true);
        }
        if (t->is_lava()) {
            return (true);
        }
        if (t == this) {
            continue;
        }
        if (t->is_hidden) {
            continue;
        }

        //
        // This is more of a look at the future position that some monst is
        // already walking toward
        //
        if (t->is_monst()) {
            return (true);
        }

        if (will_avoid(t)) {
            return (true);
        }
    }

    return (false);
}

uint8_t Thing::is_less_preferred_terrain (point p)
{
    uint8_t pref = 0;

    if (world->is_water(p)) {
        if (is_water_hater()) {
            pref += is_water_hater();
        }
    }
    return (std::min(DMAP_MAX_LESS_PREFERRED_TERRAIN, pref));
}

//
// Higher scores are more preferred
//
bool Thing::ai_is_goal_for_me (point p, int priority, float *score,
                               std::string &debug)
{
#ifdef DEBUG_AI
    float distance_scale = distance(mid_at, fpoint(p.x, p.y));
#endif

    //
    // Check from highest (0) to lowest priority for things to do
    //
    switch (priority) {
    case 0:
        //
        // Highest priority
        //
        if (is_starving) {
            FOR_ALL_INTERESTING_THINGS(world, it, p.x, p.y) {
                if (it == this) {
                    continue;
                }

                if (it->is_hidden) {
                    continue;
                }

                if (will_eat(it)) {
                    auto my_health = get_health();
                    auto it_health = get_health();
                    auto health_diff = it_health - my_health;

                    if (it->is_player()) {
                        *score += 200 - health_diff;
#ifdef DEBUG_AI
                        debug = "will try to eat player " + it->to_string();
                        debug += " distance " + std::to_string(distance_scale);
#endif
                    } else if (it->is_monst()) {
                        *score += 100 - health_diff;
#ifdef DEBUG_AI
                        debug = "will try to eat monst " + it->to_string();
                        debug += " distance " + std::to_string(distance_scale);
#endif
                    } else {
                        *score += 500 + it_health;
#ifdef DEBUG_AI
                        debug = "will eat food " + it->to_string();
                        debug += " distance " + std::to_string(distance_scale);
#endif
                        return (true);
                    }
                }
            }
        }
        break;
    case 1:
        //
        // Medium priority
        //
        if (is_hungry) {
            FOR_ALL_INTERESTING_THINGS(world, it, p.x, p.y) {
                if (it == this) {
                    continue;
                }

                if (it->is_hidden) {
                    continue;
                }

                if (will_eat(it)) {
                    auto my_health = get_health();
                    auto it_health = get_health();
                    auto health_diff = it_health - my_health;

                    if (it->is_player()) {
                        *score += 200 - health_diff;
#ifdef DEBUG_AI
                        debug = "will try to eat player " + it->to_string();
                        debug += " distance " + std::to_string(distance_scale);
#endif
                    } else if (it->is_monst()) {
                        *score += 100 - health_diff;
#ifdef DEBUG_AI
                        debug = "will try to eat monst " + it->to_string();
                        debug += " distance " + std::to_string(distance_scale);
#endif
                    } else {
                        *score += 500 + it_health;
#ifdef DEBUG_AI
                        debug = "will eat food " + it->to_string();
                        debug += " distance " + std::to_string(distance_scale);
#endif
                        return (true);
                    }
                }

                if (will_attack(it)) {
                    *score += 100;
#ifdef DEBUG_AI
                    debug = "will attack " + it->to_string(); 
                    debug += " distance " + std::to_string(distance_scale);
#endif
                    return (true);
                }
            }
        }
        break;
    case 2:
        //
        // Lowest priority
        //
        FOR_ALL_INTERESTING_THINGS(world, it, p.x, p.y) {
            if (it == this) {
                continue;
            }

            if (it->is_hidden) {
                continue;
            }

            if (will_prefer(it)) {
#ifdef DEBUG_AI
                debug = "prefer " + it->to_string(); 
                debug += " distance " + std::to_string(distance_scale);
#endif
                return (true);
            }
            break;
        }
    }
    return (false);
}

fpoint Thing::ai_get_next_hop (void)
{_
    log("calculate next-hop for ai when at %f,%f:", mid_at.x, mid_at.y);

    const float dx = (MAP_WIDTH / 6);
    const float dy = (MAP_HEIGHT / 6);

    const float minx = std::max(0,         (int)(mid_at.x - dx));
    const float maxx = std::min(MAP_WIDTH, (int)(mid_at.x + dx - 1));

    const float miny = std::max(0,          (int)(mid_at.y - dy));
    const float maxy = std::min(MAP_HEIGHT, (int)(mid_at.y + dy - 1));

    point start((int)mid_at.x, (int)mid_at.y);

    auto scent = get_dmap_scent();
    auto age_map = get_age_map();

    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            point p(x, y);
            auto X = x - minx;
            auto Y = y - miny;

            if (ai_is_obstacle_for_me(p)) {
                set(scent->val, X, Y, DMAP_IS_WALL);
            } else {
                set(scent->val, X, Y, DMAP_IS_PASSABLE);
            }
        }
    }

    //
    // We want to find how far everything is from us.
    //
    set(scent->val, start.x - minx, start.y - miny, DMAP_IS_GOAL);

    dmap_process(scent, point(0, 0), point(maxx - minx, maxy - miny));

    //
    // Find all the possible goals we can smell.
    //
    std::multiset<Goal> goals_set;
    uint32_t oldest = 0;

#ifdef DEBUG_AI
    log("goals:");
#endif
    auto tpp = tp();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            point p(x, y);
            auto X = x - minx;
            auto Y = y - miny;

            //
            // Too far away to sense?
            //
            if (get(scent->val, X, Y) > tpp->ai_scent_distance) {
                set(scent->val, X, Y, DMAP_IS_WALL);
                continue;
            }

            //
            // Look at the cell for each priority level. This means we can
            // have multiple goals per cell. We combine them all together.
            //
            bool got_one = false;
            auto terrain_score = is_less_preferred_terrain(p);

            // auto this_cell_scent = get(scent->val, X, Y);
            const auto max_priority = 3;
            for (auto priority = 0; priority < max_priority; priority++) {
                float score = 0;
                std::string why;
                if (!ai_is_goal_for_me(p, priority, &score, why)) {
                    continue;
                }

                //
                // Further -> less preferred. No, astar will factor this
                // in anyway
                //
                // score -= this_cell_scent;

                //
                // Higher priort -> more preferred
                //
                score += 100 * (max_priority - priority + 1);

                //
                // Worse terrain -> less preferred
                //
                score -= terrain_score;

                Goal goal(score);
                goal.at = point(X, Y);
                goal.why = why;
                goals_set.insert(goal);
#ifdef DEBUG_AI
                log("  goal add %d,%d (%s) prio %d score %f", 
                    (int)X, (int)Y, why.c_str(), priority, score);
#endif

                //
                // Also take note of the oldest cell age; we will use this
                // later.
                //
                uint32_t age = get(age_map->val, x, y);
                oldest = std::min(oldest, age);
                got_one = true;
                break;
            }

            if (got_one) {
                set(scent->val, X, Y, DMAP_IS_GOAL);
            } else if (terrain_score) {
                set(scent->val, X, Y, terrain_score);
            } else {
                set(scent->val, X, Y, DMAP_IS_PASSABLE);
            }
        }
    }

#ifdef DEBUG_AI
    log("initial goal map derived:");
    dmap_print(scent, 
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

    for (auto g : goals_set) {
        auto p = g.at;
        incr(cell_totals, p.x, p.y, g.score);
        auto score = get(cell_totals, p.x, p.y);

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

#ifdef DEBUG_AI
    log("sorted goals, %f (best) .. %f (worst) range %f",
        most_preferred, least_preferred, most_preferred - least_preferred);
#endif

    //
    // Scale the goals so they will fit in the dmap.
    //
    for (auto g : goals_set) {
        auto p = g.at;
        float score = get(cell_totals, p.x, p.y);
        auto orig_score = score;
        score = most_preferred - score;
        score /= (most_preferred - least_preferred);
        score *= DMAP_IS_PASSABLE - 1;

        assert(score <= DMAP_IS_PASSABLE);
        uint8_t score8 = (int)score;
        set(scent->val, p.x, p.y, score8);

#ifdef DEBUG_AI
        log("  scale goal %d to %d (%s)", 
            (int)orig_score, score8, g.why.c_str());
#endif
    }

    //
    // Record we've been here.
    //
    set(age_map->val, start.x, start.y, time_get_time_ms());

    //
    // Find the best next-hop to the best goal.
    //
#ifdef DEBUG_AI
    log("goals:");
    dmap_print(scent, 
               point(start.x - minx, start.y - miny),
               point(0, 0), 
               point(maxx - minx, maxy - miny));
#endif

    //
    // Make sure we do not want to stay in the same position by making
    // our current cell passable but the very least preferred it can be.
    //
    if (get(scent->val, start.x - minx, start.y - miny) > 0) {
        set(scent->val, start.x - minx, start.y - miny, DMAP_IS_PASSABLE);
    }

    //
    // Move diagonally if not blocked by walls
    //
    point s(start.x - minx, start.y - miny);
    auto hops = astar_solve(s, goals_set, scent,
                            point(0, 0), 
                            point(maxx - minx, maxy - miny));
    auto hopssize = hops.path.size();
    point best;
    if (hopssize >= 2) {
        auto hop0 = get(hops.path, hopssize - 1);
        auto hop1 = get(hops.path, hopssize - 2);
        if (dmap_can_i_move_diagonally(scent, s, hop0, hop1)) {
            best = hop1;
        } else {
            best = hop0;
        }
    } else if (hops.path.size() >= 1) {
        auto hop0 = get(hops.path, hopssize - 1);
        best = hop0;
    } else {
        best = s;
    }

    best.x += minx;
    best.y += miny;

    fpoint fbest;
    fbest.x = best.x + 0.5;
    fbest.y = best.y + 0.5;

#ifdef DEBUG_AI
    log("chose next-hop %f,%f", fbest.x, fbest.y);
#endif

    return (fbest);
}
