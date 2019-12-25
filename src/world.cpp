/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_dungeon.h"

bool World::is_anything_at (const int x, const int y)
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

bool World::is_anything_at (const point &p)
{_
    return (is_anything_at(p.x, p.y));
}

bool World::is_lava (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_lava, p.x, p.y));
}

bool World::is_lava (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_lava, x, y));
}

void World::set_lava (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_lava, x, y, true);
}

void World::unset_lava (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_lava, x, y, false);
}

bool World::is_blood (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_blood, p.x, p.y));
}

bool World::is_blood (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_blood, x, y));
}

void World::set_blood (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_blood, x, y, true);
}

void World::unset_blood (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_blood, x, y, false);
}

bool World::is_water (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_water, p.x, p.y));
}

bool World::is_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_water, x, y));
}

void World::set_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_water, x, y, true);
}

void World::unset_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_water, x, y, false);
}

bool World::is_deep_water (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_deep_water, p.x, p.y));
}

bool World::is_deep_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_deep_water, x, y));
}

void World::set_deep_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_deep_water, x, y, true);
}

void World::unset_deep_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_deep_water, x, y, false);
}

bool World::is_wall (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_wall, p.x, p.y));
}

bool World::is_wall (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_wall, x, y));
}

void World::set_wall (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_wall, x, y, true);
}

void World::unset_wall (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_wall, x, y, false);
}

bool World::is_corridor (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_corridor, p.x, p.y));
}

bool World::is_corridor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_corridor, x, y));
}

void World::set_corridor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_corridor, x, y, true);
}

void World::unset_corridor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_corridor, x, y, false);
}

bool World::is_dirt (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_dirt, p.x, p.y));
}

bool World::is_dirt (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_dirt, x, y));
}

void World::set_dirt (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_dirt, x, y, true);
}

void World::unset_dirt (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_dirt, x, y, false);
}

bool World::is_floor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_floor, x, y));
}

void World::set_floor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_floor, x, y, true);
}

void World::unset_floor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_floor, x, y, false);
}

bool World::is_monst (const point &p)
{_
    return (is_monst(p.x, p.y));
}

bool World::is_monst (const int x, const int y)
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

bool World::is_food (const point &p)
{_
    return (is_food(p.x, p.y));
}

bool World::is_food (const int x, const int y)
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

bool World::is_rock (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_rock, p.x, p.y));
}

bool World::is_rock (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_rock, x, y));
}

void World::set_rock (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_rock, x, y, true);
}

void World::unset_rock (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_rock, x, y, false);
}

bool World::is_visited (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_visited, p.x, p.y));
}

bool World::is_visited (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_visited, x, y));
}

void World::set_visited (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_visited, x, y, true);
}

void World::unset_visited (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_visited, x, y, false);
}

bool World::is_dungeon (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_dungeon, p.x, p.y));
}

bool World::is_dungeon (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_dungeon, x, y));
}

void World::set_dungeon (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_dungeon, x, y, true);
}

void World::unset_dungeon (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_dungeon, x, y, false);
}

bool World::is_key (const point &p)
{_
    return (is_key(p.x, p.y));
}

bool World::is_key (const int x, const int y)
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

bool World::is_gfx_large_shadow_caster (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_gfx_large_shadow_caster, p.x, p.y));
}

bool World::is_gfx_large_shadow_caster (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_gfx_large_shadow_caster, x, y));
}

void World::set_gfx_large_shadow_caster (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_gfx_large_shadow_caster, x, y, true);
}

void World::unset_gfx_large_shadow_caster (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_gfx_large_shadow_caster, x, y, false);
}

bool World::is_door (const point &p)
{_
    return (is_door(p.x, p.y));
}

bool World::is_door (const int x, const int y)
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

void World::get_all_things_at_depth (int x, int y, int z,
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

void World::get_all_interesting_things_at (int x, int y, std::vector<Thingp> &l)
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

void World::get_all_light_source_things_at (int x, int y, std::vector<Thingp> &l)
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

void World::get_all_active_things_at (int x, int y, std::vector<Thingp> &l)
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

void World::get_all_obstacle_things_at (int x, int y, std::vector<Thingp> &l)
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
