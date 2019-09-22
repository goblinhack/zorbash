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
    if (world->is_wall(p)) {
        return (true);
    }
    if (world->is_rock(p)) {
        return (true);
    }
    if (world->is_door(p)) {
        return (true);
    }
    if (world->is_lava(p)) {
        return (true);
    }

    //
    // This is more of a look at the future position that some monst is
    // already walking toward
    //
    if (world->is_monst(p)) {
        return (true);
    }

    //
    // Avoid threats and treat them as obstacles
    //
    FOR_ALL_INTERESTING_THINGS(world, t, p.x, p.y) {
        if (t == this) {
            continue;
        }

        if (t->is_hidden) {
            continue;
        }

        if (will_avoid(t)) {
            return (true);
        }
    }

    return (false);
}

int Thing::is_less_preferred_terrain (point p)
{
    if (world->is_water(p)) {
        if (is_water_hater()) {
            return (100);
        }
    }
    return (0);
}

//
// Lower scores are more preferred
// k
bool Thing::ai_is_goal_for_me (point p, int priority, float *score)
{
    float distance_scale = distance(mid_at, fpoint(p.x, p.y));
    if (!distance_scale) {
        distance_scale = 1.0;
    }

    //
    // Check from highest (0) to lowest priority for things to do
    //
    switch (priority) {
    case 0:
        if (is_starving) {
            FOR_ALL_INTERESTING_THINGS(world, it, p.x, p.y) {
                if (it == this) {
                    continue;
                }

                if (it->is_hidden) {
                    continue;
                }

                if (will_eat(it)) {
                    *score -= 1000 / distance_scale;
                    return (true);
                }
            }
        }
        break;
    case 1:
        if (is_hungry) {
            FOR_ALL_INTERESTING_THINGS(world, it, p.x, p.y) {
                if (it == this) {
                    continue;
                }

                if (it->is_hidden) {
                    continue;
                }

                if (will_eat(it)) {
                    *score -= 500;
                    return (true);
                }

                if (will_attack(it)) {
                    *score -= 1000 / distance_scale;
                    return (true);
                }
            }
        }
        break;
    case 2:
        FOR_ALL_INTERESTING_THINGS(world, it, p.x, p.y) {
            if (it == this) {
                continue;
            }

            if (it->is_hidden) {
                continue;
            }

            if (will_prefer(it)) {
                return (true);
            }
            break;
        }
    }
    return (false);
}

fpoint Thing::ai_get_next_hop (void)
{_
    const auto dx = (CHUNK_WIDTH / 2) - 1;
    const auto dy = (CHUNK_HEIGHT / 2) - 1;

    auto minx = std::max(0, (int)mid_at.x - dx);
    auto maxx = std::min(MAP_WIDTH, (int)mid_at.x + dx);

    auto miny = std::max(0, (int)mid_at.y - dy);
    auto maxy = std::min(MAP_HEIGHT, (int)mid_at.y + dy);

    fpoint fstart;
    auto tpp = tp();
    fstart = mid_at;
    point start((int)fstart.x, (int)fstart.y);

    auto scent = get_dmap_scent();
    auto goals = get_dmap_goals();
    auto age_map = get_age_map();

    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            point p(x, y);
            int value;

            //
            // Make newer cells less preferred by factoring in the age
            //
            uint32_t age;
            auto v = get(age_map->val, x, y);
            if (v) {
                age = time_get_elapsed_secs(v, get_timestamp_born());
            } else {
                age = 0;
            }

            auto X = x - minx;
            auto Y = y - miny;

            if (ai_is_obstacle_for_me(p)) {
                set(scent->val, X, Y, DMAP_IS_WALL);
                set(goals->val, X, Y, DMAP_IS_WALL);
            } else if ((value = is_less_preferred_terrain(p))) {
                set(scent->val, X, Y, DMAP_IS_PASSABLE);
                set(goals->val, X, Y, DMAP_IS_PASSABLE);
                incr(goals->val, X, Y, (uint16_t)(age + value));
            } else {
                set(scent->val, X, Y, DMAP_IS_PASSABLE);
                set(goals->val, X, Y, DMAP_IS_PASSABLE);
                incr(goals->val, X, Y, (uint16_t)age);
            }
        }
    }

    //
    // We want to find how far everything is from us.
    //
