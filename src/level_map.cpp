//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_thing.h"

void Level::update_hazard_map (void)
{
    //
    // The water tiles are twice the size of normal tiles, so work out
    // where to draw them to avoid overlaps
    //
    lava_tile_map = {};
    chasm_tile_map = {};
    water_tile_map = {};
    deep_water_tile_map = {};

    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_WIDTH; x++) {
            if (level->is_water(x, y) || level->is_deep_water(x, y)) {
                for (auto dx = -2; dx <= 2; dx++) {
                    for (auto dy = -2; dy <= 2; dy++) {
                        set(water_tile_map, x+dx, y+dy, true);
                        if (level->is_deep_water(x, y)) {
                            set(deep_water_tile_map, x+dx, y+dy, true);
                        }
                    }
                }
            }

            if (level->is_lava(x, y)) {
                for (auto dx = -2; dx <= 2; dx++) {
                    for (auto dy = -2; dy <= 2; dy++) {
                        set(lava_tile_map, x+dx, y+dy, true);
                    }
                }
            }

            if (level->is_chasm(x, y)) {
                for (auto dx = -2; dx <= 2; dx++) {
                    for (auto dy = -2; dy <= 2; dy++) {
                        set(chasm_tile_map, x+dx, y+dy, true);
                    }
                }
            }
        }
    }
}

void Level::update_map (void)
{
    update_hazard_map();
}

bool Level::is_anything_at (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }

    for (auto& t : get(all_thing_ptrs_at, x, y)) {
        if (t) {
            verify(t);
            return (true);
        }
    }
    return (false);
}

bool Level::is_anything_at (const point &p)
{_
    return (is_anything_at(p.x, p.y));
}

bool Level::is_lava (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_lava, p.x, p.y));
}

bool Level::is_lava (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_lava, x, y));
}

void Level::set_is_lava (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_lava, x, y, true);
}

void Level::unset_is_lava (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_lava, x, y, false);
}

bool Level::is_chasm (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_chasm, x, y));
}

void Level::set_is_chasm (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_chasm, x, y, true);
}

void Level::unset_is_chasm (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_chasm, x, y, false);
}

bool Level::is_hazard (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_hazard, p.x, p.y));
}

bool Level::is_hazard (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_hazard, x, y));
}

void Level::set_is_hazard (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_hazard, x, y, true);
}

void Level::unset_is_hazard (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_hazard, x, y, false);
}

bool Level::is_secret_door (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_secret_door, p.x, p.y));
}

bool Level::is_secret_door (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_secret_door, x, y));
}

void Level::set_is_secret_door (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_secret_door, x, y, true);
}

void Level::unset_is_secret_door (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_secret_door, x, y, false);
}

bool Level::is_blood (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_blood, p.x, p.y));
}

bool Level::is_blood (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_blood, x, y));
}

void Level::set_is_blood (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_blood, x, y, true);
}

void Level::unset_is_blood (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_blood, x, y, false);
}

bool Level::is_water (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_water, p.x, p.y));
}

bool Level::is_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_water, x, y));
}

void Level::set_is_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_water, x, y, true);
}

void Level::unset_is_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_water, x, y, false);
}

bool Level::is_deep_water (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_deep_water, p.x, p.y));
}

bool Level::is_deep_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_deep_water, x, y));
}

void Level::set_is_deep_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_deep_water, x, y, true);
}

void Level::unset_is_deep_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_deep_water, x, y, false);
}

bool Level::is_wall (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_wall, p.x, p.y));
}

bool Level::is_wall (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_wall, x, y));
}

void Level::set_is_wall (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_wall, x, y, true);
}

void Level::unset_is_wall (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_wall, x, y, false);
}

bool Level::is_corridor (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_corridor, p.x, p.y));
}

bool Level::is_corridor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_corridor, x, y));
}

void Level::set_is_corridor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_corridor, x, y, true);
}

void Level::unset_is_corridor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_corridor, x, y, false);
}

bool Level::is_dirt (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_dirt, p.x, p.y));
}

bool Level::is_dirt (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_dirt, x, y));
}

void Level::set_is_dirt (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_dirt, x, y, true);
}

void Level::unset_is_dirt (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_dirt, x, y, false);
}

bool Level::is_floor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_floor, x, y));
}

void Level::set_is_floor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_floor, x, y, true);
}

void Level::unset_is_floor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_floor, x, y, false);
}

bool Level::is_rock (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_rock, p.x, p.y));
}

bool Level::is_rock (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_rock, x, y));
}

void Level::set_is_rock (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_rock, x, y, true);
}

void Level::unset_is_rock (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_rock, x, y, false);
}

bool Level::is_dungeon (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_dungeon, p.x, p.y));
}

bool Level::is_dungeon (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_dungeon, x, y));
}

void Level::set_dungeon (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_dungeon, x, y, true);
}

void Level::unset_dungeon (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    set(_is_dungeon, x, y, false);
}

bool Level::is_corpse (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_corpse, p.x, p.y));
}

bool Level::is_corpse (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_corpse, x, y));
}

void Level::set_is_corpse (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_corpse, x, y, true);
}

void Level::unset_is_corpse (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_corpse, x, y, false);
}

bool Level::is_fire (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_fire, p.x, p.y));
}

bool Level::is_fire (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_fire, x, y));
}

void Level::set_is_fire (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_fire, x, y, true);
}

void Level::unset_is_fire (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_fire, x, y, false);
}

bool Level::is_monst (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_monst, p.x, p.y));
}

bool Level::is_monst (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_monst, x, y));
}

void Level::set_is_monst (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_monst, x, y, true);
}

void Level::unset_is_monst (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_monst, x, y, false);
}

bool Level::is_door (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_door, p.x, p.y));
}

bool Level::is_door (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_door, x, y));
}

void Level::set_is_door (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_door, x, y, true);
}

void Level::unset_is_door (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_door, x, y, false);
}

bool Level::is_key (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_key, p.x, p.y));
}

bool Level::is_key (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_key, x, y));
}

void Level::set_is_key (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_key, x, y, true);
}

void Level::unset_is_key (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_key, x, y, false);
}

bool Level::is_food (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_food, p.x, p.y));
}

bool Level::is_food (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_food, x, y));
}

void Level::set_is_food (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_food, x, y, true);
}

void Level::unset_is_food (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_food, x, y, false);
}

bool Level::is_treasure (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_treasure, p.x, p.y));
}

bool Level::is_treasure (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_treasure, x, y));
}

void Level::set_is_treasure (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_treasure, x, y, true);
}

void Level::unset_is_treasure (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_treasure, x, y, false);
}
