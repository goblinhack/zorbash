/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_tile.h"
#include "my_room.h"
#include "my_range.h"

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

//
// Find the floor tiles at the edge of the room. We choose
// these for corridor starts.
//
void Room::find_edge_exits (void)
{
    int x, y;

    y = 0;
    for (auto x : range<int>(0, width)) {
        if (data[Charmap::DEPTH_WALLS][y][x] == Charmap::WALL) {
            continue;
        }
        if (data[Charmap::DEPTH_FLOOR][y][x] == Charmap::FLOOR) {
            edge_exits.push_back(point(x, y));
        }
    }

    y = height - 1;
    for (auto x : range<int>(0, width)) {
        if (data[Charmap::DEPTH_WALLS][y][x] == Charmap::WALL) {
            continue;
        }
        if (data[Charmap::DEPTH_FLOOR][y][x] == Charmap::FLOOR) {
            edge_exits.push_back(point(x, y));
        }
    }

    x = 0;
    for (auto y : range<int>(0, height)) {
        if (data[Charmap::DEPTH_WALLS][y][x] == Charmap::WALL) {
            continue;
        }
        if (data[Charmap::DEPTH_FLOOR][y][x] == Charmap::FLOOR) {
            edge_exits.push_back(point(x, y));
        }
    }

    x = width - 1;
    for (auto y : range<int>(0, height)) {
        if (data[Charmap::DEPTH_WALLS][y][x] == Charmap::WALL) {
            continue;
        }
        if (data[Charmap::DEPTH_FLOOR][y][x] == Charmap::FLOOR) {
            edge_exits.push_back(point(x, y));
        }
    }

    for (auto x : range<int>(0, width)) {
        for (auto y : range<int>(0, height)) {
            if (data[Charmap::DEPTH_WALLS][y][x] == Charmap::DOOR) {
                continue;
            }
        }
    }

    /*
     * Convert the vector to a sorted vector, via a set
     */
    std::set<point> s;
    for (auto v : edge_exits) {
        s.insert(v);
    }
    edge_exits.assign(s.begin(), s.end());
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
        CON("room floor:");
        for (auto h = 0; h < height; h++) {
            CON("[%s]", data[Charmap::DEPTH_FLOOR][h].c_str());
        }
        CON("room walls:");
        for (auto h = 0; h < height; h++) {
            CON("[%s]", data[Charmap::DEPTH_WALLS][h].c_str());
        }
    }

    find_edge_exits();
}
