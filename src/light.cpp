/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_light.h"
#include "my_game.h"

static uint32_t light_id;

Lightp light_new (uint16_t max_light_rays)
{_
    auto id = ++light_id;

    auto t = std::make_shared< class Light >();
    auto result = game.state.map.all_lights.insert(std::make_pair(id, t));

    if (result.second == false) {
        DIE("light insert [%d] failed", id);
    }

    t->id = id;
    t->is_on_map      = false;
    t->max_light_rays = max_light_rays;

    // t->log("created");
    t->reset();

    return (t);
}

void Light::destroyed (void)
{_
    auto t = this;

    game.state.map.all_lights.erase(t->id);
}

void Light::pop (void)
{_
    auto t = this;

    if (unlikely(!t->is_on_map)) {
        return;
    }

    t->is_on_map = false;

    fpoint oob = { -1, -1 };
    t->at = oob;

    t->log("pop");
}

void Light::reset (void)
{_
    std::fill(ray_depth_buffer.begin(), 
              ray_depth_buffer.begin() + max_light_rays, 0.0);
    std::fill(ray_rad.begin(), ray_rad.begin() + max_light_rays, 0.0);
}

void Light::move_to (fpoint to)
{_
    auto t = this;

    t->is_on_map = true;

    t->at = to;
}

void Light::move_delta (fpoint delta)
{_
    auto t = this;

    t->move_to(t->at + delta);
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

    snprintf(tmp[loop], sizeof(tmp[loop]) - 1, "light %u at (%g,%g)",
             t->id, t->at.x, t->at.y);

    return (tmp[loop++]);
}
