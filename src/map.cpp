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

