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

#define DEBUG_AI_VERBOSE

bool Thing::possible_to_attack (const Thingp itp)
{_
    auto me = tp();
    auto it = itp->tp();

    if (!it->is_attackable()) {
        return (false);
    }

    if (is_alive_monst()) {
        if (me->is_meat_eater()) {
            if (it->is_made_of_meat() || it->is_blood()) {
                dbg("possible attack %s", itp->to_string().c_str());
                return (true);
            }
        }
    } else if (is_player()) {
        if (itp->is_monst()) {
            dbg("possible attack %s", itp->to_string().c_str());
            return (true);
        }
    }

    return (false);
}

bool Thing::will_avoid (const Thingp itp)
{_
    auto me = tp();
    auto it = itp->tp();

    if (me->is_made_of_meat()) {
        if (it->is_meat_eater()) {
            return (true);
        }
    }
    return (false);
}

bool Thing::will_eat (const Thingp itp)
{_
    auto me = tp();
    auto it = itp->tp();

    if (me->is_meat_eater()) {
        if (it->is_made_of_meat() || it->is_blood()) {
            return (true);
        }
    }
    if (me->is_fire()) {
        return (true);
    }
    return (false);
}

bool Thing::will_prefer_terrain (const Thingp itp)
{_
    auto me = tp();
    auto it = itp->tp();

    if (me->is_water_dweller()) {
        if (it->is_water() || it->is_deep_water()) {
            return (true);
        }
    }
    return (false);
}

bool Thing::ai_ai_obstacle_for_me (point p)
{_
    //
    // Avoid threats and treat them as obstacles
    //
    for (auto& t : get(level->all_thing_ptrs_at, p.x, p.y)) {
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
        if (t->is_hazard()) {
            return (true);
        }
        if (t == this) {
            continue;
        }
        if (t->is_hidden) {
            continue;
        }

        //
        // Do not include this check. It stops monsts seeing down a corridor
        // with a monst already in it
        //
        // if (t->is_alive_monst()) {
        //   return (true);
        // }
        //

        if (will_avoid(t)) {
            return (true);
        }
    }

    return (false);
}

uint8_t Thing::is_less_preferred_terrain (point p) const
{_
    uint8_t pref = 0;

    if (level->is_water(p)) {
        if (is_water_hater()) {
            pref += is_water_hater();
        }
    }
    return (std::min(DMAP_MAX_LESS_PREFERRED_TERRAIN, pref));
}

