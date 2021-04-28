//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>
#include "my_game.h"
#include "my_sys.h"
#include "my_sys.h"
#include "my_level.h"
#include "my_dmap.h"
#include "my_math.h"
#include "my_thing.h"
#include "my_random.h"
#include "my_thing_template.h"

bool Thing::spawn_next_to (const std::string& what)
{_
    log("Spawn %s next to", what.c_str());
_
    std::vector<point> possible;
    static const std::vector<point> all_deltas = {
        point(-1, -1),
        point( 1, -1),
        point(-1,  1),
        point( 1,  1),
        point(0, -1),
        point(-1, 0),
        point(1, 0),
        point(0, 1),
    };

    auto tpp = tp_find(what);
    if (!tpp) {
        err("Cannot find %s to spawn", what.c_str());
        return false;
    }

    //
    // Don't spawn too many monsts
    //
    if (tpp->is_monst()) {
        if (level->monst_count >= LEVELS_MONST_COUNT) {
            log("Too many minions");
            return false;
        }
    }

    //
    // Don't spawn too many minions
    //
    if (is_minion_generator()) {
        if (get_minion_count() >= minion_limit()) {
            return false;
        }
    }

    for (const auto& d : all_deltas) {
        auto x = mid_at.x + d.x;
        auto y = mid_at.y + d.y;
        auto p = point(x, y);

        //
        // No spawning onto chasms for example
        //
        if (tpp->will_avoid_threat(level, p)) {
            continue;
        }

        if (collision_obstacle(p)) {
            continue;
        }

        possible.push_back(p);
    }

    auto cands = possible.size();
    if (!cands) {
        return false;
    }

    auto chosen = possible[random_range(0, cands)];
    auto c = level->thing_new(what, chosen);
    c->inherit_from(this);
    c->location_check();

    if (c->is_minion()) {
        c->set_minion_owner(this);
    }

    if (is_spawner()) {
        c->set_spawned_owner(this);
    }

    return true;
}

bool Thing::spawn_next_to_or_on_monst (const std::string& what)
{_
    log("Spawn %s next to or on monst", what.c_str());

    std::vector<point> possible;
    static const std::vector<point> all_deltas = {
        point(-1, -1),
        point( 1, -1),
        point(-1,  1),
        point( 1,  1),
        point(0, -1),
        point(-1, 0),
        point(1, 0),
        point(0, 1),
    };

    auto tpp = tp_find(what);
    if (!tpp) {
        err("Cannot find %s to spawn", what.c_str());
        return false;
    }

    //
    // Don't spawn too many monsts
    //
    if (tpp->is_monst()) {
        if (level->monst_count >= LEVELS_MONST_COUNT) {
            return false;
        }
    }

    for (const auto& d : all_deltas) {
        auto x = mid_at.x + d.x;
        auto y = mid_at.y + d.y;
        auto p = point(x, y);

        if (level->is_door(x,y)         ||
            level->is_secret_door(x,y)  ||
            level->is_minion_generator(x,y)    ||
            level->is_hazard(x,y)       ||
            level->is_rock(x, y)        ||
            level->is_wall(x, y)) {
            continue;
        }

        //
        // No spawning onto chasms for example
        //
        if (tpp->will_avoid_threat(level, p)) {
            continue;
        }

        if (collision_obstacle(p)) {
            continue;
        }

        possible.push_back(p);
    }

    auto cands = possible.size();
    if (!cands) {
        return false;
    }

    auto chosen = possible[random_range(0, cands)];

    auto c = level->thing_new(what, chosen);
    c->inherit_from(this);
    c->location_check();

    if (is_spawner()) {
        c->set_spawned_owner(this);
    }

    return true;
}

