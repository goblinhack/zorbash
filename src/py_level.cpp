/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_main.h"
#include "my_python.h"
#include "my_tile.h"
#include "my_level.h"

PyObject *map_load_level_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    char *level_name = 0;
    PyObject *py_level_data = 0;

    static char *kwlist[] = {
        (char*) "level_data",
        (char*) "level_name",
        0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds,
                                     "|Os",
                                     kwlist,
                                     &py_level_data,
                                     &level_name)) {
        Py_RETURN_NONE;
    }

    if (!py_level_data) {
        DIE("map_load_level, missing floor data");
    }

    int level_data_elems = PyList_Size(py_level_data);
    if (level_data_elems % DUN_HEIGHT) {
        DIE("level elems needs to be evenly dividable by level height %d, got %d elems",
            (int) DUN_HEIGHT, (int) PyList_Size(py_level_data));
    }

    auto l = Level::level_new();
    for (auto n=0; n < DUN_WIDTH; n++) {
        for (auto y=0; y<DUN_HEIGHT; y++) {
            auto o = PyList_GetItem(py_level_data, y); /* Can't fail */
            if (!o) {
                continue;
            }

            std::string floor_string;
            std::string water_string;
            std::string deco_string;
            std::string wall_deco_string;
            std::string walls_string;
            std::string monst_string;
            std::string food_string;
            std::string blood_string;
            std::string exits_string;
            std::string items_string;

            for (auto c : py_obj_to_string(o)) {
                auto m = Charmap::all_charmaps[c];

                if (m.is_floor ||
                    m.is_secret_corridor ||
                    m.is_dirt ||
                    m.is_lava) {
                    floor_string += c;
                } else if (m.is_door ||
                           m.is_blood ||
                           m.gfx_is_floor_deco) {
                    floor_string += Charmap::FLOOR;
                } else {
                    floor_string += Charmap::SPACE;
                }

                if (m.is_water ||
                    m.is_deep_water) {
                    water_string += c;
                } else {
                    water_string += Charmap::SPACE;
                }

                if (m.is_wall ||
                    m.is_rock ||
                    m.is_door ||
                    m.is_rock) {
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
                    monst_string += c;
                } else {
                    monst_string += Charmap::SPACE;
                }

                if (m.is_food) {
                    food_string += c;
                } else {
                    food_string += Charmap::SPACE;
                }

                if (m.is_blood) {
                    blood_string += c;
                } else {
                    blood_string += Charmap::SPACE;
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

            if (floor_string.size() != DUN_WIDTH){
                DIE("level floor width mismatch, %zu, expected %d",
                    floor_string.size(), DUN_WIDTH);
            }
            if (water_string.size() != DUN_WIDTH){
                DIE("level water width mismatch, %zu, expected %d",
                    water_string.size(), DUN_WIDTH);
            }
            if (deco_string.size() != DUN_WIDTH){
                DIE("level deco width mismatch, %zu, expected %d",
                    deco_string.size(), DUN_WIDTH);
            }
            if (deco_string.size() != DUN_WIDTH){
                DIE("level deco width mismatch, %zu, expected %d",
                    deco_string.size(), DUN_WIDTH);
            }
            if (walls_string.size() != DUN_WIDTH){
                DIE("level walls width mismatch, %zu, expected %d",
                    walls_string.size(), DUN_WIDTH);
            }
            if (exits_string.size() != DUN_WIDTH){
                DIE("level exits width mismatch, %zu, expected %d",
                    exits_string.size(), DUN_WIDTH);
            }
            if (items_string.size() != DUN_WIDTH){
                DIE("level items width mismatch, %zu, expected %d",
                    items_string.size(), DUN_WIDTH);
            }

            for (auto x = 0; x < DUN_WIDTH; x++) {
                l->data[x][y][MAP_DEPTH_FLOOR]      = floor_string[x];
                l->data[x][y][MAP_DEPTH_WATER]      = water_string[x];
                l->data[x][y][MAP_DEPTH_FLOOR_DECO] = deco_string[x];
                l->data[x][y][MAP_DEPTH_WALLS]      = walls_string[x];
                l->data[x][y][MAP_DEPTH_WALLS_DECO] = wall_deco_string[x];
                l->data[x][y][MAP_DEPTH_EXIT]       = exits_string[x];
                l->data[x][y][MAP_DEPTH_MONST]      = monst_string[x];
                l->data[x][y][MAP_DEPTH_FOOD]       = food_string[x];
                l->data[x][y][MAP_DEPTH_BLOOD]      = blood_string[x];
                l->data[x][y][MAP_DEPTH_ITEM]       = items_string[x];
                l->data[x][y][MAP_DEPTH_PLAYER]     = ' ';
            }

            if (floor_string.size() != DUN_WIDTH){
                DIE("level floor width mismatch, %zu, expected %d",
                    floor_string.size(), DUN_WIDTH);
            }
            if (water_string.size() != DUN_WIDTH){
                DIE("level water width mismatch, %zu, expected %d",
                    water_string.size(), DUN_WIDTH);
            }
            if (deco_string.size() != DUN_WIDTH){
                DIE("level deco width mismatch, %zu, expected %d",
                    deco_string.size(), DUN_WIDTH);
            }
            if (deco_string.size() != DUN_WIDTH){
                DIE("level deco width mismatch, %zu, expected %d",
                    deco_string.size(), DUN_WIDTH);
            }
            if (walls_string.size() != DUN_WIDTH){
                DIE("level walls width mismatch, %zu, expected %d",
                    walls_string.size(), DUN_WIDTH);
            }
            if (exits_string.size() != DUN_WIDTH){
                DIE("level exits width mismatch, %zu, expected %d",
                    exits_string.size(), DUN_WIDTH);
            }
            if (items_string.size() != DUN_WIDTH){
                DIE("level items width mismatch, %zu, expected %d",
                    items_string.size(), DUN_WIDTH);
            }

            for (auto x = 0; x < DUN_WIDTH; x++) {
                l->data[x][y][MAP_DEPTH_FLOOR]      = floor_string[x];
                l->data[x][y][MAP_DEPTH_WATER]      = water_string[x];
                l->data[x][y][MAP_DEPTH_FLOOR_DECO] = deco_string[x];
                l->data[x][y][MAP_DEPTH_WALLS]      = walls_string[x];
                l->data[x][y][MAP_DEPTH_WALLS_DECO] = wall_deco_string[x];
                l->data[x][y][MAP_DEPTH_EXIT]       = exits_string[x];
                l->data[x][y][MAP_DEPTH_MONST]      = monst_string[x];
                l->data[x][y][MAP_DEPTH_FOOD]       = food_string[x];
                l->data[x][y][MAP_DEPTH_BLOOD]      = blood_string[x];
                l->data[x][y][MAP_DEPTH_ITEM]       = items_string[x];
                l->data[x][y][MAP_DEPTH_PLAYER]     = ' ';
            }
        }
    }
    l->finalize();

    Py_RETURN_NONE;
}
