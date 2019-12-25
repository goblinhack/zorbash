/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_dungeon.h"

void World::clear (void)
{_
    _is_blood = {};
    _is_corridor = {};
    _is_deep_water = {};
    _is_dirt = {};
    _is_floor = {};
    _is_lava = {};
    _is_rock = {};
    _is_visited = {};
    _is_gfx_large_shadow_caster = {};
    _is_wall = {};
    _is_water = {};
    _is_dungeon = {};

    next_thing_id = 1;
    timestamp_dungeon_created = time_get_time_ms();
    timestamp_dungeon_saved = 0;
}
