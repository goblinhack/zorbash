//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_dungeon.h"
#include "my_thing.h"

std::string Level::to_string (void)
{_
    return (world_at.to_string());
}

const char * Level::to_cstring (void)
{_
    return (to_string().c_str());
}

bool Level::is_anything_at (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }

    for (auto id : get(all_thing_ids_at, x, y)) {
        if (id) {
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

void Level::set_lava (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_lava, x, y, true);
}

void Level::unset_lava (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_lava, x, y, false);
}

bool Level::is_chasm (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_chasm, x, y));
}

void Level::set_chasm (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_chasm, x, y, true);
}

void Level::unset_chasm (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
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

void Level::set_hazard (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_hazard, x, y, true);
}

void Level::unset_hazard (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
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

void Level::set_secret_door (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_secret_door, x, y, true);
}

void Level::unset_secret_door (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
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

void Level::set_blood (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_blood, x, y, true);
}

void Level::unset_blood (const int x, const int y)
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

void Level::set_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_water, x, y, true);
}

void Level::unset_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
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

void Level::set_deep_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_deep_water, x, y, true);
}

void Level::unset_deep_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
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

void Level::set_wall (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_wall, x, y, true);
}

void Level::unset_wall (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
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

void Level::set_corridor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_corridor, x, y, true);
}

void Level::unset_corridor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
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

void Level::set_dirt (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_dirt, x, y, true);
}

void Level::unset_dirt (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_dirt, x, y, false);
}

bool Level::is_floor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_floor, x, y));
}

void Level::set_floor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_floor, x, y, true);
}

void Level::unset_floor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_floor, x, y, false);
}

bool Level::is_monst (const point &p)
{_
    return (is_monst(p.x, p.y));
}

bool Level::is_monst (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }

    for (auto id : get(all_thing_ids_at, x, y)) {
        if (id) {
            auto t = thing_find(id);
            auto tpp = t->tp();
            if (tp_is_monst(tpp)) {
                return (true);
            }
        }
    }
    return (false);
}

bool Level::is_food (const point &p)
{_
    return (is_food(p.x, p.y));
}

bool Level::is_food (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }

    for (auto id : get(all_thing_ids_at, x, y)) {
        if (id) {
            auto t = thing_find(id);
            auto tpp = t->tp();
            if (tp_is_food(tpp)) {
                return (true);
            }
        }
    }
    return (false);
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

void Level::set_rock (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_rock, x, y, true);
}

void Level::unset_rock (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_rock, x, y, false);
}

bool Level::is_visited (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_visited, p.x, p.y));
}

bool Level::is_visited (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_visited, x, y));
}

void Level::set_visited (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_visited, x, y, true);
}

void Level::unset_visited (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_visited, x, y, false);
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
    set(_is_dungeon, x, y, true);
}

void Level::unset_dungeon (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_dungeon, x, y, false);
}

bool Level::is_key (const point &p)
{_
    return (is_key(p.x, p.y));
}

bool Level::is_key (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }

    for (auto id : get(all_thing_ids_at, x, y)) {
        if (id) {
            auto t = thing_find(id);
            auto tpp = t->tp();
            if (tp_is_key(tpp)) {
                return (true);
            }
        }
    }
    return (false);
}

bool Level::is_gfx_large_shadow (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_gfx_large_shadow, p.x, p.y));
}

bool Level::is_gfx_large_shadow (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_gfx_large_shadow, x, y));
}

void Level::set_gfx_large_shadow (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_gfx_large_shadow, x, y, true);
}

void Level::unset_gfx_large_shadow (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_gfx_large_shadow, x, y, false);
}

bool Level::is_door (const point &p)
{_
    return (is_door(p.x, p.y));
}

bool Level::is_door (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }

    for (auto id : get(all_thing_ids_at, x, y)) {
        if (id) {
            auto t = thing_find(id);
            auto tpp = t->tp();
            if (tp_is_door(tpp)) {
                return (true);
            }
        }
    }
    return (false);
}

void Level::get_all_things_at_depth (int x, int y, int z,
                                     std::vector<Thingp> &l)
{_
    l.resize(0);

    if (unlikely(is_oob(x, y))) {
        return;
    }

    for (auto id : get(all_thing_ids_at, x, y)) {
        if (id) {
            auto t = thing_find(id);
            auto tpp = t->tp();
            if (tpp->z_depth == z) {
                l.push_back(t);
            }
        }
    }
}

void Level::get_all_interesting_things_at (int x, int y, std::vector<Thingp> &l)
{_
    l.resize(0);

    if (unlikely(is_oob(x, y))) {
        return;
    }

    for (auto id : get(all_thing_ids_at, x, y)) {
        if (id) {
            auto t = thing_find(id);
            if (t->is_interesting()) {
                l.push_back(t);
            }
        }
    }
}

void Level::get_all_collision_things_at (int x, int y, std::vector<Thingp> &l)
{_
    l.resize(0);

    if (unlikely(is_oob(x, y))) {
        return;
    }

    for (auto id : get(all_thing_ids_at, x, y)) {
        if (id) {
            auto t = thing_find(id);
            if (t->is_interesting() || t->is_obstacle()) {
                l.push_back(t);
            }
        }
    }
}

void Level::get_all_cursor_path_things_at (int x, int y, std::vector<Thingp> &l)
{_
    l.resize(0);

    if (unlikely(is_oob(x, y))) {
        return;
    }

    for (auto id : get(all_thing_ids_at, x, y)) {
        if (id) {
            auto t = thing_find(id);
            if (t->is_cursor_path()) {
                l.push_back(t);
            }
        }
    }
}

void Level::get_all_light_source_things_at (int x, int y, std::vector<Thingp> &l)
{_
    l.resize(0);

    if (unlikely(is_oob(x, y))) {
        return;
    }

    for (auto id : get(all_thing_ids_at, x, y)) {
        if (id) {
            auto t = thing_find(id);
            if (t->get_light()) {
                l.push_back(t);
            }
        }
    }
}

void Level::get_all_active_things_at (int x, int y, std::vector<Thingp> &l)
{_
    l.resize(0);
#ifdef DEBUG_CRASH
    std::vector<uint32_t> ids;
#endif

    if (unlikely(is_oob(x, y))) {
        return;
    }

    for (auto id : get(all_thing_ids_at, x, y)) {
        if (id) {
            auto t = thing_find(id);
            if (t->is_active() || t->is_movable()) {
                l.push_back(t);
#ifdef DEBUG_CRASH
                ids.push_back(id);
                if (std::count(l.begin(), l.end(), t) > 1) {
                    t->die("thing appears multiple times on the map");
                }
                if (std::count(ids.begin(), ids.end(), id) > 1) {
                    t->die("ID appears multiple times on the map");
                }
#endif
            }
        }
    }
}

void Level::get_all_obstacle_things_at (int x, int y, std::vector<Thingp> &l)
{_
    l.resize(0);

    if (unlikely(is_oob(x, y))) {
        return;
    }

    for (auto id : get(all_thing_ids_at, x, y)) {
        if (id) {
            auto t = thing_find(id);
            if (t->is_obstacle()) {
                l.push_back(t);
            }
        }
    }
}
