/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"

bool Map::is_lava_at (const point &p)
{
    if (is_oob(p.x, p.y)) {
        return (true);
    }
    return (is_lava[p.x][p.y]);
}

bool Map::is_lava_at (const int x, const int y)
{
    if (is_oob(x, y)) {
        return (true);
    }
    return (is_lava[x][y]);
}

bool Map::is_blood_at (const point &p)
{
    if (is_oob(p.x, p.y)) {
        return (true);
    }
    return (is_blood[p.x][p.y]);
}

bool Map::is_blood_at (const int x, const int y)
{
    if (is_oob(x, y)) {
        return (true);
    }
    return (is_blood[x][y]);
}

bool Map::is_water_at (const point &p)
{
    if (is_oob(p.x, p.y)) {
        return (true);
    }
    return (is_water[p.x][p.y]);
}

bool Map::is_water_at (const int x, const int y)
{
    if (is_oob(x, y)) {
        return (true);
    }
    return (is_water[x][y]);
}

bool Map::is_deep_water_at (const point &p)
{
    if (is_oob(p.x, p.y)) {
        return (true);
    }
    return (is_deep_water[p.x][p.y]);
}

bool Map::is_deep_water_at (const int x, const int y)
{
    if (is_oob(x, y)) {
        return (true);
    }
    return (is_deep_water[x][y]);
}

bool Map::is_wall_at (const point &p)
{
    if (is_oob(p.x, p.y)) {
        return (true);
    }
    return (is_wall[p.x][p.y]);
}

bool Map::is_wall_at (const int x, const int y)
{
    if (is_oob(x, y)) {
        return (true);
    }
    return (is_wall[x][y]);
}

bool Map::is_light_at (const point &p)
{
    if (is_oob(p.x, p.y)) {
        return (true);
    }
    return (is_light[p.x][p.y]);
}

bool Map::is_light_at (const int x, const int y)
{
    if (is_oob(x, y)) {
        return (true);
    }
    return (is_light[x][y]);
}

bool Map::is_corridor_at (const point &p)
{
    if (is_oob(p.x, p.y)) {
        return (true);
    }
    return (is_corridor[p.x][p.y]);
}

bool Map::is_corridor_at (const int x, const int y)
{
    if (is_oob(x, y)) {
        return (true);
    }
    return (is_corridor[x][y]);
}

bool Map::is_monst_at (const point &p)
{
    if (is_oob(p.x, p.y)) {
        return (true);
    }
    return (is_monst[p.x][p.y]);
}

bool Map::is_monst_at (const int x, const int y)
{
    if (is_oob(x, y)) {
        return (true);
    }
    return (is_monst[x][y]);
}

bool Map::is_key_at (const point &p)
{
    if (is_oob(p.x, p.y)) {
        return (true);
    }
    return (is_key[p.x][p.y]);
}

bool Map::is_key_at (const int x, const int y)
{
    if (is_oob(x, y)) {
        return (true);
    }
    return (is_key[x][y]);
}

bool Map::is_shadow_caster_at (const point &p)
{
    if (is_oob(p.x, p.y)) {
        return (true);
    }
    return (is_shadow_caster[p.x][p.y]);
}

bool Map::is_shadow_caster_at (const int x, const int y)
{
    if (is_oob(x, y)) {
        return (true);
    }
    return (is_shadow_caster[x][y]);
}

