/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_tile.h"
#include "my_room.h"

uint32_t           Room::room_count = 0;
std::vector<Roomp> Room::all_fixed_rooms;
std::vector<Roomp> Room::all_random_rooms;

Roomp Room::random_room_new (void)
{_
    auto r = std::make_shared< class Room >();
    Room::all_random_rooms.push_back(r);
    return (r);
}

Roomp Room::fixed_room_new (void)
{_
    auto r = std::make_shared< class Room >();
    Room::all_fixed_rooms.push_back(r);
    return (r);
}

void Room::finalize (void)
{
    width = data[Charmap::DEPTH_FLOOR].size();

    int floor_lines = data[Charmap::DEPTH_FLOOR].size();
    int walls_lines = data[Charmap::DEPTH_WALLS].size();
    int items_lines = data[Charmap::DEPTH_ITEMS].size();

    if (floor_lines != walls_lines) {
        DIE("mismatch in room %d floor vs wall lines, %d vs %d", roomno, floor_lines, walls_lines);
    }

    if (items_lines != walls_lines) {
        DIE("mismatch in room %d items vs wall lines, %d vs %d", roomno, items_lines, walls_lines);
    }

    height = floor_lines;

    int debug = false;

    if (debug) {
        for (auto h = 0; h < height; h++) {
            std::cout << data[Charmap::DEPTH_FLOOR][h] << std::endl;
        }
        for (auto h = 0; h < height; h++) {
            std::cout << data[Charmap::DEPTH_FLOOR][h] << std::endl;
        }
    }
}
