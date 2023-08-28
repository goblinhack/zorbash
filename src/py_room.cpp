//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_python.hpp"
#include "my_room.hpp"
#include "my_vector_bounds_check.hpp"

PyObject *map_load_room_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char     *room_name          = nullptr;
  int       xxx                = 0;
  int       yyy                = 0;
  PyObject *py_room_data       = nullptr;
  int       up                 = false;
  int       down               = false;
  int       left               = false;
  int       right              = false;
  int       is_ascend_dungeon  = false;
  int       is_descend_dungeon = false;
  int       is_lock            = false;
  int       is_key             = false;
  int       is_secret          = false;
  int       biome_dungeon      = false;
  int       biome_swamp        = false;
  int       biome_ice          = false;
  int       biome_chasms       = false;
  int       biome_lava         = false;
  int       biome_flooded      = false;
  int       depth              = 0;

  static char *kwlist[] = {(char *) "room_data",
                           (char *) "xxx",
                           (char *) "yyy",
                           (char *) "room_name",
                           (char *) "up",
                           (char *) "down",
                           (char *) "left",
                           (char *) "right",
                           (char *) "entrance",
                           (char *) "exit",
                           (char *) "lock",
                           (char *) "key",
                           (char *) "secret",
                           (char *) "biome_dungeon",
                           (char *) "biome_swamp",
                           (char *) "biome_ice",
                           (char *) "biome_chasms",
                           (char *) "biome_lava",
                           (char *) "biome_flooded",
                           (char *) "depth",
                           nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "|Oiisiiiiiiiiiiiiiiii", kwlist, &py_room_data, &xxx, &yyy,
                                    &room_name, &up, &down, &left, &right, &is_ascend_dungeon, &is_descend_dungeon,
                                    &is_lock, &is_key, &is_secret, &biome_dungeon, &biome_swamp, &biome_ice,
                                    &biome_chasms, &biome_lava, &biome_flooded, &depth)) {
    ERR("map_load_room: Bad args");
    Py_RETURN_FALSE;
  }

  if (! py_room_data) {
    ERR("Map_load_room, missing floor data");
    Py_RETURN_FALSE;
  }

  int room_data_elems = PyList_Size(py_room_data);
  if (room_data_elems % MAP_ROOM_HEIGHT) {
    ERR("Room elems needs to be evenly dividable by room height %d, got %d elems", (int) MAP_ROOM_HEIGHT,
        (int) PyList_Size(py_room_data));
    Py_RETURN_FALSE;
  }

  int rooms_across = room_data_elems / MAP_ROOM_HEIGHT;

  biome_t biome = BIOME_DUNGEON;

  if (biome_swamp) {
    biome = BIOME_SWAMP;
  }
  if (biome_ice) {
    biome = BIOME_ICE;
  }
  if (biome_chasms) {
    biome = BIOME_CHASMS;
  }
  if (biome_lava) {
    biome = BIOME_LAVA;
  }
  if (biome_flooded) {
    biome = BIOME_FLOODED;
  }

  for (auto n = 0; n < rooms_across; n++) {
    auto r = Room::room_new(biome);

    for (auto y = 0; y < MAP_ROOM_HEIGHT; y++) {
      auto o = PyList_GetItem(py_room_data, rooms_across * y + n); /* Can't fail */
      if (! o) {
        continue;
      }

      std::string floor_string;
      std::string floor2_string;
      std::string water_string;
      std::string lava_string;
      std::string chasm_string;
      std::string walls_string;
      std::string obj_strings;

      for (auto &c : py_obj_to_std_string(o)) {
        auto m = get(Charmap::all_charmaps, c);

        if (m.is_floor || m.is_bridge || m.is_corridor || m.is_secret_corridor || m.is_portal || m.is_dirt) {
          floor_string += c;
        } else if (m.is_red_blood || m.is_ascend_dungeon || m.is_barrel || m.is_brazier || m.is_deep_water
                   || m.is_descend_dungeon || m.is_door || m.is_foliage || m.is_spiderweb || m.is_block_of_ice
                   || m.is_grass_dry || m.is_grass_wet || m.is_fungus_withered || m.is_fungus_healing
                   || m.is_fungus_edible || m.is_fungus_poison || m.is_floor_deco || m.is_food || m.is_gold
                   || m.is_key || m.is_lava || m.is_mob_class_A || m.is_mob_class_B || m.is_mob_class_C
                   || m.is_monst_class_A || m.is_monst_class_B || m.is_monst_class_C || m.is_potion
                   || m.is_secret_door || m.is_shallow_water || m.is_trap || m.is_monst_class_D || m.is_monst_class_E
                   || m.is_magic_stone || m.is_weapon_class_A || m.is_weapon_class_B || m.is_weapon_class_C
                   || m.is_treasure_class_A || m.is_treasure_class_B || m.is_treasure_class_C || m.is_staff
                   || m.is_ring || m.is_deep_water) {
          floor_string += Charmap::CHAR_FLOOR;
        } else {
          floor_string += Charmap::CHAR_SPACE;
        }

        if (m.is_foliage || m.is_spiderweb || m.is_block_of_ice || m.is_grass_dry || m.is_grass_wet
            || m.is_fungus_withered || m.is_fungus_healing || m.is_fungus_edible || m.is_fungus_poison) {
          floor2_string += c;
        } else {
          floor2_string += Charmap::CHAR_SPACE;
        }

        if (m.is_shallow_water || m.is_deep_water) {
          water_string += c;
        } else {
          water_string += Charmap::CHAR_SPACE;
        }

        if (m.is_lava) {
          lava_string += c;
        } else {
          lava_string += Charmap::CHAR_SPACE;
        }

        if (m.is_chasm) {
          chasm_string += c;
        } else {
          chasm_string += Charmap::CHAR_SPACE;
        }

        if (m.is_wall || m.is_secret_door || m.is_door) {
          walls_string += c;
        } else if (m.is_descend_sewer) {
          walls_string += Charmap::CHAR_WALL;
        } else {
          walls_string += Charmap::CHAR_SPACE;
        }

        if (m.is_red_blood || m.is_ascend_dungeon || m.is_descend_dungeon || m.is_floor_deco || m.is_food
            || m.is_mob_class_A || m.is_mob_class_B || m.is_mob_class_C || m.is_gold || m.is_key || m.is_monst_class_A
            || m.is_monst_class_B || m.is_monst_class_C || m.is_monst_class_D || m.is_monst_class_E
            || m.is_magic_stone || m.is_treasure_class_A || m.is_treasure_class_B || m.is_treasure_class_C
            || m.is_weapon_class_A || m.is_weapon_class_B || m.is_weapon_class_C || m.is_potion || m.is_staff
            || m.is_ring || m.is_brazier || m.is_barrel || m.is_trap || m.is_descend_sewer) {
          obj_strings += c;
        } else {
          obj_strings += Charmap::CHAR_SPACE;
        }
      }

      if (floor_string.size() != MAP_ROOM_WIDTH) {
        DIE("Room floor width mismatch, %d, expected %d", (int) floor_string.size(), MAP_ROOM_WIDTH);
        Py_RETURN_FALSE;
      }
      if (floor2_string.size() != MAP_ROOM_WIDTH) {
        DIE("Room floor2 width mismatch, %d, expected %d", (int) floor2_string.size(), MAP_ROOM_WIDTH);
        Py_RETURN_FALSE;
      }
      if (water_string.size() != MAP_ROOM_WIDTH) {
        DIE("Room water width mismatch, %d, expected %d", (int) water_string.size(), MAP_ROOM_WIDTH);
        Py_RETURN_FALSE;
      }
      if (lava_string.size() != MAP_ROOM_WIDTH) {
        DIE("Room lava width mismatch, %d, expected %d", (int) lava_string.size(), MAP_ROOM_WIDTH);
        Py_RETURN_FALSE;
      }
      if (chasm_string.size() != MAP_ROOM_WIDTH) {
        DIE("Room chasm width mismatch, %d, expected %d", (int) chasm_string.size(), MAP_ROOM_WIDTH);
        Py_RETURN_FALSE;
      }
      if (walls_string.size() != MAP_ROOM_WIDTH) {
        DIE("Room walls width mismatch, %d, expected %d", (int) walls_string.size(), MAP_ROOM_WIDTH);
        Py_RETURN_FALSE;
      }
      if (obj_strings.size() != MAP_ROOM_WIDTH) {
        DIE("Room items width mismatch, %d, expected %d", (int) obj_strings.size(), MAP_ROOM_WIDTH);
        Py_RETURN_FALSE;
      }

      for (auto x = 0; x < MAP_ROOM_WIDTH; x++) {
        set(r->data, x, y, MAP_DEPTH_FLOOR, floor_string[ x ]);
        if (floor2_string[ x ] != ' ') {
          set(r->data, x, y, MAP_DEPTH_FLOOR2, floor2_string[ x ]);
        }
        if (water_string[ x ] != ' ') {
          set(r->data, x, y, MAP_DEPTH_LIQUID, water_string[ x ]);
        }
        if (lava_string[ x ] != ' ') {
          set(r->data, x, y, MAP_DEPTH_LIQUID, lava_string[ x ]);
        }
        if (chasm_string[ x ] != ' ') {
          set(r->data, x, y, MAP_DEPTH_CHASM, chasm_string[ x ]);
        }
        if (walls_string[ x ] != ' ') {
          set(r->data, x, y, MAP_DEPTH_OBJ, walls_string[ x ]);
        }
        if (obj_strings[ x ] != ' ') {
          set(r->data, x, y, MAP_DEPTH_OBJ, obj_strings[ x ]);
        }
      }
    }

    //////////////////////////////////////////////////////////////
    // Remember to update create_w_flip if adding new fields
    //////////////////////////////////////////////////////////////
    r->dir_up             = up != 0;
    r->dir_down           = down != 0;
    r->dir_left           = left != 0;
    r->dir_right          = right != 0;
    r->is_ascend_dungeon  = is_ascend_dungeon != 0;
    r->is_descend_dungeon = is_descend_dungeon != 0;
    r->is_lock            = is_lock != 0;
    r->is_key             = is_key != 0;
    r->is_secret          = is_secret != 0;
    r->depth              = depth;
    //////////////////////////////////////////////////////////////
    // Remember to update create_w_flip if adding new fields
    //////////////////////////////////////////////////////////////

    //
    // Sanity check the rooms
    //
    if (is_ascend_dungeon) {
      if (! r->contains(MAP_DEPTH_OBJ, Charmap::CHAR_ENTRANCE)) {
        r->con();
        DIE("Entrance room is missing dungeon entrance char '%c'", Charmap::CHAR_ENTRANCE);
      }
      if (r->contains(MAP_DEPTH_OBJ, Charmap::CHAR_EXIT)) {
        r->con();
        DIE("Exit is in entrance room");
      }
    } else if (is_descend_dungeon) {
      if (! r->contains(MAP_DEPTH_OBJ, Charmap::CHAR_EXIT)) {
        r->con();
        DIE("Exit room is missing dungeon exit char '%c'", Charmap::CHAR_EXIT);
      }
      if (r->contains(MAP_DEPTH_OBJ, Charmap::CHAR_ENTRANCE)) {
        r->con();
        DIE("Entrance is in exit room");
      }
    } else if (is_key) {
      if (! r->contains(MAP_DEPTH_OBJ, Charmap::CHAR_KEY)) {
        r->con();
        if (biome == BIOME_DUNGEON) {
          DIE("Key room is missing dungeon key char '%c'", Charmap::CHAR_KEY);
        }
        if (biome == BIOME_FLOODED) {
          DIE("Key room is missing dungeon key char '%c'", Charmap::CHAR_KEY);
        }
      }
      if (r->contains(MAP_DEPTH_OBJ, Charmap::CHAR_EXIT)) {
        r->con();
        DIE("Exit is in key room");
      }
      if (r->contains(MAP_DEPTH_OBJ, Charmap::CHAR_ENTRANCE)) {
        r->con();
        DIE("Entrance is in key room");
      }
    } else {
      if (r->contains(MAP_DEPTH_OBJ, Charmap::CHAR_EXIT)) {
        r->con();
        DIE("Exit is in normal room");
      }
      if (r->contains(MAP_DEPTH_OBJ, Charmap::CHAR_ENTRANCE)) {
        r->con();
        DIE("Entrance is in normal room");
      }
    }

    r->finalize();

    //
    // Check doors can all reach each other.
    //
    r->room_check_doors_can_reach_each_other();

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
