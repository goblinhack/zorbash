//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>
#include <set>
#include "my_main.h"
#include "my_level.h"
#include "my_dmap.h"
#include "my_math.h"
#include "my_thing.h"

bool Thing::spawn_next_to (const std::string& what)
{
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

        if (will_avoid(point(x, y))) {
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

    return (true);
}

bool Thing::spawn_next_to_or_on_monst (const std::string& what)
{
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

        if (level->is_door(x,y)         ||
            level->is_secret_door(x,y)  ||
            level->is_generator(x,y)    ||
            level->is_hazard(x,y)       ||
            level->is_rock(x, y)        ||
            level->is_wall(x, y)) {
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

    return (true);
}

bool Thing::spawn_fire (const std::string& what)
{
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

        possible.push_back(p);
    }

    auto cands = possible.size();
    if (!cands) {
        return false;
    }

    auto chosen = possible[random_range(0, cands)];

    auto c = level->thing_new(what, chosen);
    c->inherit_from(this);

    return (true);
}

bool Thing::spawn_under (const std::string& what)
{
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

    return (true);
}
