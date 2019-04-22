/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_main.h"
#include "my_tile.h"
#include "my_thing.h"
#include "my_tile_info.h"
#include "my_python.h"

std::string tile_info_name (Tileinfop t)
{_
    return (t->tilename.c_str());
}

uint32_t tile_info_delay_ms (Tileinfop t)
{_
    return (t->delay_ms);
}

uint8_t tile_info_is_moving (Tileinfop t)
{_
    return (t->is_moving);
}

uint8_t tile_info_is_dir_down (Tileinfop t)
{_
    return (t->dir == THING_DIR_DOWN);
}

uint8_t tile_info_is_dir_up (Tileinfop t)
{_
    return (t->dir == THING_DIR_UP);
}

uint8_t tile_info_is_dir_left (Tileinfop t)
{_
    return (t->dir == THING_DIR_LEFT);
}

uint8_t tile_info_is_dir_right (Tileinfop t)
{_
    return (t->dir == THING_DIR_RIGHT);
}

uint8_t tile_info_is_dir_none (Tileinfop t)
{_
    return (t->dir == THING_DIR_NONE);
}

uint8_t tile_info_is_dir_tl (Tileinfop t)
{_
    return (t->dir == THING_DIR_TL);
}

uint8_t tile_info_is_dir_bl (Tileinfop t)
{_
    return (t->dir == THING_DIR_BL);
}

uint8_t tile_info_is_dir_tr (Tileinfop t)
{_
    return (t->dir == THING_DIR_TR);
}

uint8_t tile_info_is_dir_br (Tileinfop t)
{_
    return (t->dir == THING_DIR_BR);
}

uint8_t tile_info_is_yyy5 (Tileinfop t)
{_
    return (t->is_yyy5);
}

uint8_t tile_info_is_yyy6 (Tileinfop t)
{_
    return (t->is_yyy6);
}

uint8_t tile_info_is_yyy7 (Tileinfop t)
{_
    return (t->is_yyy7);
}

uint8_t tile_info_is_yyy8 (Tileinfop t)
{_
    return (t->is_yyy8);
}

uint8_t tile_info_is_yyy9 (Tileinfop t)
{_
    return (t->is_yyy9);
}

uint8_t tile_info_is_yyy10 (Tileinfop t)
{_
    return (t->is_yyy10);
}

uint8_t tile_info_is_hp_25_percent (Tileinfop t)
{_
    return (t->is_hp_25_percent);
}

uint8_t tile_info_is_hp_50_percent (Tileinfop t)
{_
    return (t->is_hp_50_percent);
}

uint8_t tile_info_is_hp_75_percent (Tileinfop t)
{_
    return (t->is_hp_75_percent);
}

uint8_t tile_info_is_hp_100_percent (Tileinfop t)
{_
    return (t->is_hp_100_percent);
}

uint8_t tile_info_is_sleeping (Tileinfop t)
{_
    return (t->is_sleeping);
}

uint8_t tile_info_is_open (Tileinfop t)
{_
    return (t->is_open);
}

uint8_t tile_info_is_dead (Tileinfop t)
{_
    return (t->is_dead);
}

uint8_t tile_info_is_end_of_anim (Tileinfop t)
{_
    return (t->is_end_of_anim);
}

uint8_t tile_info_is_dead_on_end_of_anim (Tileinfop t)
{_
    return (t->is_dead_on_end_of_anim);
}

Tileinfop tile_info_first (Tileinfomap tiles)
{_
    Tileinfop Tileinfo;

    if (tiles.empty()) {
        return (0);
    }

    Tileinfo = tiles.begin()->second;

    return (Tileinfo);
}

Tileinfop tile_info_random (Tileinfomap tiles)
{_
    Tileinfop Tileinfo;

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

Tileinfop tile_info_next (Tileinfomap tiles, Tileinfop in)
{_
    auto cursor = tiles.find(in->index);

    if (cursor == tiles.end()) {
        return (0);
    }

    cursor = std::next(cursor);

    if (cursor == tiles.end()) {
        return (0);
    }

    auto Tileinfo = cursor->second;

    return (Tileinfo);
}
