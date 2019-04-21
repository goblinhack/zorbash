/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_main.h"
#include "my_python.h"
#include "my_tile.h"
#include "my_room.h"

PyObject *map_load_room_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    char *room_name = 0;
    int xxx = 0;
    int yyy = 0;
    PyObject *py_room_data = 0;
    int up = false;
    int down = false;
    int left = false;
    int right = false;
    int is_entrance = false;
    int is_exit = false;
    int is_lock = false;
    int is_key = false;
    int is_secret = false;
    int is_depth = 0;

    static char *kwlist[] = {
        (char*) "room_data", 
        (char*) "xxx", 
        (char*) "yyy", 
        (char*) "room_name", 
        (char*) "up", 
        (char*) "down", 
        (char*) "left", 
        (char*) "right", 
        (char*) "entrance", 
        (char*) "exit", 
        (char*) "lock", 
        (char*) "key", 
        (char*) "secret", 
        (char*) "depth", 
        0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, 
                                     "|Oiisiiiiiiiiii", 
                                     kwlist, 
                                     &py_room_data,
                                     &xxx, 
                                     &yyy, 
                                     &room_name,
                                     &up,
                                     &down,
                                     &left,
                                     &right,
                                     &is_entrance,
                                     &is_exit,
                                     &is_lock,
                                     &is_key,
                                     &is_secret,
                                     &is_depth)) {
        Py_RETURN_NONE;
    }

    if (!py_room_data) {
        DIE("map_load_room, missing floor data");
    }

    int room_data_elems = PyList_Size(py_room_data);
    if (room_data_elems % ROOM_HEIGHT) {
        DIE("room elems needs to be evenly dividable by room height %d, got %d elems",
            (int) ROOM_HEIGHT, (int) PyList_Size(py_room_data));
    }

    int rooms_across = room_data_elems / ROOM_HEIGHT;

    for (auto n=0; n < rooms_across; n++) {
        auto r = Room::room_new();

        for (auto y=0; y<ROOM_HEIGHT; y++) {
            auto o = PyList_GetItem(py_room_data, 
                                    rooms_across * y + n); /* Can't fail */
            if (!o) {
                continue;
            }

            std::string floor_string;
            std::string water_string;
            std::string deco_string;
            std::string wall_deco_string;
            std::string walls_string;
            std::string monsts_string;
            std::string exits_string;
            std::string items_string;

            for (auto c : py_obj_to_string(o)) {
                auto m = Charmap::all_charmaps[c];

                if (m.is_floor ||
                    m.is_secret_corridor ||
                    m.is_dirt ||
                    m.is_lava) {
                    floor_string += c;
                    water_string += Charmap::SPACE;
                } else if (m.is_water ||
                           m.is_deep_water) {
                    floor_string += Charmap::FLOOR;
                    water_string += c;
                } else if (m.is_door ||
                           m.gfx_is_floor_deco) {
                    floor_string += Charmap::FLOOR;
                    water_string += Charmap::SPACE;
                } else {
                    floor_string += Charmap::SPACE;
                    water_string += Charmap::SPACE;
                }

                if (m.is_wall ||
                    m.is_door) {
                    walls_string += c;
                } else if (m.gfx_is_wall_deco) {
                    walls_string += Charmap::WALL;
                } else {
                    walls_string += Charmap::SPACE;
                }

                if (m.gfx_is_floor_deco) {
                    deco_string += c;
                } else {
                    deco_string += Charmap::SPACE;
                }

                if (m.gfx_is_wall_deco) {
                    wall_deco_string += c;
                } else {
                    wall_deco_string += Charmap::SPACE;
                }

                if (m.is_monst) {
                    monsts_string += c;
                } else {
                    monsts_string += Charmap::SPACE;
                }

                if (m.is_entrance ||
                    m.is_exit) {
                    exits_string += c;
                } else {
                    exits_string += Charmap::SPACE;
                }

                if (m.is_trap ||
                    m.is_treasure ||
                    m.is_key) {
                    items_string += c;
                } else {
                    items_string += Charmap::SPACE;
                }
            }

            if (floor_string.size() != ROOM_WIDTH){
                DIE("room floor width mismatch, %zu, expected %d",
                    floor_string.size(), ROOM_WIDTH);
            }
            if (water_string.size() != ROOM_WIDTH){
                DIE("room water width mismatch, %zu, expected %d",
                    water_string.size(), ROOM_WIDTH);
            }
            if (deco_string.size() != ROOM_WIDTH){
                DIE("room deco width mismatch, %zu, expected %d",
                    deco_string.size(), ROOM_WIDTH);
            }
            if (deco_string.size() != ROOM_WIDTH){
                DIE("room deco width mismatch, %zu, expected %d",
                    deco_string.size(), ROOM_WIDTH);
            }
            if (walls_string.size() != ROOM_WIDTH){
                DIE("room walls width mismatch, %zu, expected %d",
                    walls_string.size(), ROOM_WIDTH);
            }
            if (exits_string.size() != ROOM_WIDTH){
                DIE("room exits width mismatch, %zu, expected %d",
                    exits_string.size(), ROOM_WIDTH);
            }
            if (items_string.size() != ROOM_WIDTH){
                DIE("room items width mismatch, %zu, expected %d",
                    items_string.size(), ROOM_WIDTH);
            }

            for (auto x = 0; x < ROOM_WIDTH; x++) {
                r->data[x][y][MAP_DEPTH_FLOOR]      = floor_string[x];
                r->data[x][y][MAP_DEPTH_WATER]      = water_string[x];
                r->data[x][y][MAP_DEPTH_FLOOR_DECO] = deco_string[x];
                r->data[x][y][MAP_DEPTH_WALLS]      = walls_string[x];
                r->data[x][y][MAP_DEPTH_WALLS_DECO] = wall_deco_string[x];
                r->data[x][y][MAP_DEPTH_EXIT]       = exits_string[x];
                r->data[x][y][MAP_DEPTH_MONST]      = monsts_string[x];
                r->data[x][y][MAP_DEPTH_ITEM]       = items_string[x];
                r->data[x][y][MAP_DEPTH_PLAYER]     = ' ';
            }
        }

        // remember to update create_h_flip
        r->dir_up      = up ? true : false;
        r->dir_down    = down ? true : false;
        r->dir_left    = left ? true : false;
        r->dir_right   = right ? true : false;
        r->is_entrance = is_entrance ? true : false;
        r->is_exit     = is_exit ? true : false;
        r->is_lock     = is_lock ? true : false;
        r->is_key      = is_key ? true : false;
        r->is_secret   = is_secret ? true : false;
        r->depth       = is_depth;
        // remember to update create_h_flip

        r->finalize();

        //r = r->rotate_clockwise();
        //r = r->rotate_clockwise();
        //r = r->rotate_clockwise();
        r = r->create_w_flip();
        //r = r->rotate_clockwise();
        //r = r->rotate_clockwise();
        //r = r->rotate_clockwise();
    }

    Py_RETURN_NONE;
}
