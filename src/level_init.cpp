//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_dungeon.h"
#include "my_thing.h"
#include "my_ptrcheck.h"

Level::Level (void)
{_
    newptr(this, "level");
}

void Level::clear (void)
{_
    _fade_in_map = {};
    _heatmap = {};
    _is_blood = {};
    _is_chasm = {};
    _is_corpse = {};
    _is_corridor = {};
    _is_bridge = {};
    _is_deep_water = {};
    _is_shallow_water = {};
    _is_dirt = {};
    _is_door = {};
    _is_dungeon = {};
    _is_ascend_dungeon = {};
    _is_descend_dungeon = {};
    _is_ascend_sewer = {};
    _is_descend_sewer = {};
    _is_fire = {};
    _is_floor = {};
    _is_food = {};
    _is_gold = {};
    _is_lava = {};
    _is_acid = {};
    _is_poison = {};
    _is_light_blocker = {};
    _is_movement_blocking_hard = {};
    _is_movement_blocking_soft = {};
    _is_monst = {};
    _is_rock = {};
    _is_smoke = {};
    _is_treasure = {};
    _is_treasure_class_a = {};
    _is_treasure_class_b = {};
    _is_treasure_class_c = {};
    _is_visited = {};
    _is_lit = {};
    _is_wall = {};
    _gfx_water = {};

    timestamp_dungeon_created = time_get_time_ms();
    timestamp_dungeon_saved = 0;
}
