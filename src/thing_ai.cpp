//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include <algorithm>
#include "my_main.h"
#include "my_thing.h"
#include "my_dmap.h"
#include "my_math.h"
#include <vector>

extern std::vector<point> astar_solve(point s, 
                                    std::multiset<Goal> &goals, Dmap *d);

bool Thing::will_attack (const Thingp itp)
{
    auto me = tp;
    auto it = itp->tp;

    if (tp_is_meat_eater(me)) {
        if (tp_is_made_of_meat(it) || tp_is_blood(it)) {
            return (true);
        }
    }
    return (false);
}

bool Thing::will_avoid (const Thingp itp)
{
    auto me = tp;
    auto it = itp->tp;

    if (tp_is_made_of_meat(me)) {
        if (tp_is_meat_eater(it)) {
            return (true);
        }
    }
    return (false);
}

bool Thing::will_eat (const Thingp itp)
{
    auto me = tp;
    auto it = itp->tp;

    if (tp_is_meat_eater(me)) {
        if (tp_is_made_of_meat(it) || tp_is_blood(it)) {
            return (true);
        }
    }
    return (false);
}

bool Thing::will_prefer (const Thingp itp)
{
    auto me = tp;
    auto it = itp->tp;

    if (tp_is_water_dweller(me)) {
        if (tp_is_water(it) || tp_is_deep_water(it)) {
            return (true);
        }
    }
    return (false);
}

bool Thing::is_obstacle_for_me (point p)
{
    if (game.state.map.is_wall_at(p)) {
        return (true);
    }
    if (game.state.map.is_rock_at(p)) {
        return (true);
    }
    if (game.state.map.is_door_at(p)) {
        return (true);
    }
    if (game.state.map.is_lava_at(p)) {
        return (true);
    }

    //
    // This is more of a look at the future position that some monst is
    // already walking toward
    //
    if (game.state.map.is_monst_at(p)) {
        return (true);
    }

    //
    // Avoid threats and treat them as obstacles
    //
    for (auto i : game.state.map.all_interesting_things_at[p.x][p.y]) {
        auto it = i.second;
        if (it == this) {
            continue;
        }

        if (will_avoid(it)) {
            return (true);
        }
    }

    return (false);
}

int Thing::is_less_preferred_terrain (point p)
{
    if (game.state.map.is_water_at(p)) {
        if (hates_water()) {
            return (100);
        }
    }
    return (0);
}

