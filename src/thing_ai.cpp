/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_main.h"
#include "my_thing.h"
#include "my_dmap.h"
#include <algorithm>

bool Thing::is_obstacle_for_me (point p)
{
    if (game.state.map.is_wall_at(p)) {
        return (true);
    }
    if (game.state.map.is_door_at(p)) {
        return (true);
    }
    if (game.state.map.is_lava_at(p)) {
        return (true);
    }
    if (game.state.map.is_deep_water_at(p)) {
        return (true);
    }
    return (false);
}

bool Thing::is_goal_for_me (point p, int priority, double *score)
{
    double distance_scale = distance(at, fpoint(p.x, p.y));
    if (!distance_scale) {
        distance_scale = 1.0;
    }

    switch (priority) {
    case 0:
        if (is_starving) {
            if (game.state.map.is_blood_at(p)) {
                *score -= 1000 / distance_scale;
                return (true);
            }
        }
        break;
    case 1:
        if (is_hungry) {
            if (game.state.map.is_blood_at(p)) {
                *score -= 500 / distance_scale;
                return (true);
            }
        }
        break;
    case 2:
        if (game.state.map.is_water_at(p)) {
            return (true);
        }
        break;
    }
    return (false);
}

point Thing::choose_best_nh (void)
{
    auto minx = 0;
    auto miny = 0;
    auto maxx = MAP_WIDTH;
    auto maxy = MAP_HEIGHT;
    point start((int)at.x, (int)at.y);

    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            point p(x, y);
            if (is_obstacle_for_me(p)) {
                dmap_scent->val[x][y] = DMAP_IS_WALL;
                dmap_goals->val[x][y] = DMAP_IS_WALL;
            } else {
                dmap_scent->val[x][y] = DMAP_IS_PASSABLE;
                dmap_goals->val[x][y] = DMAP_IS_PASSABLE;
            }
        }
    }

    /*
     * We want to find how far everything is from us.
     */
    dmap_scent->val[(int)at.x][(int)at.y] = DMAP_IS_GOAL;

    point tl(minx, miny);
    point br(maxx, maxy);
    dmap_process(dmap_scent, tl, br);
    // dmap_print(dmap_scent);

    /*
     * Find all the possible goals we can smell.
     */
    std::multiset<Goal> goals;
    int oldest = 0;

    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            point p(x, y);
            fpoint fp(x, y);
            if (dmap_scent->val[x][y] > tp->scent_distance) {
                continue;
            }

            /*
             * Look at the cell for each priority level. This means we can
             * have multiple goals per cell. We combine them all together.
             */
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

                /*
                 * Also take note of the oldest cell age; we will use this 
                 * later.
                 */
                int age = age_map->val[p.x][p.y];
                oldest = std::min(oldest, age);
            }
        }
    }

    /*
     * Combine the scores of multiple goals on each cell.
     */
    double cell_totals[MAP_WIDTH][MAP_HEIGHT];
    memset(&cell_totals, 0, sizeof(cell_totals));
    double highest_least_preferred = 0;
    double lowest_most_preferred = 0;
    const double wanderlust = 10;

    {
        uint8_t walked[MAP_WIDTH][MAP_HEIGHT];
        memset(&walked, 0, sizeof(walked));
        for (auto g : goals) {
            auto p = g.at;
            if (!walked[p.x][p.y]) {
                int age = age_map->val[p.x][p.y];
                cell_totals[p.x][p.y] = wanderlust * (age - oldest);
            }

            walked[p.x][p.y] = true;
            cell_totals[p.x][p.y] += g.score;
            auto score = cell_totals[p.x][p.y];

            /*
             * Find the highest/least preferred score so we can scale all
             * the goals later.
             */
            highest_least_preferred = std::max(highest_least_preferred, score);
            lowest_most_preferred = std::min(lowest_most_preferred, score);
        }
    }

    /*
     * Scale the goals so they will fit in the dmap.
     */
    for (auto g : goals) {
        auto p = g.at;
        auto score = cell_totals[p.x][p.y];
        score = score - lowest_most_preferred;
        score /= (highest_least_preferred - lowest_most_preferred);
        score *= DMAP_IS_PASSABLE / 2;
        dmap_goals->val[p.x][p.y] = score;
    }

    /*
     * Record we've neen here.
     */
    age_map->val[start.x][start.y]++;

    /*
     * Find the best next-hop to the best goal.
     */
    dmap_goals->val[start.x][start.y] = DMAP_IS_PASSABLE;
    dmap_print(dmap_goals, start);
    dmap_process(dmap_goals, tl, br);

    auto hops = dmap_solve(dmap_goals, start);
    for (auto nh : hops) {
        if (nh == start) {
            continue;
        }

        return (point(nh.x, nh.y));
    }

    return (start);
}

point Thing::get_next_hop (void)
{
    auto nh = choose_best_nh();

    return (nh);
}
