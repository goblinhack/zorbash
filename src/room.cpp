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
            for (auto x = width - 1; x >= 0; x--) {
                r->data[x][y][z] = data[x][y][z];
            }
        }
    }

    r->dir_up      = dir_up;
    r->dir_down    = dir_down;
    r->is_entrance = is_entrance;
    r->is_exit     = is_exit;
    r->is_lock     = is_lock;
    r->is_key      = is_key;

    if (dir_left) {
        r->dir_left = false;
        r->dir_right = true;
    } else {
        r->dir_left = true;
        r->dir_right = false;
    }

    r->finalize();
}

//
// Find all door exits from a room
//
void Room::find_exits (void)
{
    uint32_t e = 0;
    int x, y = 0;
    int z = Charmap::DEPTH_WALLS;

    for (e = 0, x = 0; x < width; x++) {
        e = e << 1;
        if (data[x][y][z] != Charmap::SPACE) {
            e |= 1;
        }
    }

}

void Room::finalize (void)
{
    int debug = false;
    if (debug) {
        dump();
    }

    find_exits();
}

void Room::dump (void)
{
    char tmp[width + 1][height + 1];
    memset(tmp, ' ', sizeof(tmp));

    for (auto y = 0; y < height; y++) {
        for (auto x = 0; x < width; x++) {
            auto c = data[Charmap::DEPTH_WALLS][y][x];
            if (!c || (c == ' ')) {
                c = data[Charmap::DEPTH_FLOOR][y][x];
            }
            tmp[x][y] = c;
        }
    }

    CON("ROOM(%d): width %d height %d", roomno, width, height);
    CON("ROOM(%d): up %d down %d left %d right %d",
        roomno, dir_up, dir_down, dir_left, dir_right);
    for (auto y = 0; y < height; y++) {
        std::string s;
        for (auto x = 0; x < width; x++) {
            s += tmp[x][y];
        }
        CON("ROOM(%d): %s", roomno, s.c_str());
    }
}
