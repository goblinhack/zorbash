//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_python.hpp"
#include "my_vector_bounds_check.hpp"

PyObject *map_load_skill_tree_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();

  if (! game) {
    DIE("map_load_skill_tree: no game object");
  }

  PyObject   *py_skill_data = nullptr;
  PyObject   *py_tree_data  = nullptr;
  const char *py_tree_name;

  static char *kwlist[] = {(char *) "skill_data", (char *) "tree_data", (char *) "tree_name", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "|OOs", kwlist, &py_skill_data, &py_tree_data, &py_tree_name)) {
    DIE("map_load_skill_tree: Bad args");
    Py_RETURN_FALSE;
  }

  std::string tree_name;
  if (py_tree_name) {
    tree_name = std::string(py_tree_name);
  }

  //
  // First read all the skill aliases
  //
  if (py_skill_data) {
    TRACE_NO_INDENT();
    for (auto y = 0; y < PyList_Size(py_skill_data) / 2; y++) {
      auto alias_o = PyList_GetItem(py_skill_data, y * 2); /* Can't fail */
      if (! alias_o) {
        continue;
      }

      auto name_o = PyList_GetItem(py_skill_data, y * 2 + 1); /* Can't fail */
      if (! name_o) {
        continue;
      }

      auto alias = py_obj_to_std_string(alias_o);
      auto name  = py_obj_to_std_string(name_o);

      game->skill_aliases[ alias ] = name;
    }
  }

  if (py_tree_data) {
    TRACE_NO_INDENT();
    int tree_data_down = PyList_Size(py_tree_data);
    if (tree_data_down != SKILL_TREE_DOWN * 2) {
      DIE("map_load_skill_tree: expected %u string elems, got %u", SKILL_TREE_DOWN * 2, (int) tree_data_down);
      Py_RETURN_FALSE;
    }

    //
    // Now read the skill tree but ignore the connections between skills for now.
    //
    TRACE_NO_INDENT();
    for (auto y = 0; y < SKILL_TREE_DOWN; y++) {
      auto o = PyList_GetItem(py_tree_data, y * 2); /* Can't fail */
      if (! o) {
        continue;
      }

      auto s = py_obj_to_std_string(o);
      if (s.size() != SKILL_TREE_ACROSS * 4) {
        DIE("map_load_skill_tree: expected %u chars, got %u in %s", SKILL_TREE_ACROSS * 4, (int) s.size(), s.c_str());
        Py_RETURN_FALSE;
      }

      for (auto x = 0; x < SKILL_TREE_ACROSS; x++) {
        char a = s[ x * 4 ];
        char b = s[ x * 4 + 1 ];

        std::string skill_alias;
        skill_alias += a;
        skill_alias += b;

        if (skill_alias != "  ") {
          auto skill         = new Skill();
          skill->skill_alias = skill_alias;
          LOG("New skil %s", skill_alias.c_str());
          TRACE_NO_INDENT();
          set(game->skill_tree[ tree_name ], x, y, skill);
        }
      }
    }

    //
    // Now read the skill tree connectors
    //
    TRACE_NO_INDENT();
    for (auto y = 0; y < SKILL_TREE_DOWN * 2; y++) {
      auto o = PyList_GetItem(py_tree_data, y); /* Can't fail */
      if (! o) {
        continue;
      }

      auto s = py_obj_to_std_string(o);

      for (auto x = 0; x < SKILL_TREE_ACROSS * 4; x++) {
        char a = s[ x ];
        char b = s[ x + 1 ];

        std::string connector_string;
        connector_string += a;
        connector_string += b;

        auto skill_x = x / 4;
        auto skill_y = y / 2;

        if (connector_string == "<-") {
          TRACE_NO_INDENT();
          auto skill_src = get(game->skill_tree[ tree_name ], skill_x + 1, skill_y);
          if (! skill_src) {
            DIE("Have <- connector at %u,%u, but no corresponding source skill index %u, %u", x, y, skill_x + 1,
                skill_y);
          }

          TRACE_NO_INDENT();
          auto skill_dst = get(game->skill_tree[ tree_name ], skill_x, skill_y);
          if (! skill_dst) {
            DIE("Have <- connector at %u,%u, but no corresponding dest skill index %u, %u", x, y, skill_x, skill_y);
          }

          skill_src->skill_left = skill_dst;
        }

        if (connector_string == "->") {
          TRACE_NO_INDENT();
          auto skill_src = get(game->skill_tree[ tree_name ], skill_x, skill_y);
          if (! skill_src) {
            DIE("Have -> connector at %u,%u, but no corresponding source skill index %u, %u", x, y, skill_x, skill_y);
          }

          TRACE_NO_INDENT();
          auto skill_dst = get(game->skill_tree[ tree_name ], skill_x + 1, skill_y);
          if (! skill_dst) {
            DIE("Have -> connector at %u,%u, but no corresponding dest skill index %u, %u", x, y, skill_x + 1,
                skill_y);
          }

          skill_src->skill_right = skill_dst;
        }

        if (connector_string == "v ") {
          TRACE_NO_INDENT();
          auto skill_src = get(game->skill_tree[ tree_name ], skill_x, skill_y);
          if (! skill_src) {
            DIE("Have down connector at %u,%u, but no corresponding source skill index %u, %u", x, y, skill_x,
                skill_y);
          }

          TRACE_NO_INDENT();
          auto skill_dst = get(game->skill_tree[ tree_name ], skill_x, skill_y + 1);
          if (! skill_dst) {
            DIE("Have down connector at %u,%u, but no corresponding dest skill index %u, %u", x, y, skill_x,
                skill_y + 1);
          }

          skill_src->skill_down = skill_dst;
        }

        if (connector_string == "^ ") {
          TRACE_NO_INDENT();
          auto skill_src = get(game->skill_tree[ tree_name ], skill_x, skill_y + 1);
          if (! skill_src) {
            DIE("Have up connector at %u,%u, but no corresponding source skill index %u, %u", x, y, skill_x,
                skill_y + 1);
          }

          TRACE_NO_INDENT();
          auto skill_dst = get(game->skill_tree[ tree_name ], skill_x, skill_y);
          if (! skill_dst) {
            DIE("Have up connector at %u,%u, but no corresponding dest skill index %u, %u", x, y, skill_x, skill_y);
          }

          skill_src->skill_up = skill_dst;
        }
      }
    }

    std::array< std::array< char, SKILL_TREE_DOWN * 2 >, SKILL_TREE_ACROSS * 4 > skill_tree_debug {};

    TRACE_NO_INDENT();
    for (auto y = 0; y < SKILL_TREE_DOWN; y++) {
      for (auto x = 0; x < SKILL_TREE_ACROSS; x++) {
        TRACE_NO_INDENT();
        auto skill = get(game->skill_tree[ tree_name ], x, y);
        if (! skill) {
          continue;
        }

        TRACE_NO_INDENT();
        set(skill_tree_debug, x * 4, y * 2, skill->skill_alias[ 0 ]);
        TRACE_NO_INDENT();
        set(skill_tree_debug, x * 4 + 1, y * 2, skill->skill_alias[ 1 ]);

        TRACE_NO_INDENT();
        if (skill->skill_right) {
          Skillp skill_right = get(game->skill_tree[ tree_name ], x + 1, y);
          if (skill_right) {
            TRACE_NO_INDENT();
            set(skill_tree_debug, x * 4 + 2, y * 2, '-');
            TRACE_NO_INDENT();
            set(skill_tree_debug, x * 4 + 3, y * 2, '>');
          }
        }

        TRACE_NO_INDENT();
        if (skill->skill_left) {
          Skillp skill_left = get(game->skill_tree[ tree_name ], x - 1, y);
          if (skill_left) {
            TRACE_NO_INDENT();
            set(skill_tree_debug, x * 4 - 1, y * 2, '-');
            TRACE_NO_INDENT();
            set(skill_tree_debug, x * 4 - 2, y * 2, '<');
          }
        }

        TRACE_NO_INDENT();
        if (skill->skill_down) {
          Skillp skill_down = get(game->skill_tree[ tree_name ], x, y + 1);
          if (skill_down) {
            TRACE_NO_INDENT();
            set(skill_tree_debug, x * 4, y * 2 + 1, 'v');
          }
        }

        TRACE_NO_INDENT();
        if (skill->skill_up) {
          Skillp skill_up = get(game->skill_tree[ tree_name ], x, y - 1);
          if (skill_up) {
            TRACE_NO_INDENT();
            set(skill_tree_debug, x * 4, y * 2 - 1, '^');
          }
        }
      }
    }

    TRACE_NO_INDENT();
    for (auto y = 0; y < SKILL_TREE_DOWN * 2; y++) {
      std::string out;
      TRACE_NO_INDENT();
      for (auto x = 0; x < SKILL_TREE_ACROSS * 4; x++) {
        TRACE_NO_INDENT();
        auto c = get(skill_tree_debug, x, y);
        if (c) {
          out += c;
        } else {
          out += ' ';
        }
      }
      LOG("SKILL TREE: %s", out.c_str());
    }
  }

  Py_RETURN_TRUE;
}
