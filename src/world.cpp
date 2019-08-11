/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_dungeon.h"

bool World::is_anything_at (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (!all_things_at[p.x][p.y].empty());
}

bool World::is_anything_at (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (all_things_at[x][y].size());
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

bool World::is_solid (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (_is_solid[p.x][p.y]);
}

bool World::is_solid (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (_is_solid[x][y]);
}

void World::set_solid (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_solid[x][y] = true;
}

void World::unset_solid (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_solid[x][y] = false;
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
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (_is_monst[p.x][p.y]);
}

bool World::is_monst (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (_is_monst[x][y]);
}

void World::set_monst (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_monst[x][y] = true;
}

void World::unset_monst (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_monst[x][y] = false;
}

bool World::is_food (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (_is_food[x][y]);
}

void World::set_food (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_food[x][y] = true;
}

void World::unset_food (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_food[x][y] = false;
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
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (_is_key[p.x][p.y]);
}

bool World::is_key (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (_is_key[x][y]);
}

void World::set_key (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_key[x][y] = true;
}

void World::unset_key (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_key[x][y] = false;
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
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (_is_door[p.x][p.y]);
}

bool World::is_door (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (_is_door[x][y]);
}

void World::set_door (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_door[x][y] = true;
}

void World::unset_door (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    _is_door[x][y] = false;
}

void World::clear (void)
{
    memset(_is_blood, 0, sizeof(_is_blood));
    memset(_is_corridor, 0, sizeof(_is_corridor));
    memset(_is_deep_water, 0, sizeof(_is_deep_water));
    memset(_is_dirt, 0, sizeof(_is_dirt));
    memset(_is_grass, 0, sizeof(_is_grass));
    memset(_is_floor, 0, sizeof(_is_floor));
    memset(_is_key, 0, sizeof(_is_key));
    memset(_is_lava, 0, sizeof(_is_lava));
    memset(_is_light, 0, sizeof(_is_light));
    memset(_is_monst, 0, sizeof(_is_monst));
    memset(_is_food, 0, sizeof(_is_food));
    memset(_is_rock, 0, sizeof(_is_rock));
    memset(_is_solid, 0, sizeof(_is_solid));
    memset(_is_gfx_large_shadow_caster, 0, sizeof(_is_gfx_large_shadow_caster));
    memset(_is_door, 0, sizeof(_is_door));
    memset(_is_wall, 0, sizeof(_is_wall));
    memset(_is_water, 0, sizeof(_is_water));
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
