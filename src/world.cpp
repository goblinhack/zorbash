/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_dungeon.h"

bool World::is_anything_at (const int x, const int y)
{
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
{
    return (is_anything_at(p.x, p.y));
}

bool World::is_lava (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_lava, p.x, p.y));
}

bool World::is_lava (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_lava, x, y));
}

void World::set_lava (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_lava, x, y, true);
}

void World::unset_lava (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_lava, x, y, false);
}

bool World::is_blood (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_blood, p.x, p.y));
}

bool World::is_blood (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_blood, x, y));
}

void World::set_blood (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_blood, x, y, true);
}

void World::unset_blood (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_blood, x, y, false);
}

bool World::is_water (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_water, p.x, p.y));
}

bool World::is_water (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_water, x, y));
}

void World::set_water (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_water, x, y, true);
}

void World::unset_water (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_water, x, y, false);
}

bool World::is_deep_water (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_deep_water, p.x, p.y));
}

bool World::is_deep_water (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_deep_water, x, y));
}

void World::set_deep_water (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_deep_water, x, y, true);
}

void World::unset_deep_water (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_deep_water, x, y, false);
}

bool World::is_wall (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_wall, p.x, p.y));
}

bool World::is_wall (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_wall, x, y));
}

void World::set_wall (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_wall, x, y, true);
}

void World::unset_wall (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_wall, x, y, false);
}

bool World::is_corridor (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_corridor, p.x, p.y));
}

bool World::is_corridor (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_corridor, x, y));
}

void World::set_corridor (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_corridor, x, y, true);
}

void World::unset_corridor (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_corridor, x, y, false);
}

bool World::is_dirt (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_dirt, p.x, p.y));
}

bool World::is_dirt (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_dirt, x, y));
}

void World::set_dirt (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_dirt, x, y, true);
}

void World::unset_dirt (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_dirt, x, y, false);
}

bool World::is_floor (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_floor, x, y));
}

void World::set_floor (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_floor, x, y, true);
}

void World::unset_floor (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_floor, x, y, false);
}

bool World::is_monst (const point &p)
{
    return (is_monst(p.x, p.y));
}

bool World::is_monst (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }

    for (auto id : get(all_thing_ids_at, x, y)) {
        if (id) {
            auto t = thing_find(id);
            verify(t);
            auto tpp = t->tp();
            if (tp_is_monst(tpp)) {
                return (true);
            }
        }
    }
    return (false);
}

bool World::is_food (const point &p)
{
    return (is_food(p.x, p.y));
}

bool World::is_food (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }

    for (auto id : get(all_thing_ids_at, x, y)) {
        if (id) {
            auto t = thing_find(id);
            verify(t);
            auto tpp = t->tp();
            if (tp_is_food(tpp)) {
                return (true);
            }
        }
    }
    return (false);
}

bool World::is_rock (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_rock, p.x, p.y));
}

bool World::is_rock (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_rock, x, y));
}

void World::set_rock (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_rock, x, y, true);
}

void World::unset_rock (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_rock, x, y, false);
}

bool World::is_visited (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_visited, p.x, p.y));
}

bool World::is_visited (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_visited, x, y));
}

void World::set_visited (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_visited, x, y, true);
}

void World::unset_visited (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_visited, x, y, false);
}

bool World::is_dungeon (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_dungeon, p.x, p.y));
}

bool World::is_dungeon (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_dungeon, x, y));
}

void World::set_dungeon (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_dungeon, x, y, true);
}

void World::unset_dungeon (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_dungeon, x, y, false);
}

bool World::is_key (const point &p)
{
    return (is_key(p.x, p.y));
}

bool World::is_key (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }

    for (auto id : get(all_thing_ids_at, x, y)) {
        if (id) {
            auto t = thing_find(id);
            verify(t);
            auto tpp = t->tp();
            if (tp_is_key(tpp)) {
                return (true);
            }
        }
    }
    return (false);
}

bool World::is_gfx_large_shadow_caster (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_gfx_large_shadow_caster, p.x, p.y));
}

bool World::is_gfx_large_shadow_caster (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_gfx_large_shadow_caster, x, y));
}

void World::set_gfx_large_shadow_caster (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_gfx_large_shadow_caster, x, y, true);
}