bool Thing::spawn_radius_range (Thingp item, Thingp target, 
                                const std::string& what, 
                                uint32_t radius_min, uint32_t radius_max)
{_
    auto tpp = tp_find(what);
    if (!tpp) {
        err("Cannot find %s to spawn", what.c_str());
        return false;
    }

    if (!target) {
        err("No target to spawn %s", what.c_str());
        return false;
    }

    if (!item) {
        err("No item to spawn %s", what.c_str());
        return false;
    }

    if (!radius_min && !radius_max) {
        radius_min = item->tp()->blast_min_radius();
        radius_max = item->tp()->blast_max_radius();
    }

    log("Spawn %s in radius range %u to %u", 
        what.c_str(), radius_min, radius_max);

    //
    // Don't spawn too many monsts
    //
    if (tpp->is_monst()) {
        if (level->monst_count >= LEVELS_MONST_COUNT) {
            return false;
        }
    }

    auto mid_at = target->mid_at;

    for (auto x = mid_at.x - radius_max; x <= mid_at.x + radius_max; x++) {
        for (auto y = mid_at.y - radius_max; y <= mid_at.y + radius_max; y++) {
            float dist = DISTANCE(x, y, mid_at.x, mid_at.y);

            if (dist >= radius_max + 1) {
                continue;
            }

            if (dist < radius_min) {
                continue;
            }

            if (level->is_rock(x, y) ||
                level->is_wall(x, y)) {
                continue;
            }

            auto c = level->thing_new(what, fpoint(x, y));
            c->inherit_from(this);
            c->location_check();
            c->set_timestamp_sleep_end(time_get_time_ms_cached() + dist * 100);

            if (is_spawner()) {
                c->set_spawned_owner(this);
            }
        }
    }

    return true;
}

bool Thing::spawn_fire (const std::string& what)
{_
    log("Spawn fire: %s", what.c_str());

    std::vector<point> possible;
    static const std::vector<point> all_deltas = {
        point(-1, -1),
        point( 1, -1),
        point(-1,  1),
        point( 1,  1),
        point(0, -1),
        point(-1, 0),
        point(1, 0),
        point(0, 1),
    };

    for (const auto& d : all_deltas) {
        auto x = mid_at.x + d.x;
        auto y = mid_at.y + d.y;
        auto p = point(x, y);

        if (level->is_hazard(x,y)       ||
            level->is_rock(x, y)        ||
            level->is_wall(x, y)) {
            continue;
        }

        if (collision_obstacle(p)) {
            continue;
        }

        possible.push_back(p);
    }

    auto cands = possible.size();
    if (!cands) {
        return false;
    }

    auto chosen = possible[random_range(0, cands)];

    auto c = level->thing_new(what, chosen);
    c->log("Spawned");
    c->inherit_from(this);
    c->location_check();

    if (is_spawner()) {
        c->set_spawned_owner(this);
    }

    return true;
}

bool Thing::spawn_at_if_possible (const std::string& what)
{_
    log("Spawn under: %s", what.c_str());

    std::vector<point> possible;
    auto x = mid_at.x;
    auto y = mid_at.y;
    auto p = point(x, y);

    if (level->is_hazard(x,y)       ||
        level->is_rock(x, y)        ||
        level->is_wall(x, y)) {
        return false;
    }

    possible.push_back(p);

    auto cands = possible.size();
    if (!cands) {
        return false;
    }

    auto chosen = possible[random_range(0, cands)];

    auto c = level->thing_new(what, chosen);
    c->inherit_from(this);
    c->location_check();

    if (is_spawner()) {
        c->set_spawned_owner(this);
    }

    return true;
}

bool Thing::spawn_at (const std::string& what)
{_
    log("Spawn under: %s", what.c_str());

    std::vector<point> possible;
    auto x = mid_at.x;
    auto y = mid_at.y;
    auto p = point(x, y);

    possible.push_back(p);

    auto cands = possible.size();
    if (!cands) {
        return false;
    }

    auto chosen = possible[random_range(0, cands)];

    auto c = level->thing_new(what, chosen);
    c->inherit_from(this);
    c->location_check();

    if (is_spawner()) {
        c->set_spawned_owner(this);
    }

    return true;
}
