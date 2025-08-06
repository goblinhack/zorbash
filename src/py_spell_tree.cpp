//
// Copyright goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_python.hpp"
#include "my_vector_bounds_check.hpp"

PyObject *map_load_spell_tree_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();

  if (! game) {
    DIE("map_load_spell_tree: no game object");
  }

  PyObject   *py_spell_data = nullptr;
  PyObject   *py_tree_data  = nullptr;
  const char *py_tree_name  = nullptr;

  static char *kwlist[] = {(char *) "spell_data", (char *) "tree_data", (char *) "tree_name", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "|OOs", kwlist, &py_spell_data, &py_tree_data, &py_tree_name)) {
    DIE("map_load_spell_tree: Bad args");
    Py_RETURN_FALSE;
  }

  std::string tree_name;
  if (py_tree_name) {
    tree_name = std::string(py_tree_name);
  }

  //
  // First read all the spell aliases
  //
  if (py_spell_data) {
    TRACE_NO_INDENT();
    for (auto y = 0; y < PyList_Size(py_spell_data) / 2; y++) {
      auto alias_o = PyList_GetItem(py_spell_data, y * 2); /* Can't fail */
      if (! alias_o) {
        continue;
      }

      auto name_o = PyList_GetItem(py_spell_data, y * 2 + 1); /* Can't fail */
      if (! name_o) {
        continue;
      }

      auto alias = py_obj_to_std_string(alias_o);
      auto name  = py_obj_to_std_string(name_o);

      game->spell_aliases[ alias ] = name;
    }
  }

  if (py_tree_data) {
    TRACE_NO_INDENT();
    int tree_data_down = PyList_Size(py_tree_data);
    if (tree_data_down != SPELL_TREE_DOWN * 2) {
      DIE("map_load_spell_tree: expected %u string elems, got %u", SPELL_TREE_DOWN * 2, (int) tree_data_down);
      Py_RETURN_FALSE;
    }

    //
    // Now read the spell tree but ignore the connections between spells for now.
    //
    TRACE_NO_INDENT();
    for (auto y = 0; y < SPELL_TREE_DOWN; y++) {
      auto o = PyList_GetItem(py_tree_data, y * 2); /* Can't fail */
      if (! o) {
        continue;
      }

      auto s = py_obj_to_std_string(o);
      if (s.size() != SPELL_TREE_ACROSS * 4) {
        DIE("map_load_spell_tree: expected %u chars, got %u in %s", SPELL_TREE_ACROSS * 4, (int) s.size(), s.c_str());
        Py_RETURN_FALSE;
      }

      for (auto x = 0; x < SPELL_TREE_ACROSS; x++) {
        char a = s[ x * 4 ];
        char b = s[ x * 4 + 1 ];

        std::string spell_alias;
        spell_alias += a;
        spell_alias += b;

        if (spell_alias != "  ") {
          auto spell         = new Spell();
          spell->spell_alias = spell_alias;
          DBG("New spell %s", spell_alias.c_str());
          TRACE_NO_INDENT();
          set(game->spell_tree[ tree_name ], x, y, spell);
        }
      }
    }

    //
    // Now read the spell tree connectors
    //
    TRACE_NO_INDENT();
    for (auto y = 0; y < SPELL_TREE_DOWN * 2; y++) {
      auto o = PyList_GetItem(py_tree_data, y); /* Can't fail */
      if (! o) {
        continue;
      }

      auto s = py_obj_to_std_string(o);

      for (auto x = 0; x < SPELL_TREE_ACROSS * 4; x++) {
        char a = s[ x ];
        char b = s[ x + 1 ];

        std::string connector_string;
        connector_string += a;
        connector_string += b;

        auto spell_x = x / 4;
        auto spell_y = y / 2;

        if (connector_string == "<-") {
          TRACE_NO_INDENT();
          auto spell_src = get(game->spell_tree[ tree_name ], spell_x + 1, spell_y);
          if (! spell_src) {
            DIE("Have <- connector at %u,%u, but no corresponding source spell index %u, %u", x, y, spell_x + 1,
                spell_y);
          }

          TRACE_NO_INDENT();
          auto spell_dst = get(game->spell_tree[ tree_name ], spell_x, spell_y);
          if (! spell_dst) {
            DIE("Have <- connector at %u,%u, but no corresponding dest spell index %u, %u", x, y, spell_x, spell_y);
          }

          spell_src->spell_left = spell_dst;
        }

        if (connector_string == "->") {
          TRACE_NO_INDENT();
          auto spell_src = get(game->spell_tree[ tree_name ], spell_x, spell_y);
          if (! spell_src) {
            DIE("Have -> connector at %u,%u, but no corresponding source spell index %u, %u", x, y, spell_x, spell_y);
          }

          TRACE_NO_INDENT();
          auto spell_dst = get(game->spell_tree[ tree_name ], spell_x + 1, spell_y);
          if (! spell_dst) {
            DIE("Have -> connector at %u,%u, but no corresponding dest spell index %u, %u", x, y, spell_x + 1,
                spell_y);
          }

          spell_src->spell_right = spell_dst;
        }

        if (connector_string == "v ") {
          TRACE_NO_INDENT();
          auto spell_src = get(game->spell_tree[ tree_name ], spell_x, spell_y);
          if (! spell_src) {
            DIE("Have down connector at %u,%u, but no corresponding source spell index %u, %u", x, y, spell_x,
                spell_y);
          }

          TRACE_NO_INDENT();
          auto spell_dst = get(game->spell_tree[ tree_name ], spell_x, spell_y + 1);
          if (! spell_dst) {
            DIE("Have down connector at %u,%u, but no corresponding dest spell index %u, %u", x, y, spell_x,
                spell_y + 1);
          }

          spell_src->spell_down = spell_dst;
        }

        if (connector_string == "^ ") {
          TRACE_NO_INDENT();
          auto spell_src = get(game->spell_tree[ tree_name ], spell_x, spell_y + 1);
          if (! spell_src) {
            DIE("Have up connector at %u,%u, but no corresponding source spell index %u, %u", x, y, spell_x,
                spell_y + 1);
          }

          TRACE_NO_INDENT();
          auto spell_dst = get(game->spell_tree[ tree_name ], spell_x, spell_y);
          if (! spell_dst) {
            DIE("Have up connector at %u,%u, but no corresponding dest spell index %u, %u", x, y, spell_x, spell_y);
          }

          spell_src->spell_up = spell_dst;
        }
      }
    }

    std::array< std::array< char, SPELL_TREE_DOWN * 2 >, SPELL_TREE_ACROSS * 4 > spell_tree_debug {};

    TRACE_NO_INDENT();
    for (auto y = 0; y < SPELL_TREE_DOWN; y++) {
      for (auto x = 0; x < SPELL_TREE_ACROSS; x++) {
        TRACE_NO_INDENT();
        auto spell = get(game->spell_tree[ tree_name ], x, y);
        if (! spell) {
          continue;
        }

        TRACE_NO_INDENT();
        set(spell_tree_debug, x * 4, y * 2, spell->spell_alias[ 0 ]);
        TRACE_NO_INDENT();
        set(spell_tree_debug, x * 4 + 1, y * 2, spell->spell_alias[ 1 ]);

        TRACE_NO_INDENT();
        if (spell->spell_right) {
          Spellp spell_right = get(game->spell_tree[ tree_name ], x + 1, y);
          if (spell_right) {
            TRACE_NO_INDENT();
            set(spell_tree_debug, x * 4 + 2, y * 2, '-');
            TRACE_NO_INDENT();
            set(spell_tree_debug, x * 4 + 3, y * 2, '>');
          }
        }

        TRACE_NO_INDENT();
        if (spell->spell_left) {
          Spellp spell_left = get(game->spell_tree[ tree_name ], x - 1, y);
          if (spell_left) {
            TRACE_NO_INDENT();
            set(spell_tree_debug, x * 4 - 1, y * 2, '-');
            TRACE_NO_INDENT();
            set(spell_tree_debug, x * 4 - 2, y * 2, '<');
          }
        }

        TRACE_NO_INDENT();
        if (spell->spell_down) {
          Spellp spell_down = get(game->spell_tree[ tree_name ], x, y + 1);
          if (spell_down) {
            TRACE_NO_INDENT();
            set(spell_tree_debug, x * 4, y * 2 + 1, 'v');
          }
        }

        TRACE_NO_INDENT();
        if (spell->spell_up) {
          Spellp spell_up = get(game->spell_tree[ tree_name ], x, y - 1);
          if (spell_up) {
            TRACE_NO_INDENT();
            set(spell_tree_debug, x * 4, y * 2 - 1, '^');
          }
        }
      }
    }

    TRACE_NO_INDENT();
    for (auto y = 0; y < SPELL_TREE_DOWN * 2; y++) {
      std::string out;
      TRACE_NO_INDENT();
      for (auto x = 0; x < SPELL_TREE_ACROSS * 4; x++) {
        TRACE_NO_INDENT();
        auto c = get(spell_tree_debug, x, y);
        if (c) {
          out += c;
        } else {
          out += ' ';
        }
      }
      DBG("SPELL TREE: %s", out.c_str());
    }
  }

  Py_RETURN_TRUE;
}
