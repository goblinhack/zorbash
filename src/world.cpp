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

    for (auto id : all_thing_ids_at[x][y]) {
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
    return (_is_lava[p.x][p.y]);
}

bool World::is_lava (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (_is_lava[x][y]);
}

void World::set_lava (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_lava[x][y] = true;
}

void World::unset_lava (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_lava[x][y] = false;
}

bool World::is_blood (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (_is_blood[p.x][p.y]);
}

bool World::is_blood (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (_is_blood[x][y]);
}

void World::set_blood (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_blood[x][y] = true;
}

void World::unset_blood (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_blood[x][y] = false;
}

bool World::is_water (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (_is_water[p.x][p.y]);
}

bool World::is_water (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (_is_water[x][y]);
}

void World::set_water (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_water[x][y] = true;
}

void World::unset_water (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_water[x][y] = false;
}

bool World::is_deep_water (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (_is_deep_water[p.x][p.y]);
}

bool World::is_deep_water (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (_is_deep_water[x][y]);
}

void World::set_deep_water (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_deep_water[x][y] = true;
}

void World::unset_deep_water (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_deep_water[x][y] = false;
}

bool World::is_wall (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (_is_wall[p.x][p.y]);
}

bool World::is_wall (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (_is_wall[x][y]);
}

void World::set_wall (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_wall[x][y] = true;
}

void World::unset_wall (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_wall[x][y] = false;
}

bool World::is_light (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (_is_light[p.x][p.y]);
}

bool World::is_light (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (_is_light[x][y]);
}

void World::set_light (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_light[x][y] = true;
}

void World::unset_light (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_light[x][y] = false;
}

bool World::is_corridor (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (_is_corridor[p.x][p.y]);
}

bool World::is_corridor (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (_is_corridor[x][y]);
}

void World::set_corridor (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_corridor[x][y] = true;
}

void World::unset_corridor (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_corridor[x][y] = false;
}

bool World::is_dirt (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (_is_dirt[p.x][p.y]);
}

bool World::is_dirt (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (_is_dirt[x][y]);
}

void World::dir_sett (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_dirt[x][y] = true;
}

void World::undir_sett (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_dirt[x][y] = false;
}

bool World::is_grass (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (_is_grass[p.x][p.y]);
}

bool World::is_grass (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (_is_grass[x][y]);
}

void World::set_grass (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_grass[x][y] = true;
}

void World::unset_grass (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_grass[x][y] = false;
}

bool World::is_soil (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (_is_soil[p.x][p.y]);
}

bool World::is_soil (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (_is_soil[x][y]);
}

void World::set_soil (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_soil[x][y] = true;
}

void World::unset_soil (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_soil[x][y] = false;
}

bool World::is_gravel (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (_is_gravel[p.x][p.y]);
}

bool World::is_gravel (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (_is_gravel[x][y]);
}

void World::set_gravel (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_gravel[x][y] = true;
}

void World::unset_gravel (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_gravel[x][y] = false;
}

bool World::is_snow (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (_is_snow[p.x][p.y]);
}

bool World::is_snow (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (_is_snow[x][y]);
}

void World::set_snow (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_snow[x][y] = true;
}

void World::unset_snow (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_snow[x][y] = false;
}

bool World::is_floor (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (_is_floor[p.x][p.y]);
}

bool World::is_floor (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (_is_floor[x][y]);
}

void World::set_floor (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_floor[x][y] = true;
}

void World::unset_floor (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_floor[x][y] = false;
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

    for (auto id : all_thing_ids_at[x][y]) {
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

    for (auto id : all_thing_ids_at[x][y]) {
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
    return (_is_rock[p.x][p.y]);
}

bool World::is_rock (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (_is_rock[x][y]);
}

void World::set_rock (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_rock[x][y] = true;
}

void World::unset_rock (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_rock[x][y] = false;
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

    for (auto id : all_thing_ids_at[x][y]) {
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
    return (_is_gfx_large_shadow_caster[p.x][p.y]);
}

bool World::is_gfx_large_shadow_caster (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (_is_gfx_large_shadow_caster[x][y]);
}

void World::set_gfx_large_shadow_caster (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_gfx_large_shadow_caster[x][y] = true;
}

void World::unset_gfx_large_shadow_caster (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_gfx_large_shadow_caster[x][y] = false;
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

    for (auto id : all_thing_ids_at[x][y]) {
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
    _is_grass = {};
    _is_floor = {};
    _is_lava = {};
    _is_light = {};
    _is_rock = {};
    _is_gfx_large_shadow_caster = {};
    _is_wall = {};
    _is_water = {};
}

bool World::is_oob (const int x, const int y, const int z)
{
    return ((x < 0) || (x >= MAP_WIDTH) ||
            (y < 0) || (y >= MAP_HEIGHT) ||
            (z < 0) || (z >= MAP_DEPTH));
}

bool World::is_oob (const int x, const int y)
{
    return ((x < 0) || (x >= MAP_WIDTH) ||
            (y < 0) || (y >= MAP_HEIGHT));
}

bool World::is_oob (const fpoint p)
{
    return ((p.x < 0) || (p.x >= MAP_WIDTH) ||
            (p.y < 0) || (p.y >= MAP_HEIGHT));
}

bool World::is_oob (const point p)
{
    return ((p.x < 0) || (p.x >= MAP_WIDTH) ||
            (p.y < 0) || (p.y >= MAP_HEIGHT));
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
        auto idp = &all_thing_ids_at[x][y][i];
        if (!*idp) {
            *idp = id;
            return;
        }
    }

    for (auto i = 0; i < MAP_SLOTS; i++) {
        auto idp = &all_thing_ids_at[x][y][i];
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
        auto idp = &all_thing_ids_at[x][y][i];
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

    for (auto id : all_thing_ids_at[x][y]) {
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

    for (auto id : all_thing_ids_at[x][y]) {
        if (id) {
            auto t = thing_find(id);
            verify(t);
            if (t->is_interesting()) {
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

    for (auto id : all_thing_ids_at[x][y]) {
        if (id) {
            auto t = thing_find(id);
            verify(t);
            if (t->is_active()) {
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

    for (auto id : all_thing_ids_at[x][y]) {
        if (id) {
            auto t = thing_find(id);
            verify(t);
            if (t->is_obstacle()) {
                l.push_back(t);
            }
        }
    }
}
