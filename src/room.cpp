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

void Room::create_rotated_clones (void)
{_
    {
        std::vector<std::string> rot[Charmap::DEPTH_MAX];

        for (auto d = 0; d < Charmap::DEPTH_MAX; d++) {
            for (auto w = 0; w < width; w++) {
                std::string s;
                for (auto h = 0; h < height; h++) {
                    if (!data[d].size()) {
                        s += ' ';
                    } else {
                        auto c = data[d][h][width - w - 1];
                        if (!c) {
                            DIE("room has nul char");
                        }
                        s += c;
                    }
                }
                rot[d].push_back(s);
            }
        }

        auto r = Room::room_new();
        for (auto d = 0; d < Charmap::DEPTH_MAX; d++) {
            r->data[d] = rot[d];
        }
        r->finalize();
    }

    {
        std::vector<std::string> rot[Charmap::DEPTH_MAX];

        for (auto d = 0; d < Charmap::DEPTH_MAX; d++) {
            for (auto w = 0; w < width; w++) {
                std::string s;
                for (auto h = 0; h < height; h++) {
                    if (!data[d].size()) {
                        s += ' ';
                    } else {
                        auto c = data[d][h][w];
                        if (!c) {
                            DIE("room has nul char");
                        }
                        s += c;
                    }
                }
                rot[d].push_back(s);
            }
        }

        auto r = Room::room_new();
        for (auto d = 0; d < Charmap::DEPTH_MAX; d++) {
            r->data[d] = rot[d];
        }
        r->finalize();
    }

    {
        std::vector<std::string> rot[Charmap::DEPTH_MAX];

        for (auto d = 0; d < Charmap::DEPTH_MAX; d++) {
            for (auto w = 0; w < width; w++) {
                std::string s;
                for (auto h = 0; h < height; h++) {
                    if (!data[d].size()) {
                        s += ' ';
                    } else {
                        auto c = data[d][height - h - 1][w];
                        if (!c) {
                            DIE("room has nul char");
                        }
                        s += c;
                    }
                }
                rot[d].push_back(s);
            }
        }

        auto r = Room::room_new();
        for (auto d = 0; d < Charmap::DEPTH_MAX; d++) {
            r->data[d] = rot[d];
        }
        r->finalize();
    }
}

//
// Find all door exits from a room
//
void Room::find_exits (void)
{
    for (auto x : range<int>(0, width)) {
        for (auto y : range<int>(0, height)) {
            if (data[Charmap::DEPTH_WALLS][y][x] != Charmap::DOOR) {
                continue;
            }

            bool valid = true;

            for (auto dx = x - 1; dx >= 0; dx--) {
                if ((data[Charmap::DEPTH_FLOOR][y][dx] != Charmap::SPACE) ||
                    (data[Charmap::DEPTH_WALLS][y][dx] != Charmap::SPACE)) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                left_exits.push_back(point(x, y));
            }

            valid = true;
            for (auto dx = x + 1; dx < width; dx++) {
                if ((data[Charmap::DEPTH_FLOOR][y][dx] != Charmap::SPACE) ||
                    (data[Charmap::DEPTH_WALLS][y][dx] != Charmap::SPACE)) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                right_exits.push_back(point(x, y));
            }

            valid = true;
            for (auto dy = y - 1; dy >= 0; dy--) {
                if ((data[Charmap::DEPTH_FLOOR][dy][x] != Charmap::SPACE) ||
                    (data[Charmap::DEPTH_WALLS][dy][x] != Charmap::SPACE)) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                up_exits.push_back(point(x, y));
            }

            valid = true;
            for (auto dy = y + 1; dy < height; dy++) {
                if ((data[Charmap::DEPTH_FLOOR][dy][x] != Charmap::SPACE) ||
                    (data[Charmap::DEPTH_WALLS][dy][x] != Charmap::SPACE)) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                down_exits.push_back(point(x, y));
            }
        }
    }

    if (!left_exits.size() &&
        !right_exits.size() &&
        !up_exits.size() &&
        !down_exits.size()) {
        DIE("room has no exits");
    }

#if 0
    if (left_exits.size()) {
        CON("room has left exit");
    }
    if (right_exits.size()) {
        CON("room has right exit");
    }
    if (up_exits.size()) {
        CON("room has up exit");
    }
    if (down_exits.size()) {
        CON("room has down exit");
    }
#endif
}

void Room::finalize (void)
{
    height = data[Charmap::DEPTH_FLOOR].size();
    width = data[Charmap::DEPTH_FLOOR][0].size();

    int floor_height = data[Charmap::DEPTH_FLOOR].size();
    int walls_height = data[Charmap::DEPTH_WALLS].size();
    int items_height = data[Charmap::DEPTH_ITEMS].size();
    int floor_width = data[Charmap::DEPTH_FLOOR][0].size();
    int walls_width = data[Charmap::DEPTH_WALLS][0].size();
    int items_width = data[Charmap::DEPTH_ITEMS][0].size();

    if (floor_height != walls_height) {
        DIE("mismatch in room %d floor vs wall lines, %d vs %d", roomno, floor_height, walls_height);
    }

    if (items_height != walls_height) {
        DIE("mismatch in room %d items vs wall lines, %d vs %d", roomno, items_height, walls_height);
    }

    if (floor_width != walls_width) {
        DIE("mismatch in room %d floor vs wall lines, %d vs %d", roomno, floor_width, walls_width);
    }

    if (items_width != walls_width) {
        DIE("mismatch in room %d items vs wall lines, %d vs %d", roomno, items_width, walls_width);
    }

    int debug = false;

    if (debug) {
        char tmp[width + 1][height + 1];
        memset(tmp, ' ', sizeof(tmp));

        for (auto h = 0; h < height; h++) {
            for (auto w = 0; w < width; w++) {
                auto c = data[Charmap::DEPTH_WALLS][h][w];
                if (!c || (c == ' ')) {
                    c = data[Charmap::DEPTH_FLOOR][h][w];
                }
                tmp[w][h] = c;
            }
        }

        CON("ROOM(%d): width %d height %d", roomno, width, height);
        for (auto h = 0; h < height; h++) {
            std::string s;
            for (auto w = 0; w < width; w++) {
                s += tmp[w][h];
            }
            CON("ROOM(%d): %s", roomno, s.c_str());
        }
    }

    find_exits();
}
