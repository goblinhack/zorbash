/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_game.h"
#include "my_light.h"

static uint32_t light_id;

Lightp light_new (uint16_t max_light_rays, fpoint at)
{_
    auto id = ++light_id;

    auto t = std::make_shared< class Light >();
    t->id = id;
    auto p = std::make_pair(t->id, t);
    auto result = game.state.map.all_lights.insert(p);
    if (result.second == false) {
        DIE("light insert [%d] failed", id);
    }

    point new_at((int)at.x, (int)at.y);
    auto n = &game.state.map.lights[new_at.x][new_at.y];
    result = n->insert(p);
    if (result.second == false) {
        DIE("light insert into map [%d] failed", id);
    }

    t->at = at;
    // t->log("created");
    return (t);
}

void Light::pop (void)
{_
    auto t = this;

    game.state.map.all_lights.erase(t->id);
_
    /*
     * Pop from the map
     */
    point old_at((int)at.x, (int)at.y);
    auto o = &game.state.map.lights[old_at.x][old_at.y];
    auto iter = o->find(t->id);
    if (iter == o->end()) {
        t->die("thing not found to destroy");
    }
_
    auto value = (*o)[t->id];
    o->erase(iter);
}

void Light::move_to (fpoint to)
{_
    auto t = this;

    point old_at((int)t->at.x, (int)t->at.y);
    point new_at((int)to.x, (int)to.y);

    /*
     * Keep track of where this light is on the grid
     */
    if (old_at != new_at) {
        /*
         * Pop
         */
        auto o = game.state.map.lights[old_at.x][old_at.y];
        auto iter = o.find(t->id);
        auto value = o[t->id];
        o.erase(iter);

        /*
         * Add back
         */
        auto n = game.state.map.lights[new_at.x][new_at.y];
        n.insert(std::make_pair(t->id, value));
    }

    t->at = to;
}

/*
 * Find an existing light.
 */
Lightp light_find (uint32_t id)
{_
    auto result = game.state.map.all_lights.find(id);
    if (result == game.state.map.all_lights.end()) {
        return (0);
    }

    return (result->second);
}

std::string Light::logname (void)
{_
    auto t = this;

    /*
     * Return constant strings from a small pool.
     */
    static char tmp[10][MAXSTR];
    static int loop;

    if (loop >= 10) {
        loop = 0;
    }

    snprintf(tmp[loop], sizeof(tmp[loop]) - 1, "%u at (%g,%g)",
             t->id,  t->at.x, t->at.y);

    return (tmp[loop++]);
}