//
// Lower scores are more preferred
// k
bool Thing::is_goal_for_me (point p, int priority, double *score)
{
    double distance_scale = distance(mid_at, fpoint(p.x, p.y));
    if (!distance_scale) {
        distance_scale = 1.0;
    }

    //
    // Check from highest (0) to lowest priority for things to do
    //
    switch (priority) {
    case 0:
        if (is_starving) {
            for (auto i : game.state.map.all_interesting_things_at[p.x][p.y]) {
                auto it = i.second;
                if (it == this) {
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
            for (auto i : game.state.map.all_interesting_things_at[p.x][p.y]) {
                auto it = i.second;
                if (it == this) {
                    continue;
                }
CON("  consider %s", it->to_string().c_str());

                if (will_eat(it)) {
CON("  consider %s will eat", it->to_string().c_str());
                    *score -= 500;
                    return (true);
                }

                if (will_attack(it)) {
CON("  consider %s will attack", it->to_string().c_str());
                    *score -= 1000 / distance_scale;
                    return (true);
                }
            }
        }
        break;
    case 2:
        for (auto i : game.state.map.all_interesting_things_at[p.x][p.y]) {
            auto it = i.second;
            if (it == this) {
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

fpoint Thing::get_next_hop (void)
{_
    auto minx = 0;
    auto miny = 0;
    auto maxx = MAP_WIDTH;
    auto maxy = MAP_HEIGHT;
    fpoint fstart;

    fstart = mid_at;
    point start((int)fstart.x, (int)fstart.y);

    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            point p(x, y);
            int value;

            //
            // Make newer cells less preferred by factoring in the age
            // 
            uint32_t age;
            if (age_map->val[x][y]) {
                age = time_get_elapsed_secs(age_map->val[x][y],
                                            timestamp_born);
            } else {
                age = 0;
            }

            if (is_obstacle_for_me(p)) {
                dmap_scent->val[x][y] = DMAP_IS_WALL;
                dmap_goals->val[x][y] = DMAP_IS_WALL;
            } else if ((value = is_less_preferred_terrain(p))) {
                dmap_scent->val[x][y] = DMAP_IS_PASSABLE;
                dmap_goals->val[x][y] = DMAP_IS_PASSABLE;
                dmap_goals->val[x][y] += age;
                dmap_goals->val[x][y] += value;
            } else {
                dmap_scent->val[x][y] = DMAP_IS_PASSABLE;
                dmap_goals->val[x][y] = DMAP_IS_PASSABLE;
                dmap_goals->val[x][y] += age;
            }
        }
    }

    //
    // We want to find how far everything is from us.
    //
    dmap_scent->val[start.x][start.y] = DMAP_IS_GOAL;

    point tl(minx, miny);
    point br(maxx, maxy);
#if 0
CON("scent before:");
dmap_print(dmap_scent, start);
#endif
    dmap_process(dmap_scent, tl, br);
#if 0
CON("scent after:");
dmap_print(dmap_scent, start);
#endif

    //
    // Find all the possible goals we can smell.
    //
    std::multiset<Goal> goals;
    int oldest = 0;

CON("goals:");
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            point p(x, y);
            fpoint fp(x, y);
            //
            // Too far away to sense?
            //
            if (dmap_scent->val[x][y] > tp->ai_scent_distance) {
                continue;
            }

            //
            // Look at the cell for each priority level. This means we can
            // have multiple goals per cell. We combine them all together.
            //
            for (auto priority = 0; priority < 3; priority++) {
                double score = 0;
                if (!is_goal_for_me(p, priority, &score)) {
                    continue;
                }

                score += dmap_scent->val[p.x][p.y];
                score += 100 * (priority + 1);

                Goal goal(score);
                goal.at = p;
                goals.insert(goal);
CON("  goal add at: %d, %d", p.x, p.y);

                //
                // Also take note of the oldest cell age; we will use this
                // later.
                //
                int age = age_map->val[p.x][p.y];
                oldest = std::min(oldest, age);
            }
        }
    }

    //
    // Combine the scores of multiple goals on each cell.
    //
    double cell_totals[MAP_WIDTH][MAP_HEIGHT];
    memset(&cell_totals, 0, sizeof(cell_totals));
    double highest_least_preferred = 0;
    double lowest_most_preferred = 0;
//    const double wanderlust = 10;

    {
        uint8_t walked[MAP_WIDTH][MAP_HEIGHT];
        memset(&walked, 0, sizeof(walked));
        for (auto g : goals) {
            auto p = g.at;
//            if (!walked[p.x][p.y]) {
//                int age = age_map->val[p.x][p.y];
//                cell_totals[p.x][p.y] = wanderlust * (age - oldest);
//            }

            walked[p.x][p.y] = true;
            cell_totals[p.x][p.y] += g.score;
            auto score = cell_totals[p.x][p.y];

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
    for (auto g : goals) {
        auto p = g.at;
        auto score = cell_totals[p.x][p.y];
        score = score - lowest_most_preferred;
        score /= (highest_least_preferred - lowest_most_preferred);
        score *= DMAP_IS_PASSABLE / 2;
        dmap_goals->val[p.x][p.y] = score;
    }

    //
    // Record we've been here.
    //
    age_map->val[start.x][start.y] = time_get_time_ms();

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
    dmap_process(dmap_goals, tl, br);
CON("goals after:");
    dmap_print(dmap_goals, start);

    //
    // Make sure we do not ewant to stay put/
    // moving as an option
    //
    if (dmap_goals->val[start.x][start.y] > 0) {
        dmap_goals->val[start.x][start.y] = DMAP_IS_WALL - 1;
    }

    //
    // Move diagonally if not blocked by walls
    //
    //auto hops = dmap_solve(dmap_goals, start);
    auto hops = astar_solve(start, goals, dmap_goals);
    auto hopssize = hops.size();
    point best;
    if (hopssize >= 2) {
        auto hop0 = hops[hopssize - 1];
        auto hop1 = hops[hopssize - 2];
        if (dmap_can_i_move_diagonally(dmap_goals, start, hop0, hop1)) {
            best = hop1;
        } else {
            best = hop0;
        }
    } else if (hops.size() >= 1) {
        auto hop0 = hops[hopssize - 1];
        best = hop0;
    } else {
        best = start;
    }

    fpoint fbest;
    fbest.x = best.x + 0.5;
    fbest.y = best.y + 0.5;

    return (fbest);
}
