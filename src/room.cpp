/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_tile.h"
#include "my_room.h"
#include "my_range.h"
#include <bitset>

uint32_t           Room::room_count = 0;
std::vector<Roomp> Room::all_rooms;

Roomp Room::room_new (void)
{_
    auto r = std::make_shared< class Room >();
    Room::all_rooms.push_back(r);
    return (r);
}

void Room::create_h_flip (void)
{_
    std::vector<std::string> rot[Charmap::DEPTH_MAX];

    auto r = Room::room_new();

    for (auto z = 0; z < Charmap::DEPTH_MAX; z++) {
        for (auto y = 0; y < height; y++) {
            std::string s;
            for (auto x = 0; x < width; x++) {
                r->data[x][y][z] = data[width - x - 1][y][z];
            }
        }
    }

    r->has_exit_up    = has_exit_up;
    r->has_exit_down  = has_exit_down;
    r->has_exit_left  = has_exit_right;
    r->has_exit_right = has_exit_left;

    r->dir_up         = dir_up;
    r->dir_down       = dir_down;
    r->dir_left       = dir_right;
    r->dir_right      = dir_left;

    r->is_entrance    = is_entrance;
    r->is_exit        = is_exit;
    r->is_lock        = is_lock;
    r->is_key         = is_key;

    r->finalize();
}

//
// Find all door exits from a room
//
void Room::find_exits (void)
{
    uint32_t wall_bitmap = 0;
    int x, y = 0;
    int z = Charmap::DEPTH_WALLS;

    for (wall_bitmap = 0, x = 0, y = 0; x < width; x++) {
        wall_bitmap = wall_bitmap << 1;
        if (data[x][y][z] != Charmap::SPACE) {
            wall_bitmap |= 1;
        } else {
            has_exit_up = true;
        }
    }
    up_exits = ~wall_bitmap;

    for (wall_bitmap = 0, x = 0, y = height - 1; x < width; x++) {
        wall_bitmap = wall_bitmap << 1;
        if (data[x][y][z] != Charmap::SPACE) {
            wall_bitmap |= 1;
        } else {
            has_exit_down = true;
        }
    }
    down_exits = ~wall_bitmap;

    for (wall_bitmap = 0, x = 0, y = 0; y < height; y++) {
        wall_bitmap = wall_bitmap << 1;
        if (data[x][y][z] != Charmap::SPACE) {
            wall_bitmap |= 1;
        } else {
            has_exit_left = true;
        }
    }
    left_exits = ~wall_bitmap;

    for (wall_bitmap = 0, x = width - 1, y = 0; y < height; y++) {
        wall_bitmap = wall_bitmap << 1;
        if (data[x][y][z] != Charmap::SPACE) {
            wall_bitmap |= 1;
        } else {
            has_exit_right = true;
        }
    }
    right_exits = ~wall_bitmap;
}

void Room::finalize (void)
{
    find_exits();

    int debug = true;
    if (debug) {
        dump();
    }
}

void Room::dump (void)
{
    char tmp[width + 1][height + 1];
    memset(tmp, ' ', sizeof(tmp));

    for (auto y = 0; y < height; y++) {
        for (auto x = 0; x < width; x++) {
            auto c = data[x][y][Charmap::DEPTH_WALLS];
            if (!c || (c == ' ')) {
                c = data[x][y][Charmap::DEPTH_FLOOR];
            }
            tmp[x][y] = c;
        }
    }

    CON("ROOM(%d): width %d height %d", roomno, width, height);
    auto b = std::bitset<32>(left_exits);
    CON("ROOM(%d):   left  exits: %s", roomno, b.to_string().c_str());
    b = std::bitset<32>(right_exits);
    CON("ROOM(%d):   right exits: %s", roomno, b.to_string().c_str());
    b = std::bitset<32>(up_exits);
    CON("ROOM(%d):   up    exits: %s", roomno, b.to_string().c_str());
    b = std::bitset<32>(down_exits);
    CON("ROOM(%d):   down  exits: %s", roomno, b.to_string().c_str());
    CON("ROOM(%d): direction: up %d down %d left %d right %d",
        roomno, dir_up, dir_down, dir_left, dir_right);
    CON("ROOM(%d): exits:     up %d down %d left %d right %d",
        roomno, has_exit_up, has_exit_down, has_exit_left, has_exit_right);
    for (auto y = 0; y < height; y++) {
        std::string s;
        for (auto x = 0; x < width; x++) {
            s += tmp[x][y];
        }
        CON("ROOM(%d): %s", roomno, s.c_str());
    }
    CON(" ");
}