_
    set(scent->val, start.x - minx, start.y - miny, DMAP_IS_GOAL);

#if 0
CON("scent before:");
dmap_print(dmap_scent, start);
#endif
    dmap_process(scent);
#if 0
CON("scent after:");
dmap_print(dmap_scent, start);
#endif

    //
    // Find all the possible goals we can smell.
    //
    std::multiset<Goal> goals_set;
    int oldest = 0;

#if 0
CON("goals:");
#endif
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            point p(x, y);
            auto X = x - minx;
            auto Y = y - miny;

            //
            // Too far away to sense?
            //
            if (get(scent->val, X, Y) > tpp->ai_scent_distance) {
                continue;
            }

            //
            // Look at the cell for each priority level. This means we can
            // have multiple goals per cell. We combine them all together.
            //
            for (auto priority = 0; priority < 3; priority++) {
                float score = 0;
                if (!ai_is_goal_for_me(p, priority, &score)) {
                    continue;
                }

                score += get(scent->val, X, Y);
                score += 100 * (priority + 1);

                Goal goal(score);
                goal.at = point(X, Y);
                goals_set.insert(goal);
#if 0
con("  goal add at: %d, %d", X, Y);
#endif

                //
                // Also take note of the oldest cell age; we will use this
                // later.
                //
                int age = get(age_map->val, x, y);
                oldest = std::min(oldest, age);
            }
        }
    }

    //
    // Combine the scores of multiple goals on each cell.
    //
    std::array<std::array<float, CHUNK_HEIGHT>, CHUNK_WIDTH> cell_totals = {};
    float highest_least_preferred = 0;
    float lowest_most_preferred = 0;
//    const float wanderlust = 10;

    {
        std::array<std::array<bool, CHUNK_HEIGHT>, CHUNK_WIDTH> walked = {};
        for (auto g : goals_set) {
            auto p = g.at;
//            if (!get(walked, p.x, p.y)) {
//                int age = get(age_map->val, p.x, p.y);
//                get(cell_totals, p.x, p.y) = wanderlust * (age - oldest);
//            }

_
            set(walked, p.x, p.y, true);
            incr(cell_totals, p.x, p.y, g.score);
            auto score = get(cell_totals, p.x, p.y);

            //
            // Find the highest/least preferred score so we can scale all
            // the goals later.
            //
            highest_least_preferred = std::max(highest_least_preferred, score);
            lowest_most_preferred = std::min(lowest_most_preferred, score);
        }
    }

    //
    // Scale the goals so they will fit in the dmap.
    //
    for (auto g : goals_set) {
        auto p = g.at;
        auto score = get(cell_totals, p.x, p.y);
        score = score - lowest_most_preferred;
        score /= (highest_least_preferred - lowest_most_preferred);
        score *= DMAP_IS_PASSABLE / 2;
_
        set(goals->val, p.x, p.y, (uint16_t)(int)score);
    }

    //
    // Record we've been here.
    //
_
    set(age_map->val, start.x, start.y, time_get_time_ms());

    //
    // Find the best next-hop to the best goal.
    //

    //
    // Wall clingers create a dmap that is essentially a border around
    // the existing walls
    //
#if 0
    dmap_print(dmap_goals, start);
#endif
    dmap_process(goals);
#if 0
    CON("goals after:");
    dmap_print(dmap_goals, start);
#endif

    //
    // Make sure we do not ewant to stay put/
    // moving as an option
    //
    if (get(goals->val, start.x - minx, start.y - miny) > 0) {
        set(goals->val, start.x - minx, start.y - miny, 
            (uint16_t)(DMAP_IS_WALL - 1));
    }

    //
    // Move diagonally if not blocked by walls
    //
    //auto hops = dmap_solve(dmap_goals, start);
    point s(start.x - minx, start.y - miny);
    auto hops = astar_solve(s, goals_set, goals);
    auto hopssize = hops.path.size();
    point best;
    if (hopssize >= 2) {
        auto hop0 = get(hops.path, hopssize - 1);
        auto hop1 = get(hops.path, hopssize - 2);
        if (dmap_can_i_move_diagonally(goals, s, hop0, hop1)) {
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

    return (fbest);
}
