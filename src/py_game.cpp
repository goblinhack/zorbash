//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_charmap.hpp"
#include "my_game.hpp"
#include "my_level_static.hpp"
#include "my_python.hpp"
#include "my_thing.hpp"
#include "my_vector_bounds_check.hpp"

#define GAME_VOID_FUNC(__func__, __api__)                                                                            \
  PyObject *__func__(PyObject * obj, PyObject * args, PyObject * keywds)                                             \
  {                                                                                                                  \
    TRACE_AND_INDENT();                                                                                              \
    static char *kwlist[] = {0};                                                                                     \
                                                                                                                     \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "", kwlist)) {                                                   \
      ERR("%s: Failed parsing keywords", __FUNCTION__);                                                              \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    if (! game) {                                                                                                    \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    game->__api__();                                                                                                 \
                                                                                                                     \
    Py_RETURN_TRUE;                                                                                                  \
  }

// begin sort marker1 {
GAME_VOID_FUNC(game_set_request_reset_state_change, set_request_reset_state_change);
GAME_VOID_FUNC(game_set_request_to_remake_rightbar, set_request_to_remake_rightbar);
GAME_VOID_FUNC(game_set_request_to_remake_inventory, set_request_to_remake_inventory);
GAME_VOID_FUNC(game_set_request_to_remake_actionbar, set_request_to_remake_actionbar);
GAME_VOID_FUNC(game_set_request_to_remake_skillbox, set_request_to_remake_skillbox);
GAME_VOID_FUNC(game_set_request_to_remake_spellbox, set_request_to_remake_spellbox);
GAME_VOID_FUNC(game_set_request_to_remake_debuffbox, set_request_to_remake_debuffbox);
GAME_VOID_FUNC(game_set_request_to_remake_buffbox, set_request_to_remake_buffbox);
GAME_VOID_FUNC(game_set_request_to_update_same_level, set_request_to_update_same_level);
GAME_VOID_FUNC(game_set_request_to_save_snapshot, set_request_to_save_snapshot);
GAME_VOID_FUNC(game_set_currently_saving_snapshot, set_currently_saving_snapshot);
GAME_VOID_FUNC(game_set_request_to_update_inventory_thing_over, set_request_to_update_inventory_thing_over);
GAME_VOID_FUNC(game_set_request_to_update_inventory_thing_select, set_request_to_update_inventory_thing_select);
GAME_VOID_FUNC(game_unset_request_reset_state_change, unset_request_reset_state_change);
GAME_VOID_FUNC(game_unset_request_to_remake_rightbar, unset_request_to_remake_rightbar);
GAME_VOID_FUNC(game_unset_request_to_remake_inventory, unset_request_to_remake_inventory);
GAME_VOID_FUNC(game_unset_request_to_remake_actionbar, unset_request_to_remake_actionbar);
GAME_VOID_FUNC(game_unset_request_to_remake_skillbox, unset_request_to_remake_skillbox);
GAME_VOID_FUNC(game_unset_request_to_remake_spellbox, unset_request_to_remake_spellbox);
GAME_VOID_FUNC(game_unset_request_to_remake_debuffbox, unset_request_to_remake_debuffbox);
GAME_VOID_FUNC(game_unset_request_to_remake_buffbox, unset_request_to_remake_buffbox);
GAME_VOID_FUNC(game_unset_request_to_update_same_level, unset_request_to_update_same_level);
GAME_VOID_FUNC(game_unset_request_to_save_snapshot, unset_request_to_save_snapshot);
GAME_VOID_FUNC(game_unset_currently_saving_snapshot, unset_currently_saving_snapshot);
GAME_VOID_FUNC(game_unset_request_to_update_inventory_thing_over, unset_request_to_update_inventory_thing_over);
GAME_VOID_FUNC(game_unset_request_to_update_inventory_thing_select, unset_request_to_update_inventory_thing_select);
// end sort marker1 }
