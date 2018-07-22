/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_tile.h"
#include "my_room.h"

uint32_t                    Room::last_id = 0;
std::map< uint32_t, Roomp > Room::all_fixed_rooms;
std::map< uint32_t, Roomp > Room::all_random_rooms;

Roomp Room::random_room_new (void)
{_
    auto r = std::make_shared< class Room >();
    Room::all_random_rooms.insert(std::make_pair(r->id, r));
    return (r);
}

Roomp Room::fixed_room_new (void)
{_
    auto r = std::make_shared< class Room >();
    Room::all_fixed_rooms.insert(std::make_pair(r->id, r));
    return (r);
}

void Room::finalize (void)
{
    width = floor_data[0].size();

    int floor_lines = floor_data.size();
    int walls_lines = walls_data.size();
    int items_lines = items_data.size();

    if (floor_lines != walls_lines) {
        DIE("mismatch in room %d floor vs wall lines, %d vs %d", id, floor_lines, walls_lines);
    }

    if (items_lines != walls_lines) {
        DIE("mismatch in room %d items vs wall lines, %d vs %d", id, items_lines, walls_lines);
    }

    height = floor_lines;

    int debug = false;

    if (debug) {
        for (auto h = 0; h < height; h++) {
            std::cout << floor_data[h] << std::endl;
        }
        for (auto h = 0; h < height; h++) {
            std::cout << walls_data[h] << std::endl;
        }
    }
}
