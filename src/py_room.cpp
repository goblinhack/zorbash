/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
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
        0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, 
                                     "|Oiisiiiiiiii", 
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
                                     &is_key)) {
        Py_RETURN_NONE;
    }

    if (!py_room_data) {
        DIE("map_load_room, missing floor data");
    }

    auto r = Room::room_new();

    int room_data_lines = PyList_Size(py_room_data);
    if (room_data_lines > ROOM_HEIGHT) {
        DIE("room too tall");
    }

    for (auto y=0; y<room_data_lines; y++){
        auto o = PyList_GetItem(py_room_data, y); /* Can't fail */
        if (!o) {
            continue;
        }

        std::string floor_string;
        std::string walls_string;
        std::string items_string;

        for (auto c : py_obj_to_string(o)) {
            auto m = Charmap::all_charmaps[c];

            if (m.is_floor ||
                m.is_dusty ||
                m.is_lava ||
                m.is_water) {
                floor_string += c;
            } else {
                floor_string += Charmap::SPACE;
            }

            if (m.is_wall ||
                m.is_door ||
                m.is_entrance ||
                m.is_exit ||
                m.is_rock) {
                walls_string += c;
            } else {
                walls_string += Charmap::SPACE;
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
        if (walls_string.size() != ROOM_WIDTH){
            DIE("room walls width mismatch, %zu, expected %d",
                walls_string.size(), ROOM_WIDTH);
        }
        if (items_string.size() != ROOM_WIDTH){
            DIE("room items width mismatch, %zu, expected %d",
                items_string.size(), ROOM_WIDTH);
        }

        for (auto x = 0; x < ROOM_WIDTH; x++) {
            r->data[x][y][Charmap::DEPTH_FLOOR] = floor_string[x];
            r->data[x][y][Charmap::DEPTH_WALLS] = walls_string[x];
            r->data[x][y][Charmap::DEPTH_ITEMS] = items_string[x];
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
    // remember to update create_h_flip

    r->finalize();
    r->create_h_flip();

    Py_RETURN_NONE;
}
