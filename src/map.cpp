/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#include "my_game.h"

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

bool Map::is_oob (const int x, const int y, const int z)
{
    return ((x < 0) || (x >= MAP_WIDTH) ||
            (y < 0) || (y >= MAP_HEIGHT) ||
            (z < 0) || (z >= MAP_DEPTH));
}

bool Map::is_oob (const int x, const int y)
{
    return ((x < 0) || (x >= MAP_WIDTH) ||
            (y < 0) || (y >= MAP_HEIGHT));
}