void World::unset_gfx_large_shadow_caster (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_gfx_large_shadow_caster, x, y, false);
}

bool World::is_door (const point &p)
{
    return (is_door(p.x, p.y));
}

bool World::is_door (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }

    for (auto id : get(all_thing_ids_at, x, y)) {
        if (id) {
            auto t = thing_find(id);
            verify(t);
            auto tpp = t->tp();
            if (tp_is_door(tpp)) {
                return (true);
            }
        }
    }
    return (false);
}

void World::clear (void)
{
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
}

void World::put_thing (int x, int y, uint32_t id)
{
    auto t = thing_find(id);
    if (!t) {
        ERR("oob at %d %d for put of id %u", x, y, id);
    }

    if (is_oob(x, y)) {
        t->die("oob at %d %d for put of id %u", x, y, id);
        return;
    }

    for (auto i = 0; i < MAP_SLOTS; i++) {
        auto idp = &getref(all_thing_ids_at, x, y, i);
        if (!*idp) {
            *idp = id;
            return;
        }
    }

    for (auto i = 0; i < MAP_SLOTS; i++) {
        auto idp = &getref(all_thing_ids_at, x, y, i);
        if (*idp) {
            auto t = thing_find(*idp);
            t->con("- slot %d ", i);
        }
    }
    t->die("out of thing slots at %d %d for put of id %u", x, y, id);
}

void World::put_thing (point p, uint32_t id)
{
    put_thing(p.x, p.y, id);
}

void World::remove_thing (int x, int y, uint32_t id)
{
    auto t = thing_find(id);
    if (!t) {
        ERR("oob at %d %d for remove of id %u", x, y, id);
    }

    if (is_oob(x, y)) {
        t->die("oob at %d %d for remove of id %u", x, y, id);
        return;
    }

    for (auto i = 0; i < MAP_SLOTS; i++) {
        auto idp = &getref(all_thing_ids_at, x, y, i);
        if (*idp == id) {
            *idp = 0;
            return;
        }
    }
    t->die("out of thing slots at %d %d for remove of id %u", x, y, id);
}

void World::remove_thing (point p, uint32_t id)
{
    remove_thing(p.x, p.y, id);
}

void World::get_all_things_at_depth (int x, int y, int z,
                                     std::vector<Thingp> &l)
{
    l.resize(0);

    if (unlikely(is_oob(x, y))) {
        return;
    }

    for (auto id : get(all_thing_ids_at, x, y)) {
        if (id) {
            auto t = thing_find(id);
            verify(t);
            auto tpp = t->tp();
            if (tpp->z_depth == z) {
                l.push_back(t);
            }
        }
    }
}

void World::get_all_interesting_things_at (int x, int y, std::vector<Thingp> &l)
{
    l.resize(0);

    if (unlikely(is_oob(x, y))) {
        return;
    }

    for (auto id : get(all_thing_ids_at, x, y)) {
        if (id) {
            auto t = thing_find(id);
            verify(t);
            if (t->is_interesting()) {
                l.push_back(t);
            }
        }
    }
}

void World::get_all_light_source_things_at (int x, int y, std::vector<Thingp> &l)
{
    l.resize(0);

    if (unlikely(is_oob(x, y))) {
        return;
    }

    for (auto id : get(all_thing_ids_at, x, y)) {
        if (id) {
            auto t = thing_find(id);
            verify(t);
            if (t->get_light()) {
                l.push_back(t);
            }
        }
    }
}

void World::get_all_active_things_at (int x, int y, std::vector<Thingp> &l)
{
    l.resize(0);

    if (unlikely(is_oob(x, y))) {
        return;
    }

    for (auto id : get(all_thing_ids_at, x, y)) {
        if (id) {
            auto t = thing_find(id);
            verify(t);
            if (t->is_active() || t->is_movable()) {
                l.push_back(t);
            }
        }
    }
}

void World::get_all_obstacle_things_at (int x, int y, std::vector<Thingp> &l)
{
    l.resize(0);

    if (unlikely(is_oob(x, y))) {
        return;
    }

    for (auto id : get(all_thing_ids_at, x, y)) {
        if (id) {
            auto t = thing_find(id);
            verify(t);
            if (t->is_obstacle()) {
                l.push_back(t);
            }
        }
    }
}
