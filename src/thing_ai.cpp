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

bool Thing::is_goal_for_me (point p)
{
    if (game.state.map.is_water_at(p)) {
        return (true);
    }
    return (false);
}

point Thing::choose_best_nh (void)
{
    auto minx = 0;
    auto miny = 0;
    auto maxx = MAP_WIDTH;
    auto maxy = MAP_HEIGHT;

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

    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            point p(x, y);
            fpoint fp(x, y);
            if (dmap_scent->val[x][y] > tp->scent_distance) {
                continue;
            }

            if (!is_goal_for_me(p)) {
                continue;
            }

            /*
             * We prefer the min score, so closest and not visited recently.
             */
            double score = dmap_scent->val[p.x][p.y];

            double age = memory - dmap_memory->val[p.x][p.y];
            if (age) {
                score /= age;
            }

            Goal goal(score);
            goal.at = p;
            goals.insert(goal);
        }
    }

    double max_score = 0;
    for (auto g : goals) {
        max_score = std::max(g.score, max_score);
    }

    for (auto g : goals) {
        g.score /= max_score;
        g.score *= DMAP_IS_PASSABLE / 2;
        dmap_goals->val[g.at.x][g.at.y] = (int) g.score;
    }

    point start((int)at.x, (int)at.y);

    memory++;
    dmap_memory->val[start.x][start.y]++;
    dmap_goals->val[start.x][start.y] = DMAP_IS_PASSABLE;

con("goals:");
    dmap_print(dmap_goals);
    dmap_process(dmap_goals, tl, br);

    auto hops = dmap_solve(dmap_goals, start);
    for (auto nh : hops) {
con("hops %d %d", nh.x, nh.y);
    }

    for (auto nh : hops) {
con("best to %d %d", nh.x, nh.y);
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
