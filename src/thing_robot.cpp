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

//
// Search priorities in order
//
#define SEARCH_TYPE_MAX                       6
#define SEARCH_TYPE_LOCAL_NO_JUMP             0
#define SEARCH_TYPE_LOCAL_JUMP_ALLOWED        1
#define SEARCH_TYPE_GLOBAL_NO_JUMP            2
#define SEARCH_TYPE_GLOBAL_JUMP_ALLOWED       3
#define SEARCH_TYPE_LAST_RESORTS_NO_JUMP      4
#define SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED 5

#define GOAL_ADD(score, msg)                                               \
        total_score += (score);                                            \
        got_a_goal = true;                                                 \
        if (last_msg.empty()) {                                            \
            last_msg = msg;                                                \
        } else {                                                           \
            last_msg += ", ";                                              \
            last_msg += msg;                                               \
        }                                                                  \
        dbg(" add goal (%d,%d) score %d %s, %s",                           \
            p.x + minx, p.y + miny, score, msg, it->to_string().c_str());  \

//
// Look at all the things that are currently visited (read that as light rays
// have touched them) and choose the best goal. Create a path to that goal for
// the thing to walk.
//
bool Thing::robot_ai_create_path_to_goal (int minx, int miny, int maxx, int maxy,
                                          int search_type)
{_
    point start((int)mid_at.x, (int)mid_at.y);

    dbg("Choose goal");
_
    //
    // Find all the possible goals. Higher scores, lower costs are preferred
    //
    auto dmap_can_see = get_dmap_can_see();
    auto age_map = get_age_map();

    //
    // Initialize basic visibility and things that are lit and can be seen
    //
    dbg("Choose goals (higher scores, lower costs are preferred):");

    std::multiset<Goal> goals;
    std::list<GoalMap> goalmaps;
    robot_ai_init_can_see_dmap(minx, miny, maxx, maxy, search_type);

    switch (search_type) {
        case SEARCH_TYPE_LOCAL_JUMP_ALLOWED:
        case SEARCH_TYPE_LOCAL_NO_JUMP:
            robot_ai_choose_initial_goals(goals, minx, miny, maxx, maxy);
            goalmaps.push_back(GoalMap{goals, dmap_can_see});
            break;
        case SEARCH_TYPE_GLOBAL_JUMP_ALLOWED:
        case SEARCH_TYPE_GLOBAL_NO_JUMP:
            robot_ai_choose_search_goals(goals, search_type);
            goalmaps.push_back(GoalMap{goals, dmap_can_see});
            break;
        case SEARCH_TYPE_LAST_RESORTS_NO_JUMP:
        case SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED:
            robot_ai_choose_search_goals(goals, search_type);
            goalmaps.push_back(GoalMap{goals, dmap_can_see});
            break;
    }

    //
    // No goals?
    //
    if (goalmaps.empty()) {
        if (is_player()) {
            CON("Robot: @(%s, %d,%d) No goals found",
                level->to_string().c_str(), (int)mid_at.x, (int)mid_at.y);
        }
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

        for (int y = miny; y < maxy; y++) {
            for (int x = minx; x < maxx; x++) {
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

        dbg2("Sorted goals, %d (best) .. %d (worst)",
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
                score *= DMAP_LESS_PREFERRED_TERRAIN - 2;
                score++;
            }

            assert(score <= DMAP_LESS_PREFERRED_TERRAIN);
            uint8_t score8 = DMAP_LESS_PREFERRED_TERRAIN - (int)score;
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
        if (DEBUG3) {
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
#if 0
            {
                dbg2("ASTAR pre solve:");
                auto start = point(0, 0);
                auto end = point(maxx - minx, maxy - miny);
                astar_dump(g.dmap, goal.at, start, end);
            }
#endif
            auto result = astar_solve(&goal,
                                      path_debug,
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
                if (level->is_sticky(mid_at.x, mid_at.y)) {
                    CON("Robot: Try to break free from the web");
                    return true;
                }
                CON("Robot: Empty move path");
                continue;
            }

            std::reverse(new_move_path.begin(), new_move_path.end());

            auto p = new_move_path[new_move_path.size() - 1];

            std::string goal_path_str = "";
            for (auto p1 : new_move_path) {
                goal_path_str += p1.to_string() + " ";
            }

            bool logged_one = false;
            FOR_ALL_THINGS_THAT_INTERACT(level, it, p.x, p.y) {
                if (it == this) { continue; }

                if (it->is_changing_level ||
                    it->is_hidden ||
                    it->is_falling ||
                    it->is_jumping) {
                    continue;
                }

                if (it->get_immediate_spawned_owner_id().ok()) {
                    continue;
                }

                logged_one = true;

                if (is_player()) {
                    CON("Robot: @(%s, %d,%d) Found a goal: %s %s, via (%s) score %d",
                        level->to_string().c_str(), (int)mid_at.x, (int)mid_at.y,
                        it->to_string().c_str(), result.goal.msg.c_str(),
                        goal_path_str.c_str(),
                        (int)result.goal.score);
                    BOTCON("Robot: goal %s %s",
                           result.goal.msg.c_str(),
                           it->text_the().c_str());
                } else {
                    log("Monst: Found a goal: %s %s, via (%s) score %d",
                        it->to_string().c_str(), result.goal.msg.c_str(),
                        goal_path_str.c_str(),
                        (int)result.goal.score);
                }
            } FOR_ALL_THINGS_END();

            if (!logged_one) {
                FOR_ALL_THINGS(level, it, p.x, p.y) {
                    if (it == this) { continue; }

                    if (it->is_changing_level ||
                        it->is_hidden ||
                        it->is_falling ||
                        it->is_jumping) {
                        continue;
                    }

                    if (it->get_immediate_spawned_owner_id().ok()) {
                        continue;
                    }

                    logged_one = true;

                    if (is_player()) {
                        CON("Robot: @(%s, %d,%d) Found a non active-thing goal: %s %s, via (%s) score %d",
                            level->to_string().c_str(), (int)mid_at.x, (int)mid_at.y,
                            it->to_string().c_str(), result.goal.msg.c_str(),
                            goal_path_str.c_str(),
                            (int)result.goal.score);
                        BOTCON("Robot: goal %s %s",
                            result.goal.msg.c_str(),
                            it->text_the().c_str());
                    } else {
                        log("Monst: Found a non active-thing goal: %s %s, via (%s) score %d",
                            it->to_string().c_str(), result.goal.msg.c_str(),
                            goal_path_str.c_str(),
                            (int)result.goal.score);
                    }
                } FOR_ALL_THINGS_END();
            }

            if (!logged_one) {
                if (is_player()) {
                    CON("Robot: @(%s, %d,%d) Found a non thing goal: %s, via (%s) score %d",
                        level->to_string().c_str(), (int)mid_at.x, (int)mid_at.y,
                        result.goal.msg.c_str(),
                        goal_path_str.c_str(),
                        (int)result.goal.score);
                    BOTCON("Robot: goal %s", result.goal.msg.c_str());
                } else {
                    log("Monst: Found a non thing goal: %s via (%s) score %d",
                        result.goal.msg.c_str(),
                        goal_path_str.c_str(),
                        (int)result.goal.score);
                }
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
                if (!game->tick_requested.empty()) {
                    return true;
                }
            } else {
                monstp->move_path = new_move_path;
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
int Thing::robot_ai_init_can_see_dmap (int minx, int miny, int maxx, int maxy,
                                       int search_type)
{_
    std::array< std::array<uint8_t, MAP_WIDTH>, MAP_HEIGHT> can_jump = {};
    point start((int)mid_at.x, (int)mid_at.y);
    auto dmap_can_see = get_dmap_can_see();
    auto seen_map = get_seen_map();
    point at = make_point(mid_at);
    bool jump_allowed = false;

    switch (search_type) {
        case SEARCH_TYPE_LOCAL_JUMP_ALLOWED:
            jump_allowed = true;
            break;
        case SEARCH_TYPE_LOCAL_NO_JUMP:
            jump_allowed = false;
            break;
        case SEARCH_TYPE_GLOBAL_JUMP_ALLOWED:
            jump_allowed = true;
            break;
        case SEARCH_TYPE_GLOBAL_NO_JUMP:
            jump_allowed = false;
            break;
        case SEARCH_TYPE_LAST_RESORTS_NO_JUMP:
            jump_allowed = false;
            break;
        case SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED:
            jump_allowed = true;
            break;
    }

    for (int y = miny; y < maxy; y++) {
        for (int x = minx; x < maxx; x++) {
            point p(x, y);
            int X = x - minx;
            int Y = y - miny;

            if (is_player()) {
                if (!level->is_lit_ever(p)) {
                    set(dmap_can_see->val, X, Y, DMAP_IS_WALL);
                    continue;
                }
            }

            if (!ai_obstacle_for_me(p)) {
                set(dmap_can_see->val, X, Y, DMAP_IS_PASSABLE);
                continue;
            }

            if (level->is_movement_blocking_hard(p)) {
                set(dmap_can_see->val, X, Y, DMAP_IS_WALL);
                continue;
            }

            if (level->is_secret_door(p)) {
                auto dist = distance(p, at);
                if (dist > ROBOT_CAN_SEE_SECRET_DOOR_DISTANCE) {
                    set(dmap_can_see->val, X, Y, DMAP_IS_WALL);
                    continue;
                }
            }

            switch (search_type) {
                case SEARCH_TYPE_LOCAL_NO_JUMP:
                case SEARCH_TYPE_GLOBAL_NO_JUMP:
                case SEARCH_TYPE_LAST_RESORTS_NO_JUMP:
                    if (level->is_lava(p) ||
                        level->is_chasm(p)) {
                        set(dmap_can_see->val, X, Y, DMAP_IS_WALL);
                        continue;
                    }
                    break;
                case SEARCH_TYPE_GLOBAL_JUMP_ALLOWED:
                case SEARCH_TYPE_LOCAL_JUMP_ALLOWED:
                case SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED:
                    break;
            }

            //
            // Can jump but only if not tired.
            //
            if (is_jumper() && (get_stamina() > get_stamina_max() / 2)) {
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

                        if (is_hazardous_to_me(jump_end)) {
                            continue;
                        }

                        if (is_hazardous_to_me(jump_begin)) {
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
                        if (!level->is_lit_ever(jump_begin)) {
                            continue;
                        }

                        //
                        // Too far?
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

    //
    // Grow the search space beyond the light
    //
    std::array< std::array<bool, MAP_WIDTH>, MAP_HEIGHT> walked = {};
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

                int X = x - minx;
                int Y = y - miny;

                if (get(dmap_can_see->val, X, Y) == DMAP_IS_WALL) {
                    continue;
                }

                if (!level->is_lit_ever(p)) {
                    continue;
                }

                //
                // Can't see past walls. However we can see over chasms
                // to expand the search space
                //
                if (level->is_door(p)) {
                    //
                    // Allow us to see doors so we can search them
                    //
                } else if (level->is_movement_blocking_hard(p)) {
                    //
                    // But allow chasms and lava so we can see over. Just block
                    // on walls and pillars etc...
                    //
                    continue;
                }

                set(walked, x, y, true);

                for (auto dx = -1; dx <= 1; dx++) {
                    for (auto dy = -1; dy <= 1; dy++) {
                        point o(p.x + dx, p.y + dy);
                        if (!dx && !dy) {
                            continue;
                        }
                        if (level->is_oob(o)) {
                            continue;
                        }
                        if (!level->is_able_to_stand_on(o)) {
                            continue;
                        }
                        if (level->is_door(o)) {
                            //
                            // Allow us to see doors so we can search them
                            //
                        } else if (level->is_movement_blocking_hard(o)) {
                            //
                            // But allow chasms and lava so we can see over. Just block
                            // on walls and pillars etc...
                            //
                            continue;
                        }
                        set(dmap_can_see->val, X + dx, Y + dy, DMAP_IS_PASSABLE);
                    }
                }
            }
        }
    }
#if 1
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
                if (level->is_movement_blocking_hard(x, y)) {
                    printf("X");
                } else {
                    printf("?");
                }
            } else {
                if (level->is_movement_blocking_hard(x, y)) {
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

    int something_changed = 0;

    for (int y = miny; y < maxy; y++) {
        for (int x = minx; x < maxx; x++) {
            int X = x - minx;
            int Y = y - miny;
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
    if (DEBUG3) {
        dmap_print(dmap_can_see);
    }
    dmap_process(dmap_can_see, point(0, 0), point(maxx - minx, maxy - miny));

    auto t = nearby_most_dangerous_thing_get();
    if (t) {
        something_changed = true;
    }

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

    for (int y = miny; y < maxy; y++) { for (int x = minx; x < maxx; x++) {
        point p(x, y);
        int X = x - minx;
        int Y = y - miny;

        if (get(dmap_can_see->val, X, Y) == DMAP_IS_WALL) {
            continue;
        }

        bool got_a_goal = false;
        bool avoiding = false;
        int terrain_cost = get_terrain_cost(p);
        int total_score = -(int)terrain_cost;

        std::string last_msg;

        FOR_ALL_THINGS_THAT_INTERACT(level, it, p.x, p.y) {
            last_msg = "";

            if (it == this) { continue; }

            if (it->is_changing_level ||
                it->is_hidden ||
                it->is_falling ||
                it->is_jumping) {
                continue;
            }

            if (it->get_immediate_spawned_owner_id().ok()) {
                continue;
            }

            //
            // Worse terrain, less preferred. Higher score, more preferred.
            //
            auto my_health = get_health();
            auto it_health = it->get_health();
            auto health_diff = it_health - my_health;
            bool got_one_this_tile = false;

            //
            // Don't allow of attacking monsts from memory if the player or
            // robot
            //
            auto lit_recently = level->is_lit_recently(it->mid_at.x, it->mid_at.y);
            if (is_player()) {
                if (it->is_offscreen) {
                    lit_recently = false;
                }
            } else {
                lit_recently = true;
            }

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

            if (is_treasure_type_collector()) {
                if (it->is_treasure_type() || it->is_food()) {
                    auto score = worth_collecting(it);
                    if (score) {
                        GOAL_ADD(score, "collect-treasure");
                        got_one_this_tile = true;
                        if (is_player()) {
                            CON("Robot: Is considering collecting %s", it->to_string().c_str());
                        } else {
                            con("Monst: Is considering collecting %s", it->to_string().c_str());
                        }
                    } else {
                        if (is_player()) {
                            CON("Robot: Is not collecting %s", it->to_string().c_str());
                        } else {
                            con("Monst: Is not collecting %s", it->to_string().c_str());
                        }
                    }
                }
            }

            //
            // Need more work before monsts can collect keys
            // as they will be auto collected.
            //
            if (is_key_collector()) {
                if (it->is_key()) {
                    GOAL_ADD(100, "collect-key");
                    got_one_this_tile = true;
                }
            }

            if (!it->is_dead) {
                bool avoid = false;
                auto dist = distance(mid_at, it->mid_at);
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
                        //
                        // Cannot avoid if this thing is beating on us
                        //
                        avoid = false;

                        //
                        // The closer an enemy is (something that attacked us), the
                        // higher the score
                        //
                        GOAL_ADD((int)(max_dist - dist) * 200, "attack-enemy");
                        got_one_this_tile = true;
                    } else if (!avoid && (dist < ai_avoid_distance() && will_avoid_monst(it))) {
                        //
                        // Monsters we avoid are more serious threats
                        //
                        avoid = true;
                    } else if (!avoid && it->is_minion_generator()) {
                        //
                        // Very close, high priority attack
                        //
                        GOAL_ADD((int)(max_dist - dist) * 200, "attack-nearby-generator");
                        got_one_this_tile = true;
                    } else if (!avoid && it->is_monst()) {
                        if (dist < 2) {
                            //
                            // Very close, high priority attack
                            //
                            GOAL_ADD((int)(max_dist - dist) * 100, "attack-nearby-monst");
                            got_one_this_tile = true;
                        } else if (dist < max_dist) {
                            //
                            // Further away close, lower priority attack
                            //
                            GOAL_ADD((int)(max_dist - dist) * 10, "attack-maybe-monst");
                            got_one_this_tile = true;
                        }
                    }
                }

                if (!avoid && it->is_spiderweb() && !dist) {
                    //
                    // Very close, high priority attack
                    //
                    GOAL_ADD(666, "get-out-of-web");
                    got_one_this_tile = true;
                }

                if (avoid) {
                    if (is_player()) {
                        CON("Robot: Thinks it needs to avoid %s", it->to_string().c_str());
                    } else {
                        log("Monst: Thinks it needs to avoid %s", it->to_string().c_str());
                    }

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

                            int dist = distance(mid_at + fpoint(dx, dy), it->mid_at);
                            if (dist < ai_avoid_distance()) {
                                continue;
                            }

                            point p(mid_at.x + dx, mid_at.y + dy);
                            if (ai_obstacle_for_me(p)) {
                                continue;
                            }

                            int terrain_cost = get_terrain_cost(p);
                            int total_score = -(int)terrain_cost;
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

                                int dist = distance(mid_at + fpoint(dx, dy), it->mid_at);
                                point p(mid_at.x + dx, mid_at.y + dy);
                                if (ai_obstacle_for_me(p)) {
                                    continue;
                                }

                                int terrain_cost = get_terrain_cost(p);
                                int total_score = -(int)terrain_cost;
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
                        CON("Robot could not avoid, so attack %s", it->to_string().c_str());
                    }
                }

                if (!got_one_this_tile) {
                    //
                    // No hunting monsters we cannot see just because we
                    // have visited that area before.
                    //
                    // Well this is true for the player. Monsters, we're
                    // lenient.
                    //
                    if (lit_recently) {
                        if (possible_to_attack(it)) {
                            GOAL_ADD(- health_diff, "can-attack-monst");
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
                    GOAL_ADD(1, "preferred-terrain");
                }
            }

            if (got_one_this_tile) {
                if (is_player()) {
                    CON("Robot: Is considering: %s %s", it->to_string().c_str(), last_msg.c_str());
                } else {
                    log("Monst: Is considering %s %s", it->to_string().c_str(), last_msg.c_str());
                }
            } else {
                if (is_player()) {
                    CON("Robot: Is not considering: %s %s", it->to_string().c_str(), last_msg.c_str());
                } else {
                    log("Monst: Is not considering %s %s", it->to_string().c_str(), last_msg.c_str());
                }
            }

        } FOR_ALL_THINGS_END();

        if (avoiding) {
            set(dmap_can_see->val, X, Y, DMAP_IS_WALL);
        } else if (got_a_goal) {
            goals.insert(Goal(total_score, point(X, Y), last_msg));
            set(dmap_can_see->val, X, Y, DMAP_IS_GOAL);
        } else if (terrain_cost) {
            set(dmap_can_see->val, X, Y, (uint8_t)terrain_cost);
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
void Thing::robot_ai_choose_search_goals (std::multiset<Goal> &goals,
                                          int search_type)
{_
    point start((int)mid_at.x, (int)mid_at.y);

    std::array< std::array<bool, MAP_WIDTH>, MAP_HEIGHT> walked = {};
    std::array< std::array<bool, MAP_WIDTH>, MAP_HEIGHT> pushed = {};
    std::deque<point> in;
    std::deque<point> can_reach_cands;
    std::deque<Thingp> out;
    in.push_back(start);
    set(pushed, start.x, start.y, true);

    auto dmap_can_see = get_dmap_can_see();
    if (DEBUG3) {
        log("Dmap, can see:");
        dmap_print(dmap_can_see);
    }

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
        if (p.x < MAP_BORDER_ROCK) {
            continue;
        }
        if (p.y < MAP_BORDER_ROCK) {
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

        //
        // Look as far as our memory and lighting permits
        //
        auto dist = distance(make_fpoint(p), mid_at);
        float max_dist = ai_scent_distance();

        int jump_distance;

        switch (search_type) {
            case SEARCH_TYPE_LOCAL_JUMP_ALLOWED:
                if (dist >= max_dist) {
                    continue;
                }
                jump_distance = how_far_i_can_jump();
                break;
            case SEARCH_TYPE_LOCAL_NO_JUMP:
                if (dist >= max_dist) {
                    continue;
                }
                jump_distance = 0;
                break;
            case SEARCH_TYPE_GLOBAL_JUMP_ALLOWED:
                jump_distance = how_far_i_can_jump();
                break;
            case SEARCH_TYPE_GLOBAL_NO_JUMP:
                jump_distance = 0;
                break;
            case SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED:
                jump_distance = how_far_i_can_jump();
                break;
            case SEARCH_TYPE_LAST_RESORTS_NO_JUMP:
                jump_distance = 0;
                break;
            default:
                DIE("unexpected search-type case");
                break;
        }

        for (int dx = -jump_distance; dx <= jump_distance; dx++) {
            for (int dy = -jump_distance; dy <= jump_distance; dy++) {
                if (!dx && !dy) {
                    continue;
                }
                point o(p.x + dx, p.y + dy);
                if (level->is_oob(o)) {
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
                } else if (level->is_secret_door(o)) {
                    if (dist > ROBOT_CAN_SEE_SECRET_DOOR_DISTANCE) {
                        continue;
                    }
                } else if (level->is_descend_sewer(o)) {
                    //
                    // Worth investigating unless over
                    //
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
                    if ((o.x == mid_at.x) && (o.y == mid_at.y)) {
                        continue;
                    }
                    if (search_type < SEARCH_TYPE_LAST_RESORTS_NO_JUMP) {
                        continue;
                    }
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

#if 1
    printf("\nrobot search cand\n");
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
            for (auto p : can_reach_cands) {
                if ((x == p.x) && (y == p.y)) {
                    printf("c");
                    goto next;
                }
            }
            if (get(walked, x, y)) {
                if (level->is_movement_blocking_hard(x, y)) {
                    printf("X");
                } else {
                    printf("?");
                }
            } else {
                if (level->is_movement_blocking_hard(x, y)) {
                    printf("x");
                } else {
                    if (level->is_lit_currently(x, y)) {
                        printf("l");
                    } else {
                        printf(" ");
                    }
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
        //
        // Avoid sewer descend/ascend loop
        //
        if ((p.x == mid_at.x) && (p.y == mid_at.y)) {
            continue;
        }

        //
        // Prefer easier terrain
        //
        int terrain_cost = get_terrain_cost(p);
        int total_score = -(int)terrain_cost;

        //
        // Prefer closer
        //
        float dist = distance(start, p);
        total_score -= dist * dist;

        //
        // Choose doors etc... as a last resort when nothing else
        //
        if (level->is_door(p.x, p.y)) {
            total_score -= 100;
        }

        if (level->is_descend_sewer(p.x, p.y)) {
            total_score -= 1000;
            //
            // Prefer not to walk over if there is a way around
            //
            terrain_cost += 10;
        }

        if (level->is_ascend_sewer(p.x, p.y)) {
            total_score -= 2000;
            terrain_cost += 10;
        }

        if (level->is_descend_dungeon(p.x, p.y)) {
            total_score -= 3000;
            terrain_cost += 10;
        }

        if (level->is_ascend_dungeon(p.x, p.y)) {
            total_score -= 4000;
            terrain_cost += 10;
        }

        goals.insert(Goal(total_score, p, "search cand"));
    }
}

bool Thing::robot_ai_choose_nearby_goal (void)
{_
    bool left;
    bool right;
    bool up;
    bool down;
    bool wait = false;
    bool jump = false;
    bool attack = false;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            fpoint at(mid_at.x + dx, mid_at.y + dy);

            FOR_ALL_THINGS(level, it, at.x, at.y) {
                if (it->is_door() && !it->is_open) {
                    if (get_keys()) {
                        if (open_door(it)) {
                            BOTCON("Robot opened a door");
                            game->tick_begin("Robot opened a door");
                            return true;
                        }
                    }

                    //
                    // Try hitting the door
                    //
                    left = dx < 0;
                    right = dx > 0;
                    up = dy < 0;
                    down = dy > 0;
                    attack = true;
                    CON("Robot: Try hitting the door");
                    player_tick(left, right, up, down, attack, wait, jump);
                    return true;
                }

                if (it->is_spiderweb() && (it->mid_at == mid_at)) {
                    //
                    // Try hitting the web
                    //
                    left = dx < 0;
                    right = dx > 0;
                    up = dy < 0;
                    down = dy > 0;
                    attack = true;
                    CON("Robot: Try hitting the door");
                    player_tick(left, right, up, down, attack, wait, jump);
                    return true;
                }

                auto items = anything_to_carry_at(at);
                int item_count = 1;
                if (items.size() >= 1) {
                    for (auto item : items) {
                        CON("Robot: Try to carry [%d] %s", item_count, item->to_string().c_str());
                        item_count++;
                        if (try_to_carry(item)) {
                            BOTCON("Robot collected %s", item->text_the().c_str());
                            game->tick_begin("Robot collected " + item->to_string());
                            return true;
                        }
                    }
                }
            } FOR_ALL_THINGS_END();
        }
    }
    return false;
}

void Thing::robot_tick (void)
{_
    //
    // For game smoothness we allow the player to run a bit ahead of the
    // monsters.
    //
    // Do not let the robot do this.
    //
    if (game->things_are_moving) {
        return;
    }

    if (game->tick_completed != game->tick_current) {
        return;
    }

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

    if (level->timestamp_fade_in_begin) {
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

    //
    // See if anything dangerous is close
    //
    auto threat = nearby_most_dangerous_thing_get();
    if (threat) {
        CON("Robot: Nearest thing: %s", threat->to_string().c_str());
    }

    switch (monstp->robot_state) {
        case ROBOT_STATE_IDLE:
        {
            CON("Robot: @(%s, %d,%d) Is idle, look for something to do",
                level->to_string().c_str(), (int)mid_at.x, (int)mid_at.y);

            if (!get_stamina()) {
                BOTCON("Robot is forced to rest");
                game->tick_begin("Robot is forced to rest");
                robot_change_state(ROBOT_STATE_RESTING, "need to rest");
                return;
            }

            //
            // Look for doors or things to collect, if not being attacked.
            //
            if (threat && (is_dangerous(threat) || is_enemy(threat))) {
                CON("Robot: A threat is nearby");
                if (get_stamina() < get_stamina_max() / 10) {
                    BOTCON("Robot needs to rest, low on stamina and not safe");
                    game->tick_begin("Robot needs to rest, low on stamina and not safe");
                    robot_change_state(ROBOT_STATE_RESTING, "very low on stamina, rest");
                    return;
                }
            } else {
                if (get_health() < get_health_max() / 2) {
                    BOTCON("Robot needs to rest, low on health");
                    game->tick_begin("Robot needs to rest, low on health");
                    robot_change_state(ROBOT_STATE_RESTING, "low on health, rest");
                    return;
                }

                if (get_stamina() < get_stamina_max() / 3) {
                    BOTCON("Robot needs to rest, low on stamina");
                    game->tick_begin("Robot needs to rest, low on stamina");
                    robot_change_state(ROBOT_STATE_RESTING, "low on stamina, rest");
                    return;
                }

                if (robot_ai_choose_nearby_goal()) {
                    return;
                }
            }

            for (int search_type = 0; search_type < SEARCH_TYPE_MAX; search_type++) {
                if (search_type > 0) {
                    CON("Robot: try to find goals, search-type %d", search_type);
                }
                if (robot_ai_create_path_to_goal(minx, miny, maxx, maxy, search_type)) {
                    if (monstp->move_path.size()) {
                        robot_change_state(ROBOT_STATE_MOVING, "found a new goal");
                    } else {
                        CON("Robot: Did not move, but did something");
                    }
                    return;
                }
            }

            if ((get_health() >= (get_health_max() / 4) * 3) &&
                (get_stamina() >= (get_stamina_max() / 4) * 3)) {
                BOTCON("Robot has nothing to do at all");
                wid_actionbar_robot_mode_off();
            } else {
                BOTCON("Robot has nothing to do, rest");
                game->tick_begin("nothing to do, rest");
                robot_change_state(ROBOT_STATE_RESTING, "nothing to do, rest");
            }
        }
        break;
        case ROBOT_STATE_MOVING:
        {
            CON("Robot: Continue moving");

            //
            // Check for interrupts
            //
            if (robot_ai_init_can_see_dmap(minx, miny, maxx, maxy,
                                           SEARCH_TYPE_LOCAL_JUMP_ALLOWED)) {
                CON("Robot: Something interrupted me");
                game->tick_begin("Robot move interrupted by something");
                robot_change_state(ROBOT_STATE_IDLE, "move interrupted by a change");
                wid_actionbar_init();
                return;
            }

            if (monstp->move_path.empty()) {
                CON("Robot: Move finished");
                BOTCON("Robot move finished");
                game->tick_begin("Robot move finished");
                robot_change_state(ROBOT_STATE_IDLE, "move finished");
                wid_actionbar_init();
                return;
            } else {
                CON("Robot: Moving");
                game->tick_begin("Robot move");
                return;
            }
        }
        break;
        case ROBOT_STATE_RESTING:
        {
            if ((get_health() >= (get_health_max() / 4) * 3) &&
                (get_stamina() >= (get_stamina_max() / 4) * 3)) {

                BOTCON("Robot has rested enough");
                game->tick_begin("Robot has rested enough");
                robot_change_state(ROBOT_STATE_IDLE, "rested enough");
                return;
            }

            if (get_stamina()) {
                if (threat && (is_dangerous(threat) || is_enemy(threat))) {
                    BOTCON("Robot sees a nearby threat, stop resting");
                    game->tick_begin("Robot sees a nearby threat, stop resting");
                    robot_change_state(ROBOT_STATE_IDLE, "threat nearby, stop resting");
                    return;
                }
            }

            if (eat_something()) {
                BOTCON("Robot needs to eat");
                game->tick_begin("Robot ate something");
                return;
            }

            if (get_stamina() >= (get_stamina_max() / 4) * 3) {
                BOTCON("Robot has recovered stamina");
                game->tick_begin("Robot has recovered stamina");
                robot_change_state(ROBOT_STATE_IDLE, "threat nearby, stop resting");
                return;
            }

            CON("Robot: Wait and rest");
            do_something = true;
            wait = true;
            break;
        }
        break;

        case ROBOT_STATE_OPEN_INVENTORY:
        {
        }
    }

    log("Robot: Do something");
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
        case ROBOT_STATE_RESTING:
            to = "RESTING";
            break;
        case ROBOT_STATE_OPEN_INVENTORY:
            to = "OPEN-INVENTORY";
            break;
    }
    switch (monstp->robot_state) {
        case ROBOT_STATE_IDLE:
            from = "IDLE";
            break;
        case ROBOT_STATE_MOVING:
            from = "MOVING";
            break;
        case ROBOT_STATE_RESTING:
            from = "RESTING";
            break;
        case ROBOT_STATE_OPEN_INVENTORY:
            from = "OPEN-INVENTORY";
            break;
    }

    CON("Robot: %s -> %s: %s", from.c_str(), to.c_str(), why.c_str());

    monstp->robot_state = new_state;
    switch (new_state) {
        case ROBOT_STATE_IDLE:
            clear_move_path("Robot is idle");
            BOTCON("Robot is idle");
            break;
        case ROBOT_STATE_MOVING:
            BOTCON("Robot is moving");
            break;
        case ROBOT_STATE_RESTING:
            BOTCON("Robot is resting");
            break;
        case ROBOT_STATE_OPEN_INVENTORY:
            BOTCON("Robot is looking in its inventory");
            break;
    }
}
