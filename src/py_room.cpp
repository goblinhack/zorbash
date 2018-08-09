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
    PyObject *py_combo = 0;
    PyObject *py_floor = 0;
    PyObject *py_walls = 0;
    PyObject *py_items = 0;

    static char *kwlist[] = {
        (char*) "combo", 
        (char*) "floor", 
        (char*) "walls", 
        (char*) "items", 
        (char*) "xxx", 
        (char*) "yyy", 
        (char*) "room_name", 
        0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, 
                                     "|OOOOiis", 
                                     kwlist, 
                                     &py_combo,
                                     &py_floor,
                                     &py_walls,
                                     &py_items,
                                     &xxx, 
                                     &yyy, 
                                     &room_name)) {
        Py_RETURN_NONE;
    }

    if (!py_combo) {
        if (!py_floor) {
            ERR("map_load_room, missing floor data");
            Py_RETURN_NONE;
        }
        if (!py_walls) {
            ERR("map_load_room, missing walls data");
            Py_RETURN_NONE;
        }
    }

    auto r = Room::fixed_room_new();

    if (py_combo) {
        int combo_lines = PyList_Size(py_combo);

        for (auto i=0; i<combo_lines; i++){
            auto o = PyList_GetItem(py_combo, i); /* Can't fail */
            if (!o) {
                continue;
            }

            std::string floor_string;
            std::string walls_string;
            std::string items_string;

            for (auto c : py_obj_to_string(o)) {
fprintf(stderr,"\nZZZ %s %s %d xxx %ld\n",__FILE__,__FUNCTION__,__LINE__, Charmap::all_charmaps.size());
                auto m = Charmap::all_charmaps[c];

                if (m.is_floor ||
                    m.is_dusty ||
                    m.is_corridor ||
                    m.is_chasm ||
                    m.is_lava ||
                    m.is_water) {
                    floor_string += c;
                } else {
                    floor_string += Charmap::SPACE;
                }

                if (m.is_movement_blocking ||
                    m.is_wall ||
                    m.is_cwall ||
                    m.is_door ||
                    m.is_dungeon_way_up ||
                    m.is_dungeon_way_down ||
                    m.is_rock) {
                    walls_string += c;
                } else {
                    walls_string += Charmap::SPACE;
                }

                if (m.is_treasure ||
                    m.is_key) {
                    items_string += c;
                } else {
                    items_string += Charmap::SPACE;
                }
            }
            r->data[Charmap::DEPTH_FLOOR].push_back(floor_string);
            r->data[Charmap::DEPTH_WALLS].push_back(walls_string);
            r->data[Charmap::DEPTH_ITEMS].push_back(items_string);
        }
    } else {
        int floor_lines = PyList_Size(py_floor);
        int walls_lines = PyList_Size(py_walls);
        int items_lines = PyList_Size(py_items);
        int i;

        if (floor_lines) {
            if (floor_lines != walls_lines) {
                ERR("mismatch in floor vs wall lines");
                py_err();
            }
            if (items_lines) {
                if (items_lines != walls_lines) {
                    ERR("mismatch in items vs wall lines");
                    py_err();
                }
            }
        }

        for (i=0; i<floor_lines; i++){
            auto o = PyList_GetItem(py_floor, i); /* Can't fail */
            if (!o) {
                continue;
            }

            r->data[Charmap::DEPTH_FLOOR].push_back(py_obj_to_string(o));
        }

        for (i=0; i<walls_lines; i++){
            auto o = PyList_GetItem(py_walls, i); /* Can't fail */
            if (!o) {
                continue;
            }

            r->data[Charmap::DEPTH_WALLS].push_back(py_obj_to_string(o));
        }

        for (i=0; i<items_lines; i++){
            auto o = PyList_GetItem(py_items, i); /* Can't fail */
            if (!o) {
                continue;
            }

            r->data[Charmap::DEPTH_ITEMS].push_back(py_obj_to_string(o));
        }
    }

    r->finalize();

    Py_RETURN_NONE;
}
