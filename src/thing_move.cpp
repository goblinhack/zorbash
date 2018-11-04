/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_game.h"
#include "my_thing.h"

fpoint Thing::get_velocity (void)
{
    fpoint v;

    v.x = momentum;                    
    v.y = fall_speed;

    return (v);
}

void Thing::set_velocity (double x, double y)
{
    momentum = x;
    fall_speed = y;
}

void Thing::set_velocity (fpoint v)
{
    momentum = v.x;
    fall_speed = v.y;
}

bool 
thing_overlaps_vorder (Thingp t)
{_
    auto tile = t->current_tile;
    if (!tile) {
        return (false);
    }

    for (int y = 0; y < (int)tile->pix_height; y++) {
        for (int x = 0; x < (int)tile->pix_width; x++) {
            if (!tile->pix[x][y]) {
                continue;
            }
            
            int px = t->at.x * TILE_WIDTH + x;
            int py = t->at.y * TILE_HEIGHT + y;

            if (px < MAP_BORDER * TILE_WIDTH) {
                return (true);
            }

            if (py < MAP_BORDER * TILE_HEIGHT) {
                return (true);
            }

            if (px >= (MAP_WIDTH - MAP_BORDER) * TILE_WIDTH) {
                return (true);
            }

            if (py >= (MAP_HEIGHT - MAP_BORDER) * TILE_HEIGHT) {
                return (true);
            }
        }
    }
    return (false);
}

bool 
things_overlap (Thingp t, Thingp o)
{_
    auto tile1 = t->current_tile;
    if (!tile1) {
        return (false);
    }
    auto tile2 = o->current_tile;
    if (!tile2) {
        return (false);
    }

    for (int y = 0; y < (int)tile1->pix_height; y++) {
        for (int x = 0; x < (int)tile1->pix_width; x++) {
            if (!tile1->pix[x][y]) {
                continue;
            }
            
            int px = t->at.x * TILE_WIDTH + x;
            int py = t->at.y * TILE_HEIGHT + y;

            int ox = o->at.x * TILE_WIDTH;
            int oy = o->at.y * TILE_HEIGHT;

            int dx = px - ox;
            int dy = py - oy;

            if ((dx < 0) || (dx >= (int)tile2->pix_width)) {
#if 0
if (first) {
first = 0; CON("         pix %3d,%3d %s:%3d,%3d  dx %d,%d  <>x", px, py, thing_logname(o).c_str(), ox, oy, dx, dy);
}
#endif
                continue;
            }

            if ((dy < 0) || (dy >= (int)tile2->pix_height)) {
#if 0
if (first) {
first = 0; CON("         pix %3d,%3d %s:%3d,%3d  dx %d,%d  <>y", px, py, thing_logname(o).c_str(), ox, oy, dx, dy);
}
#endif
                continue;
            }

            if (tile2->pix[dx][dy]) {
#if 0
first = 0; CON("         pix %3d,%3d %s:%3d,%3d  dx %d,%d  overlap", px, py, thing_logname(o).c_str(), ox, oy, dx, dy);
#endif
                return (true);
            }
        }
    }
    return (false);
}
