/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_tile.h"
#include "my_thing.h"
#include "my_thing_tile.h"
#include "my_python.h"

std::string thing_tile_name (thing_tilep t)
{_
    return (t->tilename.c_str());
}

uint32_t thing_tile_delay_ms (thing_tilep t)
{_
    return (t->delay_ms);
}

uint8_t thing_tile_is_moving (thing_tilep t)
{_
    return (t->is_moving);
}

uint8_t thing_tile_is_dir_down (thing_tilep t)
{_
    return (t->dir == THING_DIR_DOWN);
}

uint8_t thing_tile_is_dir_up (thing_tilep t)
{_
    return (t->dir == THING_DIR_UP);
}

uint8_t thing_tile_is_dir_left (thing_tilep t)
{_
    return (t->dir == THING_DIR_LEFT);
}

uint8_t thing_tile_is_dir_right (thing_tilep t)
{_
    return (t->dir == THING_DIR_RIGHT);
}

uint8_t thing_tile_is_dir_none (thing_tilep t)
{_
    return (t->dir == THING_DIR_NONE);
}

uint8_t thing_tile_is_dir_tl (thing_tilep t)
{_
    return (t->dir == THING_DIR_TL);
}

uint8_t thing_tile_is_dir_bl (thing_tilep t)
{_
    return (t->dir == THING_DIR_BL);
}

uint8_t thing_tile_is_dir_tr (thing_tilep t)
{_
    return (t->dir == THING_DIR_TR);
}

uint8_t thing_tile_is_dir_br (thing_tilep t)
{_
    return (t->dir == THING_DIR_BR);
}

uint8_t thing_tile_is_yyy5 (thing_tilep t)
{_
    return (t->is_yyy5);
}

uint8_t thing_tile_is_yyy6 (thing_tilep t)
{_
    return (t->is_yyy6);
}

uint8_t thing_tile_is_yyy7 (thing_tilep t)
{_
    return (t->is_yyy7);
}

uint8_t thing_tile_is_yyy8 (thing_tilep t)
{_
    return (t->is_yyy8);
}

uint8_t thing_tile_is_yyy9 (thing_tilep t)
{_
    return (t->is_yyy9);
}

uint8_t thing_tile_is_yyy10 (thing_tilep t)
{_
    return (t->is_yyy10);
}

uint8_t thing_tile_is_yyy11 (thing_tilep t)
{_
    return (t->is_yyy11);
}

uint8_t thing_tile_is_yyy12 (thing_tilep t)
{_
    return (t->is_yyy12);
}

uint8_t thing_tile_is_yyy13 (thing_tilep t)
{_
    return (t->is_yyy13);
}

uint8_t thing_tile_is_yyy14 (thing_tilep t)
{_
    return (t->is_yyy14);
}

uint8_t thing_tile_is_sleeping (thing_tilep t)
{_
    return (t->is_sleeping);
}

uint8_t thing_tile_is_open (thing_tilep t)
{_
    return (t->is_open);
}

uint8_t thing_tile_is_dead (thing_tilep t)
{_
    return (t->is_dead);
}

uint8_t thing_tile_is_end_of_anim (thing_tilep t)
{_
    return (t->is_end_of_anim);
}

uint8_t thing_tile_is_dead_on_end_of_anim (thing_tilep t)
{_
    return (t->is_dead_on_end_of_anim);
}

thing_tilep thing_tile_first (thing_tiles tiles)
{_
    thing_tilep thing_tile;

    if (tiles.empty()) {
        return (0);
    }

    thing_tile = tiles.begin()->second;

    return (thing_tile);
}

thing_tilep thing_tile_random (thing_tiles tiles)
{_
    thing_tilep thing_tile;

    if (tiles.empty()) {
        return (0);
    }

    auto n = tiles.size();
    auto m = myrand() % n;

    auto iter = tiles.begin();
    while (m--) {
        auto t = iter->second; 
        iter++;
    }

    return (iter->second);
}

thing_tilep thing_tile_next (thing_tiles tiles, thing_tilep in)
{_
    auto cursor = tiles.find(in->index);

    if (cursor == tiles.end()) {
        return (0);
    }

    cursor = std::next(cursor);

    if (cursor == tiles.end()) {
        return (0);
    }

    auto thing_tile = cursor->second;

    return (thing_tile);
}