void Thing::ai_get_next_hop (void)
{_
    log("AI (higher scores prefd):");

    const float dx = (MAP_WIDTH / 6);
    const float dy = (MAP_HEIGHT / 6);

    const float minx = std::max(0,         (int)(mid_at.x - dx));
    const float maxx = std::min(MAP_WIDTH, (int)(mid_at.x + dx - 1));

    const float miny = std::max(0,          (int)(mid_at.y - dy));
    const float maxy = std::min(MAP_HEIGHT, (int)(mid_at.y + dy - 1));

    point start((int)mid_at.x, (int)mid_at.y);

    auto dmap_scent = get_dmap_scent();

    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            point p(x, y);
            auto X = x - minx;
            auto Y = y - miny;

            if (ai_ai_obstacle_for_me(p)) {
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

#ifdef DEBUG_AI
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
            if (it->is_hidden) { continue; }

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
                    GOAL_ADD(it_stats_health, "eatp1");
                }
            } else if (is_hungry) {
                if (will_eat(it)) {
                    //
                    // Prefer easy food over attacking the player and prefer
                    // the player over a monster. Factor in health so we will
                    // go for the easier kill in preference.
                    //
                    if (it->is_player()) {
                        GOAL_ADD(- health_diff, "eatp2");
                    } else if (it->is_alive_monst()) {
                        GOAL_ADD(- health_diff, "eatm1");
                    } else {
                        GOAL_ADD(it_stats_health, "eatf1");
                    }
                }
            }

            if (will_prefer_terrain(it)) {
                //
                // Prefer certain terrains over others. i.e. I prefer water.
                //
                GOAL_ADD(1, "preferred terrain");
            }

            if (is_enemy(it)) {
                //
                // The closer an enemy is (something that attacked us), the
                // higher the scoree
                //
                float dist = distance(it->mid_at, mid_at);
                float max_dist = ai_scent_distance();

                if (dist < max_dist) {
                    GOAL_ADD((int)(max_dist - dist) * 10, "attack enemy");
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

    if (goals.empty()) {
        CON("TODO WANDER");
    }

#ifdef DEBUG_AI_VERBOSE
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

#ifdef DEBUG_AI
    log("sorted goals, %d (best) .. %d (worst)",
        (int)most_preferred, (int)least_preferred);
#endif

    //
    // Scale the goals so they will fit in the dmap.
    //
    for (auto& goal : goals) {
        auto goal_target = goal.at;
        float score = get(cell_totals, goal_target.x, goal_target.y);
#ifdef DEBUG_AI
        auto orig_score = score;
#endif
        score /= (most_preferred - least_preferred);
        score *= DMAP_IS_PASSABLE - 2;
        score++;

        assert(score <= DMAP_IS_PASSABLE);
        uint8_t score8 = (int)score;
        set(dmap_scent->val, goal_target.x, goal_target.y, score8);

#ifdef DEBUG_AI
        dbg(" scale goal (%d,%d) %d to %d",
            (int)minx + goal.at.x, (int)miny + goal.at.y, 
            (int)orig_score, (int)score8);
#endif
    }

    //
    // Record we've been here. TODO not used yet.
    //
    // set(age_map->val, start.x, start.y, time_get_time_ms());

    //
    // Find the best next-hop to the best goal.
    //
#ifdef DEBUG_AI_VERBOSE
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
    std::multiset<Next_hop> next_hops;
    char path_debug = '\0'; // astart path debug

#ifdef DEBUG_ASTAR_PATH
    astar_debug = {};
    int index = 0;
#endif
    for (auto& goal : goals) {
#ifdef DEBUG_ASTAR_PATH
        astar_debug = {};
#endif
        auto astar_end = goal.at;
        auto result = astar_solve(path_debug, astar_start, astar_end, dmap_scent);
        auto hops = result.path;
        auto cost = result.cost;
        auto hops_len = hops.size();
        point best;

#ifdef DEBUG_ASTAR_PATH
        dump(dmap, at, start, end);
#endif
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

        auto nh = fpoint(best.x + minx,
                         best.y + miny);

        log("assess (%d,%d) next (%d,%d) cost %d (lower pref)",
            (int)minx + goal.at.x, (int)miny + goal.at.y,
            (int)(nh.x), (int)(nh.y), (int)cost);

#ifdef DEBUG_ASTAR_PATH
        if (!index) {
            for (auto& p : hops) {
                set(astar_debug, p.x, p.y, '*');
            }
            auto start = point(0, 0);
            auto end = point(maxx - minx, maxy - miny);
            astar_dump(dmap_scent, goal.at, start, end);
        }
        index++;
#endif
        point nh_i(nh.x, nh.y);

        if (is_less_preferred_terrain(nh_i)) {
            log("move to %f,%f is less preferred terrain, avoid",
                nh.x, nh.y);
            continue;
        }

        if (mid_at == nh) {
            continue;
        }

        //
        // Check to see if moving to this new location will hit something
        //
        // We need to look at the next-hop at the current time which may
        // be vacant, but also to the future if a thing is moving to that
        // spot; in which case we get an attach of opportunity.
        //
        if (collision_check_only(nh)) {
            //
            // We would hit something and cannot do this move. However,
            // see if we can hit the thing that is in the way.
            //
            log("move to %f,%f hit obstacle", nh.x, nh.y);

            bool target_attacked = false;
            bool target_overlaps = false;
            collision_check_and_handle_nearby(fpoint(nh.x, nh.y),
                                              &target_attacked,
                                              &target_overlaps);
            if (target_attacked) {
                is_move_done = true;
                log("cannot move to %f,%f, must attack", nh.x, nh.y);
                return;
            } else {
                log("cannot move to %f,%f, obstacle", nh.x, nh.y);
                continue;
            }
        } else {
            is_move_done = true;
            log("move to %f,%f", nh.x, nh.y);
            move(nh);
            return;
        }
    }

    is_move_done = true;
    stop();
}
