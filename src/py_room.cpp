//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_python.h"
#include "my_room.h"
#include "my_array_bounds_check.h"
#include "my_vector_bounds_check.h"

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
    int is_ascend_dungeon = false;
    int is_descend_dungeon = false;
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
                                     &is_ascend_dungeon,
                                     &is_descend_dungeon,
                                     &is_lock,
                                     &is_key,
                                     &is_secret,
                                     &is_depth)) {
        ERR("map_load_room: bad args");
        Py_RETURN_FALSE;
    }

    if (!py_room_data) {
        ERR("Map_load_room, missing floor data");
        Py_RETURN_FALSE;
    }

    int room_data_elems = PyList_Size(py_room_data);
    if (room_data_elems % MAP_ROOM_HEIGHT) {
        ERR("Room elems needs to be evenly dividable by room height %d, got %d elems",
            (int) MAP_ROOM_HEIGHT, (int) PyList_Size(py_room_data));
        Py_RETURN_FALSE;
    }

    int rooms_across = room_data_elems / MAP_ROOM_HEIGHT;

    for (auto n=0; n < rooms_across; n++) {
        auto r = Room::room_new();

        for (auto y=0; y<MAP_ROOM_HEIGHT; y++) {
            auto o = PyList_GetItem(py_room_data,
                                    rooms_across * y + n); /* Can't fail */
            if (!o) {
                continue;
            }

            std::string floor_string;
            std::string water_string;
            std::string lava_string;
            std::string chasm_string;
            std::string walls_string;
            std::string obj_strings;

            for (auto& c : py_obj_to_string(o)) {
                auto m = get(Charmap::all_charmaps, c);

                if (m.is_floor ||
                    m.is_secret_corridor ||
                    m.is_dirt) {
                    floor_string += c;
                } else if (m.is_blood            ||
                           m.is_deep_water       ||
                           m.is_door             ||
                           m.is_ascend_dungeon   ||
                           m.is_descend_dungeon  ||
                           m.is_floor_deco       ||
                           m.is_food             ||
                           m.is_minion_generator ||
                           m.is_gold             ||
                           m.is_key              ||
                           m.is_lava             ||
                           m.is_monst            ||
                           m.is_treasure_class_a ||
                           m.is_treasure_class_b ||
                           m.is_treasure_class_c ||
                           m.is_potion           ||
                           m.is_secret_door      ||
                           m.is_torch            ||
                           m.is_trap             ||
                           m.is_shallow_water    ||
                           m.is_deep_water      
                           ) {
                    floor_string += Charmap::FLOOR;
                } else {
                    floor_string += Charmap::SPACE;
                }

                if (m.is_shallow_water || m.is_deep_water) {
                    water_string += c;
                } else {
                    water_string += Charmap::SPACE;
                }

                if (m.is_lava) {
                    lava_string += c;
                } else {
                    lava_string += Charmap::SPACE;
                }

                if (m.is_chasm) {
                    chasm_string += c;
                } else {
                    chasm_string += Charmap::SPACE;
                }

                if (m.is_wall ||
                    m.is_secret_door ||
                    m.is_door) {
                    walls_string += c;
                } else if (m.is_descend_sewer) {
                    walls_string += Charmap::WALL;
                } else {
                    walls_string += Charmap::SPACE;
                }

                if (m.is_blood            ||
                    m.is_ascend_dungeon   ||
                    m.is_descend_dungeon  ||
                    m.is_floor_deco       ||
                    m.is_food             ||
                    m.is_minion_generator ||
                    m.is_gold             ||
                    m.is_key              ||
                    m.is_monst            ||
                    m.is_treasure_class_a ||
                    m.is_treasure_class_b ||
                    m.is_treasure_class_c ||
                    m.is_potion           ||
                    m.is_torch            ||
                    m.is_trap             ||
                    m.is_descend_sewer) {
                    obj_strings += c;
                } else {
                    obj_strings += Charmap::SPACE;
                }
            }

            if (floor_string.size() != MAP_ROOM_WIDTH){
                ERR("Room floor width mismatch, %d, expected %d",
                    (int)floor_string.size(), MAP_ROOM_WIDTH);
                Py_RETURN_FALSE;
            }
            if (water_string.size() != MAP_ROOM_WIDTH){
                ERR("Room water width mismatch, %d, expected %d",
                    (int)water_string.size(), MAP_ROOM_WIDTH);
                Py_RETURN_FALSE;
            }
            if (lava_string.size() != MAP_ROOM_WIDTH){
                ERR("Room lava width mismatch, %d, expected %d",
                    (int)lava_string.size(), MAP_ROOM_WIDTH);
                Py_RETURN_FALSE;
            }
            if (chasm_string.size() != MAP_ROOM_WIDTH){
                ERR("Room chasm width mismatch, %d, expected %d",
                    (int)chasm_string.size(), MAP_ROOM_WIDTH);
                Py_RETURN_FALSE;
            }
            if (walls_string.size() != MAP_ROOM_WIDTH){
                ERR("Room walls width mismatch, %d, expected %d",
                    (int)walls_string.size(), MAP_ROOM_WIDTH);
                Py_RETURN_FALSE;
            }
            if (obj_strings.size() != MAP_ROOM_WIDTH){
                ERR("Room items width mismatch, %d, expected %d",
                    (int)obj_strings.size(), MAP_ROOM_WIDTH);
                Py_RETURN_FALSE;
            }

            for (auto x = 0; x < MAP_ROOM_WIDTH; x++) {
                set(r->data, x, y, MAP_DEPTH_FLOOR,     floor_string[x]);
                if (water_string[x] != ' ') {
                    set(r->data, x, y, MAP_DEPTH_WATER, water_string[x]);
                }
                if (lava_string[x] != ' ') {
                    set(r->data, x, y, MAP_DEPTH_LAVA,  lava_string[x]);
                }
                if (chasm_string[x] != ' ') {
                    set(r->data, x, y, MAP_DEPTH_CHASM, chasm_string[x]);
                }
                if (walls_string[x] != ' ') {
                    set(r->data, x, y, MAP_DEPTH_OBJ,   walls_string[x]);
                }
                if (obj_strings[x] != ' ') {
                    set(r->data, x, y, MAP_DEPTH_OBJ,   obj_strings[x]);
                }
            }
        }

        // remember to update create_h_flip
        r->dir_up      = up ? true : false;
        r->dir_down    = down ? true : false;
        r->dir_left    = left ? true : false;
        r->dir_right   = right ? true : false;
        r->is_ascend_dungeon = is_ascend_dungeon ? true : false;
        r->is_descend_dungeon     = is_descend_dungeon ? true : false;
        r->is_lock     = is_lock ? true : false;
        r->is_key      = is_key ? true : false;
        r->is_secret   = is_secret ? true : false;
        r->depth       = is_depth;
        // remember to update create_h_flip

        r->finalize();

        r = r->rotate_clockwise();
        r = r->rotate_clockwise();
        r = r->rotate_clockwise();
        r = r->create_w_flip();
        r = r->rotate_clockwise();
        r = r->rotate_clockwise();
        r = r->rotate_clockwise();
    }

    Py_RETURN_TRUE;
}
